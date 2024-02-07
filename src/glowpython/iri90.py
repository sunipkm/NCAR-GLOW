from __future__ import annotations
from os import path
from typing import List, SupportsFloat as Numeric, NamedTuple, Tuple

import numpy as np
from xarray import Dataset, Variable

from .fortran import iri90 as fort_iri90  # pylint: disable=import-error # type: ignore
from .utils import glowdate, glowstl, geomagidx
from .dirsetup import IRI90_DIR


def iri90(idate: int, stl: Numeric, lat: Numeric, lon: Numeric, f107a: Numeric, alt_km: np.ndarray, *, data_dir: str = IRI90_DIR, flags: Tuple[int] = (1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1), jmag: int = 0)->Dataset:
    """Calculate the IRI90 model for a given date, time, and location.

    Args:
        idate (int): Date in yyddd or yyyyddd format. Currently ignores the year.
        stl (Numeric): Local solar time, hours.
        lat (Numeric): Geographic Latitude in Deg.
        lon (Numeric): Geographic Longitude in Deg.
        f107a (Numeric): 12-months running mean of F10.7 index, or negative of the mean Solar Sunspot Number.
        alt_km (np.ndarray): Altitude grid in km. Must be in Fortran order.
        data_dir (str, optional): IRI90 URSI/CCIR data files directory. Defaults to `IRI90_DIR`.
        flags (Tuple[bool], optional): True/False flags for options. Defaults to (1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1).
           - `[0]` -> Electron density is (not) calculated.
           - `[1]` -> Temperatures are (not) calculated.
           - `[2]` -> Ion composition is (not) calculated.
           - `[3]` -> B0 from table (Gulyava, 1987) is (not) used.
           - `[4]` -> F2 peak from CCIR (from URSI).
           - `[5]` -> Ion composition standard (or Danilov-Yaichnikov, 1985).
           - `[6]` -> Standard IRI topside (IRI-79).
           - `[7]` -> nmF2 peak model (or input values).
           - `[8]` -> hoF2 peak model (or input values).
           - `[9]` -> Te model (Te-Ne model with Ne input).
           - `[10]` -> Ne standard (Lay-functions version) model.
           - `[11]` -> Direct output messages to `/dev/null` (`stderr`).
        jmag (int, optional): _description_. Defaults to 0.

    Returns:
        Dataset: Dataset containing densities and temperatures of the ionosphere, along with metadata.
    """
    assert (alt_km.flags.f_contiguous)
    jf = np.asfortranarray(np.asarray(flags, dtype=bool))
    assert (jf.flags.f_contiguous)
    assert (len(jf) == 12)
    assert (path.exists(data_dir) and path.isdir(data_dir))
    rz12 = -f107a
    mmdd = idate
    mmdd = mmdd % 1000  # IRI90 only uses the day of the year
    mmdd = -mmdd
    lon %= 360

    # Allocate space for the output
    outf = np.zeros((11, len(alt_km)), dtype=np.float32, order='F')
    oarr = np.zeros(30, dtype=np.float32, order='F')

    fort_iri90(jf, jmag, lat, lon, rz12, mmdd, stl, alt_km, data_dir, outf, oarr)

    outf[0, :] *= 1e-6  # Convert from m^-3 to cm^-3

    data_vars = {
            'Ne': Variable(('alt_km',), outf[0, :], attrs={'units': 'cm^{-3}', 'long_name': 'Electron Density'}),
            'Tn': Variable(('alt_km',), outf[1, :], attrs={'units': 'K', 'long_name': 'Neutral Temperature'}),
            'Ti': Variable(('alt_km',), outf[2, :], attrs={'units': 'K', 'long_name': 'Ion Temperature'}),
            'Te': Variable(('alt_km',), outf[3, :], attrs={'units': 'K', 'long_name': 'Electron Temperature'}),
            'O+': Variable(('alt_km',), outf[4, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'O^+ density'}),
            'H+': Variable(('alt_km',), outf[5, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'H^+ density'}),
            'He+': Variable(('alt_km',), outf[6, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'He^+ density'}),
            'O2+': Variable(('alt_km',), outf[7, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'O_2^+ density'}),
            'NO+': Variable(('alt_km',), outf[8, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'NO^+ density'}),
        }

    if jf[5] == 0:
        data_vars['ClusterIons'] = Variable(('alt_km',), outf[9, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'Cluster Ion density'})
        data_vars['AnomalousO'] = Variable(('alt_km',), outf[10, :]*outf[0, :]*0.01, attrs={'units': 'cm^{-3}', 'long_name': 'Anomalous O density'}),
    else:
        data_vars['ClusterIons'] = Variable(('alt_km',), np.full_like(outf[0, :], np.nan), attrs={'units': 'cm^{-3}', 'long_name': 'Cluster Ion density'})
        data_vars['AnomalousO'] = Variable(('alt_km',), np.full_like(outf[0, :], np.nan), attrs={'units': 'cm^{-3}', 'long_name': 'Anomalous O density'})

    ds = Dataset(
        data_vars=data_vars,
        coords={'alt_km': ('alt_km', alt_km, {'standard_name': 'altitude', 'units': 'km', 'long_name': 'Altitude'})},
    )

    ds.attrs['iri90_flags'] = jf
    ds.attrs['iri90_jmag'] = jmag
    ds.attrs['glat'] = lat
    ds.attrs['glon'] = lon
    ds.attrs['f107a'] = f107a
    ds.attrs['stl'] = stl
    ds.attrs['idate'] = idate
    ds.attrs['nmF2'] = {'value': oarr[0]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Maximum electron density at F2 layer'}
    ds.attrs['hmF2'] = {'value': oarr[1], 'units': 'km', 'long_name': 'Height of maximum electron density at F2 layer'}
    ds.attrs['nmF1'] = {'value': oarr[2]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Maximum electron density at F1 layer'}
    ds.attrs['hmF1'] = {'value': oarr[3], 'units': 'km', 'long_name': 'Height of maximum electron density at F1 layer'}
    ds.attrs['nmE'] = {'value': oarr[4]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Maximum electron density at E layer'}
    ds.attrs['hmE'] = {'value': oarr[5], 'units': 'km', 'long_name': 'Height of maximum electron density at E layer'}
    ds.attrs['nmD'] = {'value': oarr[6]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Maximum electron density at D layer'}
    ds.attrs['hmD'] = {'value': oarr[7], 'units': 'km', 'long_name': 'Height of maximum electron density at D layer'}
    ds.attrs['hhalf'] = {'value': oarr[8], 'units': 'km', 'long_name': 'Half thickness of F2 layer'}
    ds.attrs['B0'] = {'value': oarr[9], 'units': 'km', 'long_name': 'IRI thickness parameter'}
    ds.attrs['den_valley_base'] = {'value': oarr[10]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Density at the base of the ionosphere'}
    ds.attrs['den_valley_top'] = {'value': oarr[11]*1e-6, 'units': 'cm^{-3}', 'long_name': 'Density at the top of the ionosphere'}
    ds.attrs['Te_peak'] = {'value': oarr[12], 'units': 'K', 'long_name': 'Peak electron temperature'}
    ds.attrs['Te_peak_alt'] = {'value': oarr[13], 'units': 'km', 'long_name': 'Altitude of peak electron temperature'}
    ds.attrs['Te_300'] = {'value': oarr[14], 'units': 'K', 'long_name': 'Electron temperature at 300 km'}
    ds.attrs['Te_400'] = {'value': oarr[15], 'units': 'K', 'long_name': 'Electron temperature at 400 km'}
    ds.attrs['Te_600'] = {'value': oarr[16], 'units': 'K', 'long_name': 'Electron temperature at 600 km'}
    ds.attrs['Te_1400'] = {'value': oarr[17], 'units': 'K', 'long_name': 'Electron temperature at 1400 km'}
    ds.attrs['Te_3000'] = {'value': oarr[18], 'units': 'K', 'long_name': 'Electron temperature at 3000 km'}
    ds.attrs['Te_120'] = {'value': oarr[19], 'units': 'K', 'long_name': 'Electron/Ion/Neutral temperature at 120 km'}
    ds.attrs['Ti_430'] = {'value': oarr[20], 'units': 'K', 'long_name': 'Ion temperature at 430 km'}
    ds.attrs['Te_Ti'] = {'value': oarr[21], 'units': 'km', 'long_name': 'Altitude where T_e == T_i'}
    ds.attrs['SZA'] = {'value': oarr[22], 'units': 'deg', 'long_name': 'Solar Zenith Angle'}
    ds.attrs['SolDec'] = {'value': oarr[23], 'units': 'dec', 'long_name': 'Sun Declination'}
    ds.attrs['dip'] = {'value': oarr[24], 'units': 'deg', 'long_name': 'Geomagnetic Dip'}
    ds.attrs['dip_lat'] = {'value': oarr[25], 'units': 'deg', 'long_name': 'Dip Latitude'}
    ds.attrs['dip_mlat'] = {'value': oarr[26], 'units': 'deg', 'long_name': 'Modified Dip Latitude'}

    return ds
