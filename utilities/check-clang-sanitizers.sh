#!/usr/bin/env bash

# Runs multiple clang sanitizers to check mtl for bugs.
#
# You must have clang installed for this script to work.
# On Ubuntu Linux :
# sudo apt install clang



# delete the generated executable if it existed
rm -f tests
echo "Running clang sanitizers..."
# build mtl using multiple clang sanitizers
clang++ -std=c++17 -o tests -Wfatal-errors -Werror -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined ../tests/*.cpp
# run the generated executable to find errors
./tests
# delete the generated executable
rm -f tests
