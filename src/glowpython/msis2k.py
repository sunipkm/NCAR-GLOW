from __future__ import annotations
from typing import SupportsFloat as Numeric

import numpy as np
from xarray import Dataset, Variable
from .fortran import msis_wrap # pylint: disable=import-error # type: ignore


def msis2k(idate: int, ut: Numeric, stl: Numeric, glat: Numeric, glon: Numeric, f107a: Numeric, f107p: Numeric, ap: Numeric, alt_km: np.ndarray) -> Dataset:
    """Calculate the MSIS2K model for a given date, time, and location.

    Args:
        idate (int): Date in yyddd or yyyyddd format. Currently ignores the year.
        ut (Numeric): Universal time, seconds.
        stl (Numeric): Local solar time, hours.
        glat (Numeric): Geographic Latitude in Deg.
        glon (Numeric): Geographic Longitude in Deg.
        f107a (Numeric): F10.7 index, 81-day average centered on `idate`.
        f107p (Numeric): F10.7 index daily value for previous day.
        ap (Numeric): Daily magnetic index.
        alt_km (np.ndarray): Altitude grid in km. Must be in Fortran order.

    Asserts:
        1. `alt_km` is in Fortran order.

    Returns:
        Dataset: Dataset containing the neutral densities of O, N2, O2, NO, Tn, and ND.
        Densities in cm^-3 and temperature in K.
    """
    assert (alt_km.flags.f_contiguous)
    zo = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    zn2 = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    zo2 = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    zns = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    ztn = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    znd = np.zeros(alt_km.shape, dtype=np.float32, order='F')
    msis_wrap(idate, ut, glat, glon, stl, f107a, f107p, ap, alt_km, zo, zn2, zo2, zns, ztn, znd)

    ds = Dataset(
        {
            'O': Variable(('alt_km',), zo, attrs={'units': 'cm^-3', 'long_name': 'number density'}),
            'N2': Variable(('alt_km',), zn2, attrs={'units': 'cm^-3', 'long_name': 'number density'}),
            'O2': Variable(('alt_km',), zo2, attrs={'units': 'cm^-3', 'long_name': 'number density'}),
            'NO': Variable(('alt_km',), zns, attrs={'units': 'cm^-3', 'long_name': 'number density'}),
            'Tn': Variable(('alt_km',), ztn, attrs={'units': 'K', 'long_name': 'Temperature'}),
            'ND': Variable(('alt_km',), znd, attrs={'units': 'cm^-3', 'long_name': 'number density'}),
        },
        coords={'alt_km': ('alt_km', alt_km, {'standard_name': 'altitude', 'units': 'km', 'long_name': 'Altitude'})},
    )
    return ds
