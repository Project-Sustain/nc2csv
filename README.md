# nc2csv

A fast, specialized netCDF to CSV converter.

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

### Docker

To avoid dependency hell, `nc2csv` can also be run through Docker. A pre-built docker image exists at `breadcrumbs2270/nc2csv`, but you can also build an image yourself from this repo's Dockerfile.

`nc2csv`'s docker image simply drops you into a shell with a compiled executable at `/nc2csv/nc2csv`. To expose files to docker, you can use a volume, as in:

```
docker run -v "$PWD:/ncfiles" -it breadcrumbs2270/nc2csv
```

This will create a directory named `/ncfiles` that has the contents of `$PWD`. You can then run `nc2csv /ncfiles/*` to convert the files, which will appear inside of `$PWD`.

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

### Options

* `-c n | -concurrency n` specifies the amount of threads that should run. Each thread will convert exactly one of the .nc files passed to the program. Many threads will consume a lot of memory but will convert multiple files significantly faster. Defaults to 3.
* `-d dimension1,dimension2,dimension3...`  switches the program to dimension mode, where it will not output variables but instead simply the values of each of the dimensions provided. This is useful, for example, to get a list of the unique lat/long points or timestamps in a dataset. 
  Note that the argument to `-d` is a comma-separated list of dimensions.
* `-t dimension` specifies the name of the time dimension. Necessary on datasets like Gridmet that deviate from the standard "time" name. Defaults to "time".
* `-a dimension` specifies the name of the latitude dimension. Defaults to "lat".
* `-g dimension` specifies the name of the longitude dimension. Defaults to "lon".
* `-r host:port` activates GISJOIN map mode. In addition to converting, for each point in the input dataset, the given host and port are queried to discover the GISJOIN that maps to the given points, then the GISJOIN is output in the resulting CSV as the first column. There must be an active Redis server at the given host and port that has been populated with a filter set, as per the geosieve-create tool.

Options must be placed before any files passed to the program.
