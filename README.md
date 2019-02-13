[![Build Status](https://travis-ci.com/scivision/NCAR-GLOW.svg?branch=master)](https://travis-ci.com/scivision/NCAR-GLOW)

# GLOW
The GLobal airglOW Model

* Fortran-90 source code files,
* Makefiles,
* Example input and output files,
* Example job script,
* Subdirectory data/ contains input data files,
* Subdirectory data/iri90 contains IRI input data files


## Build
You can call this repo from a Meson wrap or CMake Fetch.
To build by itself, do either:


```sh
meson build

ninja -c build
```

or

```sh
cmake -B build -S .

cmake --build build -j
```

### MPI / NetCDF

The parallel version of GLOW requires MPI and NetCDF for TIEGCM I/O.

## Matlab

The Matlab and Python interfaces work similarly.
Matlab code is in the [matlab](./matlab) directory, and passes data to / from Glow over stdin / stdout pipes.
