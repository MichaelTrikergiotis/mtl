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
#define MTL_ASSERT_MSG(CONDITION, MESSAGE) assert(CONDITION && MESSAGE);



// ================================================================================================
// NO_COPY      - dissallow a class to be copied 
// NO_MOVE      - dissallow a class to be moved 
// NO_COPY_MOVE - dissallow a class to be copied or moved
// ================================================================================================

/// Inheriting from this class will make your class unable to be copied.
class no_copy
{
protected:
	no_copy() = default;
	~no_copy() = default;
	no_copy(const no_copy&) = delete;
	no_copy& operator=(const no_copy&) = delete;
};

/// Inheriting from this class will make your class unable to be moved.
class no_move
{
protected:
	no_move() = default;
	~no_move() = default;
	no_move(const no_move&&) = delete;
	no_move& operator=(const no_move&&) = delete;
};

/// Inheriting from this class will make your class unable to be copied or moved.
class no_copy_move
{
protected:
	no_copy_move() = default;
	~no_copy_move() = default;
	no_copy_move(const no_copy_move&) = delete;
	no_copy_move& operator=(const no_copy_move&) = delete;
	no_copy_move(const no_copy_move&&) = delete;
	no_copy_move& operator=(const no_copy_move&&) = delete;
};



} // namespace mtl end