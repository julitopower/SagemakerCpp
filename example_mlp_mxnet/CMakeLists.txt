cmake_minimum_required(VERSION 2.8)

project(sdk_mlp_mxnet_example)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Compatibility with older cmake versions
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DMSHADOW_USE_CBLAS -DMSHADOW_USE_SSE=0 -Wall)
set(MXNET_ROOT /home/ec2-user/environment/source/incubator-mxnet/ CACHE STRING "mxnet")
include_directories(
  /usr/local/cuda-8.0/include
  ${MXNET_ROOT}include
  ${MXNET_ROOT}dmlc-core/include
  ${MXNET_ROOT}mshadow
  ${MXNET_ROOT}nnvm/include
  ${MXNET_ROOT}dlpack/include
  ${MXNET_ROOT}cpp-package/include
  )

include_directories(
  ${CMAKE_SOURCE_DIR}/../include/
  ${CMAKE_SOURCE_DIR}/LearnMachineLearning/cpp/mlp_cpu
)

link_directories(
  ${MXNET_ROOT}lib/
  ${CMAKE_SOURCE_DIR}/../build/sagemaker
  /usr/local/lib64
)

add_subdirectory(LearnMachineLearning/cpp/mlp_cpu/)
add_subdirectory(bin)
