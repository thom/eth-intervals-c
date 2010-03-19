# Require cmake >= 2.8
cmake_minimum_required(VERSION 2.8)

# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take
# their definition, otherwise set CMAKE_BUILD_TYPE to Debug prior to
# calling PROJECT()
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel.")
endif(NOT CMAKE_BUILD_TYPE)

# Local directory
set(LOCAL_DIR ${CMAKE_SOURCE_DIR}/local CACHE STRING
  "Local build directory for external projects")

# LLVM install prefix
set(LLVM_INSTALL_PREFIX ${LOCAL_DIR} CACHE STRING
  "Installation prefix of LLVM")

# Compiler configuration
if(EXISTS ${LLVM_INSTALL_PREFIX}/bin/clang)
  set(CMAKE_C_COMPILER "${LLVM_INSTALL_PREFIX}/bin/clang")
else()
  message(WARNING
    "clang (${LLVM_INSTALL_PREFIX}/bin/clang) not found!
    Build and install LLVM first: make llvm compiler-rt or 
    set LLVM_INSTALL_PREFIX to where you installed it"
    )
endif(EXISTS ${LLVM_INSTALL_PREFIX}/bin/clang)

# Project name and language
project(Intervals C)

# Set search path for cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Threads are required
# Sets CMAKE_THREAD_LIBS_INIT
find_package(Threads REQUIRED)

# BlocksRuntime is required but we can't use REQUIRED here as it
# wouldn't allow us to install it if it's not already installed
find_package(BlocksRuntime)
if(NOT BlocksRuntime_FOUND)
  message(WARNING
  "BlocksRuntime not found!
  Build and install compiler-rt first: make compiler-rt"
  )
endif(NOT BlocksRuntime_FOUND)

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DNDEBUG")

# Disallow in-source build
include(EnsureOutOfSourceBuild)
ensure_out_of_source_build()

# Install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
    ${CMAKE_SOURCE_DIR}/local CACHE PATH "Intervals install prefix" FORCE
    )
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH
  "Single directory for all executables.")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE PATH "Single
  directory for all libraries.")

# Process subdirectories
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(examples)

# Support for Doxygen
include(UseDoxygen OPTIONAL)

# Add uninstall support
configure_file(
  "${CMAKE_MODULE_PATH}/Uninstall.cmake.in"
  "${CMAKE_MODULE_PATH}/Uninstall.cmake" @ONLY
  )
add_custom_target(
  uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/Uninstall.cmake" 
  )

# External projects: LLVM (including clang) and compiler-rt
include(ExternalProject)

# Download, build and install compiler-rt
ExternalProject_Add(compiler-rt OFF
  PREFIX ${LOCAL_DIR}
  SVN_REPOSITORY http://llvm.org/svn/llvm-project/compiler-rt/trunk
  # SVN_REVISION rev
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_PREFIX}
  BUILD_COMMAND ""
  INSTALL_COMMAND make install
  )

# Download, build and install LLVM including clang
ExternalProject_Add(llvm OFF
  # DEPENDS compiler-rt
  PREFIX ${LOCAL_DIR}
  SVN_REPOSITORY http://llvm.org/svn/llvm-project/llvm/trunk
  # SVN_REVISION rev
  CMAKE_ARGS -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_PREFIX}
  BUILD_COMMAND ""
  INSTALL_COMMAND make install
  )

# Extra step to checkout and update the clang source in the LLVM tools
# directory
ExternalProject_Add_Step(llvm clang
  # -Drev=98400: SVN revision
  COMMAND ${CMAKE_COMMAND} -Dpath=${LOCAL_DIR}/src/llvm/tools -P "${CMAKE_MODULE_PATH}/Clang.cmake"
  COMMENT "Clang"
  DEPENDEES download update
  DEPENDERS configure build install
  ALWAYS 1
  )
