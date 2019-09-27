include_directories("${PROJECT_SOURCE_DIR}/src/client")
add_executable(simple-sushi-controller SimpleSushiController.cpp)
target_link_libraries(simple-sushi-controller PRIVATE sushi-grpc-controller)