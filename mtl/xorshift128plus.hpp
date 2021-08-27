#pragma once
// xorshift128plus header by Michael Trikergiotis
// 28/09/2018
//  
// 
// This header contains the implementation of the xorshift128plus random number generator in the
// way that the C++ standard library requires for random number generation engines. No inheritance
// is used because vptrs destroy performance.
// 
// Satisfies the requirements for RandomNumberEngine :
// https://en.cppreference.com/w/cpp/named_req/RandomNumberEngine
// 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp" // various definitions
#include <cstdint>		   // uint64_t
#include <limits>		   // std::numeric_limits
#include <ostream>		   // std::basic_ostream
#include <istream>		   // std::basic_istream
#include <type_traits>     // std::is_unsigned_v


namespace mtl
{

// ================================================================================================
// XORSHIFT128PLUS_ENGINE - The xorshift128plus_engine random number generator engine.
// ================================================================================================

/// This is the engine for the xorshift128plus random number generator. For most cases, prefer to
/// use the xorshift128plus typedef instead of this. This template allows you to define the
/// resulting type and pass the default seed values.
template<typename ResultType, uint64_t DefaultSeed1, uint64_t DefaultSeed2>
class xorshift128plus_engine
{
	// check some very fundamental things for the engine to work
	static_assert(std::is_unsigned_v<ResultType>,
				  "The type for the result of xorshift128plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed1)>,
				  "The type for the default seed of xorshift128plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed2)>,
				  "The type for the default seed of xorshift128plus_engine has to be unsigned.");



public:

	// Required type definition for compatibility reasons with C++ standard library.

	/// Type used for the state.
	using state_type = uint64_t;

	/// Type used for the result.
	using result_type = ResultType;

private:

	/// Defines a type to hold values that will represent the engine state. The xorshift128plus
	/// algorithm needs 2 values for state.
	struct state_struct
	{
		/// The first seed.
		state_type seed_1;
		/// The second seed.
		state_type seed_2;

		/// Default constructor with default seed values.
		state_struct()
		{
			// default seed for xorshift128plus
			seed_1 = DefaultSeed1;
			seed_2 = DefaultSeed2;
		}

		/// Constructor with given seed values.
		/// @param[in] seed1 The first seed.
		/// @param[in] seed2 The second seed.
		/// @return The current internal state.
		state_struct(state_type seed1, state_type seed2)
		{
			seed_1 = seed1;
			seed_2 = seed2;
		}

		/// Equality operator.
		/// @param[in] other Another state_struct to compare.
		/// @return If the two states are equal or not.
		[[nodiscard]]
		bool operator== (const state_struct& other) const
		{
			return seed_1 == other.seed_1 && seed_2 == other.seed_2;
		}

		/// Inequality operator.
		/// @param[in] other Another state_struct to compare.
		/// @return If the two states are inequal or not.
		[[nodiscard]]
		bool operator!= (const state_struct& other) const
		{
			return seed_1 != other.seed_1 || seed_2 != other.seed_2;
		}
	};

	/// The engine state.
	state_struct _state;

public:

	// ============================================================================================
	// XORSHIFT128PLUS_ENGINE - Constructor with no parameters. It will use default seed values.
	// ============================================================================================

	/// Constructor with no parameters. It will use default seed values.
	xorshift128plus_engine()
	{
		_state = state_struct();
	}

	// ============================================================================================
	// XORSHIFT128PLUS_ENGINE - Constructor with a single seed value. It will use default seed 
	//                          values except one seed value which will be the given value.
	// ============================================================================================

	/// Constructor with a single seed value. It will use default seed values except one seed value
	/// which will be the given value.
	/// @param[in] seed1 A single seed value.
	xorshift128plus_engine(state_type seed1)
	{
		state_struct new_state;
		new_state.seed_1 = seed1;
		_state = new_state;
	}


	// ============================================================================================
	// XORSHIFT128PLUS_ENGINE - Constructor with multiple seed values.
	// ============================================================================================

	/// Constructor with multiple seed values.
	/// @param[in] seed1 The first seed.
	/// @param[in] seed2 The second seed.
	xorshift128plus_engine(state_type seed1, state_type seed2)
	{
		state_struct new_state(seed1, seed2);
		_state = new_state;
	}

private:

