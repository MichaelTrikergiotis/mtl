#pragma once
// numeric by Michael Trikergiotis
// 18/06/2018
// 
// Header for arlgorithms related with numbers.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "definitions.hpp" // various definitions
#include <iterator>        // std::distance, std::iterator_traits, std::advance, std::next
#include <numeric>         // std::accumulate
#include <functional>      // std::hash, std::equal_to
#include <unordered_map>   // std::unordered_map
#include <type_traits>     // std::enable_if_t
#include <cstddef>         // std::ptrdiff_t
#include "type_traits.hpp" // mtl::is_number_v

namespace mtl
{




// ================================================================================================
// IOTA - Fills a range with numbers starting by start value and is incremented by step.
// ================================================================================================


/// Fills a range with numbers starting by start value and is incremented by step. It is an an 
/// improved version of std::iota that works with all numeric types supported by C++ both integral
/// and floating point. It supports negative values for the start and the step variable.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @param[in] start An optional starting numeric value. 
/// @param[in] step An optional value that will be used as step from one item to the next. 
template<typename FwdIter>
inline std::enable_if_t<mtl::is_number_v<typename FwdIter::value_type>, void>
iota(FwdIter first, FwdIter last, typename FwdIter::value_type start = 0, 
	 typename FwdIter::value_type step = 1)
{
	typename FwdIter::value_type distance = 0;
	for (auto it = first; it != last; ++it)
	{
		*it = start + distance;
		distance += step;
	}
}



// ================================================================================================
// FREQUENCY         - Creates a frequency table for each element in the range.
// ================================================================================================

// Creates a frequency table for each element in the range. The first parameter of each pair is the
// element while the second parameter is the frequency of appearance for that element. The 
// frequency can never be 0 or lower. The hash is used to define the hashing function used.
// The parameter key_equal is the functor used for key equality.
/// @param[in] begin The beginning of the range.
/// @param[in] end The end of the range.
/// @param[in] hash A hashing function, like std::hash<T>.
/// @param[in] KeyEqual A binary predicate used for equality comparison, like std::equal_to<T>.
/// @return An std::unordered_map with the frequency of apperance of each item.
template<typename Iter, typename Number = size_t, 
		 typename Key = typename std::iterator_traits<Iter>::value_type, 
		 typename Hash = std::hash<Key>,
		 typename KeyEqual = std::equal_to<Key>>
[[nodiscard]]
inline std::enable_if_t<mtl::is_number_v<Number>, std::unordered_map<Key, Number, Hash, KeyEqual>>
frequency(Iter begin, Iter end, Hash hash, KeyEqual key_equal)
{
	// typedef to shorten the type
	using unordered_map_t = std::unordered_map<Key, Number, Hash, KeyEqual>;

	// be carefull as the size can be negative
	auto size = std::distance(begin, end);

	// if the size is negative or 0 return empty container with given hasher and key equality
	// functor
	if (size <= 0) 
	{ 
		// we set the std::unordered_map bucket count to 1 because a bucket count of 0 can cause
		// problems in some C++ standard library implementations
		unordered_map_t empty_container(static_cast<size_t>(1), hash, key_equal);
		return empty_container; 
	}

	// an std::unordered_map with the bucket size as the number of elements with the given hash and
	// the key equality functor, casting from std::ptrdiff to type size_t is ok since we previously
	// checked size is not a negative number
	unordered_map_t freq_table(static_cast<size_t>(size), hash, key_equal);

	// reserve size to avoid allocations, we can safely cast to size_t as we checked previously
	// size is not a negative number
	freq_table.reserve(static_cast<size_t>(size));

	for (auto it = begin; it != end; ++it)
	{
		// add the element if it doesn't exist, increment the frequency counter if it does
		freq_table[*it]++;
	}
	return freq_table;
}


/// Creates a frequency table for each element in the range. The first parameter of each pair is
/// the element while the second parameter is the frequency of appearance for that element. The 
/// frequency can never be 0 or lower. The hash is used to define the hashing function used.
/// The parameter key_equal is the functor used for key equality.
/// @param[in] begin The beginning of the range.
/// @param[in] end The end of the range.
/// @return An std::unordered_map with the frequency of apperance of each item.
template<typename Iter, typename Number = size_t>
[[nodiscard]]
inline std::enable_if_t<mtl::is_number_v<Number>,
std::unordered_map<typename std::iterator_traits<Iter>::value_type, Number>>
frequency(Iter begin, Iter end)
{
	// just use the mtl::frequency template that requires the hash and equality comparator defined
	using Type = typename std::iterator_traits<Iter>::value_type;
	return mtl::frequency(begin, end, std::hash<Type>{}, std::equal_to<Type>{});
}



// ================================================================================================
// MEAN - Returns the mean of all numbers in the range.
// ================================================================================================

/// Returns the mean of all numbers in the range. If there are no elements it returns 0.
/// @param[in] begin The beginning of the range.
/// @param[in] end The end of the range.
/// @return A number that is the mean of all items in the range.
template<typename Iter>
[[nodiscard]]
inline auto mean(Iter first, Iter last) -> typename std::iterator_traits<Iter>::value_type
{
	// define a zero for the given numeric type
	using Type = typename std::iterator_traits<Iter>::value_type;
	constexpr Type zero = 0;

	auto size = std::distance(first, last);
	
	if (size == 0)
	{
		return zero;
	}

	// add all the numbers together
	auto total = std::accumulate(first, last, zero);
	return total / static_cast<Type>(size);
}



// ================================================================================================
// MEDIAN - Returns the median for a sorted range.
// ================================================================================================

/// Returns the median for a sorted range. If there are no elements it returns 0. If there is just
/// a single element returns the first element.
/// @param[in] begin The beginning of a sorted range.
/// @param[in] end The end of a sorted range.
/// @return A number that is the median of all items in the range.
template<typename Iter>
[[nodiscard]]
inline auto median(Iter first, Iter last) -> typename std::iterator_traits<Iter>::value_type
{
	std::ptrdiff_t distance = std::distance(first, last);
	// if there are no elements return 0
	if (distance == 0) 
	{ 
		// define a zero for the given numeric type
		using Type = typename std::iterator_traits<Iter>::value_type;
		constexpr Type zero = 0;
		return zero; 
	}
	// if there is just one element then just return the first element
	if (distance == 1) 
	{ 
		return *first; 
	}
	
	// find the point in the middle, we need to divide by 2 but because division is slower than 
	// multiplication we instead  perform division by a constant number using multiplication
	std::ptrdiff_t mid_point = static_cast<std::ptrdiff_t>(static_cast<double>(distance) * 0.5);

	// check if the median needs to be the mean of two values or just a single value
	// if there remainder is 0 then it means we need to find the mean of two values
	if ((distance % 2) == 0)
	{
		auto it = first;
		std::advance(it, mid_point - 1);
		auto it2 = std::next(it);
		// calculate and return the mean of two values
		return mtl::mean(it, it2);
	}
	// if the remainder is different than 0 then the median is the value in the mid of the range
	else
	{
		// just return the number that is in the middle of the range
		auto it = first;
		std::advance(it, mid_point);
		return *it;
	}
}



} // namespace mtl end