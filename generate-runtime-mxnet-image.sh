#!/bin/bash

################################################################################
# Build a base runtime image that contains MxNet and all its dependencies.
# Algorithms based on MxNet must use this image as their base
################################################################################

SDK_DIR=$(readlink -f ./)
docker run --rm -v ${SDK_DIR}/:/opt/staging/sagemaker/ \
                -v /var/run/docker.sock:/var/run/docker.sock \
                -w /opt/staging/sagemaker al_mxnet_build \
                ./build-mxnet-rt-image.sh

exit 0

