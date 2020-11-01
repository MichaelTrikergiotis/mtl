#pragma once
// conversion by Michael Trikergiotis
// 04/05/2019
// 
// Header for performing casts and converting between types.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include <cmath>           // std::pow
#include <charconv> 	   // std::from_chars
#include <system_error>    // std::errc
#include <string>          // std::string
#include <limits>          // std::numeric_limits
#include <utility>         // std::pair
#include <stdexcept>       // std::overflow_error, std::invalid_argument
#include <cmath>           // std::lround, std::llround

namespace mtl
{

// ================================================================================================
// TO_NUM      - Converts an std::string to any numeric type.
// TO_NUM_NOEX - Converts an std::string to any numeric type without throwing exceptions.
// ================================================================================================


namespace detail
{

// Converts const char* to double. If there is an error or the conversion fails it throws
// std::invalid_argument.
template<typename FloatingPoint>
[[nodiscard]]
inline FloatingPoint to_double_impl(const char* num)
{
	// if the const char* is empty we have an error and can't convert to a number successfully
	if (!*num)
	{
		// mark this conversion as an error by throwing an exception
		throw std::invalid_argument("Input is empty. No characters for conversion.");
	}

	constexpr FloatingPoint zero = static_cast<FloatingPoint>(0.0);

	int sign = 1;
	FloatingPoint integer_part = zero;
	FloatingPoint fraction_part = zero;
	bool has_fraction = false;
	bool has_expo = false;

	// take care of +/- sign
	if (*num == '-')
	{
		++num;
		sign = -1;
	}
	else if (*num == '+')
	{
		++num;
	}

	while (*num != '\0')
	{
		if ((*num >= '0') && (*num <= '9'))
		{
			auto p = (*num - '0');
			integer_part = integer_part * 10 + static_cast<FloatingPoint>(p);
		}
		else if (*num == '.')
		{
			has_fraction = true;
			++num;
			break;
		}
		else
		{
			// if we reach this point then it means we encountered an error
			throw std::invalid_argument("One or more characters are invalid. Can't be converted.");
		}
		++num;
	}

	if (has_fraction)
	{
		FloatingPoint fraction_exponent = static_cast<FloatingPoint>(0.1);

		while (*num != '\0')
		{
			if ((*num >= '0') && (*num <= '9'))
			{
				auto p = (*num - '0');
				fraction_part += fraction_exponent * static_cast<FloatingPoint>(p);
				fraction_exponent *= static_cast<FloatingPoint>(0.1);
			}
			else if ((*num == 'e') || (*num == 'E'))
			{
				has_expo = true;
				++num;
				break;
			}
			else
			{
				// if we reach this point then it means we encountered an error
				throw std::invalid_argument(
					"One or more characters are invalid. Can't be converted.");
			}
			++num;
		}
	}

	// parsing exponet part
	FloatingPoint exp_part = static_cast<FloatingPoint>(1.0);
	if ((*num != '\0') && (has_expo))
	{
		int64_t exp_sign = 1;
		if (*num == '-')
		{
			exp_sign = -1;
			++num;
		}
		else if (*num == '+')
		{
			++num;
		}

		int64_t e = 0;
		while ((*num != '\0') && (*num >= '0') && (*num <= '9'))
		{
			e = e * 10 + *num - '0';
			++num;
		}
		constexpr FloatingPoint ten = static_cast<FloatingPoint>(10.0);
		exp_part = std::pow(ten, static_cast<FloatingPoint>(exp_sign * e));
	}
	return static_cast<FloatingPoint>(sign) * (integer_part + fraction_part) * exp_part;
}


// Converts const char* to double. Doesn't throw. If it can't convert set the success to false
// and returns 0.
template<typename FloatingPoint>
[[nodiscard]]
inline std::pair<FloatingPoint, bool> to_double_impl_noex(const char* num) noexcept
{
	// if the const char* is empty we have an error and can't convert to a number successfully
	if (!*num)
	{
		// mark this conversion as an error by setting the boolean to false
		auto zero_pair = std::pair<FloatingPoint, bool>(static_cast<FloatingPoint>(0.0), false);
		return zero_pair;
	}

	constexpr FloatingPoint zero = static_cast<FloatingPoint>(0.0);

	int sign = 1;
	FloatingPoint integer_part = zero;
	FloatingPoint fraction_part = zero;
	bool has_fraction = false;
	bool has_expo = false;

	// take care of +/- sign
	if (*num == '-')
	{
		++num;
		sign = -1;
	}
	else if (*num == '+')
	{
		++num;
	}

	while (*num != '\0')
	{
		if ((*num >= '0') && (*num <= '9'))
		{
			auto p = (*num - '0');
			integer_part = integer_part * 10 + static_cast<FloatingPoint>(p);
		}
		else if (*num == '.')
		{
			has_fraction = true;
			++num;
			break;
		}
		else
		{
			// if we reach this point then it means we encountered an error
			return std::pair<FloatingPoint, bool>(zero, false);
		}
		++num;
	}

	if (has_fraction)
	{
		FloatingPoint fraction_exponent = static_cast<FloatingPoint>(0.1);

		while (*num != '\0')
		{
			if ((*num >= '0') && (*num <= '9'))
			{
				auto p = (*num - '0');
				fraction_part += fraction_exponent * static_cast<FloatingPoint>(p);
				fraction_exponent *= static_cast<FloatingPoint>(0.1);
			}
			else if ((*num == 'e') || (*num == 'E'))
			{
				has_expo = true;
				++num;
				break;
			}
			else
			{
				// if we reach this point then it means we encountered an error
				return std::pair<FloatingPoint, bool>(zero, false);
			}
			++num;
		}
	}

	// parsing exponet part
	FloatingPoint exp_part = static_cast<FloatingPoint>(1.0);
	if ((*num != '\0') && (has_expo))
	{
		int64_t exp_sign = 1;
		if (*num == '-')
		{
			exp_sign = -1;
			++num;
		}
		else if (*num == '+')
		{
			++num;
		}

		int64_t e = 0;
		while ((*num != '\0') && (*num >= '0') && (*num <= '9'))
		{
			e = e * 10 + *num - '0';
			++num;
		}
		constexpr FloatingPoint ten = static_cast<FloatingPoint>(10.0);
		exp_part = std::pow(ten, static_cast<FloatingPoint>(exp_sign * e));
	}
	FloatingPoint res;
	res = static_cast<FloatingPoint>(sign) * (integer_part + fraction_part) * exp_part;
	return std::pair<FloatingPoint, bool>(res, true);
}



// Converts const char* to double. Doesn't throw. If it can't convert returns a pair with the 
// double set to 0.0 and the boolean to false.
template<typename FloatingPoint>
[[nodiscard]]
inline FloatingPoint to_double_impl_noex(const char* num, bool& success) noexcept
{
	// if the const char* is empty we have an error and can't convert to a number successfully
	if (!*num)
	{
		// mark this conversion as an error by setting the boolean to false
		success = false;
		return static_cast<FloatingPoint>(0.0);
	}

	constexpr FloatingPoint zero = static_cast<FloatingPoint>(0.0);

	int sign = 1;
	FloatingPoint integer_part = zero;
	FloatingPoint fraction_part = zero;
	bool has_fraction = false;
	bool has_expo = false;

	// take care of +/- sign
	if (*num == '-')
	{
		++num;
		sign = -1;
	}
	else if (*num == '+')
	{
		++num;
	}

	while (*num != '\0')
	{
		if ((*num >= '0') && (*num <= '9'))
		{
			auto p = (*num - '0');
			integer_part = integer_part * 10 + static_cast<FloatingPoint>(p);
		}
		else if (*num == '.')
		{
			has_fraction = true;
			++num;
			break;
		}
		else
		{
			// if we reach this point then it means we encountered an error
			success = false;
			return zero;
		}
		++num;
	}

	if (has_fraction)
	{
		FloatingPoint fraction_exponent = static_cast<FloatingPoint>(0.1);

		while (*num != '\0')
		{
			if ((*num >= '0') && (*num <= '9'))
			{
				auto p = (*num - '0');
				fraction_part += fraction_exponent * static_cast<FloatingPoint>(p);
				fraction_exponent *= static_cast<FloatingPoint>(0.1);
			}
			else if ((*num == 'e') || (*num == 'E'))
			{
				has_expo = true;
				++num;
				break;
			}
			else
			{
				// if we reach this point then it means we encountered an error
				success = false;
				return zero;
			}
			++num;
		}
	}

	// parsing exponet part
	FloatingPoint exp_part = static_cast<FloatingPoint>(1.0);
	if ((*num != '\0') && (has_expo))
	{
		int64_t exp_sign = 1;
		if (*num == '-')
		{
			exp_sign = -1;
			++num;
		}
		else if (*num == '+')
		{
			++num;
		}

		int64_t e = 0;
		while ((*num != '\0') && (*num >= '0') && (*num <= '9'))
		{
			e = e * 10 + *num - '0';
			++num;
		}
		constexpr FloatingPoint ten = static_cast<FloatingPoint>(10.0);
		exp_part = std::pow(ten, static_cast<FloatingPoint>(exp_sign * e));
	}
	success = true;
	return static_cast<FloatingPoint>(sign) * (integer_part + fraction_part) * exp_part;
}


// ---




// Converts the given string to an automatically deduced numeric type. Throws exceptions in case
// of error.
struct to_num_deductor
{
	// raw pointer to string reference, the pointer is not an owner but a const observer
	const std::string* _t;
	// constructor that just points the pointer to the correct string
	to_num_deductor(const std::string& t) { _t = &t; }

