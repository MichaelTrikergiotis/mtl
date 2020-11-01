#pragma once
// fmt include header by Michael Trikergiotis
// 04/06/2020
// 
// Header that just includes fmt library and supresses the multiple warnings related with it.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

// supress MSVC warnings
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 26498 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26439 )
#pragma warning( disable : 26437 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26812 )
#pragma warning( disable : 6385  )
#pragma warning( disable : 6323 )
#endif

// supress GCC warnings
#if defined(__GNUC__) 
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#endif
#endif

// supress clang warnings
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif



// the user may want to supply their own version of fmt and not the one with the mtl library
#ifndef MTL_EXTERNALLY_SUPPLIED_FMT

#define FMT_HEADER_ONLY 

// needed headers from fmt
#include "fmt/format.h"
#include "fmt/ostream.h"

#endif // MTL_EXTERNALLY_SUPPLIED_FMT


// stop supressing clang warnings
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

// stop suppressing MSVC warnings
#if defined(_MSC_VER)
#pragma warning( pop )
#endif