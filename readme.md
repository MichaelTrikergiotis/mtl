# mtl

## Modern Template Library

Modern, fast, easy. Makes C++ a joy to use.

![mtl logo](./docs/mtl-logo.png)

------------------------------------------------------------
| [Getting Started](#getting-started) | [Examples](#examples) | [Documentation](./docs/documentation.md) | [Listings](./docs/documentation.md#listings) | [Goals](#goals) | [License](#license) |

------------------------------------------------------------

## Introduction

The **mtl** or by its full name the **Modern Template Library** is a C++ 17 header-only library that provides everything you ever wanted but the C++ standard library is missing. It provides a lot of functionality that other programming languages include by default in their standard libraries.

For a quick overview of what **mtl** provides you can check the [list of classes and functions](./docs/listing.md).

**mtl** tries to be as standard compliant as possible by using standard compliant C++ 17. It also follows the C++ standard library naming scheme and uses the C++ standard library algorithms and containers.

A nice feature of the library is that it contains detailed comments. If you don't know how to use something the first place to look is the comments. But there is also [documentation](./docs/documentation.md).

## Getting started

- For **mtl** you need a **C++ 17** compiler. For compiler compatibility refer to the [compiler documentation](./docs/documentation.md#c-version-and-compiler-compatibility).
- For installation instructions refer to the [installation documentation](./docs/documentation.md#installation).
- For running the tests refer to the [tests documentation](./docs/documentation.md#how-to-run-the-tests).
- For contributing refer to the [contribution documentation](./contributing.md).
- For general documentation refer to the [documentation](./docs/documentation.md).

## Examples

[**EXAMPLE 1**]

Split an `std::string` :

```c++
const std::string names = "Joe, Jill, Bill, Nick, Maria, Helen";
std::vector<std::string> tokens = mtl::string::split(names, ", ");
```

Now you have a `std::vector<std::string>` that contains the following elements `"Joe", "Jill", "Bill", "Nick", "Maria", "Helen"`.

[**EXAMPLE 2**]

Join all the elements of a container to an `std::string` where each element is separated by comma and a space :

```c++
const std::vector<std::string> tokens { "Joe", "Jill", "Bill", "Nick", "Maria", "Helen" };
std::string joined_names = mtl::string::join_all(tokens.begin(), tokens.end(), ", ");
```

Now if you compare `names` from example 1 and `joined_names` from example 2 they will be equal.

[**EXAMPLE 3**]

With `mtl::string::join` you can join different types of variables together with ease. With `mtl::console::println` you can print one or more variables each followed by a newline.

```c++
const std::string planet = " planet ";
// the types of the arguments here are const char*, char, const std::string, float and const char*
std::string message = mtl::string::join("Hello from ", 'a', planet, 12.24f, " lightyears away.");
mtl::console::println(message);
```

`mtl::string::join` combines variables of various types together to an `std::string`. Then `mtl::console::println` prints to the console the message `Hello from a planet 12.24 lightyears away.` followed by a newline.

The same output as the above could also be achieved with :

```c++
mtl::console::print("Hello from ", 'a', planet, 12.24f, " lightyears away.", '\n');
```

Please note that we use `mtl::console::print` with the same variables as before but also add a newline variable at the end.

[**EXAMPLE 4**]

Generating a random number from 1 to 10 with the least amount of boilerplate code :

```c++
mtl::rng<int> rng_1to10 (1, 10);
int random_number = rng_1to10.next();
```

Now the variable `random_number` is a random integer number between 1 and 10.

[**EXAMPLE 5**]

Timing how long a super slow function takes to execute using a stopwatch :

```c++
mtl::chrono::stopwatch sw;
sw.start();
my_super_slow_function();
sw.stop();
// the non-Unicode shorthand for microseconds is us
double time_taken_us = sw.elapsed_micro();
```

The variable `time_taken_us` is a double for how many microseconds it took `my_super_slow_function` to run.

[**EXAMPLE 6**]

Write each element of a container on a different line of a file then read all lines of that file :

```c++
const std::vector<std::string> countries { "Italy", "Brazil", "Greece", "Japan" };
bool written_ok = mtl::filesystem::write_all_lines("countries.txt", countries.begin(), 
                                                                    countries.end());

std::vector<std::string> read_countries;
bool read_ok = mtl::filesystem::read_all_lines("countries.txt", read_countries);
```

If the file was written successfully the `written_ok` boolean is set to true and each country from `countries` is written in a seperate line to the specified file.

If the file was read successfully the `read_ok` boolean is set to true and the `read_countries` container contains all lines read from the specified file.

Now if you compare `countries` and `read_countries` they will be equal.

## Goals

1. High Performance. Be just as fast or faster than the C++ standard library and Boost, in case of similar algorithms.
2. Retain the only pay for what you use philosophy of C++ but be as high level as possible.
3. Be cross platform and portable. Use the least amount of platform specific code.
4. Be easy to use. If you know how to use C++ standard library you don't need to learn almost anything new.
5. Be versatile and serve different usage needs.
6. Be very well tested with very high test coverage.
7. Be very well commented and documented.
8. Have multiple high quality examples for all parts of the library.
9. If something exists in another language, works well and translates nicely to C++ we use it.
10. Use modern standard compliant C++ 17 not old style C++, C with classes or C.

## Non-goals

1. Reinvent the wheel. If there is an algorithm that is known to be the best and fits our license we use it.
2. Stop being easy to use and be expert focused for no good reason.
3. Be another C++ standard library implementation. There are a lot out there. **mtl** adds onto C++ standard library and doesn't replace it.
4. Fit the needs of absolutely everyone. The C++ community is huge and used in numerous industries, we can't please everyone.
5. Fit the needs of only a particular industry excluding all the others.

------------------------------------------------------------

## License

The **mtl** is licensed under the [MIT license](./LICENSE).

For third party licenses check [ThirdPartyNotices](./ThirdPartyNotices.txt).

**mtl** by Michael Trikergiotis 2016-2020