	// Converts the given std::string to given integral type.
	template<typename IntegralType>
	IntegralType to_integral_impl()
	{
		IntegralType result = static_cast<IntegralType>(0);
		auto [ptr, error] = std::from_chars(_t->data(), _t->data() + _t->size(), result);
		if (error == std::errc())
		{
			return result;
		}
		// GCOVR_EXCL_START
		throw std::invalid_argument("Conversion error. Can't be converted successfully.");
		// GCOVR_EXCL_STOP
	}

	// automatic deduction where return type is int8_t
	operator int8_t()
	{
		return to_integral_impl<int8_t>();
	}
	// automatic deduction where return type is short
	operator short()
	{
		return to_integral_impl<short>();
	}
	// automatic deduction where return type is int
	operator int()
	{
		return to_integral_impl<int>();
	}
	// automatic deduction where return type is long
	operator long()
	{
		return to_integral_impl<long>();
	}
	// automatic deduction where return type is long long
	operator long long()
	{
		return to_integral_impl<long long>();
	}

	// automatic deduction where return type is uint8_t
	operator uint8_t()
	{
		return to_integral_impl<uint8_t>();
	}
	// automatic deduction where return type is unsigned short
	operator unsigned short()
	{
		return to_integral_impl<unsigned short>();
	}
	// automatic deduction where return type is unsigned int
	operator unsigned int()
	{
		return to_integral_impl<unsigned int>();
	}
	// automatic deduction where return type is unsigned long
	operator unsigned long()
	{
		return to_integral_impl<unsigned long>();
	}
	// automatic deduction where return type is unsigned long long
	operator unsigned long long()
	{
		return to_integral_impl<unsigned long long>();
	}


