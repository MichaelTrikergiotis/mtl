#pragma once
// string manipulation by Michael Trikergiotis
// 13/10/2017
// 
// Header for the mtl::string namespace that contains various algorithms used for manipulating
// strings.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp"   // various definitions
#include <algorithm>         // std::copy, std::fill
#include <string>            // std::string, std::string::npos
#include <string_view>       // std::string_view
#include <cstring>           // std::strlen, std::strstr
#include <iterator>          // std::iterator_traits, std::next, std::advance, std::distance
#include <utility>           // std::pair, std::forward
#include <cmath>             // std::floor, std::ceil
#include <vector>            // std::vector
#include <array>             // std::array
#include <stdexcept>         // std::invalid_argument
#include <cstddef>           // std::ptrdiff_t
#include <type_traits>       // std::enable_if_t, std::is_same_v, std::remove_cv_t
#include "type_traits.hpp"   // mtl::is_std_string_v
#include "container.hpp"     // mtl::emplace_back
#include "fmt_include.hpp"   // fmt::format, fmt::format_int, fmt::to_string
#include "utility.hpp"       // MTL_ASSERT_MSG


namespace mtl
{


namespace string
{

// ================================================================================================
// IS_UPPER - Returns if a character is an uppercase ASCII character.
// IS_UPPER - Returns if all characters in a std::string are uppercase ASCII characters.
// IS_LOWER - Returns if a character is a lowercase ASCII character.
// IS_LOWER - Returns if all characters in a std::string are lowercase ASCII characters.
// ================================================================================================

/// Returns if a character is an uppercase ASCII character. Doesn't have undefined behavior and
/// doesn't throw exceptions.
/// @param[in] character A character to check.
/// @return If the character is an uppercase ASCII character.
[[nodiscard]]
inline bool is_upper(const char character) noexcept
{
	int value = static_cast<int>(static_cast<unsigned char>(character));
	if ((value >= 65) && (value <= 90))
	{
		return true;
	}
	return false;
}

/// Returns if all characters in a std::string are uppercase ASCII characters. Doesn't have 
/// undefined behavior and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all the characters are uppercase ASCII characters.
[[nodiscard]]
inline bool is_upper(const std::string& value) noexcept
{
	for (auto c : value)
	{
		if (is_upper(c) == false)
		{
			return false;
		}
	}
	return true;
}


/// Returns if a character is an lowercase ASCII character. Doesn't have undefined behavior and
/// doesn't throw exceptions.
/// @param[in] character A character to check.
/// @return If the character is an lowercase ASCII character.
[[nodiscard]]
inline bool is_lower(const char character) noexcept
{
	int value = static_cast<int>(static_cast<unsigned char>(character));
	if ((value >= 97) && (value <= 122))
	{
		return true;
	}
	return false;
}

/// Returns if all characters in a std::string are lowercase ASCII characters. Doesn't have 
/// undefined behavior and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all the characters are lowercase ASCII characters.
[[nodiscard]]
inline bool is_lower(const std::string& value) noexcept
{
	for (auto c : value)
	{
		if (is_lower(c) == false)
		{
			return false;
		}
	}
	return true;
}


// ================================================================================================
// TO_UPPER - Converts a lowercase ASCII character to uppercase.
// TO_UPPER - Converts all lowercase ASCII characters of a std::string to uppercase.
// TO_LOWER - Converts a uppercase ASCII character to lowercase.
// TO_LOWER - Converts all uppercase ASCII characters of a std::string to lowercase.
// ================================================================================================

/// Converts a lowercase ASCII character to uppercase. Doesn't have undefined behavior and
/// doesn't throw exceptions.
/// @param[in, out] character A character to convert to uppercase.
inline void to_upper(char& character) noexcept
{
	if (is_lower(character))
	{
		int value = static_cast<int>(static_cast<unsigned char>(character));
		// it so happens that in an ASCII table the uppercase characters are 32 positions before 
		// lowercase characters
		value = value - 32;
		character = static_cast<char>(value);
	}
}

/// Converts all lowercase ASCII characters in a std::string to uppercase. Doesn't have
/// undefined behavior and doesn't throw exceptions.
/// @param[in, out] value An std::string to convert all it's characters to uppercase.
inline void to_upper(std::string& value) noexcept
{
	for (auto& ch : value) { to_upper(ch); }
}

/// Converts an uppercase ASCII character to lowercase. Doesn't have undefined behavior and
/// doesn't throw exceptions.
/// @param[in, out] character A character to convert to lowercase.
inline void to_lower(char& character) noexcept
{
	if (is_upper(character))
	{
		int value = static_cast<int>(static_cast<unsigned char>(character));
		// it so happens that in an ASCII table the lowercase characters are 32 positions after 
		// uppercase characters
		value = value + 32;
		character = static_cast<char>(value);
	}
}

/// Converts all uppercase ASCII characters of a std::string to lowercase characters.
/// Doesn't have undefined behavior and doesn't throw exceptions.
/// @param[in, out] value An std::string to convert all it's characters to lowercase.
inline void to_lower(std::string& value) noexcept
{
	for (auto& ch : value) { to_lower(ch); }
}



// ================================================================================================
// IS_ASCII - Returns if an integer is an ASCII character.
// IS_ASCII - Returns if char is an ASCII character.
// IS_ASCII - Returns if all characters in a std::string are ASCII characters.
// ================================================================================================

/// Returns if the character is an ASCII character. Doesn't have undefined behavior
/// and doesn't throw exceptions.
/// @param[in] character A integer to check.
/// @return If the integer can be represented as an ASCII character.
[[nodiscard]]
inline bool is_ascii(const int character) noexcept
{
	// is the value within the ASCII range of characters
	if ((character >= 0) && (character <= 127))
	{
		return true;
	}
	return false;
}

/// Returns if the character is an ASCII character. Doesn't have undefined behavior
/// and doesn't throw exceptions.
/// @param[in] character A character to check.
/// @return If the character is an ASCII character.
[[nodiscard]]
inline bool is_ascii(const char character) noexcept
{
	int value = static_cast<int>(static_cast<unsigned char>(character));
	return is_ascii(value);
}

/// Returns if all the characters in a std::string are ASCII characters. Doesn't have
/// undefined behavior and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all characters of the std::string are ASCII characters.
[[nodiscard]]
inline bool is_ascii(const std::string& value) noexcept
{
	for (const auto ch : value)
	{
		// check if there are any non-ASCII characters
		if (is_ascii(ch) == false)
		{
			return false;
		}
	}
	return true;
}



// ================================================================================================
// IS_ALPHABETIC - Returns if a character / all characters in std::string are ASCII alphabetic 
//                 characters or not.
// IS_NUMERIC    - Returns if a character / all characters in std::string are ASCII numbers or not.
// IS_ALPHANUM   - Returns if a character / all characters in std::string are ASCII alphanumeric 
//                 characters or not.
// ================================================================================================

/// Returns if a character is an ASCII alphabetic character. Doesn't have undefined behavior and 
/// doesn't throw exceptions.
/// @param[in] character A character to check.
/// @return If the character is an ASCII alphabetic character.
[[nodiscard]]
inline bool is_alphabetic(const char character) noexcept
{
	int value = static_cast<int>(static_cast<unsigned char>(character));
	if (((value >= 65) && (value <= 90)) || ((value >= 97) && (value <= 122)))
	{
		return true;
	}
	return false;
}

/// Returns if all characters in a std::string are ASCII alphabetic characters. Doesn't have 
/// undefined behavior and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all the characters of an std::string are ASCII alphabetic characters.
[[nodiscard]]
inline bool is_alphabetic(const std::string& value) noexcept
{
	for (const auto ch : value)
	{
		// if the character isn't alphanumeric
		if (is_alphabetic(ch) == false)
		{
			return false;
		}
	}
	return true;
}

/// Returns if a character is an ASCII number. Doesn't have undefined behavior and doesn't throw
/// exceptions.
/// @param[in] character A character to check.
/// @return If the character is an ASCII number.
[[nodiscard]]
inline bool is_numeric(const char character) noexcept
{
	int value = static_cast<int>(static_cast<unsigned char>(character));
	if ((value >= 48) && (value <= 57))
	{
		return true;
	}
	return false;
}

/// Returns if all characters in a std::string are ASCII numbers. Doesn't have undefined behavior 
/// and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all the characters of an std::string are ASCII numeric characters.
[[nodiscard]]
inline bool is_numeric(const std::string& value) noexcept
{
	for (const auto ch : value)
	{
		// if the character isn't alphanumeric
		if (is_numeric(ch) == false)
		{
			return false;
		}
	}
	return true;
}

/// Returns if a character is an ASCII alphabetic or numeric character. Doesn't have undefined
/// behavior and doesn't throw exceptions.
/// @param[in] character A character to check.
/// @return If the character is an ASCII alphanumeric character.
[[nodiscard]]
inline bool is_alphanum(const char character) noexcept
{
	if ((is_alphabetic(character))	|| (is_numeric(character)))
	{
		return true;
	}
	return false;
}

/// Returns if all characters in a std::string are ASCII alphabetic or numeric characters. Doesn't
/// have undefined behavior and doesn't throw exceptions.
/// @param[in] value An std::string to check.
/// @return If all the characters of an std::string are ASCII alphanumeric characters.
[[nodiscard]]
inline bool is_alphanum(const std::string& value) noexcept
{
	for (const auto ch : value)
	{
		// if the character isn't alphanumeric
		if (is_alphanum(ch) == false)
		{
			return false;
		}
	}
	return true;
}


// ================================================================================================
// CONTAINS - Returns if a substring exists within a string. 
// ================================================================================================


/// Returns if a substring is found inside the input string or not.
/// @param[in] value An std::string to check for a match.
/// @param[in] match A match to search in the input.
/// @return If the match was found.
[[nodiscard]]
inline bool contains(const std::string& value, const std::string& match)
{
	size_t pos = value.find(match);
	if (pos != std::string::npos) 
	{ 
		return true; 
	}
	return false;
}

/// Returns if a substring is found inside the input string or not.
/// @param[in] value An std::string to check for a match.
/// @param[in] match A match to search in the input.
/// @return If the match was found.
[[nodiscard]]
inline bool contains(const std::string& value, const char* match)
{
	size_t pos = value.find(match);
	if (pos != std::string::npos) 
	{ 
		return true; 
	}
	return false;
}

/// Returns if a substring is found inside the input string or not.
/// @param[in] value A const char* to check for a match.
/// @param[in] match A match to search in the input.
/// @return If the match was found.
[[nodiscard]]
inline bool contains(const char* value, const std::string& match)
{
	const auto pos = std::strstr(value, match.c_str());
	if(pos)
	{
		return true;
	}
	return false;
}

/// Returns if a substring is found inside the input string or not.
/// @param[in] value A const char* to check for a match.
/// @param[in] match A match to search in the input.
/// @return If the match was found.
[[nodiscard]]
inline bool contains(const char* value, const char* match)
{
	const auto pos = std::strstr(value, match);
	if(pos)
	{
		return true;
	}
	return false;
}






// ===============================================================================================
// STRIP_FRONT  - Strips all matching characters from the front.
// STRIP_BACK   - Strips all matching characters from the back.
// STRIP        - Strips all matching characters from the front and back.
// ===============================================================================================

/// Strips all matching characters from the front side of the string. Performs no heap 
/// allocation.
/// @param[in, out] value An std::string to strip from the front.
/// @param[in] match An optional character to remove if it matches.
inline void strip_front(std::string& value, const char match = ' ')
{
	// count how many characters match
	size_t count = 0;
	for (const auto& c : value)
	{
		if (c != match) { break; }
		++count;
	}

	// if there are no matches leave
	if(count == 0)
	{
		return;
	}

	// if the number of characters matching are less that the total length of the string
	if (count < value.size())
	{
		// create an iterator from the copying should start from
		auto iter = std::next(value.begin(), static_cast<std::string::difference_type>(count));
		// copy the characters of the std::string to the front of the std::string
		std::copy(iter, value.end(), value.begin());
		// remove unwated characters from the end
		value.resize(value.size() - count);
	}
	// else if the number of characters matching are equal to the total length of the string
	else if (count == value.size())
	{
		value.resize(0);
	}
}


/// Strips all matching characters from the back side of the string. Performs no heap 
/// allocation.
/// @param[in, out] value An std::string to strip from the back.
/// @param[in] match An optional character to remove if it matches.
inline void strip_back(std::string& value, const char match = ' ')
{
	size_t count = 0;
	// count how many character match from the end using reverse iterator
	for (auto it = value.rbegin(); it != value.rend(); ++it)
	{
		if (*it != match) { break; }
		++count;
	}
	// remove as many characters as there are matches
	value.resize(value.size() - count);
}


/// Strips all matching characters from the front and back side of the string. Performs
/// no heap allocation.
/// @param[in, out] value An std::string to strip from the front and back.
/// @param[in] match An optional character to remove if it matches.
inline void strip(std::string& value, const char match = ' ')
{
	// strip the back first so the strip_front has to copy fewer characters
	strip_back(value, match);
	strip_front(value, match);
}



// ================================================================================================
// PAD_FRONT     - Pads a string's front side with a given character for a number of times.
// PAD_FRONT     - Pads a string's front side with a given character until it matches another
//                 string's size.
// PAD_BACK      - Pads a string's back side with a given character for a number of times.
// PAD_BACK      - Pads a string's back side with a given character until it matches another
//                 string's size.
// PAD           - Pads a string's front and back side with a given character for a number of times
//                 so it is centered in the middle.
// PAD           - Pads a string's front and back side with a given character for a number of times
//                 until it matches another string's size and is also centered in the middle.
// ================================================================================================


/// Pads a string's front side with a given character for a number of times.
/// @param[in, out] value An std::string to pad to the front.
/// @param[in] times The number of times to perform the pad.
/// @param[in] ch An optional character to pad with.
inline void pad_front(std::string& value, const size_t times, const char ch = ' ')
{
	// keep the original size
	const auto old_size = value.size();
	// resize the string to fit new characters
	value.resize(value.size() + times);
	// perform work on the string only if it is of a certain length and larger
	if (value.size() > 1)
	{
		// GCOVR_EXCL_START
		using std_string_diff_type = std::string::difference_type;
		// iterator to the destination we want
		auto dest = std::next(value.begin(), static_cast<std_string_diff_type>(times));
		// iterator to the position where the old string ended
		auto it_end = std::next(value.begin(), static_cast<std_string_diff_type>(old_size));
		// copy the string to the correct position
		std::copy(value.begin(), it_end, dest);
		// fill the given character to the correct positions
		std::fill(value.begin(), dest, ch);
		// GCOVR_EXCL_STOP
	}

}

/// Pads a string's front side with a given character as many number of times is needed
/// to match another string's size.
/// @param[in, out] value An std::string to pad to the front.
/// @param[in] match A std::string to match the size of.
/// @param[in] ch An optional character to pad with.
inline void pad_front(std::string& value, const std::string& match, const char ch = ' ')
{
	// we only want to resize if the target string's size is larger that the size of the string we
	// want to match
	if (match.size() > value.size())
	{
		// calculate the difference between the two strings size
		const auto difference = match.size() - value.size();
		pad_front(value, difference, ch);
	}
}

/// Pads a string's back side with a given character for a number of times.
/// @param[in, out] value An std::string to pad to the back.
/// @param[in] times The number of times to perform the pad.
/// @param[in] match An optional character to pad with.
inline void pad_back(std::string& value, const size_t times, const char ch = ' ')
{
	// resizes a string and fills it with a given character, if the string's capacity is large
	// enough it may even avoid copying memory
	value.resize(value.size() + times, ch);
}

/// Pads a string's back side with a given character as many number of times is
/// needed to match another string's size.
/// @param[in, out] value An std::string to pad to the back.
/// @param[in] match A std::string to match the size of.
/// @param[in] ch An optional character to pad with.
inline void pad_back(std::string& value, const std::string& match, const char ch = ' ')
{
	// we only want to perform work if the size of the string we are matching is bigger than the 
	// input string
	if (match.size() > value.size())
	{
		// calculate the difference between the two strings size
		const auto difference = match.size() - value.size();
		pad_back(value, difference, ch);
	}
}

/// Pads a string's front and back side with a given character for a number of times so the string
/// is centered in the middle. The variable times represents how many times it will be padded in
/// total both on the front and on the back side. If more_back is set to true it will prefer to
/// pad the back side more if the times that padding needs to be applied is an odd number.
/// @param[in, out] value An std::string to pad to the front and back.
/// @param[in] times The number of times to perform the pad.
/// @param[in] ch An optional character to pad with.
/// @param[in] more_back If the should be more padding to the back side.
inline void pad(std::string& value, const size_t times, const char ch = ' ', 
				bool more_back = false)
{
	// if we are padding an empty string for more than 0 times then just use mtl::string::pad_back
	if((value.empty()) && (times > 0))
	{
		mtl::string::pad_back(value, times, ch);
		return;
	}
	// perform work only if the string has any character and if the times to pad is larger than 0
	if ((value.empty() == false) && (times > 0))
	{
		// convert to floating point for better division, no need for double as the precision is
		// not needed
		float back_pad_d = float(times);
		// find the middle
		back_pad_d = back_pad_d / 2.0f;
		
		size_t back_pad = 0;

		// if the more_back is false the padding will be centered but in the in case the padding
		// isn't even it will have more padding to the front
		if(more_back == false)
		{
			// round the result and convert it back to an integral number type
			back_pad = size_t(std::floor(back_pad_d));
		}
		// if the more_back is true the padding will be centered but in the in case the padding
		// isn't even it will have more padding to the back
		else
		{
			// round the result and convert it back to an integral number type
			back_pad = size_t(std::ceil(back_pad_d));
		}
		

		// find the times to pad the front
		size_t front_pad = times - back_pad;
		
		// pad the front side first because it is slower as it is most likely to copy memory, and
		// the string is a smaller size here than it will be in the end
		pad_front(value, front_pad, ch);
		// pad the back
		pad_back(value, back_pad, ch);
	}
}

/// Pads a string to it's front and back with a given character as many number of times is
/// needed to match another string's size and is also centered in the middle. If more_back is set
/// to true it will prefer to pad the back side more if the times that padding needs to be applied
/// is an odd number.
/// @param[in, out] value An std::string to pad to the front and back.
/// @param[in] match A std::string to match the size of.
/// @param[in] ch An optional character to pad with.
/// @param[in] more_back If the should be more padding to the back side.
inline void pad(std::string& value, const std::string& match, const char ch = ' ', 
				bool more_back = false)
{
	// we only want to perform work if the size of the string we are matching is bigger than the 
	// input string
	if (match.size() > value.size())
	{
		// calculate the difference between the two strings size
		const auto difference = match.size() - value.size();
		// pad the string
		pad(value, difference, ch, more_back);
	}
}



// ================================================================================================
// TO_STRING - convert various types to string
// ================================================================================================

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
template<typename T>
[[nodiscard]]
inline std::enable_if_t<!mtl::is_number_v<T>, std::string>
to_string(const T& value)
{
	return fmt::to_string(value);
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
template<typename T>
[[nodiscard]]
inline std::enable_if_t<mtl::is_int_v<T>, std::string>
to_string(const T& value)
{
	return fmt::format_int(value).str(); // GCOVR_EXCL_LINE
}



/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
template<typename T>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<T>, std::string>
to_string(const T& value)
{
	return fmt::to_string(value);
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
[[nodiscard]]
inline std::string to_string(const bool value)
{ 
	if(value)
	{
		return std::string("true");
	}
	return std::string("false");
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
[[nodiscard]]
inline std::string to_string(const std::string& value) 
{ 
	return value; 
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
[[nodiscard]]
inline std::string to_string(const char* value) 
{ 
	return std::string(value); // GCOVR_EXCL_LINE
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream.
/// @param[in] value Any type that can be converted to std::string.
/// @return An std::string.
[[nodiscard]]
inline std::string to_string(const char value)
{
	std::string result;
	result.push_back(value); // GCOVR_EXCL_LINE
	return result;
}

/// Converts bool, char, char*, std::string, std::pair and all numeric types to std::string. Also
/// supports user defined types that have the operator<< overloaded for std::ostream. 
///  Specialization for std::pair with extra option that allows to define a delimiter between the
///  two items of the std::pair.
/// @param[in] value Any type that can be converted to std::string.
/// @param[in] delimiter A delimiter that will be used between the pair.
/// @return An std::string.
template<typename T1, typename T2>
[[nodiscard]]
inline std::string to_string(const std::pair<T1, T2>& value, const std::string& delimiter = ", ")
{
	// convert the first item of the pair into a string
	std::string first_part = mtl::string::to_string(value.first);
	// convert the second part of the item into a string
	std::string second_part = mtl::string::to_string(value.second);
	// create a string to add the two parts together
	std::string result;

	// reserve space to avoid allocations;
	result.reserve(first_part.size() + second_part.size() + delimiter.size());

	// add all the parts together with a delimiter inbetween them
	result += first_part;
	result += delimiter;
	result += second_part;
	return result;
}


// ===============================================================================================
// JOIN_ALL - Joins all items from a range (first, last) and returns a std::string.
// ===============================================================================================

/// Join all items of a range from first to last with a delimiter. Allows you to specify the output
/// string so you can reserve memory.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[out] result Where the result will be placed that you can use reserve.
/// @param[in] delimiter Delimiter to use when joining the elements.
template<typename Iter>
inline std::enable_if_t
<std::is_same_v<std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>, std::string>,
void>
join_all(Iter first, Iter last, std::string& result, const std::string& delimiter)
{
	// if there is nothing to join leave the function
	if (first == last) { return; } // excluding live from gcovr code coverage, GCOVR_EXCL_LINE

	// the size of the delimiter
	const size_t delim_size = delimiter.size();

	// count total size of all strings in the container plus the delimiter size
	size_t total_size = 0;
	for (auto it = first; it != last; ++it)
	{
		total_size += it->size() + delim_size;
	}

	// reserve space to avoid extra allocations
	result.reserve(total_size);

	// join the string with a delimiter
	if (delim_size > 0)
	{
		for (auto it = first; it != last; ++it)
		{
			// GCOVR_EXCL_START
			result += *it;
			result += delimiter;
			// GCOVR_EXCL_STOP
		}

		// remove as many characters as the delimiter's size because we added one unwated
		// delimiter at the end
		result.resize(result.size() - delimiter.size());
	}
	// join the string without adding the delimiter
	else
	{
		for (auto it = first; it != last; ++it)
		{
			result += *it; // GCOVR_EXCL_LINE
		}
	}
}


/// Join all items of a range from first to last with a delimiter. Allows you to specify the output
/// string so you can reserve memory.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[out] result Where the result will be placed that you can use reserve.
/// @param[in] delimiter Delimiter to use when joining the elements.
template<typename Iter>
inline std::enable_if_t
<!std::is_same_v<std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>, std::string>,
void>
join_all(Iter first, Iter last, std::string& result, const std::string& delimiter)
{
	// if there is nothing to join leave the function
	if (first == last) { return; } // excluding live from gcovr code coverage, GCOVR_EXCL_LINE

	// the size of the delimiter
	const size_t delim_size = delimiter.size();

	// GCOVR_EXCL_START
	// join the string with a delimiter
	if (delim_size > 0)
	{
		for (auto it = first; it != last; ++it)
		{
			
			// convert the element to string and add it
			result += mtl::string::to_string(*it); 
			result += delimiter;
			
		}

		// remove as many characters as the delimiter's size because we added one unwated
		// delimiter at the end
		result.resize(result.size() - delimiter.size()); 
	}
	// join the string without adding the delimiter
	else
	{
		for (auto it = first; it != last; ++it)
		{
			result += mtl::string::to_string(*it); 
		}
	}
	// GCOVR_EXCL_STOP
	
}


/// Join all items of a range from first to last with a delimiter. Allows you to specify the output
/// string so you can reserve memory.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[out] result Where the result will be placed that you can use reserve.
/// @param[in] delimiter Delimiter to use when joining the elements.
template<typename Iter>
inline void join_all(Iter first, Iter last, std::string& result, const char delimiter)
{
	// GCOVR_EXCL_START
	mtl::string::join_all(first, last, result, mtl::string::to_string(delimiter));
	// GCOVR_EXCL_STOP
}


/// Join all items of a range from first to last with a delimiter. Allows you to specify the output
/// string so you can reserve memory.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[out] result Where the result will be placed that you can use reserve.
/// @param[in] delimiter Delimiter to use when joining the elements.
template<typename Iter>
inline void join_all(Iter first, Iter last, std::string& result, const char* delimiter)
{
	mtl::string::join_all(first, last, result, mtl::string::to_string(delimiter));
}


/// Join all items of a range from first to last with optional delimiter and returns a std::string.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[in] delimiter Delimiter to use when joining the elements.
/// @return An std::string with all the elements joined together.
template<typename Iter>
[[nodiscard]]
inline std::string join_all(Iter first, Iter last, const std::string& delimiter = "")
{
	std::string result;
	// use the mtl::string::join_all version where you select the container
	mtl::string::join_all(first, last, result, delimiter);
	return result;
}

/// Join all items of a range from first to last with a delimiter and returns a std::string.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[in] delimiter Delimiter to use when joining the elements.
/// @return An std::string with all the elements joined together.
template<typename Iter>
[[nodiscard]]
inline std::string join_all(Iter first, Iter last, const char delimiter)
{
	return mtl::string::join_all(first, last, mtl::string::to_string(delimiter));
}

/// Join all items of a range from first to last with a delimiter and returns a std::string.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[in] delimiter Delimiter to use when joining the elements.
/// @return An std::string with all the elements joined together.
template<typename Iter>
[[nodiscard]]
inline std::string join_all(Iter first, Iter last, const char* delimiter)
{
	return mtl::string::join_all(first, last, mtl::string::to_string(delimiter));
}





// ===============================================================================================
// JOIN - Joins one or more items of various types and returns a std::string
// ===============================================================================================



namespace detail 
{

// Actual implementation for variadic template join.
template<typename Type>
inline void join_impl(std::string& value, const Type& type)
{
	value += mtl::string::to_string(type);
}

// Actual implementation for variadic template join.
template<typename Type, typename... Args>
inline void join_impl(std::string& value, const Type& type, Args&&... args)
{
	join_impl(value, type);
	join_impl(value, std::forward<Args>(args)...);
}

// Count size for std::string.
inline void count_size_impl(size_t& size, const std::string& type)
{
	size += type.size();
}

// Count size for const char*.
inline void count_size_impl(size_t& size, const char* type)
{
	// std::strlen doesn't count the null terminator \0 which is what we want since it will
	// not be included in the resulting string when const char* is concatenated 
	size += std::strlen(type);
}

// Count size for bool.
inline void count_size_impl(size_t& size, const bool type)
{
	if(type)
	{
		size += 4;
	}
	else
	{
		size += 5;
	}
	
}

// Count size for int. This is intentionally empty and also declared so integer are not implicitly
// converted to chars and to stop warnings about integer conversion.
inline void count_size_impl(size_t&, const int)
{

}

// Count size for char.
inline void count_size_impl(size_t& size, const char)
{
	size += 1;
}

// Count size for std::pairt<T, U>.
template<typename Type1, typename Type2>
inline void count_size_impl(size_t& size, const std::pair<Type1, Type2>& type)
{
	count_size_impl(size, type.first);
	count_size_impl(size, type.second);
	// add 2 characers because when std::pair is converted to string with mtl::string::to_string 
	// there is a two character delimiter added between the items by default
	size += 2;
}

// Count size for all non-specialize types. Do not remove.
template<typename Type>
inline void count_size_impl(size_t&, const Type&)
{
	// For non-specialized type the count is 0. All modern compilers with high otpimization
	// setting turn this function into a NOOP.
}




// Variadic template that counts the number of characters for std::string, const char*, char and
// std::pair found in the arguments. All other types are not counted.
template<typename Type, typename... Args>
inline void count_size_impl(size_t& size, const Type& type, Args&&... args)
{
	count_size_impl(size, type);
	count_size_impl(size, std::forward<Args>(args)...);
}


// Variadic join implementation with the ability to reserve space to avoid allocations.
template<typename Type, typename... Args>
[[nodiscard]]
inline std::string join_select_impl(const Type& type, Args&&... args)
{
	size_t size = 0;
	// count the number of characters of types that can be counted like std::string, const char* 
	// and char so we can reserve the std::string's size
	count_size_impl(size, type, args...);

	std::string result;
	// reserve space to avoid unnecessary allocations
	result.reserve(size); 
	join_impl(result, type, std::forward<Args>(args)...);
	return result;
}

} // namespace detail end


/// Join one or more elements of any type to a std::string.
/// @param[in] type An item to join.
/// @return An std::string with all the items joined together.
template<typename Type>
[[nodiscard]]
inline std::string join(const Type& type)
{
	return mtl::string::to_string(type);
}

/// Join one or more elements of any type to a std::string.
/// @param[in] type An item to join.
/// @param[in] args Any number of items to join.
/// @return An std::string with all the items joined together.
template<typename Type, typename... Args>
[[nodiscard]]
inline std::string join(const Type& type, Args&&... args)
{
	return detail::join_select_impl(type, std::forward<Args>(args)...);
}

// ===============================================================================================
// SPLIT - Splits a string into tokens with a given delimiter.
// ===============================================================================================

/// Splits a string into tokens with a delimiter. Gives the ability to select the type of container
/// to used as output and even allows you to reserve memory for it, if it supports reserve. The
/// containers element type has to be string.
/// @param[in] value The std::string to split.
/// @param[out] result The container where all the parts will placed. The element for the container
///                    has to be std::string. You can use reserve.
/// @param[in] delimiter A delimiter that will be used to identify where to split.
template<typename Container>
inline void split(const std::string& value, Container& result, const std::string& delimiter)
{
	// if the input string is empty do nothing and return
	if (value.empty())
	{
		return;
	}

	// if the delimiter is empty add the entire input to the container and return
	if(delimiter.empty())
	{
		mtl::emplace_back(result, value);
		return;
	}

	// the size of the container before we start modifying it
	const auto original_size = result.size();

	// remember the starting position
	size_t start = 0;
	// position of the first match
	size_t match_pos = value.find(delimiter);

	// keep the position for the last item
	size_t last_pos = 0;

	// add all tokens to the container except the last one
	while (match_pos != std::string::npos)
	{
		last_pos = match_pos;

		// everything is fine add the token to the container
		const std::string_view token(value.data() + start, match_pos - start);
		mtl::emplace_back(result, token);

		
		// set the a new starting position
		start = match_pos + delimiter.size();
		// find a new position in the input string if there are any matches left
		match_pos = value.find(delimiter, start);
	}

	// how much we added to the container
	const auto size_difference = result.size() - original_size;

	// if container changed size it means there are tokens in the output
	if(size_difference > 0)
	{
		// add the last item using the last position
		const std::string_view token(value.data() + (last_pos + delimiter.size()));
		mtl::emplace_back(result, token);
	}


	// if the container's size didn't change at all then add the entire input string because it
	// means there are no places that it needs to be split
	if (size_difference == 0) { mtl::emplace_back(result, value); }
}


/// Splits a string into tokens with a delimiter. Gives the ability to select the type of container
/// to used as output and even allows you to reserve memory for it, if it supports reserve. The
/// containers element type has to be string.
/// @param[in] value The std::string to split.
/// @param[out] result The container where all the parts will placed. The element for the container
///                    has to be std::string. You can use reserve.
/// @param[in] delimiter A delimiter that will be used to identify where to split.
template<typename Container>
inline void split(const std::string& value, Container& result, const char delimiter)
{
	mtl::string::split(value, result, mtl::string::to_string(delimiter)); // GCOVR_EXCL_LINE
}

/// Splits a string into tokens with a delimiter. Gives the ability to select the type of container
/// to used as output and even allows you to reserve memory for it, if it supports reserve. The
/// containers element type has to be string.
/// @param[in] value The std::string to split.
/// @param[out] result The container where all the parts will placed. The element for the container
///                    has to be std::string. You can use reserve.
/// @param[in] delimiter A delimiter that will be used to identify where to split.
template<typename Container>
inline void split(const std::string& value, Container& result, const char* delimiter)
{
	mtl::string::split(value, result, mtl::string::to_string(delimiter));
}


/// Splits a string into tokens with an optional delimiter.
/// @param[in] value The std::string to split.
/// @param[in] delimiter An optional delimiter that will be used to identify where to split.
/// @return An std::vector of std::string that holds all the parts.
[[nodiscard]]
inline std::vector<std::string> split(const std::string& value, const std::string& delimiter = " ")
{
	std::vector<std::string> result;

	// use the split version where you select the container type to avoid code duplication
	mtl::string::split(value, result, delimiter);

	return result;
}

/// Splits a string into tokens with a delimiter.
/// @param[in] value The std::string to split.
/// @param[in] delimiter A delimiter that will be used to identify where to split.
/// @return An std::vector of std::string that holds all the parts.
[[nodiscard]]
inline std::vector<std::string> split(const std::string& value, const char delimiter)
{
	return mtl::string::split(value, mtl::string::to_string(delimiter));
}

/// Splits a string into tokens with a delimiter.
/// @param[in] value The std::string to split.
/// @param[in] delimiter A delimiter that will be used to identify where to split.
/// @return An std::vector of std::string that holds all the parts.
[[nodiscard]]
inline std::vector<std::string> split(const std::string& value, const char* delimiter)
{
	return mtl::string::split(value, mtl::string::to_string(delimiter));
}





// ================================================================================================
// REPLACE - Replaces all places in the input string where a match is found with 
//           the replacement std::string / char* / char.
// ================================================================================================

namespace detail
{

// Replaces all places in the input std::string where a match is found with the replacement 
// std::string. Version specialized for handling short strings much faster.
inline void replace_short(std::string& value, const std::string& match, 
						  const std::string& replacement)
{
	size_t pos = 0;
	while ((pos = value.find(match, pos)) != std::string::npos)
	{
		value.replace(pos, match.size(), replacement);
		pos += replacement.size();
	}
}



// Replaces all places in the input std::string where a match is found with the replacement 
// std::string. Version specialized for handling long strings faster but is even more specialized
// than mtl::string::replace_long to be called only after the stack array is full and we have to
// start using heap allocations for keeping track of the positions where matches where found.
inline void replace_long_heap(std::string& value, const std::string& match,
							  const std::string& replacement,
							  const std::array<size_t, 20>& found_positions,
							  const size_t starting_position)
{
	std::vector<size_t> positions(found_positions.begin(), found_positions.end());

	size_t pos = starting_position;
	// find all matches and keep their index
	while ((pos = value.find(match, pos)) != std::string::npos)
	{
		positions.push_back(pos);
		// move the position forward enough so we don't match the same thing again
		pos += match.size();
	}

	std::string result;
	size_t difference = 0;

	// if what we replace is larger than the match then it is easy
	if (replacement.size() >= match.size())
	{
		difference = value.size() + (positions.size() * (replacement.size() - match.size()));
	}
	// if what we replace is smaller than the match then we have to convert numbers to a
	// singed integer type so we can accept negative numbers
	else
	{
		// turn size_t to int64_t
		int64_t positions_size = static_cast<int64_t>(positions.size());
		int64_t replacement_size = static_cast<int64_t>(replacement.size());
		int64_t match_size = static_cast<int64_t>(match.size());
		// this value will never be negative
		int64_t diff = positions_size * (match_size - replacement_size);
		// after this calculation the number can never be negative as the input string size is
		// always larger as we have checked for this before
		diff = static_cast<int64_t>(value.size()) - diff;

#ifndef MTL_DISABLE_SOME_ASSERTS
		MTL_ASSERT_MSG(diff >= 0, 
		"Error. Number can't be negative. mtl::string::detail::replace_long contains errors.");
#endif  // MTL_DISABLE_SOME_ASSERTS end

		// convert to size_t with no problems as this can't be negative
		difference = static_cast<size_t>(diff);
	}

	// resize to avoid unnecessary allocations
	result.resize(difference);

	// create various iterators
	const auto beginning = value.begin();
	auto it_begin = value.begin();
	auto it_end = value.begin();
	auto it_output = result.begin();

	for (const auto position : positions)
	{
		// GCOVR_EXCL_START
		// copies parts to output string and moves the iterators along
		it_end = std::next(beginning, static_cast<std::ptrdiff_t>(position));
		std::copy(it_begin, it_end, it_output);
		std::advance(it_output, std::distance(it_begin, it_end));
		std::copy(replacement.begin(), replacement.end(), it_output);
		std::advance(it_output, static_cast<std::ptrdiff_t>(replacement.size()));
		it_begin = std::next(it_end, static_cast<std::ptrdiff_t>(match.size()));
		// GCOVR_EXCL_STOP
	}
	// copy from the last match to the end
	std::copy(it_begin, value.end(), it_output);

	// set the input string to the resulting string that we have perfomed all the replacements on
	value = result;
}



// Replaces all places in the input std::string where a match is found with the replacement 
// std::string. Version specialized for handling long strings much faster.
inline void replace_long(std::string& value, const std::string& match,
						 const std::string& replacement)
{
	// if input size is smaller than match then do nothing, this covers the cases where input size
	// is 0
	if (value.size() < match.size())
	{
		return;
	}

	// set the maximum size of items for our stack array
	constexpr size_t max_size = 20;
	// create an array on the stack to avoid heap allocations, the array will usually be larger 
	// than the amount of positions found, if the positions fill the array we call an algorithm 
	// where we use the heap and can track more positions
	std::array<size_t, max_size> positions {};
	// this is the number that keeps track of number of positions found to match, they stack array 
	// size can be larger that this number so we can't use std::array::size
	size_t actual_size = 0;

	size_t pos = 0;
	// find all matches and keep their index
	while ((pos = value.find(match, pos)) != std::string::npos)
	{
		// if the array can't hold more items start using the heap instead of the stack
		if (actual_size == max_size)
		{
			replace_long_heap(value, match, replacement, positions, pos);
			return;
		}

		// store the position where a match was found
		positions[actual_size] = pos;
		++actual_size;
		// move the position forward enough so we don't match the same thing again
		pos += match.size();
	}

	// if nothing is found leave
	if (actual_size == 0) { return; }


	std::string result;
	size_t difference = 0;

	// if what we replace is larger than the match then it is easy
	if (replacement.size() >= match.size())
	{
		difference = value.size() + (actual_size * (replacement.size() - match.size()));
	}
	// if what we replace is smaller than the match then we have to convert numbers to a
	// singed integer type so we can accept negative numbers
	else 
	{
		// turn size_t to int64_t
		int64_t positions_size = static_cast<int64_t>(actual_size);
		int64_t replacement_size = static_cast<int64_t>(replacement.size());
		int64_t match_size = static_cast<int64_t>(match.size());
		// this value will never be negative
		int64_t diff = positions_size * (match_size - replacement_size);
		// after this calculation the number can never be negative as the input size is always
		// larger, we have checked for this before
		diff = static_cast<int64_t>(value.size()) - diff;

#ifndef MTL_DISABLE_SOME_ASSERTS
		MTL_ASSERT_MSG(diff >= 0,
		"Error. Number can't be negative. mtl::string::detail::replace_long contains errors.");
#endif  // MTL_DISABLE_SOME_ASSERTS end

		// convert to size_t with no problems as this can't be negative
		difference = static_cast<size_t>(diff);
	}

	// resize to avoid unnecessary allocations
	result.resize(difference);

	// create various iterators
	const auto beginning = value.begin();
	auto it_begin = value.begin();
	auto it_end = value.begin();
	auto it_output = result.begin();

	// loop over the actual number of positions found and not the size of the array
	for (size_t i = 0; i < actual_size; ++i)
	{
		// GCOVR_EXCL_START
		// copies parts to output string and moves the iterators along
		it_end = std::next(beginning, static_cast<std::ptrdiff_t>(positions[i]));
		std::copy(it_begin, it_end, it_output);
		std::advance(it_output, std::distance(it_begin, it_end));
		std::copy(replacement.begin(), replacement.end(), it_output);
		std::advance(it_output, static_cast<std::ptrdiff_t>(replacement.size()));
		it_begin = std::next(it_end, static_cast<std::ptrdiff_t>(match.size()));
		// GCOVR_EXCL_STOP
	}
	// copy from the last match to the end
	std::copy(it_begin, value.end(), it_output);

	// set the input string to the resulting string that we have perfomed all the replacements on
	value = result;
}


} // namespace detail end



/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const std::string& match, const std::string& replacement)
{
	// if the string is relatively short use the algorithm for short strings
	if (value.size() < 350)
	{
		mtl::string::detail::replace_short(value, match, replacement);
	}
	// for longer strings there is another algorithm that is benchmarked and proven faster
	else
	{
		mtl::string::detail::replace_long(value, match, replacement);
	}
}


/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const std::string& match, const char replacement)
{
	replace(value, match, mtl::string::to_string(replacement));
}

/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const std::string& match, const char* replacement)
{
	replace(value, match, mtl::string::to_string(replacement));
}



/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char match, const std::string& replacement)
{
	replace(value, mtl::string::to_string(match), replacement);
}

/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char match, const char replacement)
{
	replace(value, mtl::string::to_string(match), mtl::string::to_string(replacement));
}

/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char match, const char* replacement)
{
	replace(value, mtl::string::to_string(match), mtl::string::to_string(replacement));
}


/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char* match, const std::string& replacement)
{
	replace(value, mtl::string::to_string(match), replacement);
}

