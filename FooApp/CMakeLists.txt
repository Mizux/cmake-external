add_executable(FooApp)
get_cpp_proto(PROTO_HDRS PROTO_SRCS)
target_sources(FooApp PRIVATE
  src/main.cpp
  ${PROTO_HDRS} ${PROTO_SRCS})
target_include_directories(FooApp PRIVATE
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_compile_features(FooApp PRIVATE cxx_std_17)
set_target_properties(FooApp PROPERTIES
  VERSION ${PROJECT_VERSION})
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(FooApp PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX)
  set_target_properties(FooApp PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_link_libraries(FooApp PRIVATE
  absl::flags
  absl::flags_parse
  absl::log
  absl::strings
  protobuf::libprotobuf
  CMakeExternal::Foo
)

add_executable(${PROJECT_NAMESPACE}::FooApp ALIAS FooApp)

if(BUILD_TESTING)
  add_test(NAME cpp_FooApp_test COMMAND FooApp)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS FooApp
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
