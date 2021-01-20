#pragma once
// algorithms by Michael Trikergiotis
// 09/09/2018
// 
// Header for algorithms.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "definitions.hpp"  // various definitions
#include <vector>           // std::vector
#include <list>             // std::list
#include <unordered_set>    // std::unordered_set
#include <functional>       // std::equal_to, std::hash, std::less
#include <tuple>            // std::tuple, std::get, std::tuple_size_v
#include <utility>          // std::pair, std::forward
#include <stdexcept>        // std::invalid_argument
#include <cstddef>          // std::ptrdiff_t
#include <iterator>         // std::next, std::advance, std::forward_iterator_tag
#include <algorithm>        // std::remove, std::adjacent_find, std::find, std::for_each,
							// std::unique, std::sort, std::includes 
#include <type_traits>      // std::enable_if_t, std::remove_cv_t, std::add_pointer_t,
							// std::add_lvalue_reference_t
#include "type_traits.hpp"  // mtl::is_number_v, mtl::has_find_v
#include "container.hpp"    // mtl::emplace_back



namespace mtl
{


// ================================================================================================
// NOT_UNIQUE_INCLUSIVE - Keeps all the duplicate items including the original item that is used
//                        to identify the duplicates.
// NOT_UNIQUE_EXCLUSIVE - Keeps all the duplicate items excluding the original item that is used
//                        to identify the duplicates.
// NOT_UNIQUE           - Keeps only a single copy of each duplicate item.
// ================================================================================================

namespace detail
{

// Actual implementation of the not_unique_inclusive function to avoid code duplication.
template<typename Iter, typename BinaryPredicate>
[[nodiscard]]
inline Iter not_unique_inclusive_impl(Iter first, Iter last, BinaryPredicate binary_pred)
{
	// if there are no elements return an iterator at the starting position
	if (first == last) { return first; }

	// iterator to the first element matched
	auto start_match = first;
	// iterator pointing to where the new end should be
	auto new_end = first;
	for (;;)
	{
		// find the position of the first element we want to move from
		start_match = std::adjacent_find(start_match, last, binary_pred);
		// if no more matches are found returns an iterator pointing the last match
		if (start_match == last)
		{
			return new_end;
		}
		else
		{
			// keep an iterator pointing to the last matching element
			auto end_match = start_match;
			// move the iterator for the last matching element forward while being careful to not
			// move past the end
			while ((end_match != last) && (binary_pred(*end_match, *start_match)))
			{
				++end_match;
			}
			// move all matching elements to the front part of the range
			for (auto it = start_match; it != end_match; ++it)
			{
				*new_end = *it;
				++new_end;
			}
			// make sure that we start at the last point we found a matching element
			start_match = end_match;
		}
	}
}

} // namespace detail end


/// Moves all duplicates to the front and returns an iterator to the new end. Keeps all the
/// duplicate items including the original item that is used to identify the duplicates. Requires
/// that the items in the range are sorted. 
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter>
[[nodiscard]]
inline Iter not_unique_inclusive(Iter first, Iter last)
{
	return detail::not_unique_inclusive_impl(first, last, 
											 std::equal_to<typename Iter::value_type>{});
}

/// Moves all duplicates to the front and returns an iterator to the new end. Keeps all the
/// duplicate items including the original item that is used to identify the duplicates. Requires
/// that the items in the range are sorted. This specialization allows you to pass a
/// binary predicate for equality comparison of duplicate items.
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @param[in] binary_pred A binary predicate used for equality comparison, like std::equal_to<T>.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter, typename BinaryPredicate>
[[nodiscard]]
inline Iter not_unique_inclusive(Iter first, Iter last, BinaryPredicate binary_pred)
{
	return detail::not_unique_inclusive_impl(first, last, binary_pred);
}


// --



namespace detail
{

// Actual implementation of the not_unique_exlcusive function to avoid code duplication.
template<typename Iter, typename BinaryPredicate>
[[nodiscard]]
inline Iter not_unique_exclusive_impl(Iter first, Iter last, BinaryPredicate binary_pred)
{
	// if there are no elements return an iterator at the starting position
	if (first == last) { return first; }

	// iterator to the first element matched
	auto start_match = first;
	// iterator pointing to where the new end should be
	auto new_end = first;
	for (;;)
	{
		// find the position of the first element we want to move from
		start_match = std::adjacent_find(start_match, last, binary_pred);
		// if no more matches are found returns an iterator pointing the last match
		if (start_match == last)
		{
			return new_end;
		}
		else
		{
			// keep an iterator pointing to the last matching element
			auto end_match = start_match;
			// move the iterator for the last matching element forward while being careful to not
			// move past the end
			while ((end_match != last) && (binary_pred(*end_match, *start_match)))
			{
				++end_match;
			}
			// move the iterator for the first matching element one forward because we don't want
			// to keep the original element only the duplicated elements
			++start_match;
			// move all matching elements to the front part of the range
			for (auto it = start_match; it != end_match; ++it)
			{
				*new_end = *it;
				++new_end;
			}
			// make sure that we start at the last point we found a matching element
			start_match = end_match;
		}
	}
}

} // namespace detail end


/// Moves all duplicates to the front and returns an iterator to the new end. Keeps all the
/// duplicate items excluding the original item that is used to identify the duplicates. Requires
/// that the items in the range are sorted.
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter>
[[nodiscard]]
inline Iter not_unique_exclusive(Iter first, Iter last)
{
	// use a shortened name for the item type of the range
	using ItemType = typename Iter::value_type;
	
	return detail::not_unique_exclusive_impl(first, last, std::equal_to<ItemType>{});
}


/// Moves all duplicates to the front and returns an iterator to the new end. Keeps all the
/// duplicate items excluding the original item that is used to identify the duplicates. Requires
/// that the items in the range are sorted. This specialization allows you to pass a
/// binary predicate for equality comparison of duplicate items.
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @param[in] binary_pred A binary predicate used for equality comparison, like std::equal_to<T>.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter, typename BinaryPredicate>
[[nodiscard]]
inline Iter not_unique_exclusive(Iter first, Iter last, BinaryPredicate binary_pred)
{
	return detail::not_unique_exclusive_impl(first, last, binary_pred);
}



// --

/// Moves all duplicates to the front and returns an iterator to the new end. Keeps only a single
/// copy of each duplicate item. Requires that the items in the range are sorted. 
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter>
[[nodiscard]]
inline Iter not_unique(Iter first, Iter last)
{
	// use a shortened name for the item type of the range
	using ItemType = typename Iter::value_type;

	// move all duplicates excluding the original to the front
	auto it = detail::not_unique_exclusive_impl(first, last, std::equal_to<ItemType>{});
	// move only a single copy of each duplicate to the front and return an iterator to new end
	return std::unique(first, it);
}


/// Moves all duplicates to the front and returns an iterator to the new end. Keeps only a single
/// copy of each duplicate item. Requires that the items in the range are sorted. This 
/// specialization allows you to pass A binary predicate used for equality comparison of duplicate
/// items.
/// @param[in] first The iterator to the beginning of the range.
/// @param[in] last The iterator to the end of the range.
/// @param[in] binary_pred A binary predicate used for equality comparison, like std::equal_to<T>.
/// @return Iterator to the new end where all the non unique items are moved.
template<typename Iter, typename BinaryPredicate>
[[nodiscard]]
inline Iter not_unique(Iter first, Iter last, BinaryPredicate binary_pred)
{
	// move all duplicates excluding the original to the front
	auto it = detail::not_unique_exclusive_impl(first, last, binary_pred);
	// move only a single copy of each duplicate to the front and return an iterator to new end
	return std::unique(first, it, binary_pred);
}




// ================================================================================================
// REM_DUPLICATES_SORTED   - Removes duplicates in an already sorted container.
// REM_DUPLICATES          - Sorts the container and then removes duplicates.
// REM_DUPLICATES_PRESERVE - Removes duplicates while preserving the ordering of the container.
// ================================================================================================

namespace detail
{

// Actual implementation of rem_duplicates_sorted to avoid code duplication.
template<typename Container, typename BinaryPredicate>
inline void rem_duplicates_sorted_impl(Container& container, BinaryPredicate bp)
{
	// if the container is empty exit the function
	if (container.empty()) { return; }

	// erase elements that match a specific value that is passed by std::unique
	container.erase(std::unique(container.begin(), container.end(), bp), container.end());
}
} // namespace detail end


/// Removes duplicates in an already sorted container.
/// @param[in, out] container A sorted container.
template<typename Container>
inline void rem_duplicates_sorted(Container& container)
{
	// use a shortened name for the item type that is containted in the container
	using ItemType = typename Container::value_type;
	// actual implementation of the duplicate removal function, default binary predicate
	detail::rem_duplicates_sorted_impl(container, std::equal_to<ItemType>{});
}

/// Removes duplicates in an already sorted container. This specialization allows you to pass a 
/// binary predicate for equality comparison of duplicate items.
/// @param[in, out] container A sorted container.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename BinaryPredicate>
inline void rem_duplicates_sorted(Container& container, BinaryPredicate bp)
{
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_sorted_impl(container, bp);
}



// ----

namespace detail
{

// Actual implementation of rem_duplicates to avoid code duplication.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void rem_duplicates_impl(Container& container, Compare comp, BinaryPredicate bp)
{
	// if the container is empty exit the function
	if (container.empty()) { return; }

	// sort the container with the given comparator
	std::sort(container.begin(), container.end(), comp);
	// remove duplicates
	rem_duplicates_sorted(container, bp);
}

} // namespace detail end

/// Sorts the container and removes duplicates. 
/// @param[in, out] container A container.
template<typename Container>
inline void rem_duplicates(Container& container)
{
	// use a shortened name for the item type that is containted in the container
	using ItemType = typename Container::value_type;
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_impl(container, std::less<ItemType>{}, std::equal_to<ItemType>{});
}

/// Sorts the container and removes duplicates. This specialization allows you to pass a comparator
/// that will be used to sort the containter and also A binary predicate used for equality
/// comparison of duplicate items. 
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void rem_duplicates(Container& container, Compare comp, BinaryPredicate bp)
{
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_impl(container, comp, bp);
}




namespace detail
{
	
// Actual implementation of rem_duplicates to avoid code duplication.
template<typename Type, typename Compare, typename BinaryPredicate>
inline void rem_duplicates_impl(std::list<Type>& container, Compare comp, BinaryPredicate bp)
{
	// if the container is empty exit the function
	if (container.empty()) { return; }

	// sort the std::list
	container.sort(comp);
	// just use the sorted version of remove duplicates
	mtl::rem_duplicates_sorted(container, bp);
}

} // namespace detail end


/// Sorts the container and removes duplicates. 
/// @param[in, out] container An std::list.
template<typename Type>
inline void rem_duplicates(std::list<Type>& container)
{
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_impl(container, std::less<Type>{}, std::equal_to<Type>{});
}

/// Sorts the container and removes duplicates. This specialization allows you to pass a comparator
/// that will be used to sort the containter and also A binary predicate used for equality
/// comparison of duplicate items. 
/// @param[in, out] container An std::list.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Type, typename Compare, typename BinaryPredicate>
inline void rem_duplicates(std::list<Type>& container, Compare comp, BinaryPredicate bp)
{
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_impl(container, comp, bp);
}



// ----

namespace detail
{

// The actual implmentation of rem_duplicates_preserve function to avoid code duplication.
template<typename Container, typename Hash, typename BinaryPredicate>
inline void rem_duplicates_preserve_impl(Container& container, Hash hash, BinaryPredicate bp)
{
	using Type = typename Container::value_type;
	// keep track of all the duplicates
	std::unordered_set<Type, Hash, BinaryPredicate> database(16, hash, bp);

	// keep all the non duplicates here
	Container non_duplicates;
	for (auto& item : container)
	{
		// remember the size before adding the current item
		size_t prev_size = database.size();

		database.insert(item);
		// if after adding the item to the std::unordered_set<T> the size changes then it means it 
		// is not a duplicate
		if (prev_size != database.size())
		{
			// keep the non duplicate item
			mtl::emplace_back(non_duplicates, item);
		}
	}
	container = non_duplicates;
}

} // namespace detail end


/// Removes duplicates while preserving order. Slower and uses more memory compared to the 
/// rem_duplicates function because it needs to preserve order.
/// @param[in, out] container A container.
template<typename Container>
inline void rem_duplicates_preserve(Container& container)
{
	using Type = typename Container::value_type;

	// actual implementation of the duplicate removal function
	detail::rem_duplicates_preserve_impl(container, std::hash<Type>{}, std::equal_to<Type>{});
}


/// Removes duplicates while preserving order. Slower and uses more memory compared to the 
/// rem_duplicates function because it needs to preserve order. This specialization allows you to 
/// pass custom hashing function and a binary predicate used for equality comparison.
/// @param[in, out] container A container.
/// @param[in] hash A hashing function, like std::hash<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Hash,
		 typename BinaryPredicate>
inline void rem_duplicates_preserve(Container& container, Hash hash, BinaryPredicate bp)
{
	// actual implementation of the duplicate removal function
	detail::rem_duplicates_preserve_impl(container, hash, bp);
}




// ================================================================================================
// KEEP_DUPLICATES_INCLUSIVE_SORTED   - Keeps duplicates including the original duplicate. Requires
//                                      the container to be sorted.
// KEEP_DUPLICATES_INCLUSIVE          - Keeps duplicates including the original duplicate without
//                                      preserving ordering.
// KEEP_DUPLICATES_INCLUSIVE_PRESERVE - Keeps duplicates including the original duplicate while
// 								        preserving ordering.
// ================================================================================================

/// Keeps duplicates including the original duplicate. Requires the container to be sorted.
/// @param[in, out] container A sorted container.
template<typename Container>
inline void keep_duplicates_inclusive_sorted(Container& container)
{
	container.erase(mtl::not_unique_inclusive(container.begin(), container.end()), 
											  container.end());
}

/// Keeps duplicates including the original duplicate. Allows you to pass a binary predicate for
/// equality comparison of duplicate items. Requires the container to be sorted.
/// @param[in, out] container A sorted container.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename BinaryPredicate>
inline void keep_duplicates_inclusive_sorted(Container& container, BinaryPredicate bp)
{
	container.erase(mtl::not_unique_inclusive(container.begin(), container.end(), bp), 
					container.end());
}


// --

/// Keeps duplicates including the original duplicate without preserving ordering.
/// @param[in, out] container An std::list.
template<typename Type>
inline void keep_duplicates_inclusive(std::list<Type>& container)
{
	container.sort();
	mtl::keep_duplicates_inclusive_sorted(container);
}


/// Keeps duplicates including the original duplicate without preserving ordering. Allows you to
/// pass a comparator that will be used to sort the containter and also a
/// binary predicate for equality comparison of duplicate items.
/// @param[in, out] container An std::list.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Type, typename Compare, typename BinaryPredicate>
inline void keep_duplicates_inclusive(std::list<Type>& container, Compare comp, BinaryPredicate bp)
{
	container.sort(comp);
	mtl::keep_duplicates_inclusive_sorted(container, bp);
}


/// Keeps duplicates including the original duplicate without preserving ordering.
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates_inclusive(Container& container)
{
	std::sort(container.begin(), container.end());
	mtl::keep_duplicates_inclusive_sorted(container);
}


/// Keeps duplicates including the original duplicate without preserving ordering. Allows you to
/// pass a comparator that will be used to sort the containter and also a
/// binary predicate for equality comparison of duplicate items. 
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void keep_duplicates_inclusive(Container& container, Compare comp, BinaryPredicate bp)
{
	std::sort(container.begin(), container.end(), comp);
	mtl::keep_duplicates_inclusive_sorted(container, bp);
}


// --

/// Keeps duplicates including the original duplicate while preserving ordering. Allows you to pass
/// A binary predicate used for equality comparison of duplicate items. Be careful about the size
/// of the container as this algorithm has quadratic time complexity.
/// @param[in, out] container A container.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename BinaryPredicate>
inline void keep_duplicates_inclusive_preserve(Container& container, BinaryPredicate bp)
{
	// if the container is less than 2 leave without doing anything
	if (container.size() < 2) { return; }
	// keep all inclusive duplicate here
	Container duplicates;
	// counter where the next loop will start looking from
	size_t counter = 1;
	// if a duplicate is found avoid searching in the duplicates
	bool found = false;
	for (auto& item : container)
	{
		// look at all items after this item for a duplicate, use iterators instead of subscript
		// operator so it supports std::list too
		auto start_it = std::next(container.begin(), static_cast<std::ptrdiff_t>(counter));
		for(auto it = start_it; it != container.end(); ++it)
		{
			if (bp(item, *it))
			{
				// if an item is a duplicate add it and leave
				mtl::emplace_back(duplicates, item);
				// mark that we found a duplicate so we don't have to also search in the duplicates
				// for a match
				found = true;
				break;
			}
		}

		// if we didn't found a duplicate this loop search in the duplicates container
		if (found == false)
		{
			// look at all the duplicates for a match with the current item
			for (auto& dupe : duplicates)
			{
				if (bp(item, dupe))
				{
					// if an item is a duplicate add it and leave
					mtl::emplace_back(duplicates, item);
					break;
				}
			}
		}
		// mark that the was no duplicate found this round
		found = false;
		// increase coutner so the next loop will from the next item
		++counter;
	}
	container = duplicates;
}

/// Keeps duplicates including the original duplicate while preserving ordering. Be careful about
/// the size of the container as this algorithm has quadratic time complexity.
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates_inclusive_preserve(Container& container)
{
	mtl::keep_duplicates_inclusive_preserve(container, 
											std::equal_to<typename Container::value_type>{});
}

// ================================================================================================
// KEEP_DUPLICATES_EXCLUSIVE_SORTED   - Keeps duplicates excluding the original duplicate. Requires
//                                      the container to be sorted.
// KEEP_DUPLICATES_EXCLUSIVE          - Keeps duplicates excluding the original duplicate without
//                                 	    preserving ordering.
// KEEP_DUPLICATES_EXCLUSIVE_PRESERVE - Keeps duplicates excluding the original duplicate while
// 								  	    preserving ordering.
// ================================================================================================


/// Keeps duplicates excluding the original duplicate without preserving ordering. Requires the 
/// container to be sorted.
/// @param[in, out] container A sorted container.
template<typename Container>
inline void keep_duplicates_exclusive_sorted(Container& container)
{
	container.erase(mtl::not_unique_exclusive(container.begin(), container.end()), 
											  container.end());
}

/// Keeps duplicates excluding the original duplicate without preserving ordering. Allows you to
/// pass A binary predicate used for equality comparison of duplicate items. Requires the container
/// to be sorted.
/// @param[in, out] container A sorted container.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename BinaryPredicate>
inline void keep_duplicates_exclusive_sorted(Container& container, BinaryPredicate bp)
{
	container.erase(mtl::not_unique_exclusive(container.begin(), container.end(), bp),
					container.end());
}


// --

/// Keeps duplicates excluding the original duplicate without preserving ordering.
/// @param[in, out] container An std::list.
template<typename Type>
inline void keep_duplicates_exclusive(std::list<Type>& container)
{
	container.sort();
	mtl::keep_duplicates_exclusive_sorted(container);
}

/// Keeps duplicates excluding the original duplicate without preserving ordering. Allows you to
/// pass a comparator that will be used to sort the containter and also a
/// binary predicate for equality comparison of duplicate items. 
/// @param[in, out] container An std::list.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Type, typename Compare, typename BinaryPredicate>
inline void keep_duplicates_exclusive(std::list<Type>& container, Compare comp, BinaryPredicate bp)
{
	container.sort(comp);
	mtl::keep_duplicates_exclusive_sorted(container, bp);
}


/// Keeps duplicates excluding the original duplicate without preserving ordering.
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container>
inline void keep_duplicates_exclusive(Container& container)
{
	std::sort(container.begin(), container.end());
	mtl::keep_duplicates_exclusive_sorted(container);
}

/// Keeps duplicates excluding the original duplicate without preserving ordering. Allows you to
/// pass a comparator that will be used to sort the containter and also a
/// binary predicate for equality comparison of duplicate items. 
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void keep_duplicates_exclusive(Container& container, Compare comp, BinaryPredicate bp)
{
	std::sort(container.begin(), container.end(), comp);
	mtl::keep_duplicates_exclusive_sorted(container, bp);
}


// --


/// Keeps duplicates including the original duplicate while preserving ordering. Slower and uses
/// more memory than the non-preserving functions. Allows you to pass custom hashing function and
/// and binary predicate.
/// @param[in, out] container A container.
/// @param[in] hash A hashing function, like std::hash<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Hash, typename BinaryPredicate>
inline void keep_duplicates_exclusive_preserve(Container& container, Hash hash, BinaryPredicate bp)
{
	using Type = typename Container::value_type;
	// keep track of all the duplicates
	std::unordered_set<Type, Hash, BinaryPredicate> database(16, hash, bp);
	
	// keep all the duplicates here
	Container duplicates;
	for (auto& item : container)
	{
		// remember the size before adding the current item
		size_t prev_size = database.size();

		database.insert(item);
		// if after adding the item to the std::unordered_set<T> the size doesn't chance then it
		// means that the item is a duplicate
		if (prev_size == database.size())
		{
			// keep the duplicate item
			mtl::emplace_back(duplicates, item);
		}
	}
	container = duplicates;
}

/// Keeps duplicates including the original duplicate while preserving ordering. Slower and uses
/// more memory than the non-preserving functions. 
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates_exclusive_preserve(Container& container)
{
	using Type = typename Container::value_type;
	mtl::keep_duplicates_exclusive_preserve(container, std::hash<Type>{}, std::equal_to<Type>{});
}



// ================================================================================================
// KEEP_DUPLICATES_SORTED   - Keeps a single copy of each duplicate without preserving order. 
//                            Requires the container to be sorted.
// KEEP_DUPLICATES          - Keeps a single copy of each duplicate without preserving ordering.
// KEEP_DUPLICATES_PRESERVE - Keeps a single copy of each duplicate while preserving ordering.
// ================================================================================================



/// Keeps a single copy of each duplicate without preserving order. Requires the container to be
/// sorted.
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates_sorted(Container& container)
{
	container.erase(mtl::not_unique(container.begin(), container.end()), container.end());
	// keep only one of each duplicate
	mtl::rem_duplicates(container);
}

/// Keeps a single copy of each duplicate without preserving order. Requires the container to be
/// sorted. Allows you to pass a comparator that will be used to sort the containter and also a
/// binary predicate for equality comparison of duplicate items. 
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void keep_duplicates_sorted(Container& container, Compare comp, BinaryPredicate bp)
{
	container.erase(mtl::not_unique(container.begin(), container.end(), bp), container.end());
	// keep only one of each duplicate
	mtl::rem_duplicates(container, comp, bp);
}


// --

/// Keeps a single copy of each duplicate without preserving ordering.
/// @param[in, out] container An std::list.
template<typename Type>
inline void keep_duplicates(std::list<Type>& container)
{
	container.sort();
	mtl::keep_duplicates_sorted(container);
}

/// Keeps a single copy of each duplicate without preserving ordering. Allows you to pass a 
/// comparison function object, that will be used to sort the containter and also a binary
/// predicate for equality comparison of duplicate items. 
/// @param[in, out] container An std::list.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Type, typename Compare, typename BinaryPredicate>
inline void keep_duplicates(std::list<Type>& container, Compare comp, BinaryPredicate bp)
{
	container.sort(comp);
	mtl::keep_duplicates_sorted(container, comp, bp);
}


/// Keeps a single copy of each duplicate without preserving ordering.
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates(Container& container)
{
	std::sort(container.begin(), container.end());
	mtl::keep_duplicates_sorted(container);
}

/// Keeps a single copy of each duplicate without preserving ordering. Allows you to pass a
/// comparison function object, that will be used to sort the containter and also a binary
/// predicate for equality comparison of duplicate items. 
/// @param[in, out] container A container.
/// @param[in] comp A comparator used for sorting, like std::less<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Compare, typename BinaryPredicate>
inline void keep_duplicates(Container& container, Compare comp, BinaryPredicate bp)
{
	std::sort(container.begin(), container.end(), comp);
	mtl::keep_duplicates_sorted(container, comp, bp);
}


// --


/// Keeps a single copy of each duplicate while preserving ordering. Slower and uses more memory
/// compared to the non-preserving functions. 
/// @param[in, out] container A container.
template<typename Container>
inline void keep_duplicates_preserve(Container& container)
{
	mtl::keep_duplicates_inclusive_preserve(container);
	// keep a single copy of each duplicate 
	mtl::rem_duplicates_preserve(container);
}

/// Keeps a single copy of each duplicate while preserving ordering. Slower and uses more memory
/// compared to the non-preserving functions. Allows you to pass custom hashing function and
/// binary predicate.
/// @param[in, out] container A container.
/// @param[in] hash A hashing function, like std::hash<T>.
/// @param[in] bp A binary predicate used for equality comparison, like std::equal_to<T>.
template<typename Container, typename Hash, typename BinaryPredicate>
inline void keep_duplicates_preserve(Container& container, Hash hash, BinaryPredicate bp)
{
	mtl::keep_duplicates_inclusive_preserve(container, bp);
	// keep a single copy of each duplicate
	mtl::rem_duplicates_preserve(container, hash, bp);
}






// ================================================================================================
// CONTAINS - Returns if an item exists within a container. 
// ================================================================================================

namespace detail
{

// Returns if an item is inside the container. Implementation for containers that support the
// find function like std::set, std::unordered_set, std::map etc.
template<typename Container, typename Type>
[[nodiscard]]
inline std::enable_if_t<mtl::has_find_v<Container>, bool>
contains_impl(const Container& container, const Type& match)
{
	// if the container supports the find function use it
	auto it = container.find(match);
	if (it != container.end()) { return true; }
	return false;
}

// Returns if an item is inside the container. Implementation for containers that do not support
// the find function like std::vector, std::deque, std::list.
template<typename Container, typename Type>
[[nodiscard]]
inline std::enable_if_t<!mtl::has_find_v<Container>, bool>
contains_impl(const Container& container, const Type& match)
{
	// if the container doesn't support the find function use std::find
	auto it = std::find(container.begin(), container.end(), match);
	if (it != container.end()) { return true; }
	return false;
}

} // namespace detail end

/// Returns if an item exists within a container.
/// @param[in] container A container.
/// @param[in] match An item to match.
/// @return If the item exists in the container or not.
template<typename Container, typename Type>
[[nodiscard]]
inline bool contains(const Container& container, const Type& match)
{
	// do not accept if the type of the container is std::string or const char* and inform the user
	// that he should use mtl::string::contains instead
	static_assert(!mtl::is_std_string_v<Container>, 
	"The mtl::contains doesn't support std::string. Use mtl::string::contains instead.");
	static_assert(!mtl::is_c_string_v<Container>,
	"The mtl::contains doesn't support const char*. Use mtl::string::contains instead.");

	return mtl::detail::contains_impl(container, match);
}

// ================================================================================================
// CONTAINS_ALL        - Returns if all items of container exists within another container. 
// CONTAINS_ALL_SORTED - Returns if all items of container exists within another container. 
//                       Both containers are required to be sorted.
// ================================================================================================

/// Returns if all the elements of a container are contained in another container. The elements 
/// don't have to be in a certain order to match. Neither container has to be sorted. 
/// @param[in] container_contains A container.
/// @param[in] elements_to_find A container of matches.
/// @return If the all the matches exists in the container.
template<typename ContainerContains, typename ContainerToFind>
[[nodiscard]]
inline std::enable_if_t<mtl::has_find_v<ContainerContains>, bool>
contains_all(const ContainerContains& container_contains, const ContainerToFind& elements_to_find)
{
	for (const auto& item : elements_to_find)
	{
		if (container_contains.find(item) == container_contains.end())
		{
			return false;
		}
	}
	return true;
}

/// Returns if all the elements of a container are contained in another container. The elements 
/// don't have to be in a certain order to match. Neither container has to be sorted. 
/// @param[in] container_contains A container.
/// @param[in] elements_to_find A container of matches.
/// @return If the all the matches exists in the container.
template<typename ContainerContains, typename ContainerToFind>
[[nodiscard]]
inline std::enable_if_t<!mtl::has_find_v<ContainerContains>, bool>
contains_all(const ContainerContains& container_contains, const ContainerToFind& elements_to_find)
{
	// create a copy of the containers
	std::vector<typename ContainerContains::value_type> 
	cp_contains (container_contains.begin(), container_contains.end());
	std::vector<typename ContainerContains::value_type> 
	cp_find(elements_to_find.begin(), elements_to_find.end());
	// sort the containers
	std::sort(cp_contains.begin(), cp_contains.end());
	std::sort(cp_find.begin(), cp_find.end());
	// find if all items exist in the sorted container
	return std::includes(cp_contains.begin(), cp_contains.end(), cp_find.begin(), cp_find.end());
}


/// Returns if all the elements of a container are contained in another container. Requires that
/// both containers are sorted.
/// @param[in] container_contains A sorted container.
/// @param[in] elements_to_find A sorted container of matches.
/// @return If the all the matches exists in the container.
template<typename ContainerContains, typename ContainerToFind>
[[nodiscard]]
inline std::enable_if_t<mtl::has_find_v<ContainerContains>, bool>
contains_all_sorted(const ContainerContains& container_contains, 
					const ContainerToFind& elements_to_find)
{
	// this is the same as mtl::contains_all for containers that support find as the sorting
	// doesn't matter for them and is here for sake of ease of use by the user
	return mtl::contains_all(container_contains, elements_to_find);
}

/// Returns if all the elements of a container are contained in another container. Requires that
/// both containers are sorted.
/// @param[in] container_contains A sorted container.
/// @param[in] elements_to_find A sorted container of matches.
/// @return If the all the matches exists in the container.
template<typename ContainerContains, typename ContainerToFind>
[[nodiscard]]
inline std::enable_if_t<!mtl::has_find_v<ContainerContains>, bool>
contains_all_sorted(const ContainerContains& container_contains, 
					const ContainerToFind& elements_to_find)
{
	// find if all items exist in the sorted container
	return std::includes(container_contains.begin(), container_contains.end(),
						 elements_to_find.begin(), elements_to_find.end());
}



// ================================================================================================
// FOR_EACH - Applies a function to all elements. A drop in replacement for std::for_each that 
//            works on everything std::for_each works and also works on std::tuple and std::pair.
// ================================================================================================

// ------------------------------------------------------------------------------------------------
// mtl::for_each for std::tuple 
// ------------------------------------------------------------------------------------------------

namespace detail
{

// Helper struct for for_each function with std::tuple.
template<size_t Index, typename Function, typename... Types>
struct for_each_tuple
{
	void operator() (std::tuple<Types...>& value, Function&& func)
	{
		// use recursion to call all the other parts of the tuple
		for_each_tuple<Index - 1, Function, Types...>{}
		(value, std::forward<Function>(func));
		// call the given function for the specific index of the tuple
		func(std::get<Index>(value));
	}
};

// Helper struct for for_each function with std::tuple. Template specialization for index 0.
template<typename Function, typename... Types>
struct for_each_tuple<0, Function, Types...>
{
	void operator() (std::tuple<Types...>& value, Function&& func)
	{
		func(std::get<0>(value));
	}
};

} // namespace detail end

/// Applies a function to all elements. A drop in replacement for std::for_each that works on
/// everything std::for_each works and also works on std::tuple and std::pair.
/// @param[in] value An std::tuple.
/// @param[in] func A function to apply.
template<typename Function, typename... Types>
inline void for_each(std::tuple<Types...>& value, Function&& func)
{
	const auto size = std::tuple_size_v<std::tuple<Types...>>;
	detail::for_each_tuple<size - 1, Function, Types...>{}
	(value, std::forward<Function>(func));
}

// ------------------------------------------------------------------------------------------------
// mtl::for_each for const std::tuple 
// ------------------------------------------------------------------------------------------------

namespace detail
{

// Helper struct for for_each function with std::tuple.
template<size_t Index, typename Function, typename... Types>
struct for_each_const_tuple
{
	void operator() (const std::tuple<Types...>& value, Function&& func)
	{
		// use recursion to call all the other parts of the tuple
		for_each_const_tuple<Index - 1, Function, Types...>{}
		(value, std::forward<Function>(func));
		// call the given function for the specific index of the tuple
		func(std::get<Index>(value));
	}
};

// Helper struct for for_each function with std::tuple. Template specialization for index 0.
template<typename Function, typename... Types>
struct for_each_const_tuple<0, Function, Types...>
{
	void operator() (const std::tuple<Types...>& value, Function&& func)
	{
		func(std::get<0>(value));
	}
};

} // namespace detail end

/// Applies a function to all elements. A drop in replacement for std::for_each that works on
/// everything std::for_each works and also works on std::tuple and std::pair.
/// @param[in] value An std::tuple.
/// @param[in] func A function to apply.
template<typename Function, typename... Types>
inline void for_each(const std::tuple<Types...>& value, Function&& func)
{
	const auto size = std::tuple_size_v<std::tuple<Types...>>;
	detail::for_each_const_tuple<size - 1, Function, Types...>{}
	(value, std::forward<Function>(func));
}


// ------------------------------------------------------------------------------------------------
// mtl::for_each for std::pair
// ------------------------------------------------------------------------------------------------

/// Applies a function to all elements. A drop in replacement for std::for_each that works on
/// everything std::for_each works and also works on std::tuple and std::pair.
/// @param[in] std_pair An std::pair.
/// @param[in] func A function to apply.
template<typename Function, typename Type1, typename Type2>
inline void for_each(std::pair<Type1, Type2>& std_pair, Function&& func)
{
	func(std_pair.first);
	func(std_pair.second);
}

// ------------------------------------------------------------------------------------------------
// mtl::for_each for const std::pair
// ------------------------------------------------------------------------------------------------

/// Applies a function to all elements. A drop in replacement for std::for_each that works on
/// everything std::for_each works and also works on std::tuple and std::pair.
/// @param[in] std_pair An std::pair.
/// @param[in] func A function to apply.
template<typename Function, typename Type1, typename Type2>
inline void for_each(const std::pair<Type1, Type2>& std_pair, Function&& func)
{
	func(std_pair.first);
	func(std_pair.second);
}



// ------------------------------------------------------------------------------------------------
// mtl::for_each for two iterators
// ------------------------------------------------------------------------------------------------

/// Applies a function to all elements. A drop in replacement for std::for_each that works on
/// everything std::for_each works and also works on std::tuple and std::pair.
/// @param[in] first Iterator to the beginning of a range.
/// @param[in] last Iterator to the end of a range.
/// @param[in] func A function to apply.
template<typename Iter, typename Function>
inline void for_each(Iter first, Iter last, Function&& func)
{
	std::for_each(first, last, std::forward<Function>(func));
}



// ================================================================================================
// FOR_ADJ_PAIRS - Applies a function to all adjacent pairs.
// ================================================================================================


/// Applies a function to all adjacent pairs in a range first to last. Like std::for_each but 
/// works on adjacent pairs of elements instead of a single element.
/// @param[in] first Iterator to the beginning of a range.
/// @param[in] last Iterator to the end of a range.
/// @param[in] func A function to apply.
template<typename FwdIter, typename Func>
inline void for_adj_pairs(FwdIter first, FwdIter last, Func&& func)
{
	// check that the range contains at least 1 element
	if (first != last)
	{
		// an iterator pointing to the previous element
		auto previous = first;
		// move the iterator to the next element
		++first;
		// loop while incrementing current and previous iterator
		for (; first != last; ++first, ++previous)
		{
			// apply the function to each pair of elements
			func(*previous, *first);
		}
	}
}

// ================================================================================================
// FOR_ALL_PAIRS - Applies a function to all pairs. The algorithm has logarithmic time complexity.
// ================================================================================================


/// Applies a function to a each pair of elements in a range first to last. Every element is paired
/// with all other elements of the range. The algorithm has quadratic time complexity.
/// @param[in] first Iterator to the beginning of a range.
/// @param[in] last Iterator to the end of a range.
/// @param[in] func A function to apply.
template<typename FwdIter, typename Func>
inline void for_all_pairs(FwdIter first, FwdIter last, Func&& func)
{
	// check that the range contains at least 1 element
	if (first != last)
	{
		// an iterator pointing to the previous element
		auto previous = first;
		// move the iterator to the next element
		++first;
		// loop while incrementing the previous iterator
		for (; first != last; ++first, ++previous)
		{
			// loop while incrementing the current iterator
			for (auto it = first; it != last; ++it)
			{
				// apply the function to each pair of elements
				func(*previous, *it);
			}
		}
	}
}




// ================================================================================================
// FILL_RANGE - Copies an input range to an output range repeatedly.
// ================================================================================================

/// Copies an input range to an output range repeatedly until the output range is filled. If the 
/// input range is larger than the output range only the part of the input range that fits in the 
/// output range is copied. Input range and output range can be from different kind of containers
/// (ex. std::vector to std::list) as long as the element type is exactly the same. It has the same
/// functionality as std::fill but instead of accepting a single value it works with a range of 
/// values.
/// @param[in] in_first Iterator to the the start of the input range.
/// @param[in] in_last Iterator to the the end of the input range.
/// @param[out] out_first Iterator to the the start of the output range.
/// @param[out] out_last Iterator to the the end of the output range.
template<typename FwdIterIn, typename FwdIterOut>
inline void fill_range(FwdIterIn in_first, FwdIterIn in_last, FwdIterOut out_first, 
					   FwdIterOut out_last)
{
	// leave the function if any of the two ranges is empty
	if ((in_first == in_last) || (out_first == out_last)) { return; }

	// iterator to the start of the input range
	auto input_it = in_first;

	for (auto it = out_first; it != out_last; ++it)
	{
		// copy input range element to output range element
		*it = *input_it;

		// move the input iterator one element forward
		std::advance(input_it, 1);

		// if the input iterator reaches the end of the range set it to the beginning of the range
		if (input_it == in_last)
		{
			input_it = in_first;
		}
	}
}




// ================================================================================================
// RANGE - Generates a range of numbers from start to end with a given step.
// ================================================================================================

namespace detail
{

// Range generator that generates an object with begin and end iterators for a range of values 
// without actually holding all the values in memory at once. Supports both incrementing and 
// decrementing ranges. Throws std::invalid_argument if incorrect values are passed for any
// of the parameters.
template<typename Type, typename Enable = void>
class _range_generator 
{
public:
	// Deleted constructor because this instantiation should never happen.
	_range_generator() = delete;
};

// Range generator that generates an object with begin and end iterators for a range of values 
// without actually holding all the values in memory at once. Supports both incrementing and 
// decrementing ranges. Throws std::invalid_argument if incorrect values are passed for any
// of the parameters.
template<typename Type>
class _range_generator<Type, std::enable_if_t<mtl::is_number_v<Type>>>
{
	// Iterator for _range_generator.
	template<typename ValueType = Type>
	class range_iterator
	{
		// Current value.
		ValueType _value;
		// Value for each step.
		const ValueType _step;
		// Value representing if the range is incremental or decremental.
		const bool incremental;