/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char* match, const char replacement)
{
	replace(value, mtl::string::to_string(match), mtl::string::to_string(replacement));
}

/// Replaces all places in the input where a match is found with the replacement.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A match to search for.
/// @param[in] replacement A replacement to replace the matches with.
inline void replace(std::string& value, const char* match, const char* replacement)
{
	replace(value, mtl::string::to_string(match), mtl::string::to_string(replacement));
}


// ================================================================================================
// REPLACE_ALL - Replaces all matches in the input with all the replacements.
// ================================================================================================


/// Replaces all places in the input where a match is found with the replacement. The process is
/// repeated for all matches in the matches container replacing them with all replacements from the
/// replacement container. If the number of elements for the provided containers isn't the same it
/// throws std::invalid_argument. The element type for both containers should be std::string.
/// @param[in, out] value An std::string to replace parts that match with a replacement.
/// @param[in] match A container of std::string matches to search for.
/// @param[in] replacement A container of std::string to replace the matches with.
template<typename ContainerMatches, typename ContainerReplacements>
inline 
std::enable_if_t
<mtl::is_std_string_v<typename ContainerMatches::value_type> && 
mtl::is_std_string_v<typename ContainerReplacements::value_type>, void>
replace_all(std::string& value, const ContainerMatches& container_matches, 
			const ContainerReplacements& container_replacements)
{
	// cache size values
	const auto matches_size = container_matches.size();
	const auto replacements_size = container_replacements.size();

	// check that the both containers are the same size
	if(matches_size != replacements_size)
	{
		throw std::invalid_argument(
		"Error mtl::string::replace_all requires the containers to be the same size.");
	}

	// just run mtl::string::replace for each item in each container
	for(size_t i = 0; i < matches_size; ++i)
	{
		mtl::string::replace(value, container_matches[i], container_replacements[i]);
	}
}


} // namespace string end
} // namespace mtl end