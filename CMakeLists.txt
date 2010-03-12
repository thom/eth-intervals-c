# Require cmake >= 2.8
cmake_minimum_required(VERSION 2.8)

# Set search path for cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Disallow in-source build
# TODO: Is there a reason to disallow in-source builds?
include(EnsureOutOfSourceBuild)
ensure_out_of_source_build()

# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take
# their definition and dump it in the cache along with proper
# documentation, otherwise set CMAKE_BUILD_TYPE to Debug prior to
# calling PROJECT()
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug
Release RelWithDebInfo MinSizeRel.")
else()
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build,
options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release
RelWithDebInfo MinSizeRel.")
endif()

# Compiler configuration
# TODO: Make path to clang configurable
set(CMAKE_C_COMPILER "/usr/local/bin/clang")

# Project name and language
project(Intervals C)

# Flags
set(CMAKE_C_FLAGS "-fblocks")
set(CMAKE_C_FLAGS_DEBUG "-DNDEBUG")

# Install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
    # TODO: Make this configurable
    "/home/thom/tmp" CACHE PATH "Intervals install prefix" FORCE
    )
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH
  "Single directory for all executables.")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single
  directory for all libraries.")

# Threads are required
# Sets CMAKE_THREAD_LIBS_INIT
find_package(Threads REQUIRED)

# BlocksRuntime is required
find_package(BlocksRuntime REQUIRED)

# Process subdirectories
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)

# Add uninstall support
CONFIGURE_FILE(
  "${CMAKE_MODULE_PATH}/Uninstall.cmake.in"
  "${CMAKE_MODULE_PATH}/Uninstall.cmake" @ONLY
  )
ADD_CUSTOM_TARGET(
  uninstall "${CMAKE_COMMAND}" -P
  "${CMAKE_MODULE_PATH}/Uninstall.cmake"
)