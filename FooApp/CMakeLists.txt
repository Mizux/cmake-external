cmake_minimum_required(VERSION 3.8.2)
project(FooApp VERSION 1.0.0 LANGUAGES CXX)

file(GLOB _SRCS "src/*.[hc]pp")

find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Foo REQUIRED)

# Generate Protobuf cpp sources from .proto file(s)
set(PROTO_HDRS)
set(PROTO_SRCS)
file(GLOB_RECURSE proto_files RELATIVE ${PROJECT_SOURCE_DIR} "*.proto")
foreach (PROTO_FILE ${proto_files})
	#message(STATUS "protoc proto: ${PROTO_FILE}")
	get_filename_component(PROTO_DIR ${PROTO_FILE} DIRECTORY)
	get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
	set(PROTO_HDR ${PROJECT_BINARY_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.h)
	set(PROTO_SRC ${PROJECT_BINARY_DIR}/${PROTO_DIR}/${PROTO_NAME}.pb.cc)
	message(STATUS "protoc hdr: ${PROTO_HDR}")
	message(STATUS "protoc src: ${PROTO_SRC}")
	add_custom_command(
		OUTPUT ${PROTO_SRC} ${PROTO_HDR}
		COMMAND protobuf::protoc
		"--proto_path=${PROJECT_SOURCE_DIR}"
		"--cpp_out=${PROJECT_BINARY_DIR}"
		${PROTO_FILE}
		DEPENDS ${PROTO_FILE} protobuf::protoc
		COMMENT "Running C++ protocol buffer compiler on ${PROTO_FILE}"
		VERBATIM)
	list(APPEND PROTO_HDRS ${PROTO_HDR})
	list(APPEND PROTO_SRCS ${PROTO_SRC})
endforeach()

add_executable(${PROJECT_NAME} ${_SRCS} ${PROTO_HDR} ${PROTO_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
	)
target_link_libraries(${PROJECT_NAME} PRIVATE
	gflags::gflags
	glog::glog
	ZLIB::ZLIB
	protobuf::libprotobuf
  Foo::Foo
	)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
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
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
