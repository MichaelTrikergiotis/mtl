#!/usr/bin/env bash

# Runs clang-tidy for all .hpp files with almost all checks turned on. All .h files are not from
# mtl but code that is included from other projects so we don't want to check those.
#
# You must have clang and llvm installed for this script to work.
# On Ubuntu Linux in a terminal type :
# sudo apt install clang llvm
#
# You have to give the script executable permission before running it :
# chmod +x check-clang-tidy.sh
# ./check-clang-tidy.sh

echo "Running clang-tidy..."
# The reasons for disabling some of the rules :
# 1.) fuchsia rules are not used because some conflict with mtl coding style
# 2.) llvm-include-order is not used because the headers should never be sorted for mtl
# 3.) modernize-use-trailing-return-type is not used because it conflicts with the mtl coding style
# 4.) llvm-header-guard is not included because the headers don't use header guards but pragma once instead
clang-tidy ../tests/main.cpp --checks=*,-fuchsia-*,-llvm-include-order,-modernize-use-trailing-return-type,-llvm-header-guard -header-filter=.hpp -- -std=c++17