	// automatic deduction where return type is float
	operator float()
	{
		return to_double_impl<float>(_t->data());
	}
	// automatic deduction where return type is double
	operator double()
	{
		return to_double_impl<double>(_t->data());
	}
	// automatic deduction where return type is long double
	operator long double()
	{
		return to_double_impl<long double>(_t->data());
	}
};


// Converts the given string to an automatically deduced numeric type without throwing exceptions
// in case of error.
struct to_num_deductor_noex
{
	// raw pointer to string reference, the pointer is not an owner but a const observer
	const std::string* _t;
	// raw pointer to bool reference
	bool* _success;
	// constructor that just points the pointer to the correct string
	to_num_deductor_noex(const std::string& t, bool& success) { _t = &t; _success = &success; }

	// Converts the given std::string to given integral type.
	template<typename IntegralType>
	IntegralType to_integral_impl()
	{
		IntegralType result = static_cast<IntegralType>(0);
		auto [ptr, error] = std::from_chars(_t->data(), _t->data() + _t->size(), result);
		if (error == std::errc())
		{
			*_success = true;
			return result;
		}
		*_success = false;
		return static_cast<IntegralType>(0);
	}

	// automatic deduction where return type is int8_t
	operator int8_t()
	{
		return to_integral_impl<int8_t>();
	}
	// automatic deduction where return type is short
	operator short()
	{
		return to_integral_impl<short>();
	}
	// automatic deduction where return type is int
	operator int()
	{
		return to_integral_impl<int>();
	}
	// automatic deduction where return type is long
	operator long()
	{
		return to_integral_impl<long>();
	}
	// automatic deduction where return type is long long
	operator long long()
	{
		return to_integral_impl<long long>();
	}

