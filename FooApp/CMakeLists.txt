project(FooApp VERSION 1.0.0 LANGUAGES CXX)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${PROJECT_NAME} ${_SRCS})
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
target_link_libraries(${PROJECT_NAME} PRIVATE
	gflags
	zlibstatic)
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
