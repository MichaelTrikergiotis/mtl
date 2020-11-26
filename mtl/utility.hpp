#pragma once
// utility by Michael Trikergiotis
// 21/09/2016
// 
// Header for utility functions.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include <cassert>	// assert


namespace mtl
{


// ================================================================================================
// MTL_ASSERT_MSG - Assert that checks a condition during runtime and displays the provided error 
//                  message.
// ================================================================================================


/// Assert MACRO that checks a condition during runtime and displays the provided error message 
/// along with file and line where the error happened before terminating the current program.
/// Like assert but also includes a message. Also like static_assert but at runtime.
/// 
/// EXAMPLES :
/// std::string name;
/// MTL_ASSERT_MSG(name.size() > 0, "Error. Variable was empty.");
/// 
/// int length = -1;
/// MTL_ASSERT_MSG(!(length < 0), "Error. Variable had negative value.");
#define MTL_ASSERT_MSG(CONDITION, MESSAGE) assert((CONDITION) && (MESSAGE));



// ================================================================================================
// NO_COPY      - Dissallow a class to be copied.
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
// NO_MOVE      - Dissallow a class to be copied or moved.
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