	// automatic deduction where return type is uint8_t
	operator uint8_t()
	{
		return to_integral_impl<uint8_t>();
	}
	// automatic deduction where return type is unsigned short
	operator unsigned short()
	{
		return to_integral_impl<unsigned short>();
	}
	// automatic deduction where return type is unsigned int
	operator unsigned int()
	{
		return to_integral_impl<unsigned int>();
	}
	// automatic deduction where return type is unsigned long
	operator unsigned long()
	{
		return to_integral_impl<unsigned long>();
	}
	// automatic deduction where return type is unsigned long long
	operator unsigned long long()
	{
		return to_integral_impl<unsigned long long>();
	}


	// automatic deduction where return type is float
	operator float()
	{
		return to_double_impl_noex<float>(_t->data(), *_success);
	}
	// automatic deduction where return type is double
	operator double()
	{
		return to_double_impl_noex<double>(_t->data(), *_success);
	}
	// automatic deduction where return type is long double
	operator long double()
	{
		return to_double_impl_noex<long double>(_t->data(), *_success);
	}
};


// Converts the given string to an automatically deduced numeric type without throwing exceptions
// in case of error. Deductor for std::pair specialization.
struct to_num_deductor_noex_pair
{
	// raw pointer to string reference, the pointer is not an owner but a const observer
	const std::string* _t;
	// constructor that just points the pointer to the correct string
	to_num_deductor_noex_pair(const std::string& t) { _t = &t; }

	// Converts the given std::string to given integral type.
	template<typename IntegralType>
	std::pair<IntegralType, bool> to_integral_impl()
	{
		IntegralType result = static_cast<IntegralType>(0);
		auto [ptr, error] = std::from_chars(_t->data(), _t->data() + _t->size(), result);
		if (error == std::errc())
		{
			return std::pair<IntegralType, bool>(result, true);
		}
		return std::pair<IntegralType, bool>(static_cast<IntegralType>(0), false);
	}


	// automatic deduction where return type is int8_t
	operator std::pair<int8_t, bool>()
	{
		return to_integral_impl<int8_t>();
	}
	// automatic deduction where return type is short
	operator std::pair<short, bool>()
	{
		return to_integral_impl<short>();
	}
	// automatic deduction where return type is int
	operator std::pair<int, bool>()
	{
		return to_integral_impl<int>();
	}
	// automatic deduction where return type is long
	operator std::pair<long, bool>()
	{
		return to_integral_impl<long>();
	}
	// automatic deduction where return type is long long
	operator std::pair<long long, bool>()
	{
		return to_integral_impl<long long>();
	}

