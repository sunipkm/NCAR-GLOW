from __future__ import annotations
from datetime import datetime, timedelta
from typing import Tuple, SupportsFloat as Numeric

import geomagdata as gi


def glowdate(t: datetime)->Tuple[int, Numeric]:
    """Convert a datetime object to a string in the format yyyymmdd and yyyymmddhhmmss.

    Args:
        t (datetime): The date and time.

    Returns:
        Tuple[int, Numeric]: The date and time as strings.
    """
    idate = int(f'{t.year:04d}{t.strftime("%j")}')
    utsec = (t.hour * 3600) + (t.minute * 60) + t.second

    return idate, utsec

def glowstl(utsec: Numeric, lon: Numeric)->Numeric:
    """Calculate the local solar time.

    Args:
        utsec (Numeric): The time in seconds.
        lon (Numeric): The longitude in degrees.

    Returns:
        Numeric: The local solar time in hours.
    """
    lon = lon % 360
    return ((utsec / 3600) + (lon / 15)) % 24

def geomagidx(time: datetime, tzaware: bool)->Tuple[Numeric, Numeric, Numeric, Numeric]:
    """Get the geomagnetic indices for a given time.

    Args:
        time (datetime): Model evaluation time.
        tzaware (bool): Whether `time` is timezone aware. If true, `time` is recast to 'UTC' using `time.astimezone(pytz.utc)`.

    Returns:
        Tuple[Numeric, Numeric, Numeric, Numeric]: _description_
    """
    ip = gi.get_indices([time - timedelta(days=1), time], 81, tzaware=tzaware)
    f107a = float(ip['f107s'].iloc[1])
    f107 = float(ip['f107'].iloc[1])
    f107p = float(ip['f107'].iloc[0])
    ap = float(ip['Ap'].iloc[1])
    return f107a, f107, f107p, ap