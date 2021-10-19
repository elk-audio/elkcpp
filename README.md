# Sushi - gRPC controller wrapper #

A simple wrapper for controlling sushi over gRPC via c++.

### Installation ###

Clone the repository and generate the build directory by using:
```console
$ mkdir build && cd build && cmake ..
```
Build the library by using:
```console
$ make
```
Finally install with:
```console
$ make install
```

The default path where the proto file is installed is used when not specified `/usr/share/sushi/sushi_rpc.proto`.
A custom proto file can be set with the provided cmake flag `PROTO_FILE_PATH`.
Printing errors to std::cout can be enabled by setting the `PRINT_ERRORS_TO_CONSOLE` option.

### Include in CMake-base Projects ###

Add the elkcpp folder to you project folder and in your CMakeLists.txt add:
```cmake
add_subdirectory($PATH_TO_ELKCPP)
target_link_libraries($YOUR_TARGET elkcpp)
```

### Usage ###

Include the library to your source file using:
```c++
#include "sushi_client.h"
```
To create a controller instance use:
```c++
std::shared_ptr<sushi_controller::ControlInterface> controller = sushi_controller::CreateSushiController();
```

A more in depth example can be found [here](https://bitbucket.org/mindswteam/elkcpp/src/master/examples/SimpleSushiController.cpp).
