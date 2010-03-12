# Require cmake >= 2.8
cmake_minimum_required(VERSION 2.8)

# Set search path for cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Project name and language
project(Intervals C)

# Process subdirectories
add_subdirectory(include)

# Add uninstall support
CONFIGURE_FILE(
  "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake.in"
  "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake" @ONLY
  )
ADD_CUSTOM_TARGET(
  uninstall "${CMAKE_COMMAND}" -P
  "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake"
)