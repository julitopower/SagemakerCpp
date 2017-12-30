#!/bin/bash

set -e

SDK_DIR=$(readlink -f ./)
rm -rf build
mkdir build
cd build
cmake ..
make -j $(nproc)
make test
make install

cd ../../project
ls
./build.sh $1

cd ${SDK_DIR}
rm -rf build
