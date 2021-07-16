FROM alpine:edge

COPY . /nc2csv

RUN echo "https://dl-cdn.alpinelinux.org/alpine/edge/testing" >> /etc/apk/repositories
RUN apk update
RUN apk add bash git cmake make g++ python3-dev py3-pip py3-pybind11-dev netcdf-dev netcdf-cxx4-dev hdf5-dev
RUN pip install netCDF4
RUN cd /nc2csv && cmake . && make

CMD "/nc2csv/nc2csv /ncfiles/*"
