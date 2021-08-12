#!/usr/bin/env bash

# Generates test coverate report using gcovr for mtl.
#
# You must have gcc and gcovr installed for this script to work.
# On Ubuntu Linux :
# sudo apt install g++ gcovr
#
# For a guide on gcovr go to :
# https://gcovr.com/en/stable/guide.html





# check that we are in the utilities folder
if ! [[ $PWD == *"utilities" ]]; then
    echo "Error !!! The script is not executed from the utilities folder. Exiting."
    exit 1
fi


# delete the generated executable if it existed
rm -f tests
echo "Compiling tests..."
# run g++ using specific parameters to make test coverage reporting more accurate
g++ -std=c++17 -o tests -Wfatal-errors -fprofile-arcs -ftest-coverage -fPIC -O0 ../tests/*.cpp
echo "Running tests..."
# run the executable
./tests
echo "Running tests with output to file..."
# run the executable again, but this time write the output to a file, this increases test coverage
./tests > temp.output
# delete the temporary output file
rm -rf temp.output


echo "Generating coverage report..."
# create the directory to store the html coverage report if it doesn't already exist
mkdir -p coverage-report
# we only include .hpp files because the .h files are not from mtl but from other libraries
# we use --exclude-unreachable-branches to remove compiler-generated dead code
# we use --exclude-throw-branches to remove compiler generated exception handling 
# the gcovr manual says gcovr generates much more sensible reports with the above options
gcovr -r ../ -f '.*[_-|A-Z|a-z|0-9]*\.hpp' --exclude-unreachable-branches --exclude-throw-branches -d --html-details -o ./coverage-report/coverage.html
# remove files left behind from gcvor
rm -f *.gcno
rm -f tests
echo "Done generating coverage report."
