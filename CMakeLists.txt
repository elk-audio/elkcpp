#########################
#  CMake configuration  #
#########################

project(elkcpp)
cmake_minimum_required(VERSION 3.8)

# CMake find modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

include(CMakeParseArguments)

##########################
#  Custom build options  #
##########################

set(GRPC_WRAPPER_BUILD_EXAMPLES true CACHE BOOL "Build included examples")
set(GRPC_WRAPPER_RUN_TESTS true CACHE BOOL "Build and run unit tests")
option(PRINT_ERRORS_TO_CONSOLE "Set to print control status errors to cout" OFF)

if(${PRINT_ERRORS_TO_CONSOLE})
    add_definitions(-DSUSHI_CONTROLLER_PRINT_ERRORS)
endif()

############################
#  Compiler configuration  #
############################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

####################
#  Public Headers  #
####################

set(GRPC_WRAPPER_PUBLIC_HEADER_DIR "${PROJECT_SOURCE_DIR}/include/sushi_controller")

set(PUBLIC_HEADER_FILES
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/control_interface.h
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/sushi_client.h
)

#####################
#  gRPC / Protobuf  #
#####################

set(PROTO_FILE_PATH
    /usr/share/sushi/sushi_rpc.proto CACHE STRING "Path to the proto file for the sushi rpc"
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTO_FILE_PATH})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTO_FILE_PATH})

# there are plenty of these warnings in auto-generated files
foreach(ITEM ${PROTO_SRCS} ${GRPC_SRCS})
    set_source_files_properties(${ITEM} PROPERTIES COMPILE_FLAGS -Wno-unused-parameters)
endforeach()

####################
#  Library target  #
####################

set(COMPILATION_UNITS src/client/sushi_grpc_client.cpp
                      src/client/async_client_call_data.cpp
                      src/client/audio_graph_controller.cpp
                      src/client/audio_routing_controller.cpp
                      src/client/cv_gate_controller.cpp
                      src/client/keyboard_controller.cpp
                      src/client/midi_controller.cpp
                      src/client/notification_controller.cpp
                      src/client/osc_controller.cpp
                      src/client/parameter_controller.cpp
                      src/client/program_controller.cpp
                      src/client/session_controller.cpp
                      src/client/system_controller.cpp
                      src/client/timing_controller.cpp
                      src/client/transport_controller.cpp)

set(EXTRA_CLION_SOURCES ${PUBLIC_HEADER_FILES}
                        src/client/sushi_grpc_client.h
                        src/client/async_client_call_data.h
                        src/client/audio_graph_controller.h
                        src/client/audio_routing_controller.h
                        src/client/cv_gate_controller.h
                        src/client/keyboard_controller.h
                        src/client/midi_controller.h
                        src/client/notification_controller.h
                        src/client/osc_controller.h
                        src/client/parameter_controller.h
                        src/client/program_controller.h
                        src/client/session_controller.h
                        src/client/system_controller.h
                        src/client/timing_controller.h
                        src/client/transport_controller.h)

set(SOURCE_FILES "${COMPILATION_UNITS}" "${EXTRA_CLION_SOURCES}" "${PROTO_SRCS}" "${GRPC_SRCS}")

add_library(elkcpp STATIC ${SOURCE_FILES})
target_include_directories(elkcpp PUBLIC ${GRPC_WRAPPER_PUBLIC_HEADER_DIR})
target_include_directories(elkcpp PRIVATE ${PROTO_SRC_DIR})
target_link_libraries(elkcpp
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

#############
#  Install  #
#############

set_target_properties(elkcpp PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_FILES}")
install(TARGETS elkcpp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

##################
#  Sub projects  #
##################

if(${GRPC_WRAPPER_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

if(${GRPC_WRAPPER_RUN_TESTS})
    add_subdirectory(test)
endif()
