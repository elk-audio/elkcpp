# build gtest framework
add_subdirectory(googletest)
enable_testing()

#####################################
#  Disable logging at compile time  #
#####################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDISABLE_LOGGING")

################
#  Test Files  #
################

SET(TEST_FILES unittests/sushi_client_integration_test.cpp)

##########################################
#  Include directories relative to test  #
##########################################

set(INCLUDE_DIRS "${INCLUDE_DIRS}"
                 ${PROJECT_SOURCE_DIR}/test/googletest/include
                 ${PROJECT_SOURCE_DIR}/src/client)

include_directories(${INCLUDE_DIRS})

#################################
#  Statically linked libraries  #
#################################

set(LINK_LIBRARIES "${LINK_LIBRARIES}"
                   sushi-grpc-controller
                   gtest
                   gtest_main)

add_executable(unit_tests ${TEST_FILES})

target_link_libraries(unit_tests "${LINK_LIBRARIES}")

# TODO: Ugly fix to get tests building. probably existst better solution.
set(PROTO_SRC_DIR ${CMAKE_BINARY_DIR}/src/proto-src)
target_include_directories(unit_tests PRIVATE ${PROTO_SRC_DIR})

add_test(unit_tests unit_tests)

# custom target for running the tests
add_custom_target(run_tests ALL COMMAND "./unit_tests")
add_dependencies(run_tests unit_tests)

