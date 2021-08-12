#!/usr/bin/env bash

# Runs clang-analyzer to check mtl for bugs.
#
# You must have clang and clang-tools installed for this script to work.
# On Ubuntu Linux :
# sudo apt install clang clang-tools





# delete the generated executable if it existed
rm -f tests
echo "Running clang analyzer..."
# run clang-analyzer using the scan-build command line utility
scan-build --exclude ../mtl/fmt/ clang++ -o tests -std=c++17 ../tests/*.cpp
# delete the generated executable
rm -f tests
