#pragma once
// definitions by Michael Trikergiotis
// 02/12/2020
// 
// Header for various definitions.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

// ================================================================================================

// This fixes an error on Windows when the Windows.h header is included because it defines
// two MACROS that break standard C++ compliant code. If you encounter an error about 
// MACRO invocation this is because you have included the Windows.h header before any mtl headers.
// To fix the error you have to either include this or any other mtl header before including the 
// Windows.h header. As an alternative you can pass the /DNOMINMAX flag when compiling
// with MSVC / clang-cl or the -DNOMINMAX flag when compiling with clang++.

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX end
#endif // _WIN32 end

// ================================================================================================
