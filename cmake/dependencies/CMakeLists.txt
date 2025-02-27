include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_TESTING OFF)
set(CMAKE_Fortran_COMPILER OFF)

# ##############################################################################
# ZLIB
# ##############################################################################
if(BUILD_ZLIB)
  message(CHECK_START "Fetching ZLIB")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(ZLIB_BUILD_EXAMPLES OFF)
  FetchContent_Declare(
    ZLIB
    GIT_REPOSITORY "https://github.com/madler/ZLIB.git"
    GIT_TAG "v1.3.1"
    PATCH_COMMAND git apply --ignore-whitespace
    "${CMAKE_CURRENT_LIST_DIR}/../../patches/ZLIB-v1.3.1.patch")
  FetchContent_MakeAvailable(ZLIB)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# ABSEIL-CPP
# ##############################################################################
if(BUILD_absl)
  message(CHECK_START "Fetching Abseil-cpp")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(ABSL_USE_SYSTEM_INCLUDES ON)
  # We want Abseil to declare what C++ standard it was compiled with.
  set(ABSL_PROPAGATE_CXX_STD ON)
  # We want Abseil to keep the INSTALL rules enabled, even though it is a
  # subproject. Otherwise the install rules in this project break.
  set(ABSL_ENABLE_INSTALL ON)
  set(ABSL_BUILD_TESTING OFF)
  FetchContent_Declare(
    absl
    GIT_REPOSITORY "https://github.com/abseil/abseil-cpp.git"
    GIT_TAG "20240722.0"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace
    "${CMAKE_CURRENT_LIST_DIR}/../../patches/abseil-cpp-20240722.0.patch"
    OVERRIDE_FIND_PACKAGE)
  FetchContent_MakeAvailable(absl)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# Protobuf
# ##############################################################################
if(BUILD_Protobuf)
  message(CHECK_START "Fetching Protobuf")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(protobuf_BUILD_TESTS OFF)
  set(protobuf_BUILD_SHARED_LIBS ON)
  set(protobuf_BUILD_EXPORT OFF)
  set(protobuf_MSVC_STATIC_RUNTIME OFF)
  #set(protobuf_BUILD_LIBUPB ON)
  FetchContent_Declare(
    Protobuf
    GIT_REPOSITORY "https://github.com/protocolbuffers/protobuf.git"
    GIT_TAG "v29.3"
    GIT_SHALLOW TRUE
    GIT_SUBMODULES ""
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/protobuf-v29.3.patch"
  )
  FetchContent_MakeAvailable(Protobuf)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# RE2
# ##############################################################################
if(BUILD_re2)
  message(CHECK_START "Fetching re2")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  set(RE2_BUILD_TESTING OFF)
  FetchContent_Declare(
    re2
    GIT_REPOSITORY "https://github.com/google/re2.git"
    GIT_TAG "2024-04-01"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/re2-2024-04-01.patch"
  )
  FetchContent_MakeAvailable(re2)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# BOOST
# ##############################################################################
if(BUILD_Boost)
  message(CHECK_START "Fetching Boost")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    Boost
    URL
    https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.gz
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_NO_EXTRACT FALSE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/boost-1.87.0.patch"
  )
  set(BOOST_INCLUDE_LIBRARIES multiprecision serialization)
  option(BOOST_SKIP_INSTALL_RULES NO)
  set(BOOST_ENABLE_CMAKE ON)
  FetchContent_MakeAvailable(Boost)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# SOPLEX
# ##############################################################################
if(BUILD_soplex)
  message(CHECK_START "Fetching SOPLEX")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    soplex
    GIT_REPOSITORY "https://github.com/scipopt/soplex.git"
    GIT_TAG        "release-713"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/soplex-v7.1.3.patch"
  )
  set(SHARED OFF)
  set(ZLIB ON CACHE BOOL "Soplex param" FORCE)
  set(GMP OFF CACHE BOOL "Soplex param" FORCE)
  set(PAPILO OFF CACHE BOOL "Soplex param" FORCE)
  set(BOOST ON CACHE BOOL "Soplex param" FORCE)
  set(QUADMATH  OFF CACHE BOOL "Soplex param" FORCE)
  set(MPFR OFF CACHE BOOL "Soplex param" FORCE)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "Soplex param" FORCE)
  set(Boost_INCLUDE_DIR "../boost-src/libs/config/include" CACHE PATH "Soplex param" FORCE)
  FetchContent_MakeAvailable(SOPLEX)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# SCIP
# ##############################################################################
if(BUILD_scip)
  message(CHECK_START "Fetching SCIP")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    scip
    GIT_REPOSITORY "https://github.com/scipopt/scip.git"
    GIT_TAG        "v921"
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/../../patches/scip-v921.patch"
  )
  set(SHARED OFF)
  set(READLINE OFF)
  set(GMP OFF)
  set(PAPILO OFF)
  set(ZIMPL OFF)
  set(IPOPT OFF)
  set(AMPL OFF)

  set(TPI "tny" CACHE STRING "Scip param")
  set(EXPRINT "none" CACHE STRING "Scip param")
  set(LPS "spx" CACHE STRING "Scip param")
  set(SYM "none" CACHE STRING "Scip param")
  FetchContent_MakeAvailable(scip)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

###############
##  TESTING  ##
###############
if(BUILD_Catch2)
  message(CHECK_START "Fetching Catch2")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG devel
    GIT_SHALLOW TRUE
    FIND_PACKAGE_ARGS)
  FetchContent_MakeAvailable(Catch2)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

if(BUILD_googletest)
  message(CHECK_START "Fetching googletest")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
    PATCH_COMMAND git apply --ignore-whitespace
    "${CMAKE_CURRENT_LIST_DIR}/../../patches/googletest-v1.15.2.patch"
    #FIND_PACKAGE_ARGS NAMES GTest GMock
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(INSTALL_GTEST OFF)
  set(GTEST_HAS_ABSL ON)
  FetchContent_MakeAvailable(googletest)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

if(BUILD_benchmark)
  message(CHECK_START "Fetching benchmark")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")
  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.1
    GIT_SHALLOW TRUE
    #PATCH_COMMAND git apply --ignore-whitespace ""
  )
  set(BENCHMARK_ENABLE_TESTING OFF)
  set(BENCHMARK_ENABLE_WERROR OFF)
  set(BENCHMARK_ENABLE_INSTALL OFF)
  FetchContent_MakeAvailable(benchmark)
  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()
