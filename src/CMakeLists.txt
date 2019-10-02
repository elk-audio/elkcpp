set(PUBLIC_HEADER_FILES
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/control_interface.h
    ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}/sushi_client.h
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

####################
#  Library target  #
####################

set(COMPILATION_UNITS client/sushi_grpc_client.cpp)

set(EXTRA_CLION_SOURCES ${PUBLIC_HEADER_FILES}
                        client/sushi_grpc_client.h)

set(SOURCE_FILES "${COMPILATION_UNITS}" "${EXTRA_CLION_SOURCES}" "${PROTO_SRCS}" "${GRPC_SRCS}")

add_library(sushi-grpc-controller STATIC ${SOURCE_FILES})
target_include_directories(sushi-grpc-controller PUBLIC ${GRPC_WRAPPER_PUBLIC_HEADER_DIR})
target_include_directories(sushi-grpc-controller PRIVATE ${PROTO_SRC_DIR})
target_link_libraries(sushi-grpc-controller
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

#############
#  Install  #
#############

set_target_properties(sushi-grpc-controller PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_FILES}")
install(TARGETS sushi-grpc-controller
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)