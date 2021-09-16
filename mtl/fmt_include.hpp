#pragma once
// fmt include header by Michael Trikergiotis
// 04/06/2020
// 
// 
// Header that includes and configures the fmt library. It also suppresses multiple warnings 
// related to it.
// 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.




// suppress MSVC warnings
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 6285  )
#pragma warning( disable : 6323  )
#pragma warning( disable : 6385  )
#pragma warning( disable : 26437 )
#pragma warning( disable : 26439 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26498 )
#pragma warning( disable : 26812 )
#endif // _MSC_VER end


// suppress GCC warnings
#if defined(__GNUC__) 
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#endif // __clang__ end
#endif // __GNUC__ end


// suppress clang warnings
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wmicrosoft-enum-value"
#endif // __clang__ end 






// increase the performance of fmt when formatting floating point numbers
#define FMT_USE_FULL_CACHE_DRAGONBOX 1

// the user may want to supply their own version of fmt and not the one provided with the mtl
#ifndef MTL_EXTERNALLY_SUPPLIED_FMT

// use fmt in header only mode
#define FMT_HEADER_ONLY 


// header that contains various definitions
#include "definitions.hpp"

// needed headers from fmt
#include "fmt/format.h"
#include "fmt/ostream.h"

#endif // MTL_EXTERNALLY_SUPPLIED_FMT







// stop suppressing clang warnings
#if defined(__clang__)
#pragma clang diagnostic pop
#endif // __clang__ end


// stop suppressing MSVC warnings
#if defined(_MSC_VER)
#pragma warning( pop )
#endif // _MSC_VER end
