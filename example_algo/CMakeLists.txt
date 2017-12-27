cmake_minimum_required(VERSION 2.8)

project(SagemakerCppIntegration)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Compatibility with older cmake versions
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/include/
)

link_directories(
  ${CMAKE_SOURCE_DIR}/../build/sagemaker
)

add_subdirectory(bin)
