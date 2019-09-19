set(PUBLIC_HEADER_FILES
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/SushiControllerInterface.h
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/SushiGRPCClient.h
)

#####################
#  gRPC / Protobuf  #
#####################

set(PROTOS
    ${PROJECT_SOURCE_DIR}/protos/sushi_rpc.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# there are plenty of these warnings in auto-generated files
foreach(ITEM ${PROTO_SRCS} ${GRPC_SRCS})
    set_source_files_properties(${ITEM} PROPERTIES COMPILE_FLAGS -Wno-unused-parameters)    
endforeach()

######################
#  Helper functions  #
######################

### Add a static library target that depends on gRPC
#   Usage:
#       add_grpc_static_library(NAME target_name SRCS source_file_list)
function(add_grpc_static_library)
    cmake_parse_arguments(PARSED_ARGS "" "NAME" "SRCS" ${ARGN})
    # note: if it remains unparsed arguments, here, they can be found in variable PASSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_NAME)
        message(FATAL_ERROR "add_grpc_static_library: NAME not specified")
    endif(NOT PARSED_ARGS_NAME)
    add_library(${PARSED_ARGS_NAME} STATIC
        ${PARSED_ARGS_SRCS}
        ${PROTO_SRCS}
        ${GRPC_SRCS}
    )
    target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${PROTO_SRC_DIR})
    target_link_libraries(${PARSED_ARGS_NAME}
        gRPC::grpc++_reflection
        protobuf::libprotobuf
    )
    set_target_properties(${PARSED_ARGS_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_FILES}")
    install(TARGETS ${PARSED_ARGS_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    )
endfunction(add_grpc_static_library)

################
#  Client lib  #
################

include_directories(${PROJECT_SOURCE_DIR}/src/client)
set(CLIENT_LIB_SOURCES
    client/sushi_grpc_client.cpp
)

add_grpc_static_library(NAME sushi-grpc-controller SRCS ${CLIENT_LIB_SOURCES})