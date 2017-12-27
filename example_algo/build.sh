#!/bin/bash

################################################################################
# This script is executed by the build docker image to build the Runtime one
################################################################################

rm -rf build && mkdir -p build && cd build
cmake .. && make && make install && cd ..
docker build . -f Dockerfile -t $1
