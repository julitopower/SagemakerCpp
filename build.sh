#!/bin/bash

-e

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

