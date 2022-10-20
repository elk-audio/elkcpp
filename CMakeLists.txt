#########################
#  CMake configuration  #
#########################

cmake_minimum_required(VERSION 3.19)

set(ELKCPP_VERSION_MAJOR 1)
set(ELKCPP_VERSION_MINOR 0)
set(ELKCPP_VERSION_REVISION 0)

project(elkcpp
    DESCRIPTION "A simple wrapper for controlling sushi over gRPC via C++"
    HOMEPAGE_URL "https://github.com/elk-audio/elkcpp"
    LANGUAGES CXX
    VERSION ${ELKCPP_VERSION_MAJOR}.${ELKCPP_VERSION_MINOR}.${ELKCPP_VERSION_REVISION}
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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

########################################
#  gRPC / Protobuf intermediary target #
########################################

find_package(gRPC REQUIRED)

set(PROTOS "${PROJECT_SOURCE_DIR}/sushi-grpc-api/sushi_rpc.proto")

# Intermediate library target with the generated protobuf objects
add_library(protos-lib OBJECT)
target_sources(protos-lib PRIVATE ${PROTOS})
target_link_libraries(protos-lib PUBLIC gRPC::grpc++)
target_include_directories(protos-lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

protobuf_generate(TARGET protos-lib LANGUAGE cpp)
protobuf_generate(
    TARGET protos-lib
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN
    "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
)

####################
#  Library target  #
####################

set(SOURCE_FILES src/client/sushi_grpc_client.cpp
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

set(SUSHI_GRPC_INCLUDE_DIRS
    "${CMAKE_CURRENT_BINARY_DIR}/sushi-grpc-api"
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SUSHI_GRPC_LINK_LIBRARIES
    gRPC::grpc++
    protos-lib
)

add_library(elkcpp STATIC ${SOURCE_FILES})
target_include_directories(elkcpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/elkcpp>
    $<INSTALL_INTERFACE:include/elkcpp>
)
target_include_directories(elkcpp PRIVATE ${SUSHI_GRPC_INCLUDE_DIRS})
target_link_libraries(elkcpp PUBLIC ${SUSHI_GRPC_LINK_LIBRARIES})

#############
#  Package  #
#############

set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(elkcpp_export "${generated_headers}/elkcpp/ELKCPP_EXPORT.h")

generate_export_header(elkcpp EXPORT_FILE_NAME ${elkcpp_export})
generate_export_header(protos-lib EXPORT_FILE_NAME ${protos_export})

set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS elkcpp protos-lib
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    DIRECTORY "include/elkcpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

install(
    FILES "${elkcpp_export}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/elkcpp"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
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

