#pragma once
// math by Michael Trikergiotis
// 22/09/2018
// 
// Header for mathematical algorithms.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "definitions.hpp" // various definitions
#include <algorithm>       // std::max
#include <cmath>           // std::fabs, std::round
#include <stdexcept>       // std::invalid_argument
#include <type_traits>	   // std::enable_if_t
#include "type_traits.hpp" // mtl::is_float_v, mtl::is_int_v

namespace mtl
{

// ================================================================================================
// APPROX_EQUAL_ABS  - Approximate equality between two numbers with absolute tolerance.
// APPROX_EQUAL_REL  - Approximate equality between two numbers with relative tolerance.
// APPROX_EQUAL_COMB - Approximate equality between two numbers with absolute and relative
//                     tolerance combined.
// ================================================================================================




/// Approximately equal absolute. Approximate equality between two floating point numbers using an
/// absolute tolerance value. The size of the values v1 and v2 don't affect the absolute tolerance.
/// @param[in] v1 A floating point number. Types can be float, double and long double.
/// @param[in] v2 A floating point number. Types can be float, double and long double.
/// @param[in] absolute_tolerance A optional floating point number used as an absolute tolerance.
/// @return If the numbers are approximately equal.
template<typename Type>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Type>, bool>
approx_equal_abs(Type v1, Type v2, Type absolute_tolerance = static_cast<Type>(0.0009999999))
{
	if (std::fabs(v1 - v2) <= absolute_tolerance)
	{
		return true;
	}
	return false;
}

/// Approximately equal relative. Approximate equality between two floating point numbers using a
/// relative tolerance value. The size of the values v1 and v2 affect the relative tolerance.
/// @param[in] v1 A floating point number. Types can be float, double and long double.
/// @param[in] v2 A floating point number. Types can be float, double and long double.
/// @param[in] relative_tolerance A optional floating point number used as an relative tolerance.
/// @return If the numbers are approximately equal.
template<typename Type>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Type>, bool>
approx_equal_rel(Type v1, Type v2, Type relative_tolerance = static_cast<Type>(0.0000099999))
{
	if (std::fabs(v1 - v2) <= relative_tolerance * std::max(std::fabs(v1), std::fabs(v2)))
	{
		return true;
	}
	return false;
}

/// Approximately equal combined. Approximate equality between two floating point numbers using an
/// absolute tolerance value and a relative tolerance value. The size of the values v1 and v2 
/// affect the relative tolerance but not the absolute tolerance.
/// @param[in] v1 A floating point number. Types can be float, double and long double.
/// @param[in] v2 A floating point number. Types can be float, double and long double.
/// @param[in] absolute_tolerance A optional floating point number used as an absolute tolerance.
/// @param[in] relative_tolerance A optional floating point number used as an relative tolerance.
/// @return If the numbers are approximately equal.
template<typename Type>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Type>, bool>
approx_equal_comb(Type v1, Type v2, Type absolute_tolerance = static_cast<Type>(0.0009999999),
					  Type relative_tolerance = static_cast<Type>(0.0000099999))
{
	auto relative = relative_tolerance * std::max(std::fabs(v1), std::fabs(v2));
	auto tolerance = std::max(absolute_tolerance, relative);
	if (std::fabs(v1 - v2) <= tolerance)
	{
		return true;
	}
	return false;
}


// ================================================================================================
// PERCENT_WHOLE   - Calculate the whole number given the percentage and the portion.
// PERCENT_PORTION - Calculate the portion number given the percentage and the whole.
// PERCENT         - Calculate the percent number given the portion and the whole.
// ================================================================================================

/// Given a number that is a percentage of the whole and a number that is a portion of the whole it
/// returns a number that represents the whole. If the percent parameter is 0 then it is a
/// division by zero, but if the macro MTL_DIV_ZERO_THROW is defined then it throws an 
/// std::invalid_argument exception instead.
/// @param[in] percent A number representing the percentage.
/// @param[in] portion A number representing the portion of the whole.
/// @return A number representing the whole.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Number>, Number>
percent_whole(Number percent, Number portion)
{

// if this macro is defined prevents division by zero by throwing an exception
#if defined(MTL_DIV_ZERO_THROW)
	constexpr Number zero = static_cast<Number>(0.0);
	// check if zero, comparing floating point numbers with equality will make compilers complain
	// with this trick we have to use one more comparison but no compiler complains
	if(!(percent < zero) && !(percent > zero))
	{ 
		throw std::invalid_argument(
		"The percent parameter is zero. This results in division by zero.");
	}
#endif // MTL_DIV_ZERO_THROW end

	constexpr Number hundred = static_cast<Number>(100.0);
	// calculate the portion
	const Number result = (hundred / percent) * portion;
	return result;
}


/// Given a number that is a percentage of the whole and a number that is a portion of the whole it
/// returns a number that represents the whole. If the percent parameter is 0 then it is a
/// division by zero, but if the macro MTL_DIV_ZERO_THROW is defined then it throws an 
/// std::invalid_argument exception instead.
/// @param[in] percent A number representing the percentage.
/// @param[in] portion A number representing the portion of the whole.
/// @return A number representing the whole.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_int_v<Number>, Number>
percent_whole(Number percent, Number portion)
{
	// to find correct percentage for an integer we have to convert the integral numeric type
	// to floating point type double, double fits all integral types
	const double percent_d = static_cast<double>(percent);
	const double portion_d = static_cast<double>(portion);
	// calculate the portion by passing it to the mtl::percent_whole that accepts floating point
	const Number res = static_cast<Number>(std::round(mtl::percent_whole(percent_d, portion_d)));
	return res;
}


/// Given a number that represents the whole and a number that represents a percentage of that
/// whole returns a number that represents the portion of the whole for the given percentage. 
/// @param[in] whole A number representing the whole.
/// @param[in] percent A number representing the percentage.
/// @return A number representing the portion.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Number>, Number> 
percent_portion(Number whole, Number percent)
{
	// we need to divide by 100.0 but because division is slower	than multiplication we instead 
	// perform division by a constant number using multiplication, this makes this function faster
	// by 200% to 800% depending on OS, CPU, compiler and compiler flags
	constexpr Number one_hundredth = static_cast<Number>(0.01l);
	// calculate the portion
	const Number result = (percent * whole) * one_hundredth;
	return result;
}


/// Given a number that represents the whole and a number that represents a percentage of that
/// whole returns a number that represents the portion of the whole for the given percentage. 
/// @param[in] whole A number representing the whole.
/// @param[in] percent A number representing the percentage.
/// @return A number representing the portion.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_int_v<Number>, Number>
percent_portion(Number whole, Number percent)
{
	// to find correct percentage for an integer we have to convert the integral numeric type
	// to floating point type double because double fits all integral types
	const double percent_d = static_cast<double>(percent);
	const double whole_d = static_cast<double>(whole);

	// since we converted the numbers to double we can call the percent_portion for doubles
	const double result_d = mtl::percent_portion(whole_d, percent_d);
	const Number result = static_cast<Number>(std::round(result_d));
	return result;
}


/// Given a number that the whole and a number that represents a portion of that whole 
/// returns what percentage of the whole that portion represents. If the whole parameter is 0 then
/// it is a division by zero, but if the macro MTL_DIV_ZERO_THROW is defined then it throws an 
/// std::invalid_argument exception instead.
/// @param[in] whole A number representing the whole.
/// @param[in] percent A number representing the portion.
/// @return A number representing the percentage.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_float_v<Number>, Number>
percent(Number whole, Number portion)
{

// if this macro is defined prevents division by zero by throwing an exception
#if defined(MTL_DIV_ZERO_THROW)
	constexpr Number zero = static_cast<Number>(0.0);
	// check if zero, comparing floating point numbers with equality will make compilers complain
	// with this trick we have to use one more comparison but no compiler complains
	if(!(whole < zero) && !(whole > zero))
	{ 
		throw std::invalid_argument(
		"The whole parameter is zero. This results in division by zero.");
	}
#endif // MTL_DIV_ZERO_THROW end

	constexpr Number hundred = static_cast<Number>(100.0);
	// find the percentage of the portion from the whole
	const Number result = (portion / whole) * hundred;
	return result;
}


/// Given a number that the whole and a number that represents a portion of that whole 
/// returns what percentage of the whole that portion represents. If the whole parameter is 0 then
/// it is a division by zero, but if the macro MTL_DIV_ZERO_THROW is defined then it throws an 
/// std::invalid_argument exception instead.
/// @param[in] whole A number representing the whole.
/// @param[in] percent A number representing the portion.
/// @return A number representing the percentage.
template<typename Number>
[[nodiscard]]
inline std::enable_if_t<mtl::is_int_v<Number>, Number>
percent(Number whole, Number portion)
{
	// to find correct percentage for an integer we have to convert the integral numeric type
	// to double, double fits all integral types 
	const double whole_d = static_cast<double>(whole);
	const double part_d = static_cast<double>(portion);
	// pass the number to mlt::percent that accept floating point types
	const Number result = static_cast<Number>(std::round(percent(whole_d, part_d)));
	return result;
}


} // namespace mtl end