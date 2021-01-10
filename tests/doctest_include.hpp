#pragma once 
// doctect include header by Michael Trikergiotis
// 05/08/2020
// 
// Header that just includes doctest library and supresses the multiple warnings related with it.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.


// supress MSVC warnings about doctest.h
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4804 )
#pragma warning( disable : 4805 )
#pragma warning( disable : 4996 )
#endif 

// supress clang warning about doctest.h
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// make the tests run faster but they are not as easy to debug when a debugger is attached
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

// Remember to add the following code inside doctest.h file again if we repalce the current version
// of doctest.h file with a newer version doctest.h file but the bug isn't fixed yet.
/*
// This is added to fix a bug that exists with doctest 2.4 with clang on Windows
// github.com/onqtam/doctest/issues/356
#if defined(__clang__) && defined(_WIN32)
#define DOCTEST_CONFIG_COLORS_NONE
#endif
*/

#include "doctest.h"

#if defined(__APPLE__)
// including iostream header fixes a linking error with doctest on macOS, 
// check the issue at github.com/onqtam/doctest/issues/126
#include <iostream>
#endif

// stop supressing clang warnings
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

// stop suppressing MSVC warnings
#if defined(_MSC_VER)
#pragma warning( pop )
#endif