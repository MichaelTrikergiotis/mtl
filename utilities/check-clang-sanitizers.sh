# Runs clang sanitizers for the mtl library.
#
# You must have clang and llvm installed for this script to work.
# On Ubuntu Linux in a terminal type :
# sudo apt install clang llvm
#
# You have to give the script executable permission before running it :
# chmod +x check-clang-sanitizers.sh
# ./check-clang-sanitizers.sh

rm -f tests
echo "Running clang sanitizers..."
clang++ -std=c++17 -o tests -Wfatal-errors -Werror -Wall -Wextra -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=integer -fsanitize-blacklist=blacklist.txt ../tests/*.cpp
./tests
rm -rf tests
