# Documentation

| [Installation](#installation) | [Running Tests](#how-to-run-the-tests) | [Naming Convetions](#naming-Convetions) | [Listings](#listings) |

## C++ version and compiler compatibility

Requires a C++ 17 compiler and a **fully** implemented C++ 17 standard library.

Minimum requirement for compiler version :

- **gcc 9.1** or later
- **clang 9.0** or later
- **MSVC 2019** with the latest service pack or later

Minimum requirements for C++ standard library version :

- **GNU stdlibc++ 9.1** or later
- **LLVM libc++ 9.0** or later
- **MSVC 2019 stl** or later

Previous versions of these compilers do not work because they do not support features required by the C++ 17 standard.
Other C++ 17 conforming compilers may work correctly but are not currently actively supported or tested.

Tested compiler and operating systems combinations :

1. MSVC and clang on Windows
2. gcc and clang on Linux
3. gcc and clang on MacOS

------------------------------------------------------------

## Installation

The **mtl** is a C++ 17 header-only library. To use it just copy the the **mtl** folder containing all the headers to your project's folder. That is it, you can now and use it. Just remember to enable C++ 17 if your compiler isn't in C++ 17 mode by default.

After that if you want to use **mtl** to print something to the console followed by a newline :

```c++
#include "mtl/console.hpp"

int main()
{
     mtl::console::println("Hello world.");
}
```

------------------------------------------------------------

## How to run the tests

**You must have [CMake](https://cmake.org/) installed.**

[**NOTE**]
There is a CMake option ```ENABLE_CONSOLE_TESTS``` that enables all the tests for ```mtl::console```, that are disabled by default. If you want to visually inspect the ```mtl::console``` tests output use the ```-tce="*clear"``` option when running the tests.

### LINUX with gcc

Open the console and navigate to the the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```
5. ```./tests```

### LINUX with clang

[**NOTE**] There is a CMake option ```ENABLE_LIBCXX``` to enable libc++.

Open the console and navigate to the the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++```
4. ```cmake --build .```
5. ```./tests```

### WINDOWS with MSVC

Open x64 Native Tools Command Prompt for VS 2019 (vcvars64.bat) and navigate to the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```
5. ```Debug\tests.exe```

### WINDOWS with clang-cl

[**NOTE**] Because of a bug in doctest 2.4 all colors for doctest are disabled for clang in Windows. For more info check :
[https://github.com/onqtam/doctest/issues/356](https://github.com/onqtam/doctest/issues/356)

You must add **clang** to your path. If you don't know how to do that check [adding clang to your PATH](./docs/clang-windows.md).

**You must have [Ninja](https://ninja-build.org/) installed.**

Open x64 Native Tools Command Prompt for VS 2019 (vcvars64.bat) and navigate to the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake .. -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl```
4. ```cmake --build .```
5. ```tests.exe```

### Note about line and branch coverage

We strive to reach above 90% test line coverage. We test the **Modern Template Library** very extensively with multiple thousands of tests but due to gcovr's implementation for reporting C++ test coverage, achieving 100% coverage is simply impossible for all programs written in C++. For that reason we try very hard to keep branch coverage over 90% using the flags ```--exclude-unreachable-branches``` and ```--exclude-throw-branches```
but even then we have to further use ```GCOVR_EXCL_LINE```, ```GCOVR_EXCL_START``` and ```GCOVR_EXCL_STOP``` to exclude lines that it is certain that they are incorrectly reported or function calls to third party code like the C++ standard library or external libraries that is not our responsibility to cover with tests. You can read about gcovr's inability to reach 100% coverage with C++ code and about uncovered branches at :
[https://www.gcovr.com/en/stable/faq.html#why-does-c-code-have-so-many-uncovered-branches](https://www.gcovr.com/en/stable/faq.html#why-does-c-code-have-so-many-uncovered-branches)

Sadly gcovr doesn't allow to only exclude lines from branch coverage as that would be very helpful for **mtl** because most of the excluded lines in **mtl** are for false branch coverage. This issue this is tracked at :
[https://github.com/gcovr/gcovr/issues/121](https://github.com/gcovr/gcovr/issues/121)

------------------------------------------------------------

## Naming Convetions

For naming conventions as well as similarities and differences with the C++ standard library read [here](./differences.md).

------------------------------------------------------------

## Listings

List of namespaces :

- `mtl`
  - `mtl::console`
  - `mtl::filesystem`
  - `mtl::chrono`
  - `mtl::string`

[**NOTE**]
There is also the `mtl::detail` namespace which should **never**  be used for any reason. It is reserved for the internal implementation details of **mtl**. It retains the ability to change at any moment without warning or notice.

List of classes and functions with documentation and examples read [here](./listing.md).

List of MACROS along with detailed explanation read [here](./macros.md).

------------------------------------------------------------

If you don't understand something, need clarification, something doesn't seem to make sense or you think it can be made easier to understand please open an issue and explain your problem in detail.
