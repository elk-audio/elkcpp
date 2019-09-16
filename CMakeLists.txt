#######################
# CMake configuration #
#######################

project(sushi-grpc-cpp-warpper)
cmake_minimum_required(VERSION 3.2)

# CMake find modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

include(CMakeParseArguments)

########################
# Custom build options #
########################