	// automatic deduction where return type is uint8_t
	operator std::pair<uint8_t, bool>()
	{
		return to_integral_impl<uint8_t>();
	}
	// automatic deduction where return type is unsigned short
	operator std::pair<unsigned short, bool>()
	{
		return to_integral_impl<unsigned short>();
	}
	// automatic deduction where return type is unsigned int
	operator std::pair<unsigned int, bool>()
	{
		return to_integral_impl<unsigned int>();
	}
	// automatic deduction where return type is unsigned long
	operator std::pair<unsigned long, bool>()
	{
		return to_integral_impl<unsigned long>();
	}
	// automatic deduction where return type is unsigned long long
	operator std::pair<unsigned long long, bool>()
	{
		return to_integral_impl<unsigned long long>();
	}


	// automatic deduction where return type is float
	operator std::pair<float, bool>()
	{
		return to_double_impl_noex<float>(_t->data());
	}
	// automatic deduction where return type is double
	operator std::pair<double, bool>()
	{
		return to_double_impl_noex<double>(_t->data());
	}
	// automatic deduction where return type is long double
	operator std::pair<long double, bool>()
	{
		return to_double_impl_noex<long double>(_t->data());
	}
};

} // namsepace detail end


/// Convert a string to a number. Number type is automatically decuced. On error it throws 
/// std::invalid_argument if no conversion could be performed. 
/// @param[in] input An std::string representing a number.
/// @return A number of any type. You have to specify the resulting type and not use auto.
[[nodiscard]]
inline auto to_num(const std::string& input)
{
	return detail::to_num_deductor(input);
}

/// Convert a string to a number. Number type is automatically decuced. On error it returns 0 if it
/// can not convert the value and the boolean is set to false.
/// @param[in] input An std::string representing a number.
/// @param[out] success A boolean used to denote success or failure to covert to a number.
/// @return A number of any type. You have to specify the resulting type and not use auto.
[[nodiscard]]
inline auto to_num_noex(const std::string& input, bool& success) noexcept
{
	return detail::to_num_deductor_noex(input, success);
}


/// Convert a string to a number. Returns a std::pair containing the number and if it succeeded.
/// Number type is automatically decuced. On error it returns a pair containing 0 for the 
/// requested numeric type and a boolean set to false to indicate failure.
/// @param[in] input An std::string representing a number.
/// @return An std::pair of any type of number and a boolean. You have to specify the resulting 
///         type and not use auto.
[[nodiscard]]
inline auto to_num_noex(const std::string& input) noexcept
{
	return detail::to_num_deductor_noex_pair(input);
}


// Because on a false positive we have to disable MSVC static analyzers warning about overflow in
// constant arithmetic. It is certainely a false positive. It has some strange behavior too.
// It only happens when the code is compiled in Release mode (/O2). It doesn't like casting
// long double to other types even though we previously checked the number to fit the lower and 
// upper bounds of that type. It happily allows us to cast long double to double and then to
// any type we want but it has the peculiarity that it want each cast to be in each own line else
// it doesn't understand it and complains for the same thing again.
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4756 )
#endif 


// ================================================================================================
// NUMERIC_CAST       - Casts from one numeric type to another. Throws an exception if the value
// 					    doesn't fit the requested type.
// NUMERIC_CAST_NOEX  - Casts from one numeric type to another. Doesn't throw if value doesn't fit.
// ================================================================================================


/// Casts from one numeric type to another. Supports casting from unsigned to signed and 
/// vice versa. If the value doesn't fit the resulting type it throws an exception.
/// @param[in] number A number of any type.
/// @return Any numeric type. You have to specify the resulting type and not use auto.
template<typename Result, typename Type>
[[nodiscard]]
inline Result numeric_cast(const Type number)
{
	using numeric_limit = std::numeric_limits<Result>;
	// all types of C++ fit inside long double so conversion is not a problem
	constexpr long double result_min = static_cast<long double>(numeric_limit::lowest());
	constexpr long double result_max = static_cast<long double>(numeric_limit::max());
	const long double number_ld = static_cast<long double>(number);
	// values can be safely compared since they are all the same type
	if ((number_ld >= result_min) && (number_ld <= result_max))
	{
		return static_cast<Result>(number);
	}
	// value can't fit the resulting type
	throw std::overflow_error("Requested value can't fit target type."); // GCOVR_EXCL_LINE
} 


