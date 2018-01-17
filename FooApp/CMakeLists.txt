cmake_minimum_required(VERSION 3.8.2)
project(FooApp VERSION 1.0.0 LANGUAGES CXX)

file(GLOB _SRCS "src/*.[hc]pp")

find_package(gflags REQUIRED)
find_package(glog REQUIRED)

add_executable(${PROJECT_NAME} ${_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
	)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
target_link_libraries(${PROJECT_NAME} PRIVATE gflags	glog::glog)
if(UNIX)
	if(NOT APPLE)
		set_target_properties(${PROJECT_NAME} PROPERTIES
			INSTALL_RPATH "$ORIGIN/../lib")
	else()
		set_target_properties(${PROJECT_NAME} PROPERTIES
			INSTALL_RPATH
			"@loader_path/../lib")
	endif()
endif()
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Test
include(CTest)
if(BUILD_TESTING)
	add_test(NAME FooApp_UT COMMAND FooApp)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
install(EXPORT ${PROJECT_NAME}Targets
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	)
