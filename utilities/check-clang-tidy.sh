#!/usr/bin/env bash

# Runs clang-tidy for all .hpp files with almost all checks turned on. All .h files are not from
# mtl but code that is included from other projects so we don't want to check those.
#
# You must have clang, clang-tidy and llvm installed for this script to work.
# On Ubuntu Linux in a terminal type :
# sudo apt install clang clang-tidy llvm
#
# You have to give the script executable permission before running it :
# chmod +x check-clang-tidy.sh
# ./check-clang-tidy.sh

echo "Running clang-tidy..."

# run clang-tidy with a lot of checks
clang-tidy ../tests/*.cpp --checks=*,-fuchsia-*,-hicpp-*,-llvm-*,-google-*,-cert-*,-misc-*,-readability-*,-cppcoreguidelines-pro-*,-modernize-use-auto,-modernize-use-equals-delete,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-macro-usage,-modernize-use-trailing-return-type -header-filter=.hpp -- -std=c++17
