FROM ubuntu:latest

COPY . /nc2csv

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake build-essential pybind11-dev python3 python3-pip python3-dev libnetcdf-c++4-dev
RUN pip install netCDF4
RUN cd /nc2csv && cmake . && make

CMD "/nc2csv/nc2csv", "/ncfiles/*"
