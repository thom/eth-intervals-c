# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build library
add_library(intervals interval.c thread_pool.c)

# Install library in lib
install (TARGETS intervals DESTINATION lib)