	public:

		// typedefs needed for proper iterator declaration

		// typedef for iterator type.
		using value_type = std::remove_cv_t<ValueType>;
		// typedef for iterator difference.
		using difference_type = std::ptrdiff_t;
		// typedef for iterator catecory.
		using iterator_category = std::forward_iterator_tag;
		// typedef for iterator pointer type.
		using pointer = std::add_pointer_t<value_type>;
		// typedef for iterator reference type.
		using reference = std::add_lvalue_reference_t<value_type>;

		// Iterator constructor.
		range_iterator(value_type value, value_type step = 1, bool increment = true)
		: _value(value), _step(step), incremental(increment) {}

		// Equality operator for the iterator that actually changes the comparison operation based
		// if it is an incremental or decremental range.
		[[nodiscard]]
		bool operator==(const range_iterator& other) const
		{
			// if range is marked as incremental use this comparison
			if (incremental)
			{
				return _value + _step > other._value;
			}
			// if range is not marked as incremental, then it is decremental so use this comparison
			else
			{
				return _value < other._value;
			}
		}
		// Difference operator for iterator.
		[[nodiscard]]
		bool operator!=(const range_iterator& other) const
		{
			return !(*this == other);
		}

		// Pre increment operator.
		ValueType operator++() { return _value += _step; }

