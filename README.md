# nc2csv

A fast*, specialized netCDF to CSV converter.

_*hopefully_

## Build

This program builds with C++11, and depends on:

* `libnetcdf`
* `libnetcdf_c++4`
* `pybind11`

...so these should be installed in a standard location.

The use of `bybind11` is to leverage some very useful features of the `netCDF4` python library, so this python package should also be installed globally (though this is a run-time dependency, not a build-time one.)

This is a CMake project, so if the dependencies are met, you can build with:

```
cmake .
make
```

Using `cmake -DCMAKE_BUILD_TYPE=Debug .` will compile with debug symbols and no optimization - otherwise optimization at `-O3` will be used.

## Usage

Supply every file you want to convert as an argument, e.g.

```
./nc2csv netcdffile1.nc netcdffile2.nc ...
```

Each one will be converted to a file with the same name, having `.nc` removed and replaced with `.csv`. This means they will appear in the same directory as the original files.

What will be output is a CSV file with the following header:

```
time,lat,lon,<another variable>
```

... where "another variable" is the first variable encountered in the file that is NOT either "time", "lat", "long", "crs", "time_bnds", "lat_bnds", or "lon_bnds". You cannot manually specify a variable to convert, so currently this is only useful for netCDF files that have one variable, e.g. the TerraClimate datasets.

There are currently no other command-line options. This will probably change in the future.