/// Casts from one numeric type to another. Supports casting from unsigned to signed and vice
/// versa. If the value doesn't fit the resulting type returns a zero of the resulting type and 
/// sets the boolean to false. Doesn't throw exceptions.
/// @param[in] number A number of any type.
/// @return An std::pair with any numeric type and a boolean. You have to specify the resulting
///         type and not use auto.
template<typename Result, typename Type>
[[nodiscard]]
inline std::pair<Result, bool> numeric_cast_noex(const Type number) noexcept
{
	using numeric_limit = std::numeric_limits<Result>;
	// all types of C++ fit inside long double so conversion is not a problem
	constexpr long double result_min = static_cast<long double>(numeric_limit::lowest());
	constexpr long double result_max = static_cast<long double>(numeric_limit::max());
	const long double number_ld = static_cast<long double>(number);
	// values can be safely compared since they are all the same type
	if ((number_ld >= result_min) && (number_ld <= result_max))
	{
		return std::pair<Result, bool>(static_cast<Result>(number), true);
	}
	// value can't find the resulting type
	return std::pair<Result, bool>(static_cast<Result>(0), false);
}

/// Casts from one numeric type to another. Supports casting from unsigned to signed and vice
/// versa. If the value doesn't fit the resulting type it returns a zero and sets the boolean
/// to false. Doesn't throw exceptions.
/// @param[in] number A number of any type.
/// @param[out] success A boolean used to denote success or failure to cast.
/// @return Any numeric type. You have to specify the resulting type and not use auto.
template<typename Result, typename Type>
[[nodiscard]]
inline Result numeric_cast_noex(const Type number, bool& success) noexcept
{
	using numeric_limit = std::numeric_limits<Result>;
	// all types of C++ fit inside long double so conversion is not a problem
	constexpr long double result_min = static_cast<long double>(numeric_limit::lowest());
	constexpr long double result_max = static_cast<long double>(numeric_limit::max());
	const long double number_ld = static_cast<long double>(number);
	// values can be safely compared since they are all the same type
	if ((number_ld >= result_min) && (number_ld <= result_max))
	{
		success = true;
		return static_cast<Result>(number);
	}
	// value can't find the resulting type
	success = false;
	return static_cast<Result>(0);
}



// ================================================================================================
// ROUNDING_CAST      - Round and cast a floating point number to int/long/long long. Can throw.
// ROUNDING_CAST_NOEX - Round and cast a floating point number to int/long/long long. 
//                      Doesn't throw.
// ================================================================================================


namespace detail
{

// Actual rounding_cast deductor implmentation.
template<typename FloatingPoint>
struct rounding_cast_deductor
{
	FloatingPoint number;
	rounding_cast_deductor(FloatingPoint value)
	{
		number = value;
	}

	operator int()
	{
		// check that it fits int
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<int>::lowest())) && 
		    (number <= static_cast<FloatingPoint>(std::numeric_limits<int>::max())))
		{
			// it is ok to cast from long to int as we know it fits as we checked previously
			return static_cast<int>(std::lround(number));
		}
		// value can't fit the resulting type
		throw std::overflow_error("Requested value can't fit target type."); // GCOVR_EXCL_LINE
	}

	operator long()
	{
		// check that it fits long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long>::max())))
		{
			return std::lround(number);
		}
		// value can't fit the resulting type
		throw std::overflow_error("Requested value can't fit target type."); // GCOVR_EXCL_LINE
	}

	operator long long()
	{
		// check that it fits long long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long long>::max())))
		{
			return std::llround(number);
		}
		// value can't fit the resulting type
		throw std::overflow_error("Requested value can't fit target type."); // GCOVR_EXCL_LINE
	}
};

