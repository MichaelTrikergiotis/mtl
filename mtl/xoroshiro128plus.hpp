#pragma once
// xoroshiro128plus random number generator by Michael Trikergiotis
// 28/09/2018
//  
// Header that implements the xoroshiro128plus random number generator in the way that the C++ 
// standard library requires. No inheritance used becacuse vptrs destroy performance.
//  
// Satisfies requirements for RandomNumberEngine :
// https:// en.cppreference.com/w/cpp/named_req/RandomNumberEngine
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "definitions.hpp" // various definitions
#include <cstdint>		   // uint64_t
#include <limits>		   // std::numeric_limits
#include <ostream>		   // std::basic_ostream
#include <istream>		   // std::basic_istream
#include <type_traits>     // std::is_unsigned_v


namespace mtl
{

// ================================================================================================
// XOROSHIRO128PLUS_ENGINE - The xoroshiro128plus_engine random number generator engine.
// ================================================================================================

/// This is the engine for the xoroshiro128plus random number generator. For general purpose
/// everyday use you should use the xoroshiro128plus typedef instead of this. This template allows
/// to define the result type and pass the default seed values.
template<typename ResultType, uint64_t DefaultSeed1, uint64_t DefaultSeed2>
class xoroshiro128plus_engine
{
	// check some very fundumental thing for the engine to work
	static_assert(std::is_unsigned_v<ResultType>,
				  "The type for the result of xoroshiro128plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed1)>,
				  "The type for the default seed of xoroshiro128plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed2)>,
				  "The type for the default seed of xoroshiro128plus_engine has to be unsigned.");


public:

	// Required type definition for compatibility reasons with C++ standard library.

	/// Type used for the state.
	using state_type = uint64_t;

	/// Type used for the result.
	using result_type = ResultType;

private:

	/// Defines a type to hold values that will represent the engine state. The xoroshiro128plus
	/// algorithm needs 2 values for state.
	struct state_struct
	{
		///  The first seed.
		state_type seed_1;
		/// The second seed.
		state_type seed_2;

		/// Default constructor with default seed values.
		state_struct()
		{
			// default seed for xoroshiro128plus
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
		bool operator==(const state_struct& other) const
		{
			return seed_1 == other.seed_1 && seed_2 == other.seed_2;
		}

		/// Inequality operator.
		/// @param[in] other Another state_struct to compare.
		/// @return If the two states are inequal or not.
		[[nodiscard]]
		bool operator!=(const state_struct& other) const
		{
			return seed_1 != other.seed_1 || seed_2 != other.seed_2;
		}
	};

	/// The engine state.
	state_struct _state;

public:

	// ============================================================================================
	// XOROSHIRO128PLUS_ENGINE - Constructor with no parameters. It will use default seed values.
	// ============================================================================================

	/// Constructor with no parameters. It will use default seed values.
	xoroshiro128plus_engine()
	{
		_state = state_struct();
	}

	// ============================================================================================
	// XOROSHIRO128PLUS_ENGINE - Constructor with a single seed value. It will use default seed 
	//                           values except one seed value which will be the given value.
	// ============================================================================================

	/// Constructor with a single seed value. It will use default seed values except one seed value
	/// which will be the given value.
	/// @param[in] seed1 A single seed value.
	xoroshiro128plus_engine(state_type seed1)
	{
		state_struct new_state;
		new_state.seed_1 = seed1;
		_state = new_state;
	}

	// ============================================================================================
	// XOROSHIRO128PLUS_ENGINE - Constructor with multiple seed values.
	// ============================================================================================

	/// Constructor with multiple seed values.
	/// @param[in] seed1 The first seed.
	/// @param[in] seed2 The second seed.
	xoroshiro128plus_engine(state_type seed1, state_type seed2)
	{
		state_struct new_state(seed1, seed2);
		_state = new_state;
	}
private:

	/// Get engine internal state.
	/// @return The engine internal state.
	[[nodiscard]]
	state_struct state() const { return _state; }

	/// Set the state given another state.
	/// @param[in] new_sate A different state of the engine.
	void seed(const state_struct &new_state) { _state = new_state; }

public:

