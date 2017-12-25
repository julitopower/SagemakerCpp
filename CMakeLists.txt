cmake_minimum_required(VERSION 2.8)

project(SagemakerCppIntegration)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  sagemaker/include/
)

add_subdirectory(sagemaker)
add_subdirectory(bin)
add_subdirectory(tst)
