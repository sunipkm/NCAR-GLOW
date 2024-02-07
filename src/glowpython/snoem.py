import copy
import os
from .fortran import snoem_init, snoemint
from .dirsetup import DATA_DIR
import xarray as xr
from typing import SupportsFloat as Numeric
import numpy as np

class MeanNO:
    """Initialize the routine to calculate NO estimate from the NOEM empirical model.
    """
    def __init__(self, data_dir: str = DATA_DIR):
        """Initialize the coefficients.

        Args:
            data_dir (str, optional): _description_. Defaults to DATA_DIR.
        """
        if data_dir is not None and not os.path.exists(data_dir):
            raise ValueError(f"Data directory {data_dir} does not exist.")
        self._data_dir = data_dir
        self._zin = None
        self._mlatin = None
        self._no_mean = None
        self._eofs = None
        if data_dir is None:
            return
        self._load()
        
    def _load(self):
        snoem_zin, snoem_mlatin, snoem_no_mean, snoem_eofs = snoem_init(self._data_dir)
        self._zin = snoem_zin
        self._mlatin = snoem_mlatin
        self._no_mean = snoem_no_mean
        self._eofs = snoem_eofs
    
    def calculate_zno(self, idate: int, glat: Numeric, glon: Numeric, f107: Numeric, ap: Numeric, alt_km: np.ndarray, ztn: np.ndarray)->xr.Variable:
        """Calculate the NO estimate from the NOEM empirical model.

        Args:
            idate (int): Date in yyddd or yyyyddd format.
            glat (Numeric): Geographic Latitude in Deg.
            glon (Numeric): Geographic Longitude in Deg.
            f107 (Numeric): 10.7 cm Solar Radio Flux.
            ap (Numeric): Ap index.
            alt_km (np.ndarray): Altitude grid in km.
            ztn (np.ndarray): Neutral temperature at Z in K.

        Asserts:
            1. `alt_km` and `ztn` are in Fortran order.
            2. `alt_km` and `ztn` have the same shape.

        Returns:
            np.ndarray: NO density at Z in cm^-3.
        """
        assert(alt_km.flags.f_contiguous)
        assert(ztn.flags.f_contiguous)
        assert(alt_km.shape == ztn.shape)
        out = snoemint(idate, glat, glon, f107, ap, alt_km, ztn, self._zin, self._mlatin, self._no_mean, self._eofs)
        return xr.Variable(('alt_km',), out, attrs={'units': 'cm^-3'})
    
    def __copy__(self):
        """Return a deep copy of the object.
        """
        obj = MeanNO(None)
        obj._data_dir = copy.copy(self._data_dir)
        obj._zin = self._zin.copy()
        obj._mlatin = self._mlatin.copy()
        obj._no_mean = self._no_mean.copy()
        obj._eofs = self._eofs.copy()      
        return obj  
    