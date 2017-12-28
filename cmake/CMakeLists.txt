set(BUILD_SHARED_LIBS OFF)
set(SKIP_INSTALL_ALL ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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

add_subdirectory(${CMAKE_BINARY_DIR}/zlib ${CMAKE_BINARY_DIR}/zlib)
set_target_properties(zlibstatic PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
	${CMAKE_BINARY_DIR}/zlib)
add_library(ZLIB ALIAS zlibstatic)

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

set(BUILD_TESTING OFF)
#set(GFLAGS_IS_SUBPROJECT TRUE)
add_subdirectory(${CMAKE_BINARY_DIR}/gflags ${CMAKE_BINARY_DIR}/gflags)

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

# Do not call find_package for gflags and fill all relevant info manually
# We cannot make glog link to gflags __target__, because cmake would try to
# pull it into glog's export set and will get confused and fail
# Instead we manually specify location and include path for gflags, this way
# cmake does not create inter-target dependency and export set does not fail
set(WITH_GFLAGS "OFF" CACHE "" INTERNAL)
set(HAVE_LIB_GFLAGS "ON")
set(gflags_NAMESPACE "gflags")
set(gflags_FOUND "ON")
get_target_property(gflags_INCLUDE_DIR gflags INTERFACE_INCLUDE_DIRECTORIES)
#get_target_property(gflags_LIBRARIES gflags INTERFACE_LINK_LIBRARIES)
set(gflags_LIBRARIES $<TARGET_FILE:gflags>)
set(BUILD_TESTING OFF)

add_subdirectory(${CMAKE_BINARY_DIR}/glog ${CMAKE_BINARY_DIR}/glog)

# We need to ask CMake to compile gflags before compiling glog, so that
# ${gflags_LIBRARIES} actually exists
add_dependencies(glog gflags)

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

set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "Build Protobuf Shared Libraries" FORCE)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "Build Protobuf tests" FORCE)
# Zlib disable by default on MSVC...
set(protobuf_WITH_ZLIB ON CACHE BOOL "Protobuf with zlib" FORCE)
add_subdirectory(${CMAKE_BINARY_DIR}/protobuf/cmake	${CMAKE_BINARY_DIR}/protobuf)

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
