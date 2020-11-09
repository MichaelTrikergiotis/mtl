#!/usr/bin/env bash

# Runs clang analyzer for the mtl library.
#
# You must have clang, clang tools and llvm installed for this script to work.
# On Ubuntu Linux in a terminal type :
# sudo apt install clang clang-tools llvm
#
# You have to give the script executable permission before running it :
# chmod +x check-clang-analyzer.sh
# ./check-clang-analyzer.sh


rm -f tests
echo "Running clang analyzer..."
# run the clang analysis while excluding the fmt library
scan-build --exclude ../mtl/fmt/ clang++ -o tests -std=c++17 ../tests/*.cpp
rm -rf tests