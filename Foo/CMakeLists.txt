cmake_minimum_required(VERSION 3.8.2)
project(Foo VERSION 1.0.0 LANGUAGES CXX)

file(GLOB _HDRS "include/foo/*.hpp" "include/foo/*.hxx")
file(GLOB _SRCS "src/*.[hc]pp")

find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Protobuf REQUIRED)

add_library(${PROJECT_NAME}_obj OBJECT ${_HDRS} ${_SRCS})
target_include_directories(${PROJECT_NAME}_obj PRIVATE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	$<TARGET_PROPERTY:gflags::gflags,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:glog::glog,INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_options(${PROJECT_NAME}_obj PRIVATE
	$<TARGET_PROPERTY:gflags::gflags,INTERFACE_COMPILE_OPTIONS>
	$<TARGET_PROPERTY:glog::glog,INTERFACE_COMPILE_OPTIONS>
	)
target_compile_definitions(${PROJECT_NAME}_obj PRIVATE
	$<TARGET_PROPERTY:gflags::gflags,INTERFACE_COMPILE_DEFINITIONS>
	$<TARGET_PROPERTY:glog::glog,INTERFACE_COMPILE_DEFINITIONS>
	)
target_compile_features(${PROJECT_NAME}_obj PUBLIC cxx_std_11)
# CMakeError: Object library may not link to anything.
#target_link_libraries(${PROJECT_NAME}_obj PUBLIC gflags::gflags glog::glog)

add_library(${PROJECT_NAME} STATIC "")
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	)
target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER ${_HDRS}
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} PUBLIC
	gflags::gflags
	glog::glog
	ZLIB::ZLIB
	protobuf::libprotobuf
	)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Install
install(TARGETS ${PROJECT_NAME}
	EXPORT SampleTargets
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/foo
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	#RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