	// ============================================================================================
	// XOROSHIRO128PLUS_ENGINE - Copy constructor that copies the state of another random engine 
	//                           of the same type.
	// ============================================================================================

	/// Copy constructor that copies the state of another random engine of the same type.
	/// @param[in] other Another random engine of the same type.
	xoroshiro128plus_engine(const xoroshiro128plus_engine& other)
	{
		seed(other.state());
	}

	// ============================================================================================
	// XOROSHIRO128PLUS_ENGINE - Move constructor that copies the state of another random engine 
	//                           of the same type.
	// ============================================================================================

	/// Move constructor that moves the state of another random engine of the same type.
	/// @param[in] other Another random generation engine of the same type.
	xoroshiro128plus_engine(xoroshiro128plus_engine&& other) noexcept
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
	xoroshiro128plus_engine& operator= (const xoroshiro128plus_engine& other)
	{
		seed(other.state());
		return *this;
	}

	// ============================================================================================
    // OPERATOR= - Move assignment operator that moves the state of another random engine of the
	//             same type.
	// ============================================================================================

	/// Move assignment operator that moves the state of another random engine of the same type.
	/// @param[in] other Another random generation engine of the same type.
	xoroshiro128plus_engine& operator=(xoroshiro128plus_engine&& other) noexcept
	{
		seed(other.state());
		return *this;
	}

	// ============================================================================================
	// ~XOROSHIRO128PLUS_ENGINE - Destructor.
	// ============================================================================================
	
	/// Destructor.
	~xoroshiro128plus_engine() = default;

	// ============================================================================================
	// SEED - Set the seed by copying the seed values of another random engine of the same type.
	// ============================================================================================

	/// Set the seed by copying the seed values of another random engine of the same type.
	/// @param[in] other Another random engine.
	void seed(const xoroshiro128plus_engine& other) { _state = other.state(); }

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
		// ----------------------------------------------------------------------------------------
		// xoroshiro128plus algorithm
		// ----------------------------------------------------------------------------------------
		state_type seed1 = _state.seed_1;
		state_type seed2 = _state.seed_2;
		state_type result = seed1 + seed2;
		seed2 ^= seed1;
		_state.seed_1 = ((seed1 << 24) | (seed1 >> (64 - 24))) ^ seed2 ^ (seed2 << 16);
		_state.seed_2 = (seed2 << 37) | (seed2 >> (64 - 37));
		return static_cast<result_type>(result);
	}

	// ============================================================================================
	// GENERATE - Fills the range first to last with values from the random number generator.
	// ============================================================================================

	/// Fills the range first to last with values from the random number generator.
	/// @param[in] first Iterator to the beginning of the range.
	/// @param[in] last Iterator to the end of the range.
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
	/// @param[in] count Number of time to advance the random number generator.
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
	/// @param[out] os An std::basic_ostream to use as ouput.
	/// @param[in] rngen The random number generator engine to get the state.
	/// @return An std::basic_ostream.
	template<typename CharType, typename Traits>
	friend std::basic_ostream<CharType, Traits>&
	operator<< (std::basic_ostream<CharType, Traits>& os, const xoroshiro128plus_engine& rngen)
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
	operator>> (std::basic_istream<CharType, Traits>& is, xoroshiro128plus_engine& rngen)
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
	friend bool operator==(const xoroshiro128plus_engine& rhs, const xoroshiro128plus_engine& lhs)
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
	friend bool operator!=(const xoroshiro128plus_engine& rhs, const xoroshiro128plus_engine& lhs) 
	{
		return !(rhs == lhs);
	}
};


// ================================================================================================
// XOROSHIRO128PLUS        - Typedef of xoroshiro128plus_engine random number generator engine with
//                           default types and default seed values for easier usage.
// ================================================================================================

/// The xoroshiro128plus random number generator is extremely fast with very good quality
/// randomness. It is three times faster than Mersenne Twister (std::mt19937_64) while also having
/// better randomness and a smaller footprint. It is not cryptographically secure. 
using xoroshiro128plus = xoroshiro128plus_engine<uint64_t,
												 0xdf900294d8f554a5, 0x170865df4b3201fc>;


} // namespace mtl end