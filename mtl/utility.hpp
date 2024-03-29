#pragma once
// utility header by Michael Trikergiotis
// 21/09/2016
// 
// 
// This header contains various utility functions.
// 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp" // various definitions
#include <cassert>	       // assert


namespace mtl
{


// ================================================================================================
// MTL_ASSERT_MSG - Assert that checks a condition during runtime and displays the provided error 
//                  message.
// ================================================================================================


/// Assert MACRO that checks a condition during runtime and displays the provided error message 
/// along with the file and the line where the error happened before terminating the current
/// program. Like assert but also includes a message.
#define MTL_ASSERT_MSG(CONDITION, MESSAGE) assert((CONDITION) && (MESSAGE));



// ================================================================================================
// NO_COPY      - Disallow a class to be copied.
// ================================================================================================

/// Inheriting from this class will make your class unable to be copied.
class no_copy
{
protected:
	no_copy() = default;
	~no_copy() = default;
	no_copy(const no_copy&) = delete;
	no_copy& operator=(const no_copy&) = delete;
	no_copy(no_copy&&) noexcept = default;
	no_copy& operator=(no_copy&&) = default;
};


// ================================================================================================
// NO_MOVE      - Disallow a class to be copied or moved.
// ================================================================================================

/// Inheriting from this class will make your class unable to be copied or moved.
class no_move
{
protected:
	no_move() = default;
	~no_move() = default;
	no_move(const no_move&) = delete;
	no_move& operator=(const no_move&) = delete;
	no_move(no_move&&) = delete;
	no_move& operator=(no_move&&) = delete;
};


} // namespace mtl end
