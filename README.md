# Sushi - gRPC controller wrapper #

A simple wrapper for controlling sushi over gRPC via c++. 

### Installation ###

Clone the repository using:
```console
$ git clone git@bitbucket.org:mindswteam/sushi-grpc-cxx-wrapper.git
```
Create a build directory with:
```console
$ mkdir build
```
Move into the build directory with:
```console
$ cd build
```
Then generate the build script using:
```console
$ cmake ..
```
Finally build the library using:
```console
$ make
``` 

### Usage ###

First move `sushi_client.h`and `control_interface.h` into your projects include directory.
Then include the library to your source file using:
```c++
#include "sushi_client.h"
```
To create a controller instance use:
```c++
std::shared_ptr<sushi_controller::ControlInterface> controller = sushi_controller::CreateSushiController();
```

A more in depth example can be found [here](https://bitbucket.org/mindswteam/sushi-grpc-cxx-wrapper/src/master/examples/SimpleSushiController.cpp).