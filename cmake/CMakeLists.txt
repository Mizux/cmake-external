set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Backup the value of CMAKE_SKIP_INSTALL_RULES
set(_SKIP_INSTALL ${CMAKE_SKIP_INSTALL_RULES})
# TODO Keep install rules of dependencies (and adapt them if needed)
set(CMAKE_SKIP_INSTALL_RULES TRUE)

##############
##  GFLAGS  ##
##############
message(STATUS "Subproject: Gflag...")
# Download and unpack gflags at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/gflags.CMakeLists.txt
	${CMAKE_BINARY_DIR}/gflags-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download)
if(result)
  message(FATAL_ERROR "CMake step for gflags failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download)
if(result)
  message(FATAL_ERROR "Build step for gflags failed: ${result}")
endif()

set(GFLAGS_NAMESPACE "gflags" CACHE INTERNAL "Namespace for gflags")
#set(GFLAGS_IS_SUBPROJECT TRUE)
add_subdirectory(
	${CMAKE_BINARY_DIR}/gflags-src
	${CMAKE_BINARY_DIR}/gflags-build
	EXCLUDE_FROM_ALL)
message(STATUS "Subproject: Gflag...DONE")

############
##  GLOG  ##
############
message(STATUS "Subproject: Glog...")
# Download and unpack glog at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/glog.CMakeLists.txt
	${CMAKE_BINARY_DIR}/glog-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glog-download)
if(result)
  message(FATAL_ERROR "CMake step for glog failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glog-download)
if(result)
  message(FATAL_ERROR "Build step for glog failed: ${result}")
endif()

set(gflags_NAMESPACE "gflags" CACHE INTERNAL "Namespace for gflags")
add_subdirectory(
	${CMAKE_BINARY_DIR}/glog-src
	${CMAKE_BINARY_DIR}/glog-build
	EXCLUDE_FROM_ALL)
message(STATUS "Subproject: Glog...DONE")

############
##  ZLIB  ##
############
message(STATUS "Subproject: ZLIB...")
# Download and unpack zlib at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/zlib.CMakeLists.txt
	${CMAKE_BINARY_DIR}/zlib-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/zlib-download)
if(result)
  message(FATAL_ERROR "CMake step for zlib failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/zlib-download)
if(result)
  message(FATAL_ERROR "Build step for zlib failed: ${result}")
endif()

add_subdirectory(
	${CMAKE_BINARY_DIR}/zlib-src
	${CMAKE_BINARY_DIR}/zlib-build
	EXCLUDE_FROM_ALL)
message(STATUS "Subproject: ZLIB...DONE")

################
##  PROTOBUF  ##
################
message(STATUS "Subproject: Protobuf...")
# Download and unpack protobuf at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/protobuf.CMakeLists.txt
	${CMAKE_BINARY_DIR}/protobuf-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/protobuf-download )
if(result)
  message(FATAL_ERROR "CMake step for protobuf failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/protobuf-download )
if(result)
  message(FATAL_ERROR "Build step for protobuf failed: ${result}")
endif()

set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "Disable Protobuf tests")
add_subdirectory(
	${CMAKE_BINARY_DIR}/protobuf-src/cmake
	${CMAKE_BINARY_DIR}/protobuf-build
	EXCLUDE_FROM_ALL)
message(STATUS "Subproject: Protobuf...DONE")

set(CMAKE_SKIP_INSTALL_RULES ${_SKIP_INSTALL})
