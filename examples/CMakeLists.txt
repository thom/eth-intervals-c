# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Examples are all compiled the same way
set(PROGRAMS playground nqueens fibonacci forkjoin arraytest hb)

# Set core libraries used to compile examples
set(CORELIBS ${CMAKE_THREAD_LIBS_INIT} ${BlocksRuntime_LIBRARIES} intervals)

# Build examples
foreach(program ${PROGRAMS})
  add_executable(${program} ${program}.c)
  target_link_libraries(${program} ${CORELIBS})
  install(TARGETS ${program} DESTINATION bin)
endforeach(program)
