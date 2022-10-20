# Sushi - gRPC controller wrapper #

A simple wrapper for controlling sushi over gRPC via c++.

### Installation ###

Clone the repository and generate the build directory by using:
```console
$ git submodule update --init --recursive
$ ./third-party/vcpkg/bootstrap-vcpkg.sh
$ mkdir build && cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=../third-party/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```

Build the library by using:
```console
$ make
```

Finally install with:
```console
$ make install
```

Printing errors to std::cout can be enabled by setting the `PRINT_ERRORS_TO_CONSOLE` option.

### Include in CMake-base Projects ###

First, build and then install elkcpp. The installations includes a CMake package that other projects can use to find the library.

In your CMake project, add these lines:
```cmake
find_package(gRPC REQUIRED)
find_package(elkcpp CONFIG REQUIRED)
target_link_libraries($YOUR_TARGET elkcpp::elkcpp)
```

If you don't have gRPC available in your system, you can make it available through vcpkg:
  * Copy the file `vcpkg.json` of this project to your project folder (or, if you already have vcpkg, add the grpc dependency listed there)
  * Add vcpkg as a submodule:
```console
$ git submodule add https://github.com/Microsoft/vcpkg.git third-party/vcpkg
```
  * Bootstrap vcpkg in your project directory:
```console
$ ./third-party/vcpkg/bootstrap-vcpkg.sh
```
  * Pass the option `-DCMAKE_TOOLCHAIN_FILE=../third-party/vcpkg/scripts/buildsystems/vcpkg.cmake` when configuring your project

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

## License
elkcpp is licensed under the GNU General Public License v3 (“GPLv3”). Commercial licenses are available on request at tech@elk.audio.

Copyright 2017-2022 Modern Ancient Instruments Networked AB, dba Elk, Stockholm, Sweden.

