################################################################################
# This is the runtime image Dockerfile. It simply contains the artifacts built
# by the build image, and defines a suitable entrypoint
################################################################################
FROM amazonlinux_mxnet

ADD build/bin/algo /usr/bin/algo

#ENTRYPOINT ["algo"]
