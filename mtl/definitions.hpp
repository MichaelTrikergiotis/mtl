#pragma once
// definitions by Michael Trikergiotis
// 02/12/2020
// 
// Header for various definitions.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

// ================================================================================================

// This fixes an error on Windows when the Windows.h header is included because it defines
// two MACROS that break standard compliant C++ code. For a much more detailed explanation :
// gist.github.com/MichaelTrikergiotis/8ab0994ac000e74203a60657f5b1da45

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX end
#endif // _WIN32 end

// ================================================================================================
