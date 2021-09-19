#pragma once 
// doctect include header by Michael Trikergiotis
// 05/08/2020
// 
//
// This header includes doctest and suppresses multiple warnings related to it.
//
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.


// suppress MSVC warnings about doctest.h
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4804 )
#pragma warning( disable : 4805 )
#pragma warning( disable : 4996 )
#endif 

// suppress clang warning about doctest.h
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdouble-promotion"
#endif

// make the tests run faster but they are not as easy to debug when a debugger is attached
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

#include "doctest.h"

#if defined(__APPLE__)
// including iostream header fixes a linking error with doctest on macOS, 
// check the issue at https://github.com/onqtam/doctest/issues/126
#include <iostream>
#endif

// stop suppressing clang warnings
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

// stop suppressing MSVC warnings
#if defined(_MSC_VER)
#pragma warning( pop )
#endif