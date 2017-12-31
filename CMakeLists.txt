cmake_minimum_required(VERSION 2.8)

project(SagemakerCppIntegration)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Compatibility with older cmake versions
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rapidjson/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

enable_testing()

add_subdirectory(sagemaker)
add_subdirectory(include)
add_subdirectory(thirdparty/rapidjson)
add_subdirectory(tst)
