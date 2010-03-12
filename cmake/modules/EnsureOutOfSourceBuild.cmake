# ensure_out_of_source_build
macro(ensure_out_of_source_build)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" _insource)
if(_insource)
 message(FATAL_ERROR
 "In-source builds are not allowed.
 Please create a directory and run cmake from there, passing the path
 to this source directory as the last argument.
 This process created the file `CMakeCache.txt' and the directory `CMakeFiles'.
 Please delete them."
 )
endif(_insource)

endmacro(ensure_out_of_source_build)
