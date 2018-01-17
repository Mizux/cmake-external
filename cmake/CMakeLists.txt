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

set(CMAKE_SKIP_INSTALL_RULES ${_SKIP_INSTALL})