		// Post increment operator.
		ValueType operator++(int) { return _value += _step; }

		// Return pointer to the value.
		operator ValueType*()  { return &_value; }
	};

	// Range iterator type.
	using iterator = range_iterator<Type> ;

	// Starting value for the range.
	Type _start;
	// Ending value for the range.
	Type _end;
	// Value for each step.
	Type _step;
	// Value that says if a range is incremental or decremental.
	bool incremental;

public:
	// Constructor for _range_generator with proper initializations.
	_range_generator(Type start, Type end, Type step) : _start(start), _end(end), _step(step)	
	{
		// value representing zero for all numeric types
		constexpr Type zero = static_cast<Type>(0);

		// check if the range is incrementing
		if ((_start <= _end) && (_step > zero))
		{
			incremental = true;
		}
		// check if the range is decrementing
		else if((_start >= _end) && (_step < zero))
		{
			incremental = false;
		}
		// else throw an error because values given make no sense
		else
		{
			throw std::invalid_argument(
			"Error. One or more parameters for mtl::range are incorrect."); // GCOVR_EXCL_LINE
		}
	}

	// Equality operator for _range_generator<Type>.
	[[nodiscard]]
	bool operator==(const _range_generator<Type>& other) const
	{
		return ((_start == other._start) && (_end == other._end) &&
				(_step == other._step));
	}
	
