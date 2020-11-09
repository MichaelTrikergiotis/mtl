#!/usr/bin/env bash

# Runs gcc sanitizers for the mtl library.
#
# You must have g++ and llvm installed for this script to work.
# On Ubuntu Linux in a terminal type :
# sudo apt install g++ llvm
#
# You have to give the script executable permission before running it :
# chmod +x check-gcc-sanitizers.sh
# ./check-gcc-sanitizers.sh

rm -f tests
echo "Running gcc sanitizers..."
g++ -std=c++17 -o tests -Wfatal-errors -Werror -Wall -Wextra -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak -fsanitize=undefined ../tests/*.cpp
./tests
rm -rf tests
