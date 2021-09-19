#!/usr/bin/env bash

# Runs gcc sanitizers to check mtl for bugs.
#
# You must have g++ installed for this script to work.
# On Ubuntu Linux :
# sudo apt install g++





# check that we are in the utilities folder
if ! [[ $PWD == *"utilities" ]]; then
    echo "Error !!! The script is not executed from the utilities folder. Exiting."
    exit 1
fi


# delete the generated executable if it existed
rm -f tests

echo "Running gcc sanitizers..."
# build mtl using multiple gcc sanitizers
g++ -std=c++17 -o tests -Wfatal-errors -Werror -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined ../tests/*.cpp
# run the generated executable to find errors
./tests
# delete the generated executable
rm -rf tests