	// Difference operator for _range_generator<Type>.
	[[nodiscard]]
	bool operator!=(const _range_generator<Type>& other) const
	{
		return !(*this == other);
	}

	// Returns an iterator to the beginning of the range.
	[[nodiscard]]
	iterator begin()  { return iterator(_start, _step, incremental); }

	// Returns an iterator to the end of the range.
	[[nodiscard]]
	iterator end()    { return iterator(_end , _step, incremental); }

	// Returns a const iterator to the beginning of the range.
	[[nodiscard]]
	iterator cbegin() const { return iterator(_start, _step, incremental); }

	// Returns a const iterator to the end of the range.
	[[nodiscard]]
	iterator cend()   const { return iterator(_end , _step, incremental); }
};

} // namespace detail end

/// Generates a range of numbers from start to end with a given step. Support both incrementing 
/// and decrementing ranges of numbers. The values for the range are generated on the fly and they 
/// are not kept in memory. Throws std::invalid_argument if incorrect values are passed for any
/// of the parameters.
/// @param[in] start The starting number of the range.
/// @param[in] end The ending number of the range.
/// @param[in] step A number to use as a step between each number.
/// @return A range from start to end with a given step.
template<typename Type = int>
[[nodiscard]]
inline std::enable_if_t<mtl::is_number_v<Type>, detail::_range_generator<Type>>
range(const Type start, const Type end, const Type step = 1)
{
	// generates an object with begin()/end() and cbegin()/cend() that can be incremented or 
	// decremented
	return detail::_range_generator<Type>(start, end, step);
}


} // namespace mtl end
