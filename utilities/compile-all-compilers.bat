@echo off

rem Compiles mtl tests for all compilers in debug and release for Windows.
rem This script requires you have MSVC, clang, ninja and CMake installed.
rem clang should be in your PATH.

rem check that we are in the utilities folder
set cwd=%cd%
if not "%cwd:~-9%"=="utilities" (
	echo Script not executed from utilities folder. Exiting...
	exit /b 1
	)

rem get to the tests folder
cd ..
cd tests

rem check we are in the tests folder
set test_folder=%cd%
IF NOT "%test_folder:~-5%"=="tests" (
	echo Script couldn't find the tests folder. Exiting...
	exit /b 1
	)


echo.
echo [Compiling tests for all compilers on Windows.]
echo.

echo.
echo [Compiling CMake - MSVC on debug build.]
mkdir build-msvc-debug 2> NUL
cd build-msvc-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON
cmake --build .
cd..

echo.
echo [Compiling CMake - clang-cl on debug build.]
mkdir build-clangcl-debug 2> NUL
cd build-clangcl-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
cmake --build .
cd..

echo.
echo [Compiling CMake - clang++ on debug build.]
mkdir build-clang-debug 2> NUL
cd build-clang-debug
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build .
cd..



echo.
echo [Compiling CMake - MSVC on release build.]
mkdir build-msvc-release 2> NUL
cd build-msvc-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd..

echo.
echo [Compiling CMake - clang-cl on release build.]
mkdir build-clangcl-release 2> NUL
cd build-clangcl-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd..

echo.
echo [Compiling CMake - clang++ on release build.]
mkdir build-clang-release 2> NUL
cd build-clang-release
cmake .. -G Ninja -DENABLE_CONSOLE_TESTS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd..


rem return to the folder we started from
cd..
cd utilities
echo.
echo [Done compiling tests.]


@echo on