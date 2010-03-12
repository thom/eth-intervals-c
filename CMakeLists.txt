# Require cmake >= 2.8
cmake_minimum_required(VERSION 2.8)

# Set search path for cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Disallow in-source build
# TODO: Is there a reason to disallow in-source builds?
#include(MacroEnsureOutOfSourceBuild)
#MACRO_ENSURE_OUT_OF_SOURCE_BUILD()

# Compiler configuration
# TODO: Make path to clang configurable
set(CMAKE_C_COMPILER "/usr/local/bin/clang")

# Project name and language
project(Intervals C)

# Flags
set(CMAKE_C_FLAGS "-fblocks")
set(CMAKE_C_FLAGS_DEBUG "-DNDEBUG")

# Process subdirectories
add_subdirectory(include)

# Add uninstall support
CONFIGURE_FILE(
  "${CMAKE_MODULE_PATH}/Uninstall.cmake.in"
  "${CMAKE_MODULE_PATH}/Uninstall.cmake" @ONLY
  )
ADD_CUSTOM_TARGET(
  uninstall "${CMAKE_COMMAND}" -P
  "${CMAKE_MODULE_PATH}/Uninstall.cmake"
)