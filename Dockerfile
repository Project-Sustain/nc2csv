FROM ubuntu:latest

COPY . /nc2csv

RUN apt update && apt install -y cmake build-essential pybind11-dev python3 python3-pip python3-dev libnetcdf-c++4-dev
RUN pip install netCDF4
RUN cd /nc2csv && cmake . && make

CMD "/nc2csv/nc2csv /ncfiles/*"
