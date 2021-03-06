# Implementation of Intervals for C

## Build instructions

```
$ git clone git://github.com/thom/eth-intervals-c.git
$ mkdir build
$ cd build
$ cmake ../
$ make
$ make doc
$ make install
```

Intervals uses [C blocks](http://thirdcog.eu/pwcblocks/) and therefore
clang to compile. The CMake file can build and install the needed
compiler and libraries:

```
$ make compiler-rt llvm
```

This fetches, builds and installs compiler-rt and LLVM including
clang.

By default, compiler-rt and LLVM are fetched to and built in

```
${CMAKE_SOURCE_DIR}/local
```

You can configure this by specifying the CMake option

```
-D LOCAL_DIR=/path/to/local/dir
```

LLVM and compiler-rt will be installed into

```
${CMAKE_SOURCE_DIR}/local
```

Use the CMake option

```
-D LLVM_INSTALL_PREFIX=/path/to/llvm/installation/dir
```

to change the LLVM installation prefix.

## Note

You also have to set ```LLVM_INSTALL_PREFIX``` if you installed LLVM and
clang on your own in another directory as the CMake scripts will use
```LLVM_INSTALL_PREFIX``` to determine the location of clang and the Blocks
runtime.

Clean your build directory after building LLVM and compiler-rt and run
cmake again:

```
# in build/
$ rm -rf *
$ cmake ../
$ make
```

## License

- **[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)**
- Copyright 2010 © <a href="https://github.com/thom" target="_blank">Thomas Weibel</a>.
