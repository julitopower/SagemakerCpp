#!/bin/bash

################################################################################
# This is the outer script that builds the runtime image generation:
#
# 1.- Build build image. As part of this build the algorithm code gets compiled
# 2.- Invoke the build image entrypoint, which will create the runtime image
#
################################################################################

BUILD_IMG_NAME=build_image
docker build . -f Dockerfile -t ${BUILD_IMG_NAME}

# Note how the socket to communicate with the external docker daemon is passed
# to the container. This enables the container to create images in the host
# docker registry
docker run --rm -v /var/run/docker.sock:/var/run/docker.sock ${BUILD_IMG_NAME} $1
