#pragma once
// random by Michael Trikergiotis
// 22/10/2017
// 
// Header for algorithms related to random number generation.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include <random>				// std::random_device, std::uniform_int_distribution
#include <iterator>				// std::next, std::distance
#include <algorithm>			// std::iter_swap
#include <type_traits>          // std::enable_if_t
#include <cstddef>              // std::ptrdiff_t
#include "type_traits.hpp"      // mtl::is_int_v, mtl::is_float_v
#include "xoroshiro128plus.hpp" // mtl::xoroshiro128plus



namespace mtl
{


// ================================================================================================
// RNG - An extremly fast and easy to use random number generator.
// ================================================================================================

namespace detail
{

// Selects between std::uniform_int_distribution<Type> when the used type is integral
// std::uniform_real_distribution<Type> when the used type is floating point.
template<typename Type, typename = void>
struct uniform_distribution_type_selector
{
	// this specialization just deletes it's constructor so it can't be used
	uniform_distribution_type_selector() = delete;
};

// Selects between std::uniform_int_distribution<Type> when the used type is integral
// std::uniform_real_distribution<Type> when the used type is floating point.
template<typename Type>
struct uniform_distribution_type_selector<Type, std::enable_if_t<mtl::is_int_v<Type>>>
{
	// uniform distribution for integral types
	std::uniform_int_distribution<Type> distribution;

	// empty constructor, this need to be declared
	uniform_distribution_type_selector() {}

	// constructor that sets the minimum and maximum values for the uniform distribution
	uniform_distribution_type_selector(Type min, Type max)
	{
		std::uniform_int_distribution<Type> configured_ud(min, max);
		distribution = configured_ud;
	}
};

// Selects between std::uniform_int_distribution<Type> when the used type is integral
// std::uniform_real_distribution<Type> when the used type is floating point.
template<typename Type>
struct uniform_distribution_type_selector<Type, std::enable_if_t<mtl::is_float_v<Type>>>
{
	// uniform distribution for floating point types
	std::uniform_real_distribution<Type> distribution;

	// empty constructor, this need to be declared
	uniform_distribution_type_selector() {}

	// constructor that sets the minimum and maximum values for the uniform distribution
	uniform_distribution_type_selector(Type min, Type max)
	{
		std::uniform_real_distribution<Type> configured_ud(min, max);
		distribution = configured_ud;
	}
};


} // namespace detail end

/// An extremly fast and easy to use random number generator.
template<typename Type = int>
class rng
{
private:
	// the actual random engine that will be used to produce the random numbers
	mtl::xoroshiro128plus engine;

	// a selector that based on type selects the correct the uniform distrubition type
	detail::uniform_distribution_type_selector<Type> ud_selector;

public:

	/// Constructor, takes the range from min to max for the generated numbers.
	/// @param[in] min A number for the minimum value that can be generated.
	/// @param[in] max A number for the maximum value that can be generated.
	rng(Type min, Type max)
	{
		seed_random();
		set_min_max(min, max);
	}

	/// Sets the values for the range from the minimum to the maximum possible numbers to generate.
	/// @param[in] min A number for the minimum value that can be generated.
	/// @param[in] max A number for the maximum value that can be generated.
	void set_min_max(Type min, Type max)
	{
		detail::uniform_distribution_type_selector<Type> di(min, max);
		ud_selector = di;
		engine.discard(1);
	}

	/// Returns the minimum value for the range of possible values.
	/// @return The minimum value that the mtl::rng will generate.
	[[nodiscard]]
	Type min() const { return ud_selector.distribution.min(); }

	/// Returns the maximum value for the range of possible values.
	/// @return The maximum value that the mtl::rng will generate.
	[[nodiscard]]
	Type max() const { return ud_selector.distribution.max(); }

	/// Returns a random number.
	/// @return Returns a random number.
	[[nodiscard]]
	Type next() { return ud_selector.distribution(engine); }

	/// Set the seed values of the engine to the engine's default seed values.
	void seed()
	{
		engine.seed();
	}

