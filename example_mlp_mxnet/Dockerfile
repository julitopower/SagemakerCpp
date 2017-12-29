################################################################################
# This is the runtime image Dockerfile. It simply contains the artifacts built
# by the build image, and defines a suitable entrypoint
################################################################################
FROM amazonlinux

ADD ./libs/* /usr/lib64/
ADD build/bin/algo /usr/bin/algo

#ENTRYPOINT ["algo"]
