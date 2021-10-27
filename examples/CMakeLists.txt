add_executable(simple-sushi-controller SimpleSushiController.cpp)
add_executable(async-sushi-controller AsyncSushiController.cpp)
target_link_libraries(simple-sushi-controller PRIVATE elkcpp)
target_link_libraries(async-sushi-controller PRIVATE elkcpp)