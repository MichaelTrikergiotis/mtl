# mtl

## Modern Template Library

Modern, fast, easy. Makes C++ a joy to use.

![mtl logo](./docs/mtl-logo.png)

## Introduction

The **mtl** or by it's full name the **Modern Template Library** is a C++ 17 header-only library that provides everything you ever wanted but the C++ standard library is missing. It also includes some functionality that other languages like Python or C# include by default in their standard libraries.

**mtl** tries to be as standard compliant as possible by following the C++ standard library naming and uses the C++ standard algorithms and containers.

A nice feature of the library is that it has detailed comments. If you don't know how to use something the first place to look is it's comments. But there is also [documentation](./docs/documentation.md).

For a quick overview of the functionality that **mtl** provides you can check the [list of classes and functions](./docs/listing.md).

## Getting started

- For **mtl** you need a **C++ 17** compiler. For compiler compatibility refer to the [compiler documentation](./docs/documentation.md#C++-version-and-compiler-compatibility).
- For installation instructions refer to the [installation documentation](./docs/documentation.md#Installation).
- For running the tests refer to the [tests documentation](./docs/documentation.md#How-to-run-the-tests).
- For general documentation refer to the [documentation](./docs/documentation.md).
- For contributing refer to the [contributing documenation](./contributing.md).

## Examples

[**EXAMPLE 1**]

Split an `std::string` :

```c++
const std::string names = "Joe, Jill, Bill, Nick, Maria, Helen";
std::vector<std::string> tokens = mtl::string::split(names, ", ");
```

Now you have a `std::vector<std::string>` that contains the following elements `"Joe", "Jill", "Bill", "Nick", "Maria", "Helen"`.

[**EXAMPLE 2**]

Joining all the tokens from a container to an `std::string` with all the names separated by comma and a space :

```c++
const std::vector<std::string> tokens { "Joe", "Jill", "Bill", "Nick", "Maria", "Helen" };
std::string joined_names = mtl::string::join_all(tokens.begin(), tokens.end(), ", ");
```

Now `names` from example 1 and `joined_names` from example 2 if compared will be equal.

[**EXAMPLE 3**]

Generating a random number from 1 to 10 with the least amount of boilerplate code :

```c++
mtl::rng<int> rng_1to10 (1, 10);
int random_number = rng_1to10.next();
```

Now the variable `random_number` is a random integer number between 1 and 10.

[**EXAMPLE 4**]

Timing how long a super slow function takes to execute using a stopwatch :

```c++
mtl::chrono::stopwatch sw;
sw.start();
my_super_slow_function();
sw.stop();
double time_taken_ns = sw.elapsed_nano();
```

The variable `time_taken_ns` is a double for how many nanoseconds it took `my_super_slow_function` to run.

[**EXAMPLE 5**]

Read all lines of a file :

```c++
std::vector<std::string> lines;
bool read_ok = mtl::filesystem::read_all_lines("../document.txt", lines);
```

If the file was read successfully the `read_ok` boolean is set to true and the `std::vector<std::string>` lines contain all lines read from the file.

## Goals

1. High Performance. Be just as fast or faster than the C++ standard library and Boost, in case of similar algorithms.
2. Retain the only pay for what you use philosophy of C++ but be as high level as possible.
3. Be easy to use, if you know how to use C++ standard library you don't need to learn almost anything new.
4. Be very well tested with very high test coverage.
5. Be very well commented and documented.
6. With many good high quality examples for all parts of the library.
7. Be portable with the least amount of platform specific code possible. If something is much better we will still use platform specific code.
8. If something exists in another language, works well, we like it and translates nicely to C++ we use it.
9. Be versatile and serve different usage needs.
10. Use modern C++ 17, not old style C++, C with classes or C. Use naming conventions close to the C++ standard library.

## Non-goals

1. Reinvent the wheel. If there is an algorithm that is known to be the best and fits our license we use it.
2. Stop being easy to use and be expert focused for no good reason. If there is a function that can perform better we still have the easy to use everyday version and also include a more specialized version with better performance.
3. Be another C++ standard library implementation. There are a lot out there. **mtl** adds onto C++ standard library and doesn't replace it.
4. Fit the needs of absolutely everyone. The C++ community is huge and used in numerous industries, we can't please everyone.
5. Fit the needs of only a particular industry excluding all the others.

-----------------------

## License

The **mtl** is licensed under the [MIT license](./LICENSE).

For third party licenses check [ThirdPartyNotices](./ThirdPartyNotices.txt).

**mtl** by Michael Trikergiotis 2016-2020