	/// Get the engine's internal state.
	/// @return The engine internal state.
	[[nodiscard]]
	state_struct state() const { return _state; }

	/// Set the state given another state.
	/// @param[in] new_sate A different state of the engine.
	void seed(const state_struct& new_state) { _state = new_state; }

public:

	// ============================================================================================
	// XORSHIFT128PLUS_ENGINE - Copy constructor that copies the state of another random engine 
	//                          of the same type.
	// ============================================================================================

	/// Copy constructor that copies the state of another random engine of the same type.
	/// @param[in] other Another random engine of the same type.
	xorshift128plus_engine(const xorshift128plus_engine& other)
	{
		seed(other.state());
	}

	// ============================================================================================
	// XORSHIFT128PLUS_ENGINE - Move constructor that copies the state of another random engine 
	//                          of the same type.
	// ============================================================================================

	/// Move constructor that moves the state of another random engine of the same type.
	/// @param[in] other Another random generation engine of the same type.
	xorshift128plus_engine(xorshift128plus_engine&& other) noexcept
	{
		seed(other.state());
	}

	// ============================================================================================
	// OPERATOR= - Copy assignment operator that copies the state of another random engine of the
	//             same type.
	// ============================================================================================

	/// Copy assignment operator that copies the state of another random engine of the same type.
	/// @param[in] other Another random generation engine of the same type.
	[[nodiscard]]
	xorshift128plus_engine& operator= (const xorshift128plus_engine& other)
	{
		// handle self-copy assignment
		if(this == &other)
		{
			return *this;
		}
		seed(other.state());
		return *this;
	}

	// ============================================================================================
    // OPERATOR= - Move assignment operator that moves the state of another random engine of the
	//             same type.
	// ============================================================================================

	/// Move assignment operator that moves the state of another random engine of the same type.
	/// @param[in] other Another random generation engine of the same type.
	xorshift128plus_engine& operator= (xorshift128plus_engine&& other) noexcept
	{
		// handle self-copy assignment
		if(this == &other)
		{
			return *this;
		}
		seed(other.state());
		return *this;
	}

	// ============================================================================================
	// ~XORSHIFT128PLUS_ENGINE - Destructor.
	// ============================================================================================
	
	/// Destructor.
	~xorshift128plus_engine() = default;

	// ============================================================================================
	// SEED - Set the seed by copying the seed values of another random engine of the same type.
	// ============================================================================================

	/// Set the seed by copying the seed values of another random engine of the same type.
	/// @param[in] other Another random engine.
	void seed(const xorshift128plus_engine& other) { _state = other.state(); }

	// ============================================================================================
	// SEED - Set the seed state to the default seed values.
	// ============================================================================================

	/// Set the seed state to the default seed values.
	void seed() { _state = state_struct(); }

	// ============================================================================================
	// SEED - Seed the random engine to the default seed values except the one given seed value.
	// ============================================================================================

	/// Seed the random engine to the default seed values except the one given seed value.
	/// @param[in] seed1 A single seed value.
	void seed(state_type seed1)
	{
		auto new_state = state_struct();
		new_state.seed_1 = seed1;
		_state = new_state;
	}

	// ============================================================================================
	// SEED - Seed the random engine with multiple seed values.
	// ============================================================================================

	/// Seed the random engine with multiple seed values.
	/// @param[in] seed1 The first seed.
	/// @param[in] seed2 The second seed.
	void seed(state_type seed1, state_type seed2)
	{
		state_struct new_state(seed1, seed2);
		_state = new_state;
	}

	// ============================================================================================
	// MIN - Returns the minimum value the random number generator can produce.
	// ============================================================================================

	/// Returns the minimum value the random number generator can produce.
	/// @return The minimum value the random number generator can produce.
	[[nodiscard]]
	constexpr static result_type min() { return std::numeric_limits<result_type>::min(); }

	// ============================================================================================
	// MAX - Returns the maximum value the random number generator can produce.
	// ============================================================================================

	/// Returns the maximum value the random number generator can produce.
	/// @return The maximum value the random number generator can produce.
	[[nodiscard]]
	constexpr static result_type max() { return std::numeric_limits<result_type>::max(); }

	// ============================================================================================
	// OPERATOR() - Returns the next value of the random number generator.
	// ============================================================================================

