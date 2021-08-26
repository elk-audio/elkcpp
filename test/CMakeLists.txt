# build gtest framework
add_subdirectory(googletest EXCLUDE_FROM_ALL)
enable_testing()

################
#  Test Files  #
################

SET(TEST_FILES unittests/audio_graph_integration_test.cpp
               unittests/audio_routing_integration_test.cpp
               unittests/keyboard_integration_test.cpp
               unittests/midi_integration_test.cpp
               unittests/notification_integration_test.cpp
               unittests/osc_integration_test.cpp
               unittests/parameter_integration_test.cpp
               unittests/program_integration_test.cpp
               unittests/system_integration_test.cpp
               unittests/timing_integration_test.cpp
               unittests/transport_integration_test.cpp)

##########################################
#  Include directories relative to test  #
##########################################

set(INCLUDE_DIRS ${GRPC_WRAPPER_PUBLIC_HEADER_DIR}
                 ${PROJECT_SOURCE_DIR}/test/googletest/include
                 ${PROJECT_SOURCE_DIR}/src/client)

#################################
#  Statically linked libraries  #
#################################

set(LINK_LIBRARIES elkcpp
                   gtest
                   gtest_main)

add_executable(unit_tests ${TEST_FILES})

target_link_libraries(unit_tests "${LINK_LIBRARIES}")
target_include_directories(unit_tests PRIVATE "${INCLUDE_DIRS}")
target_include_directories(unit_tests PRIVATE ${PROTO_SRC_DIR})

add_test(unit_tests unit_tests)

# custom target for running the tests
add_custom_target(run_tests ALL COMMAND "./unit_tests")
add_dependencies(run_tests unit_tests)