// Actual rounding_cast deductor with no exceptions implmentation that can deduce std::pair.
template<typename FloatingPoint>
struct rounding_cast_deductor_noex_pair
{
	FloatingPoint number;
	rounding_cast_deductor_noex_pair (FloatingPoint value)
	{
		number = value;
	}

	operator std::pair<int, bool>() noexcept
	{
		// check that it fits int
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<int>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<int>::max())))
		{
			// it is ok to cast from long to int as we know it fits as we checked previously
			return std::make_pair(static_cast<int>(std::lround(number)), true);
		}
		return std::make_pair(0, false);
	}

	operator std::pair<long, bool>() noexcept
	{
		// check that it fits long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long>::max())))
		{
			return std::make_pair(std::lround(number), true);
		}
		return std::make_pair(0L, false);
	}

	operator std::pair<long long, bool>() noexcept
	{
		// check that it fits long long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long long>::max())))
		{
			return std::make_pair(std::llround(number), true);
		}
		return std::make_pair(0LL, false);
	}
};

// Actual rounding_cast deductor with no exceptions implmentation.
template<typename FloatingPoint>
struct rounding_cast_deductor_noex
{
	FloatingPoint number;
	bool* success;
	rounding_cast_deductor_noex(FloatingPoint value, bool& done)
	{
		number = value;
		success = &done;
	}

	operator int() noexcept
	{
		// check that it fits int
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<int>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<int>::max())))
		{
			*success = true;
			// it is ok to cast from long to int as we know it fits as we checked previously
			return static_cast<int>(std::lround(number));
		}
		*success = false;
		return 0;
	}

	operator long() noexcept
	{
		// check that it fits long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long>::max())))
		{
			*success = true;
			return static_cast<long>(std::lround(number));
		}
		*success = false;
		return 0L;
	}

	operator long long() noexcept
	{
		// check that it fits long long
		if ((number >= static_cast<FloatingPoint>(std::numeric_limits<long long>::lowest())) &&
			(number <= static_cast<FloatingPoint>(std::numeric_limits<long long>::max())))
		{
			*success = true;
			return std::llround(number);
		}
		*success = false;
		return 0LL;
	}
};

}

/// Rounds and casts a floating point number to int, long or long long. Can throw 
/// std::overflow_error if the requested value doesn't fit the target type.
/// @param[in] number A floating point number. Types can be float, double and long double.
/// @return Any integral numeric type. You have to specify the resulting type and not use auto.
template<typename FloatingPoint>
[[nodiscard]]
inline auto rounding_cast(FloatingPoint number)
{
	return detail::rounding_cast_deductor<FloatingPoint>(number);
}

/// Rounds and casts a floating point number to int, long or long long. Doesn't throw exceptions.
/// Returns a std::pair with either int, long, long long and a bool that is true if the cast
/// succeeded or false if it failed.
/// @param[in] number A floating point number. Types can be float, double and long double.
/// @return An std::pair with an integral numeric type and a boolean. You have to specify the 
///         resulting type and not use auto.
template<typename FloatingPoint>
[[nodiscard]]
inline auto rounding_cast_noex(FloatingPoint number) noexcept
{
	return detail::rounding_cast_deductor_noex_pair<FloatingPoint>(number);
}

/// Rounds and casts a floating point number to int, long or long long. Doesn't throw exceptions.
/// The bool that is set to true if the cast succeeded or false if it failed.
/// @param[in] number A floating point number. Types can be float, double and long double.
/// @param[out] success A boolean used to denote success or failure to cast.
/// @return Any integral numeric type. You have to specify the resulting type and not use auto.
template<typename FloatingPoint>
[[nodiscard]]
inline auto rounding_cast_noex(FloatingPoint number, bool& success) noexcept
{
	return detail::rounding_cast_deductor_noex<FloatingPoint>(number, success);
}





// stop suppressing MSVC warnings about false positives
#if defined(_MSC_VER)
#pragma warning( pop )
#endif


} // namespace mtl end