	/// Returns the next value of the random number generator.
	/// @return The next value of the random number generator.
	[[nodiscard]]
	result_type operator()()
	{
		state_type seed1 = _state.seed_1;
		state_type seed2 = _state.seed_2;
		_state.seed_1 = seed2;
		seed1 ^= seed1 << 23;
		seed1 ^= seed1 >> 17;
		seed1 ^= seed2;
		seed1 ^= seed2 >> 26;
		_state.seed_2 = seed1;
		return static_cast<result_type>(_state.seed_1 + _state.seed_2);
	}

	// ============================================================================================
	// GENERATE - Fills the range first to last with values from the random number generator.
	// ============================================================================================

	/// Fills the range first to last with values from the random number generator.
	/// @param[out] first Iterator to the beginning of the range.
	/// @param[out] last Iterator to the end of the range.
	template<typename Iter>
	void generate(Iter first, Iter last)
	{
		for (auto it = first; it != last; ++it)
		{
			// write the value to the range by using the operator () from the this pointer
			*it = this->operator()();
		}
	}

	// ============================================================================================
	// DISCARD - Advances the state of the random number generator by a number of times.
	// ============================================================================================

	/// Advances the state of the random number generator by a number of times.
	/// @param[in] count Number of times to advance the random number generator.
	void discard(size_t count)
	{
		for (size_t i = count; i > 0; i--)
		{
			[[maybe_unused]]auto result = this->operator()();
		}
	}

	// ============================================================================================
	// OPERATOR<< - Writes the textual representation of the seed values to an std::ostream.
	// ============================================================================================

	/// Writes the textual representation of the seed values to an std::ostream.
	/// @param[out] os An std::basic_ostream to use as output.
	/// @param[in] rngen The random number generator engine to get the state.
	/// @return An std::basic_ostream.
	template<typename CharType, typename Traits>
	friend std::basic_ostream<CharType, Traits>&
	operator<< (std::basic_ostream<CharType, Traits>& os, const xorshift128plus_engine& rngen)
	{
		state_struct current_state = rngen._state;
		os << current_state.seed_1 << ' ' << current_state.seed_2;
		return os;
	}

	// ============================================================================================
	// OPERATOR>> - Reads and sets seed values from the textual representation of an std::istream.
	// ============================================================================================

	/// Reads and sets seed values from the textual representation of an std::istream.
	/// @param[in] is An std::basic_istream to use as input.
	/// @param[in] rngen The random number generator engine to set the state.
	/// @return An std::basic_istream.
	template<typename CharType, typename Traits>
	friend std::basic_istream<CharType, Traits>& 
	operator>> (std::basic_istream<CharType, Traits>& is, xorshift128plus_engine& rngen)
	{
		state_type seed1 = 0;
		state_type seed2 = 0;
		is >> seed1 >> seed2;
		rngen.seed(seed1, seed2);
		return is;
	}

	// ============================================================================================
	// OPERATOR== - Equality operator.
	// ============================================================================================

	/// Equality operator.
	/// @param[in] rhs A random number generation engine to compare for equality.
	/// @param[in] lhs A random number generation engine to compare for equality.
	[[nodiscard]]
	friend bool operator== (const xorshift128plus_engine& rhs, const xorshift128plus_engine& lhs)
	{
		return (rhs.state() == lhs.state());
	}

	// ============================================================================================
	// OPERATOR!= - Inequality operator.
	// ============================================================================================

	/// Inequality operator.
	/// @param[in] rhs A random number generation engine to compare for inequality.
	/// @param[in] lhs A random number generation engine to compare for inequality.
	[[nodiscard]]
	friend bool operator!= (const xorshift128plus_engine& rhs, const xorshift128plus_engine& lhs)
	{
		return !(rhs == lhs);
	}
};

// ================================================================================================
// XORSHIFT128PLUS        - Typedef of xorshift128plus_engine random number generator engine with 
//                          default types and default seed values for easier usage.
// ================================================================================================

/// The xorshift128plus random number generator is very fast with good quality randomness. It is 
/// faster than Mersenne Twister (std::mt19937_64) while also having better randomness and a 
/// smaller footprint. It is not cryptographically secure. 
using xorshift128plus = xorshift128plus_engine<uint64_t,
											   0x8a5cd789635d2dff, 0x121fd2155c472f96>;


} // namespace mtl end
