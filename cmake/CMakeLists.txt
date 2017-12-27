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
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/zlib-download )
if(result)
  message(FATAL_ERROR "CMake step for zlib failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/zlib-download )
if(result)
  message(FATAL_ERROR "Build step for zlib failed: ${result}")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/zlib ${CMAKE_BINARY_DIR}/zlib)
set_target_properties(zlibstatic PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
	${CMAKE_BINARY_DIR}/zlib)

##############
##  GFLAGS  ##
##############
# Download and unpack gflags at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/gflags.CMakeLists.txt
	${CMAKE_BINARY_DIR}/gflags-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download )
if(result)
  message(FATAL_ERROR "CMake step for gflags failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gflags-download )
if(result)
  message(FATAL_ERROR "Build step for gflags failed: ${result}")
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/gflags ${CMAKE_BINARY_DIR}/gflags)
