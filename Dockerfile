################################################################################
# This is the build image Dockerfile. Note that as part of this build, the 
# actual algorithm code gets compiled.
################################################################################
FROM amazonlinux

# Install all packages necesary to build and create docker images
RUN yum -y groupinstall "Development Tools" && yum -y install cmake \
    && gcc --version && yum -y install docker

# Prepare the staging area to build the SDK and the algorithm project
RUN mkdir -p /opt/staging/ && mkdir -p /opt/stating/project
ADD ./ /opt/staging/sagemaker

# Build the SDK
WORKDIR /opt/staging/sagemaker
RUN rm -rf build && mkdir -p build && cd build && \
    cmake .. && make && make test && make install 

# Set CWD to the location where the algorithm code will be 
# mounted
WORKDIR /opt/staging/project
