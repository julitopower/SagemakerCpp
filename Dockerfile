################################################################################
# This is the build image Dockerfile. Note that as part of this build, the 
# actual algorithm code gets compiled.
################################################################################
FROM amazonlinux

RUN yum -y groupinstall "Development Tools" && yum -y install cmake && gcc --version

RUN yum -y install docker
RUN mkdir -p /opt/staging/
ADD ./ /opt/staging/sagemaker
WORKDIR /opt/staging/sagemaker
RUN rm -rf build && mkdir -p build && cd build && cmake .. && make && make test \
    && make install && cd .. && cp /usr/local/bin/algo ./
WORKDIR /opt/staging/sagemaker

ENTRYPOINT ["./build.sh"]
