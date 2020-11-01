# mtl

## Modern Template Library

Modern, fast, easy. Makes C++ a joy to use.

![mtl logo](./docs/mtl-logo.png)

The **mtl** or by it's full name **Modern Template Library** sets a very high bar for quality. It is blazing fast but actually easy to use. Tries to remain very well tested while also featuring excellent documentation.

The **mtl** fills the parts that the C++ standard library doesn't have or are lacking in terms of performance.
But also includes some functionality that other languages like Python or C# have by default in their standard libraries.
Tries to be as standard compliant as possible by following the C++ standard library naming and uses the C++ standard algorithms and containers as much as possible. A feature of the library, that is the defacto standard in most modern programming languages and libraries, is that it has detailed comments. If you don't know how to use something the first place to look is it's comments. But there is also [documentation](./docs/documentation.md).

For a quick overview of the various functionality mtl has you can check [list of classes and functions](./docs/listing.md).

## Getting Started

- For **mtl** you need a **C++ 17** compiler. For compiler compatibility refer to [compiler documentation](./docs/documentation.md#C++-version-and-compiler-compatibility).
- For installation instructions refer to [installation documentation](./docs/documentation.md#Installation).
- For running the tests refer to [tests documentation](./docs/documentation.md#How-to-run-the-tests).
- For general documentation refer to [documentation](./docs/documentation.md).
- For contributing to **mtl** refer to [contributing](./contributing.md).

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
