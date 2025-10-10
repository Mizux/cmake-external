add_executable(FooApp)
get_cpp_proto(PROTO_HDRS PROTO_SRCS)
target_sources(FooApp
  PRIVATE
    src/main.cpp
    ${PROTO_HDRS} ${PROTO_SRCS})
target_include_directories(FooApp
  PRIVATE
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_compile_features(FooApp PRIVATE cxx_std_17)
if(MSVC AND BUILD_SHARED_LIBS)
  target_compile_definitions(FooApp INTERFACE "PROTO_DLL=__declspec(dllimport)")
  target_compile_definitions(FooApp PRIVATE "PROTO_DLL=__declspec(dllexport)")
 else()
  target_compile_definitions(FooApp PUBLIC "PROTO_DLL=")
endif()
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(FooApp PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX)
  set_target_properties(FooApp PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
set_target_properties(FooApp PROPERTIES
  VERSION ${PROJECT_VERSION})
target_link_libraries(FooApp PRIVATE
  ZLIB::ZLIB
  absl::flags_parse
  absl::log
  absl::log_globals
  absl::log_initialize
  absl::log_severity
  absl::strings
  protobuf::libprotobuf
  CMakeExternal::Foo
  CMakeExternal::Bar
)
add_executable(${PROJECT_NAMESPACE}::FooApp ALIAS FooApp)

# Test
if(BUILD_TESTING)
  add_test(NAME cpp_FooApp_test COMMAND FooApp)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS FooApp
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
