cmake_minimum_required(VERSION 3.16)
project(Sample VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
find_package(CMakeExternal CONFIG REQUIRED)

add_executable(sample)
target_sources(sample PRIVATE
  main.cpp)
target_compile_features(sample PUBLIC cxx_std_17)
set_target_properties(sample PROPERTIES
  VERSION ${PROJECT_VERSION})
target_link_libraries(sample PRIVATE
  absl::flags_parse
  absl::log
  absl::log_initialize
  absl::strings
  CMakeExternal::Foo
  CMakeExternal::Bar
)

if(BUILD_TESTING)
  add_test(NAME sample_UT COMMAND sample)
endif()

# Install
include(GNUInstallDirs)
install(TARGETS sample
  EXPORT SampleTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
