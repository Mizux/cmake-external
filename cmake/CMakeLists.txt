set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_SKIP_INSTALL_RULES TRUE)
set(SKIP_INSTALL_ALL ON)

##############
##  GFLAGS  ##
##############
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

#set(GFLAGS_IS_SUBPROJECT TRUE)
add_subdirectory(${CMAKE_BINARY_DIR}/gflags-src ${CMAKE_BINARY_DIR}/gflags-build
	EXCLUDE_FROM_ALL)

############
##  GLOG  ##
############
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
add_subdirectory(${CMAKE_BINARY_DIR}/glog-src ${CMAKE_BINARY_DIR}/glog-build
	EXCLUDE_FROM_ALL)

############
##  ZLIB  ##
############
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

################
##  PROTOBUF  ##
################
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

#set(protobuf_BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build Protobuf Shared Libraries")
set(protobuf_BUILD_TESTS OFF CACHE INTERNAL "Build Protobuf tests")
# Zlib disable by default on MSVC...
set(protobuf_WITH_ZLIB ON CACHE INTERNAL "Protobuf with zlib")
add_subdirectory(${CMAKE_BINARY_DIR}/protobuf/cmake	${CMAKE_BINARY_DIR}/protobuf
	EXCLUDE_FROM_ALL)

###############
##  COIN-OR  ##
###############
if(MSVC)
    add_definitions(/bigobj /DNDEBUG /DUSE_GLOP /DUSE_BOP)
else()
    add_definitions(-fwrapv -DNDEBUG -DUSE_GLOP -DUSE_BOP)
endif()

# Find or build Dependencies
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies.txt _Dependency_file)
foreach(DEPENDENCY Cbc CoinUtils Osi Clp Cgl)
    string(REGEX REPLACE ".*${DEPENDENCY} = ([0-9.]+).*" "\\1" ${DEPENDENCY}_VERSION ${_Dependency_file})
endforeach()

#include(Cbc)
