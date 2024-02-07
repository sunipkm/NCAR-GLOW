from __future__ import annotations
from datetime import datetime
from enum import IntEnum
from typing import Tuple, SupportsFloat as Numeric
import numpy as np
from xarray import Variable, DataArray, Dataset
from .fortran import egrid, snoem_init, ssflux_init, ephoto_init, exsect, fieldm, solzen, ssflux, rcolum, ephoto, qback, etrans, gchem, bands

from .snoem import MeanNO

from .dirsetup import DATA_DIR, IRI90_DIR
from .utils import glowdate, glowstl, geomagidx


class FluxScale(IntEnum):
    Hinteregger = 0
    EUVAC = 1
    User = 2


class CGlow:
    def __init__(self, jmax: int, nbins: int = 250, iscale: FluxScale = FluxScale.Hinteregger, data_dir: str = DATA_DIR):
        self._jmax = jmax
        self._nbins = nbins
        self._iscale = iscale
        self._data_dir = data_dir
        self._mean_no = MeanNO(data_dir)
        # self._lmax = 123  # number of wavelength intervals for solar flux
        # self._nmaj = 3    # number of major species
        # self._nst = 6     # number of states produced by photoionization/dissociation
        # self._nei = 10    # number of states produced by electron impact
        # self._nex = 12    # number of excited/ionized species
        # self._nw = 15     # number of airglow emission wavelengths
        # self._nc = 10     # number of component production terms for each emission
        
        # self._vcb = np.zeros(self._nw, dtype=np.float32, order='F')

        # self._zz    = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zo    = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zn2   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zo2   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zno   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zns   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._znd   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zrho  = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._ze    = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._ztn   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zti   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._zte   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._eheat = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._tez   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._ecalc = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._tei   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._tpi   = np.zeros(self._jmax, dtype=np.float32, order='F')
        # self._tir   = np.zeros(self._jmax, dtype=np.float32, order='F')

        # self._phitop = np.zeros(self._nbins, dtype=np.float32, order='F')
        # self._ener   = np.zeros(self._nbins, dtype=np.float32, order='F')
        # self._edel   = np.zeros(self._nbins, dtype=np.float32, order='F')

        # self._wave1     = np.zeros(self._lmax, dtype=np.float32, order='F')
        # self._wave2     = np.zeros(self._lmax, dtype=np.float32, order='F')
        # self._sflux     = np.zeros(self._lmax, dtype=np.float32, order='F')
        # self._sf_rflux  = np.zeros(self._lmax, dtype=np.float32, order='F')
        # self._sf_scale1 = np.zeros(self._lmax, dtype=np.float32, order='F')
        # self._sf_scale2 = np.zeros(self._lmax, dtype=np.float32, order='F')

        # self._pespec = np.zeros((self._nbins, self._jmax), dtype=np.float32, order='F')
        # self._sespec = np.zeros((self._nbins, self._jmax), dtype=np.float32, order='F')
        # self._uflx   = np.zeros((self._nbins, self._jmax), dtype=np.float32, order='F')
        # self._dflx   = np.zeros((self._nbins, self._jmax), dtype=np.float32, order='F')

        # self._zmaj = np.zeros((self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._zcol = np.zeros((self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._pia  = np.zeros((self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._sion = np.zeros((self._nmaj, self._jmax), dtype=np.float32, order='F')

        # self._photoi = np.zeros((self._nst, self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._photod = np.zeros((self._nst, self._nmaj, self._jmax), dtype=np.float32, order='F')

        # self._phono = np.zeros((self._nst, self._jmax), dtype=np.float32, order='F')

        # self._epsil1 = np.zeros((self._nst, self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._epsil2 = np.zeros((self._nst, self._nmaj, self._jmax), dtype=np.float32, order='F')
        # self._eprobs = np.zeros((self._nmaj, self._jmax), dtype=np.float32, order='F')

        # self._sigion = np.zeros((self._nmaj, self._lmax), dtype=np.float32, order='F')
        # self._sigabs = np.zeros((self._nmaj, self._lmax), dtype=np.float32, order='F')

        # self._aglw = np.zeros((self._nei, self._nmaj, self._jmax), dtype=np.float32, order='F')

        # self._zxden = np.zeros((self._nex, self._jmax), dtype=np.float32, order='F')

        # self._zeta = np.zeros((self._nw, self._jmax), dtype=np.float32, order='F')

        # self._ceta = np.zeros((self._nc, self._nw, self._jmax), dtype=np.float32, order='F')

        # self._zlbh = np.zeros((self._nc, self._jmax), dtype=np.float32, order='F')

        # self._sigs = np.zeros((self._nmaj, self._nbins), dtype=np.float32, order='F')
        # self._pe   = np.zeros((self._nmaj, self._nbins), dtype=np.float32, order='F')
        # self._pin  = np.zeros((self._nmaj, self._nbins), dtype=np.float32, order='F')

        # self._sigex = np.zeros((self._nei, self._nmaj, self._nbins), dtype=np.float32, order='F')
        # self._sigix = np.zeros((self._nei, self._nmaj, self._nbins), dtype=np.float32, order='F')

        # self._siga = np.zeros((self._nei, self._nbins, self._nbins), dtype=np.float32, order='F')
        # self._sec  = np.zeros((self._nei, self._nbins, self._nbins), dtype=np.float32, order='F')

        # self._iimaxx = np.zeros((self._nbins), dtype=np.int32, order='F')

        # self._ww   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._ao   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._omeg = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._anu  = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._bb   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._auto = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._thi  = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._ak   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._aj   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._ts   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._ta   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._tb   = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._gams = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')
        # self._gamb = np.zeros((self._nei, self._nmaj), dtype=np.float32, order='F')

        # self._prod = np.zeros((self._nex, self._jmax), dtype=np.float32, order='F')
        # self._loss = np.zeros((self._nex, self._jmax), dtype=np.float32, order='F')

        # self._snoem_zin = np.zeros((16), dtype=np.float32, order='F')
        # self._snoem_mlatin = np.zeros((33), dtype=np.float32, order='F')
        # self._snoem_no_mean = np.zeros((33, 16), dtype=np.float32, order='F')
        # self._snoem_eofs = np.zeros((33, 16, 3), dtype=np.float32, order='F')

        # egrid(self._edel, self._ener)