	/// Seed the engine with a single value and leave the other seed(s) to the default values.
	/// @param[in] seed1 A seed for the randomg engine.
	void seed(uint64_t seed1)
	{
		engine.seed(seed1);
	}

	/// Seed the engine with two seed values.
	/// @param[in] seed1 A seed for the randomg engine.
	/// @param[in] seed2 A seed for the randomg engine.
	void seed(uint64_t seed1, uint64_t seed2)
	{
		engine.seed(seed1, seed2);
	}

	/// Seed the engine with two random seed values from std::random_device.
	void seed_random()
	{
		static std::random_device rd;
		engine.seed(rd(), rd());
	}
};

// ================================================================================================
// RANDOM_CHOICE - Given a container/range selects a random element. 
//                 Similar to Python's random.choice.
// ================================================================================================

/// Given a container returns an iterator to a random element of the container. If the container is
/// empty returns an iterator to the start of the container.
/// @param[in] container A container.
/// @return An iterator to a random element.
template<typename Container>
[[nodiscard]]
inline auto random_choice(const Container& container)
{
	auto size = container.size();
	// keep an iterator to the begining of the containter, if the container is empty the it is the
	// same thing as an iterator to the end of the container
	auto iterator = container.begin();
	// make sure the container has at least one element
	if (size >= 1)
	{
		// create a random number generator with index values that fit within the container
		rng<int> rng_selector(0, static_cast<int>(size - 1));
		// move the iterator forward a random number of values
		iterator = std::next(container.begin(), rng_selector.next());
	}
	return iterator;
}

/// Given a range first to last returns an iterator to a random element in the range. If the 
/// range is empty returns an iterator to the start of the range.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
/// @return An iterator to a random element in the range.
template<typename Iter>
[[nodiscard]]
inline auto random_choice(Iter first, Iter last)
{
	// find how many elements exist in the range (first, last)
	auto size = std::distance(first, last);
	// keep an iterator to the begining of the containter, if the container is empty the it is the
	// same thing as an iterator to the end of the container
	auto iterator = first;
	// make sure the container has at least one element
	if (size >= 1)
	{
		// create a random number generator with index values that fit within the container
		rng<int> rng_selector(0, static_cast<int>(size - 1));
		// move the iterator forward a random number of values
		iterator = std::next(first, rng_selector.next());
	}
	return iterator;
}

// ================================================================================================
// SHUFFLE - Shuffles all elements in a container / range from first to last.
// ================================================================================================

/// Shuffles all elements in a range from first to last. All elements in the range are moved to a
/// random position at least once.
/// @param[in] first Iterator to the start of the range.
/// @param[in] last Iterator to the end of the range.
template<typename Iter>
inline void shuffle(Iter first, Iter last)
{
	// find the number of elements in the range so we can configure the rng
	const auto size = std::distance(first, last);
	// we need at least 2 elements to do anything
	if (size > 1)
	{
		// create an rng that will select random positions
		rng<uint64_t> positions(0, static_cast<uint64_t>(size - 1));
		// loop through the entire range
		for (auto it = first; it != last; ++it)
		{
			// create an iterator to a random position in the range
			auto target_it = std::next(first, static_cast<std::ptrdiff_t>(positions.next()));
			// swap the two elements
			std::iter_swap(it, target_it);
		}
	}
}



/// Shuffles all elements in a container that support bidirectional access.
/// @param[in] container A container.
template<typename Container>
inline void shuffle(Container& container)
{
	// get iterators to the start and and of the container
	auto first = container.begin();
	auto last = container.end();

	// keep the size of the container
	size_t size = container.size();

	// we need at least 2 elements to do anything
	if (size > 1)
	{
		// create an rng that will select random positions
		rng<size_t> positions(0, size - 1);
		// loop through the entire range
		for (auto it = first; it != last; ++it)
		{
			// create an iterator to a random position in the range
			auto target_it = std::next(first, static_cast<std::ptrdiff_t>(positions.next()));
			// swap the two elements
			std::iter_swap(it, target_it);
		}
	}
}


} // namespace mtl end