#!/usr/bin/env bash

# Compiles mtl tests for all compilers in debug and release for Linux.
# This script requires you have g++, clang, libc++, ninja and CMake installed.
# If clang-tidy is installed it will be used to check the code for errors.

# check that we are in the utilities folder
if ! [[ $PWD == *"utilities" ]]; then
    echo "Script not executed from utilities folder. Exiting..."
    exit 1
fi

#get to the tests folder
cd ..
cd tests

# check we are in the tests folder
if ! [[ $PWD == *"tests" ]]; then
    echo "Script couldn't find the tests folder. Exiting..."
    exit 1
fi

echo ""
echo "[Compiling tests for all compilers on Linux.]"
echo ""

echo ""
echo "[Compiling CMake - g++ - debug build.]"
mkdir -p build-gcc-debug
cd build-gcc-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build .
cd ..

echo ""
echo "[Compiling CMake - clang++ - debug build.]"
mkdir -p build-clang-debug
cd build-clang-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build .
cd ..

echo ""
echo "[Compiling CMake - clang++ using libc++ - debug build.]"
mkdir -p build-clang-wlibcpp-debug
cd build-clang-wlibcpp-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DENABLE_LIBCXX=ON
cmake --build .
cd ..



echo ""
echo "[Compiling CMake - g++ - release build.]"
mkdir -p build-gcc-release
cd build-gcc-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON  -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..

echo ""
echo "[Compiling CMake - clang++ - release build.]"
mkdir -p build-clang-release
cd build-clang-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..

echo ""
echo "[Compiling CMake - clang++ using libc++ - release build.]"
mkdir -p build-clang-wlibcpp-release
cd build-clang-wlibcpp-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DENABLE_LIBCXX=ON -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..

echo ""
echo "[Compiling CMake - clang-tidy.]"
mkdir -p build-clang-tidy
cd build-clang-tidy
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DENABLE_CLANG_TIDY=ON
cmake --build .
cd ..


# return to the folder we started from
cd ..
cd utilities
echo ""
echo "[Done compiling tests.]"