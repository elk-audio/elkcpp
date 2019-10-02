add_executable(simple-sushi-controller SimpleSushiController.cpp)
target_link_libraries(simple-sushi-controller PRIVATE sushi-grpc-controller)