#!/bin/bash

################################################################################
# This script is executed by the build docker image to build the Runtime one
################################################################################

# Copy all required libraries to /opt/staging/libs
ls /opt/staging/
mkdir ./libs
find /opt/staging/ -name "*.so.3.4" -exec cp '{}' ./libs \;
find /opt/staging/ -name "libmxnet.so" -exec cp '{}' ./libs \;
cp /usr/lib/libopenblas.so.0 ./libs 
cp /usr/local/lib64/libgomp* ./libs 
cp /usr/lib/liblapack* ./libs 
cp /usr/local/lib64/libgfortran.so.3 ./libs
cp /usr/local/lib64/libquadmath.so.0 ./libs
cp /usr/lib/libblas.so.3 ./libs

# Build the image. The images will copy the contents of 
# /opt/staging/libs to /usr/lib/
docker build . -f DockerfileALMxNetRT -t amazonlinux_mxnet

# Cleanup
rm -rf ./libs
