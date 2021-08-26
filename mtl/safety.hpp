#pragma once
// safety header by Michael Trikergiotis
// 02/02/2018
// 
// 
// This header contains safe algorithms that help reduce bugs.
// 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp" // various definitions
#include <algorithm>       // std::copy
#include <iterator>        // std::next, std::begin
#include <type_traits>     // std::enable_if_t
#include "type_traits.hpp" // mtl::has_size_v
#include "utility.hpp"     // MTL_ASSERT_MSG



namespace mtl
{


// ================================================================================================
// SAFE_COPY   - Is a safe version of std::copy that works with containers.
// SAFE_COPY_N - Is a safe version of std::copy_n that works with containers.
// ================================================================================================

/// mtl::safe_copy is a safer bound checking version of std::copy that protects from all 
/// out of bounds errors. Works with any container that supports the size function. Copies all 
/// elements from one container to the other. If everything is correct, copying is performed and
/// it returns true. In the case that the output container is smaller than the source no copying
/// is performed and it returns false. Doesn't throw exceptions.
/// @param[in] source An input container.
/// @param[out] destination An output container.
/// @return If the copying was performed successfully.
template<typename InContainer, typename OutContainer>
[[nodiscard]]
inline std::enable_if_t<mtl::has_size_v<InContainer>&& mtl::has_size_v<OutContainer>, bool>
safe_copy(const InContainer& source, OutContainer& destination) noexcept
{
	// sizes of both containers
	const size_t source_size = source.size();
	const size_t dest_size = destination.size();

#ifndef MTL_DISABLE_SOME_ASSERTS
	// check bounds errors with assert to report out of bound errors while debugging
	MTL_ASSERT_MSG((dest_size >= source_size), 
			   	   "Destination container smaller than the source container.");
#endif // MTL_DISABLE_SOME_ASSERTS end

	// check out of bounds at runtime
	if (dest_size >= source_size)
	{
		// perform a std::copy without no worries of out of bounds errors
		std::copy(source.begin(), source.end(), destination.begin());
		return true;
	}
	return false;
}


/// mtl::safe_copy is a safer bound checking version of std::copy that protects from all 
/// out of bounds errors. Requires you to pass iterators from an input range from in_first to 
/// in_last and an output range from out_first to out_last. If everything is correct, copying is 
/// performed and it returns true. In case that any of the iterators is out of bounds for either
/// range no copying is performed and it returns false. Doesn't throw exceptions.
/// @param[in] in_first Iterator to the start of the input range.
/// @param[in] in_last Iterator to the end of the input range.
/// @param[in] out_first Iterator to the start of the output range.
/// @param[in] out_last Iterator to the end of the output range.
/// @return If the copying was performed successfully.
template<typename InIter, typename OutIter>
[[nodiscard]]
inline bool safe_copy(InIter in_first, InIter in_last, OutIter out_first, 
					  OutIter out_last) noexcept
{
	// sizes of both ranges, if iterators are incorrect the numbers may be negative
	const auto source_distance = std::distance(in_first, in_last);
	const auto dest_distance = std::distance(out_first, out_last);

	// if the input range is exactly 0 elements return true to report copying was performed
	// successfully as there is nothing to copy
	if (source_distance == 0) { return true; }

#ifndef MTL_DISABLE_SOME_ASSERTS
	// check bounds errors with assert to report out of bound errors while debugging
	MTL_ASSERT_MSG(!(source_distance < 0), "Input iterators are incorrect.");
	MTL_ASSERT_MSG(!(dest_distance < 0), "Output iterators are incorrect.");
	MTL_ASSERT_MSG(!(dest_distance < source_distance), 
				   "The output range is smaller than the input range.");
#endif // MTL_DISABLE_SOME_ASSERTS end

	// if any of the values is negative or if the destination is 0 or the destination is smaller
	// than the source return false to indicate failure
	if ((source_distance < 0) || (dest_distance <= 0) || (dest_distance < source_distance))
	{ 
		return false; 
	}

	// perform a std::copy without no worries of out of bounds errors
	std::copy(in_first, in_last, out_first);
	return true;
}


/// mtl::safe_copy_n is a safer bound checking version of std::copy_n that protects from all out of
/// bounds errors. Works with any container that supports the size function. The start_pos
/// points to the starting index of the source container to be copied and count is the number of
/// elements to be copied. If everything is correct, copying is performed and it returns true. In 
/// case that any of the parameters is out of bounds for either container no copying is performed
/// and it returns false. Doesn't throw exceptions.
/// @param[in] source An input container.
/// @param[out] destination An output container.
/// @param[in] start_pos The starting position from where to start copying.
/// @param[in] count The number of items to copy.
/// @return If the copying was performed successfully.
template<typename InContainer, typename OutContainer>
[[nodiscard]]
inline std::enable_if_t<mtl::has_size_v<InContainer> && mtl::has_size_v<OutContainer>, bool>
safe_copy_n(const InContainer& source, OutContainer& destination, const size_t start_pos,
		    const size_t count) noexcept
{
	// if count is 0 then report we copied successfully and do nothing
	if(count == 0) { return true; }

	// sizes of both containers
	const size_t source_size = source.size();
	const size_t dest_size = destination.size();

	// the minimum size the source container should have
	const size_t min_size = start_pos + count;

#ifndef MTL_DISABLE_SOME_ASSERTS
	// check bounds errors with assert to report out of bound errors while debugging
	MTL_ASSERT_MSG((start_pos < source_size), "Starting position is out of bounds.");
	MTL_ASSERT_MSG((min_size <= source_size), 
			   "The destination container doesn't have enough space.");
	MTL_ASSERT_MSG((count <= dest_size), 
			   "The number of items requested to be copied are more than the destination size");
#endif // MTL_DISABLE_SOME_ASSERTS end

	// check out of bounds at runtime
	if ((start_pos < source_size) && (min_size <= source_size) && (count <= dest_size))
	{
		// move iterator to correct point of the container
		auto source_begin = std::next(std::begin(source), static_cast<long>(start_pos));
		auto source_end = std::next(std::begin(source), static_cast<long>(min_size));
		// perform a std::copy without no worries of out of bounds errors
		std::copy(source_begin, source_end, std::begin(destination));
		return true;
	}
	return false;
}



} // namespace mtl end
