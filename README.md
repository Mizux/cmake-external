Github-CI:<br>
[![Build Status][github_linux_status]][github_linux_link]
[![Build Status][github_macos_status]][github_macos_link]
[![Build Status][github_windows_status]][github_windows_link]

[github_linux_status]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_linux.yml/badge.svg
[github_linux_link]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_linux.yml
[github_macos_status]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_macos.yml/badge.svg
[github_macos_link]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_macos.yml
[github_windows_status]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_windows.yml/badge.svg
[github_windows_link]: https://github.com/Mizux/cmake-external/actions/workflows/amd64_windows.yml

# Introduction

This is an example of how to create a Modern [CMake](https://cmake.org/) C++ Project using
 [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html) module to include dependency(ies) as subproject(s).

This project should run on Linux, Mac and Windows.

# CMake Dependencies Tree
To complexify a little, the CMake project is composed of one executable (FooApp)
with the following dependencies:  
```sh
gflags:
glog: gflags
zlib:
protobuf: zlib
FooApp: gflags glog zlib protobuf
```
note 1: All dependencies are built in static to have one standalone executable `FooApp`.  
note 2: glog, zlib, protobuf need patches to be use as subproject.
## Project directory layout
Thus the project layout is as follow:
```
 CMakeLists.txt // meta CMake doing the orchestration and python packaging
 cmake
 ├── CMakeLists.txt
 ├── gflags.CMakeLists.txt
 ├── glog.CMakeLists.txt
 ├── zlib.CMakeLists.txt
 ├── protobuf.CMakeLists.txt
 patches
 ├── glog.patch
 ├── zlib.patch
 ├── protobuf.patch
 FooApp
 ├── CMakeLists.txt
 └── src
     └── main.cpp
```

# C++ Project Build
To build the C++ project, as usual:
```sh
cmake -H. -Bbuild
cmake --build build
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --target test
```
## Build directory layout
Since we want to use the [CMAKE_BINARY_DIR](https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html) to generate the binary package.  
We want this layout (tree build --prune -P "*.a|FooApp"):
```
build
├── gflags-build
│   └── libgflags_nothreads.a
├── glog-build
│   └── libglog.a
├── zlib-build
│   └── libz.a
├── protobuf-build
│   └── libprotobuf.a
└── FooApp
   └── FooApp
```

# Contributing

The [CONTRIBUTING.md](./CONTRIBUTING.md) file contains instructions on how to
file the Contributor License Agreement before sending any pull requests (PRs).
Of course, if you're new to the project, it's usually best to discuss any
proposals and reach consensus before sending your first PR.

# License

Apache 2. See the LICENSE file for details.

# Disclaimer

This is not an official Google product, it is just code that happens to be
owned by Google.
