# - Try to find BlocksRuntime
# Once done, this will define
#
#  BlocksRuntime_FOUND - system has BlocksRuntime
#  BlocksRuntime_INCLUDE_DIRS - the BlocksRuntime include directories
#  BlocksRuntime_LIBRARIES - link these to use BlocksRuntime

include(LibFindMacros)

# Include dir
find_path(BlocksRuntime_INCLUDE_DIR
  NAMES Block.h Block_private.h
  # TODO: Set path according to install prefix
  PATHS /usr/include /usr/local/include
  )

# Finally the library itself
find_library(BlocksRuntime_LIBRARY
  NAMES BlocksRuntime
  # TODO: Set path according to install prefix
  PATHS /usr/include /usr/local/include
  )

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(BlocksRuntime_PROCESS_INCLUDES BlocksRuntime_INCLUDE_DIR)
set(BlocksRuntime_PROCESS_LIBS BlocksRuntime_LIBRARY)
libfind_process(BlocksRuntime)