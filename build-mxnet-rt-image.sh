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
cp /usr/lib/x86_64-linux-gnu/libgthread-2.0.so.0 ./libs
cp /usr/lib/x86_64-linux-gnu/libglib-2.0.so ./libs/libglib-2.0.so.0
cp /usr/lib/x86_64-linux-gnu/libjpeg.so.62 ./libs
cp /usr/lib/x86_64-linux-gnu/libwebp.so.5 ./libs
cp /usr/lib/x86_64-linux-gnu/libpng12.so.0 ./libs
cp /usr/lib/x86_64-linux-gnu/libtiff.so.5 ./libs
cp /usr/lib/x86_64-linux-gnu/libjasper.so.1 ./libs
cp /usr/lib/x86_64-linux-gnu/libI* ./libs
cp /usr/lib/x86_64-linux-gnu/lib* ./libs
# Build the image. The images will copy the contents of 
# /opt/staging/libs to /usr/lib/
docker build . -f DockerfileALMxNetRT -t amazonlinux_mxnet

# Cleanup
rm -rf ./libs
