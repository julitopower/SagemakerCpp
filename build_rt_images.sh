#!/bin/bash

################################################################################
# This is the outer script that drives the runtime image generation:
#
# 1.- Build the al_build image if not yet built
# 2.- Invoke the sdk build.sh script which first builds the SDK and then builds
#     the actual algorithm
#
################################################################################

BUILD_IMG_NAME=$1
ROOT_DIR=$(readlink -f $2)
SDK_DIR=$(readlink -f ./)
IMG=$3

# Note how the socket to communicate with the external docker daemon is passed
# to the container. This enables the container to create images in the host
# docker registry
docker run --rm -v ${ROOT_DIR}/:/opt/staging/project/ \
                -v ${SDK_DIR}/:/opt/staging/sagemaker/ \
                -v /var/run/docker.sock:/var/run/docker.sock \
                -w /opt/staging/sagemaker ${BUILD_IMG_NAME} \
                ./build.sh ${IMG}
