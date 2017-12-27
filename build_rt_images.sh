#!/bin/bash

################################################################################
# This is the outer script that builds the runtime image generation:
#
# 1.- Build build image. The SDK gets built in this step
# 2.- Invoke the build.sh script provided by the algoritm project
#
################################################################################

ROOT_DIR=$(readlink -f $1)
IMG=$2

echo ${ROOT_DIR}

BUILD_IMG_NAME=build_image
docker build . -f Dockerfile -t ${BUILD_IMG_NAME}

# Note how the socket to communicate with the external docker daemon is passed
# to the container. This enables the container to create images in the host
# docker registry
docker run --rm -v ${ROOT_DIR}/:/opt/staging/project/ \
                -v /var/run/docker.sock:/var/run/docker.sock ${BUILD_IMG_NAME} \
                ./build.sh ${IMG}
