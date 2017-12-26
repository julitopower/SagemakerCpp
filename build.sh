#!/bin/bash

################################################################################
# This script is executed by the build docker image to build the Runtime one
################################################################################

docker build . -f Dockerfile2 -t $1
