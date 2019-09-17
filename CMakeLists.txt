#########################
#  CMake configuration  #
#########################

project(sushi-grpc-cpp-warpper)
cmake_minimum_required(VERSION 3.2)

# CMake find modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

include(CMakeParseArguments)

##########################
#  Custom build options  #
##########################

set(GRPC_WRAPPER_BUILD_EXAMPLES true CACHE BOOL "Build included examples")

############################
#  Compiler configuration  #
############################

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra)

####################
#  Public headers  #
####################

set(GRPC_WRAPPER_PUBLIC_HEADER_DIR
    "${PROJECT_SOURCE_DIR}/include"
)
include_directories(${GRPC_WRAPPER_PUBLIC_HEADER_DIR})

##################
#  Sub projects  #
##################

add_subdirectory(src)
if(${GRPC_WRAPPER_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()