from datetime import datetime

from matplotlib import pyplot as plt
from glowpython import CGlow, glowdate, glowstl, geomagidx, msis2k, iri90
import numpy as np

glow = CGlow(100)
alt_km = np.arange(60, 1000, 1, dtype=np.float32)
alt_km = np.asfortranarray(alt_km)
ztn = np.log10(alt_km)*300
print(glow._mean_no.calculate_zno(2023111, 0, 0, 100, 4, alt_km, ztn))

time = datetime(2023, 1, 1, 0, 0, 0)
idate, ut = glowdate(time)
glat, glon = 42, -71
f107a, f107, f107p, ap = geomagidx(time, False)
stl = glowstl(ut, glon)

# ds = msis2k(idate, ut, stl, glat, glon, f107a, f107p, ap, alt_km)

# ds.O.plot()
# plt.show()

ds = iri90(idate, stl, glat, glon, f107a, alt_km)

ds.Ne.plot()
plt.show()

ds.Te.plot()
ds.Tn.plot()
ds.Ti.plot()
plt.show()