#!/bin/bash

################################################################################
# This script builds build images. The only argument is the type of build
# image to build, which can be [al | al-mxnet].
#
# Run this script just once at the beginning of your project
################################################################################

TYPE=$1

if [[ ${TYPE} == "al" ]]
then
    docker build . -f DockerfileAL -t al_build
    exit 0
fi

if [[ ${TYPE} == "al-mxnet" ]]
then
    docker build . -f DockerfileALMxNet -t al_mxnet_build
    exit 0
fi

echo "Specify image type [al | al-mxnet]"
exit 1

