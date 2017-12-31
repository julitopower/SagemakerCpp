cmake_minimum_required(VERSION 2.8)

project(sdk_mlp_mxnet_example)

# Set CMake modules path and look for MxNet
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/)

find_package(MxNet REQUIRED)

# Set build type and compilation flags
set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Compatibility with older cmake versions
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include and link directories
add_definitions(-DMSHADOW_USE_CBLAS -DMSHADOW_USE_SSE=0 -Wall)
set(MXNET_ROOT /home/ec2-user/environment/source/incubator-mxnet/ CACHE STRING "mxnet")
include_directories(
  /usr/local/cuda-8.0/include
  ${MxNet_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/../include/
  ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/rapidjson/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/LearnMachineLearning/cpp/mlp_cpu
  )

link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../build/sagemaker/
  /usr/local/lib64
)

# Configure the subdirectories
add_subdirectory(LearnMachineLearning/cpp/mlp_cpu/)
add_subdirectory(bin)
