#pragma once
// definitions header by Michael Trikergiotis
// 02/12/2020
// 
//
// This header contains various definitions.
//
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.


// ================================================================================================


// This fixes an error on Windows when the Windows.h header is included because it defines
// two MACROS that break standard compliant C++ code. For a much more detailed explanation :
// gist.github.com/MichaelTrikergiotis/8ab0994ac000e74203a60657f5b1da45

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX end

#ifdef min
#undef min
#endif // min end

#ifdef max
#undef max
#endif // max end

#endif // _WIN32 end

// ================================================================================================
