#pragma once
// containers by Michael Trikergiotis
// 12/05/2020
// 
// Header for algorithms used to manipulate containers in a generic fashion.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "definitions.hpp" // various definitions
#include <type_traits>     // std::enable_if_t
#include <stdexcept>       // std::out_of_range
#include "type_traits.hpp" // mtl::has_reserve_v, mtl::has_push_back_v, mtl::has_emplace_back_v


namespace mtl
{

// ================================================================================================
// RESERVE          - If the container supports the reserve function it reserves space else it does
//                    nothing.
// ================================================================================================

/// If the container supports the reserve function it reserves the requested space else it 
/// does nothing.
/// @param[in, out] container A container.
/// @param[in] size The size to reserve for the container.
template<typename Container>
inline std::enable_if_t<!mtl::has_reserve_v<Container>, void>
reserve(Container&, std::size_t) {}


/// If the container supports the reserve function it reserves the requested space else it 
/// does nothing.
/// @param[in, out] container A container.
/// @param[in] size The size to reserve for the container.
template<typename Container>
inline std::enable_if_t<mtl::has_reserve_v<Container>, void>
reserve(Container& container, std::size_t size) { container.reserve(size); }




// ================================================================================================
// PUSH_BACK      - Add an element to the end of a container if it supports the function push_back
//                  else add an element to the container using the function insert.
// ================================================================================================

/// Add an element to the end of a container if it supports the function push_back else add an
/// element to the container using the function insert.
/// @param[in, out] container A container.
/// @param[in] item The item to push_back to the container.
template <typename Container, typename Type>
inline std::enable_if_t<!mtl::has_push_back_v<Container>, void>
push_back(Container& container, Type&& item) { container.insert( std::forward<Type>(item)); }

/// Add an element to the end of a container if it supports the function push_back else add an
/// element to the container using the function insert.
/// @param[in, out] container A container.
/// @param[in] item The item to push_back to the container.
template <typename Container, typename Type>
inline std::enable_if_t<mtl::has_push_back_v<Container>, void>
push_back(Container& container, Type&& item) { container.push_back(std::forward<Type>(item)); }




// ================================================================================================
// EMPLACE_BACK     - Add an element to the end of a container inplace if it supports the function
//                    emplace_back else add an element to the container inplace using the function
//                    emplace.
// ================================================================================================

/// Add an element to the end of a container inplace if it supports the function emplace_back else
/// add an element to the container inplace using the function emplace.
/// @param[in, out] container A container.
/// @param[in] item Any number of items to emplace_back to the container.
template<typename Container, typename... Args>
inline void emplace_back(Container& container, Args&&... args)
{
	// if the container support emplace_back use it
	if constexpr (mtl::has_emplace_back_v<Container>)
	{
		container.emplace_back(std::forward<Args>(args)...);
	}
	// if the container doesn't support emplace_back use emplace instead
	else
	{
		container.emplace(std::forward<Args>(args)...);
	}
}






// ================================================================================================
// SLICE        - Returns a slice of a container from starting position to ending position.
// SLICE_N      - Returns a slice of a container from starting position for a number of elements.
// ================================================================================================

/// Returns a slice of a container from starting position to ending position. Performs 
/// bound checking that all the parameters are within bounds and if one or more parameters are not
/// throws an std::out_of_range exception.
/// @param[in] container A container.
/// @param[in] start_pos The starting position where to create the slice from.
/// @param[in] end_pos The ending position where to create the slice from.
/// @return A container the same type as the container passed in.
template<typename Container>
inline Container slice(const Container& container, const size_t start_pos, const size_t end_pos)
{
	// keep size of the container
	const auto cont_size = container.size();

	// if both starting position and ending position is 0 then we just return an empty container
	if((start_pos == 0) && (end_pos == 0))
	{
		Container empty_container;
		return empty_container;
	}

	// if starting position is larger than ending position then throw
	if(start_pos > end_pos)
	{
		throw std::out_of_range
		("Error. For mtl::slice the starting position can't be larger than the ending position.");
	}

	// check if we are within bounds
	if ((start_pos >= cont_size) || (end_pos > cont_size))
	{
		// some parameter is out of range and we have to throw
		throw std::out_of_range
		("Error. Invalid attempt to access out of the range of the container with mtl::slice.");
	}
	
	// get an iterator to position where the slice will start
	auto start_it = std::next(container.begin(), static_cast<long>(start_pos));
	// get an iterator to where the slice will end
	auto end_it = std::next(container.begin(), static_cast<long>(end_pos));
	
	
	// if we are here then it mean nothing went wrong so we can safely do our work
	Container output(start_it, end_it);
	return output;
}


/// Returns a slice of a container from starting position for the number of elements requested. 
/// Performs bound checking that all the parameters are within bounds and if one or more parameters
/// are not throws an std::out_of_range exception.
/// @param[in] container A container.
/// @param[in] start_pos The starting position where to create the slice from.
/// @param[in] count The number of items used to create the slice.
/// @return A container the same type as the container passed in.
template<typename Container>
inline Container slice_n(const Container& container, const size_t start_pos, const size_t count)
{
	// keep size of the container
	const auto cont_size = container.size();

	// if both starting position and count is 0 then we just return an empty container
	if((start_pos == 0) && (count == 0))
	{
		Container empty_container;
		return empty_container;
	}

	// check if we are within bounds
	if ((start_pos >= cont_size) || (start_pos + count > cont_size) || (count > cont_size))
	{
		// some parameter is out of range and we have to throw
		throw std::out_of_range
		("Error. Invalid attempt to access out of the range of the container with mtl::slice_n.");
	}
	
	// get an iterator to position where the slice will start
	auto start_it = std::next(container.begin(), static_cast<long>(start_pos));
	// get an iterator to position the slice will end
	auto end_it = std::next(container.begin(), static_cast<long>(start_pos + count));
	
	
	// if we are here then it mean nothing went wrong so we can safely do our work
	Container output(start_it, end_it);
	return output;
}



} // namespace mtl end