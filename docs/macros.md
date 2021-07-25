# List of MACROS

## The following MACROS require parameters to be passed

[**Recommended to use**]

```c++
MTL_ASSERT_MSG
```

This is a direct replacement for the C++ ```assert``` macro that has the same functionality but also includes a message to report the exact cause for the assert to the user.
It is found in the *utility.hpp*. This macro is recommended to use as it adds more clarity than ```assert```.

## The following the MACROS just need to be defined before the appropriate headers

[**Recommended to use**]

```c++
MTL_DIV_ZERO_THROW
```

If the macro is defined doesn't allow some of the mathematical functions from math.hpp to perform division by zero and instead throws an exception of type ```std::invalid_argument```. It is recommended to define this flag to catch division by zero errors. The reason it is not defined by default is to follow the C++ way of not paying for what you don't use and also follow C++ standard library convention of not catching division by zero errors. This has some implications for performance. When defined and the code doesn't perform division by zero, so we don't have to throw, the performance hit should be very minimal. In the case we throw an exception the performance hit is very big, as is to be expected for the current implementation of exceptions in C++.

----------------------

[**Not recommended to use**]

```c++
MTL_DISABLE_SOME_ASSERTS
```

If the macro is defined, disables somes of the asserts defined in the mtl. Please note that not all of the asserts in **mtl** are disabled with this macro. It is not recommended to define this macro because asserts help you detect bugs in your code more easily and pinpoint the exact
problem as all **mtl** asserts have an informational message associated with them.

----------------------

[**Not recommended to use**]

```c++
MTL_EXTERNALLY_SUPPLIED_FMT
```

The **mtl** uses the **fmt** library. The **fmt** library is used with its header only implementation because **mtl** itself is header only. To make **mtl** more self-contained and easier to use by having fewer requirements to search and install external libraries all the headers for the **fmt** library are included with **mtl** in the folder ```mtl/fmt```. In the case the user want to use his own version of **fmt** a problem arises, the problem of different versions for the same library. Including different versions of the same library is a bad practice that can lead to errors. For that reason you can use the macro ```MTL_EXTERNALLY_SUPPLIED_FMT``` and then supply the **fmt** version of your choice instead of the one included with **mtl**. This macro is not recommended being used if you don't need to because defining this macro without properly providing the **fmt** library will stop you from compiling successfully.

The **fmt** version included and tested with **mtl** is the latest version, we recommend using that because of bugfixes and performance improvements. We do not test **mtl** with previous versions of **fmt**. If there is a compilation problem you may need to update your externally supplied **fmt** version to a newer one.

There are some requirements for using this macro :

1. The macro should be defined BEFORE any **mtl** headers are included and in all files that include **mtl** headers.
2. You have to supply your own version of **fmt** and include all the **fmt** headers BEFORE including any of the **mtl** headers. Preferably the same version used in **mtl**.
3. Your externally supplied version of **fmt** can be used either as a header only or not, doesn't make a difference.
