# This file is just an orchestration
cmake_minimum_required(VERSION 3.8.2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Force default build type to Release
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
	"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.")

# Use find_package everywhere, no-op if it's a target
macro(find_package)
	if(NOT TARGET ${ARGV0} AND NOT TARGET ${ARGV0}::${ARGV0})
		_find_package(${ARGV})
	else()
		if(TARGET ${ARGV0}::${ARGV0})
			get_target_property(TGT_VER ${ARGV0}::${ARGV0} VERSION)
			set(TGT ${ARGV0}::${ARGV0})
		else()
			get_target_property(TGT_VER ${ARGV0} VERSION)
			set(TGT ${ARGV0})
		endif()
		message(STATUS "Found ${ARGV0}: CMake Target ${TGT} (found version \"${TGT_VER}\")")
		set(${ARGV0}_FOUND TRUE)
	endif()
endmacro()

# Apple: Don't modify install_name when touching RPATH.
if(POLICY CMP0068)
	cmake_policy(SET CMP0068 NEW)
endif()

project(meta VERSION 1.0 LANGUAGES NONE)

include(CTest)
include(GNUInstallDirs)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries(.so)." ON)
else()
	# only support for static build on Windows.
	set(BUILD_SHARED_LIBS OFF)
endif()

# Build Dependencies
add_subdirectory(cmake)

add_subdirectory(Foo)
add_subdirectory(FooApp)

add_subdirectory(Bar)

# Install
install(EXPORT SampleTargets
	NAMESPACE Sample::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Sample
	COMPONENT Devel)
include(CMakePackageConfigHelpers)
configure_package_config_file(SampleConfig.cmake.in
	"${PROJECT_BINARY_DIR}/SampleConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Sample"
	NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/SampleConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
	"${PROJECT_BINARY_DIR}/SampleConfig.cmake"
	"${PROJECT_BINARY_DIR}/SampleConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Sample"
	COMPONENT Devel)
