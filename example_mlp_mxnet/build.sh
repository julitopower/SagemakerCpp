#!/bin/bash

################################################################################
# This script is executed by the build docker image to build the Runtime one
################################################################################

rm -rf build && mkdir -p build && cd build
ls /opt/staging/
cmake .. -DMXNET_ROOT=/opt/staging/incubator-mxnet/ && make && make install && cd ..
mkdir ./libs
find /opt/staging/ -name "*.so.3.4" -exec cp '{}' ./libs \;
find /opt/staging/ -name "libmxnet.so" -exec cp '{}' ./libs \;
cp /usr/lib64/libopenblas.so.0 ./libs 
cp /usr/lib64/libgomp* ./libs 
cp /usr/lib64/liblapack* ./libs 
cp /usr/lib64/libgfortran.so.3 ./libs
cp /usr/lib64/libquadmath.so.0 ./libs
cp /usr/lib64/libblas.so.3 ./libs
docker build . -f Dockerfile -t $1
rm -rf ./libs
