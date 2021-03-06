if(DEFINED rev)
  set(revision "-r${rev}")
endif(DEFINED rev)

find_package(Subversion REQUIRED)

if(EXISTS ${path}/clang)
  message(STATUS "Updating clang repository")
  execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${path}/clang ${Subversion_SVN_EXECUTABLE} up ${revision})
else()
  message(STATUS "Checking out clang repository")
  execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${path} ${Subversion_SVN_EXECUTABLE} co ${revision} http://llvm.org/svn/llvm-project/cfe/trunk clang)
endif(EXISTS ${path}/clang)
