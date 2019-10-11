# Sushi - gRPC controller wrapper #

A simple wrapper for controlling sushi over gRPC via c++. 

### Installation ###

Clone the repository using:
```console
$ git clone git@bitbucket.org:mindswteam/sushi-grpc-cxx-wrapper.git
```
Generate the build directory with the generate script using:
```console
$ ./generate --cmake-args="-DPROTO_FILE_PATH=your/path/to/sushi_rpc.proto"
```
Build the library by moving either into either the debug or the release folder and then using:
```console
$ make
```
Finally install into the prefix specified with cmake with:
```console
$ make install
```

### Include in CMake-base Projects ###

Add the sushi-grpc-cxx-wrapper folder to you project folder and in your CMakeLists.txt add:
```cmake
add_subdirectory($PATH_TO_SUSHI_GRPC_WRAPPER)
target_link_libraries($YOUR_TARGET sushi-grpc-controller)
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

A more in depth example can be found [here](https://bitbucket.org/mindswteam/sushi-grpc-cxx-wrapper/src/master/examples/SimpleSushiController.cpp).