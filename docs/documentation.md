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

1. MSVC, clang and gcc on Windows
2. clang and gcc on Linux
3. clang and gcc on MacOS

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

### LINUX with gcc

Open the terminal and navigate to the the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```
5. ```./tests```

### LINUX with clang

[**NOTE**] There is a CMake option ```ENABLE_LIBCXX``` to enable `libc++`.

Open the terminal and navigate to the the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++```
4. ```cmake --build .```
5. ```./tests```

### WINDOWS with MSVC

Open `x64 Native Tools Command Prompt for VS 2019` (`vcvars64.bat`) and navigate to the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake ..```
4. ```cmake --build .```
5. ```Debug\tests.exe```

### WINDOWS with clang-cl

You must add **clang** to your path. If you don't know how to do that check [adding clang to your PATH](./clang-windows.md).

**You must have [Ninja](https://ninja-build.org/) installed.**

Open `x64 Native Tools Command Prompt for VS 2019` (`vcvars64.bat`) and navigate to the the **mtl** tests folder :

1. ```mkdir build```
2. ```cd build```
3. ```cmake .. -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl```
4. ```cmake --build .```
5. ```tests.exe```

### Note about test coverage

We strive to reach the highest possible test coverage. We test the **Modern Template Library** very extensively with multiple thousands tests.

------------------------------------------------------------

## Naming Convetions

For naming conventions read [here](./naming.md).

For naming similarities and differences with the C++ standard library read [here](./differences.md).

------------------------------------------------------------

## Listings

### List of namespaces

- `mtl`
  - `mtl::console`
  - `mtl::filesystem`
  - `mtl::chrono`
  - `mtl::string`

[**NOTE**]
There is also the `mtl::detail` namespace which should **never**  be used for any reason. It is reserved for the internal implementation details of **mtl**. It retains the ability to change at any moment without warning or notice.

### List of classes and functions

For a list of classes and functions with documentation and examples read [here](./listing.md).

### List of MACROS

For a list of MACROS along with detailed explanation read [here](./macros.md).

------------------------------------------------------------

If you don't understand something or need clarification please open an issue.
