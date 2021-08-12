#!/usr/bin/env bash

# Runs clang-analyzer to check mtl for bugs.
#
# You must have clang, clang-tools, CMake and make installed for this script to work.
# On Ubuntu Linux :
# sudo apt install clang clang-tools cmake make






# delete the build directory if it exists
rm -rf build-clang-analyzer
# create the build directory
mkdir build-clang-analyzer
cd build-clang-analyzer


# the scan-build command line utility allows us to setup and run the clang analyzer

echo "Configuring clang analyzer..."
# use scan-build to run CMake, set clang as the compiler
scan-build --use-cc=clang --use-c++=clang++ cmake ../../tests/ -DENABLE_CONSOLE_TESTS=ON

echo ""
echo "Running clang analyzer..."
# use scan-build to build with make, make will use all cores, set clang as the compiler
scan-build --use-cc=clang --use-c++=clang++ make -j$(nproc)

# delete the build directory
cd ..
rm -rf build-clang-analyzer
