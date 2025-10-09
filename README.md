Github-CI:<br>
[![Build Status][amd64_linux_status]][amd64_linux_link]
[![Build Status][amd64_macos_status]][amd64_macos_link]
[![Build Status][arm64_macos_status]][arm64_macos_link]
[![Build Status][amd64_windows_status]][amd64_windows_link]<br>

[![Build Status][amd64_docker_status]][amd64_docker_link]
[![Build Status][arm64_docker_status]][arm64_docker_link]
[![Build Status][riscv64_docker_status]][riscv64_docker_link]<br>

[amd64_linux_status]: ./../../actions/workflows/amd64_linux_cmake.yml/badge.svg
[amd64_linux_link]: ./../../actions/workflows/amd64_linux_cmake.yml
[amd64_macos_status]: ./../../actions/workflows/amd64_macos_cmake.yml/badge.svg
[amd64_macos_link]: ./../../actions/workflows/amd64_macos_cmake.yml
[arm64_macos_status]: ./../../actions/workflows/arm64_macos_cmake.yml/badge.svg
[arm64_macos_link]: ./../../actions/workflows/arm64_macos_cmake.yml
[amd64_windows_status]: ./../../actions/workflows/amd64_windows_cmake.yml/badge.svg
[amd64_windows_link]: ./../../actions/workflows/amd64_windows_cmake.yml

[amd64_docker_status]: ./../../actions/workflows/amd64_docker_cmake.yml/badge.svg
[amd64_docker_link]: ./../../actions/workflows/amd64_docker_cmake.yml
[arm64_docker_status]: ./../../actions/workflows/arm64_docker_cmake.yml/badge.svg
[arm64_docker_link]: ./../../actions/workflows/arm64_docker_cmake.yml
[riscv64_docker_status]: ./../../actions/workflows/riscv64_docker_cmake.yml/badge.svg
[riscv64_docker_link]: ./../../actions/workflows/riscv64_docker_cmake.yml

# Introduction

<nav for="project"> |
<a href="#requirement">Requirement</a> |
<a href="#codemap">Codemap</a> |
<a href="#dependencies">Dependencies</a> |
<a href="#build">Build</a> |
<a href="ci/README.md">CI</a> |
<a href="#appendices">Appendices</a> |
<a href="#contributing">Contributing</a> |
<a href="#license">License</a> |
</nav>

This is an example of how to create a Modern [CMake](https://cmake.org/) C++ Project using
 [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) module to include dependency(ies) as subproject(s).

This project should run on GNU/Linux, MacOS and Windows.

## Requirement

You'll need:

* "CMake >= 3.24".

## Codemap

The project layout is as follow:

* [CMakeLists.txt](CMakeLists.txt) Top-level for [CMake](https://cmake.org/cmake/help/latest/) based build.
* [cmake](cmake) Subsidiary CMake files.

* [ci](ci) Root directory for continuous integration.

* [Foo](Foo) Root directory for `Foo` library.
  * [CMakeLists.txt](Foo/CMakeLists.txt) for `Foo`.
  * [include](Foo/include) public folder.
    * [foo](Foo/include/foo)
      * [Foo.hpp](Foo/include/foo/Foo.hpp)
  * [src](Foo/src) private folder.
    * [src/Foo.cpp](Foo/src/Foo.cpp)
* [Bar](Bar) Root directory for `Bar` library.
  * [CMakeLists.txt](Bar/CMakeLists.txt) for `Bar`.
  * [include](Bar/include) public folder.
    * [bar](Bar/include/bar)
      * [Bar.hpp](Bar/include/bar/Bar.hpp)
  * [src](Bar/src) private folder.
    * [src/Bar.cpp](Bar/src/Bar.cpp)
* [FooApp](FooApp) Root directory for `FooApp` executable.
  * [CMakeLists.txt](FooApp/CMakeLists.txt) for `FooApp`.
  * [src](FooApp/src) private folder.
    * [src/main.cpp](FooApp/src/main.cpp)

## Dependencies

To complexify a little, the CMake project is composed of three libraries (Foo, Bar and FooBar)
with the following dependencies:

```sh
Foo:
Bar:
FooApp: PUBLIC Foo PRIVATE Bar
```

note: Since `Foo` is a public dependency of `FooBar`, then `FooBarApp` will
*see* `Foo` inlude directories

## Build

To build the C++ project, as usual:

```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --config Release --target test
```
## Build directory layout

Since we want to use the [CMAKE_BINARY_DIR](https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html) to generate the binary package.  
We want this layout (tree build --prune -P "*.so|FooApp"):

```
build
├── bin
│   └── FooApp
└── lib
    └── lib*.so
```

## Appendices

Few links on the subject...

### Resources

Project layout:
* [The Pitchfork Layout Revision 1 (cxx-pflR1)](https://github.com/vector-of-bool/pitchfork)

CMake:
* https://llvm.org/docs/CMakePrimer.html
* https://cliutils.gitlab.io/modern-cmake/
* https://cgold.readthedocs.io/en/latest/

# Contributing

The [CONTRIBUTING.md](./CONTRIBUTING.md) file contains instructions on how to
file the Contributor License Agreement before sending any pull requests (PRs).
Of course, if you're new to the project, it's usually best to discuss any
proposals and reach consensus before sending your first PR.

## License

Apache 2. See the LICENSE file for details.

## Disclaimer

This is not an official Google product, it is just code that happens to be
owned by Google.

