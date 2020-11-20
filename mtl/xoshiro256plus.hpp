#pragma once
// xoshiro256plus random number generator by Michael Trikergiotis
// 28/09/2018
//  
// Header that implements the xoshiro256plus random number generator in the way that the C++ 
// standard library requires. No inheritance used becacuse vptrs destroy performance.
//  
// Satisfies requirements for RandomNumberEngine :
// https:// en.cppreference.com/w/cpp/named_req/RandomNumberEngine
// 
// For information about third party licenses check ThirdPartyNotices.txt.


#include <cstdint>		// uint64_t
#include <limits>		// std::numeric_limits::min, std::numeric_limits::max
#include <ostream>		// std::basic_ostream
#include <istream>		// std::basic_istream
#include <type_traits>  // std::is_unsigned_v

namespace mtl
{


// ================================================================================================
// XOSHIRO256PLUS_ENGINE - The xoshiro256plus_engine random number generator engine.
// ================================================================================================

/// This is the engine for the xoshiro256plus random number generator. For general purpose
/// everyday use you should use the xoshiro256plus typedef instead of this. This template allows
/// to define the result type and pass the default seed values.
template<typename ResultType, uint64_t DefaultSeed1, uint64_t DefaultSeed2, 
		 uint64_t DefaultSeed3, uint64_t DefaultSeed4>
class xoshiro256plus_engine
{
	// check some very fundumental thing for the engine to work
	static_assert(std::is_unsigned_v<ResultType>,
				  "The type for the result of xoshiro256plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed1)>,
				  "The type for the default seed of xoshiro256plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed2)>,
				  "The type for the default seed of xoshiro256plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed3)>,
				  "The type for the default seed of xoshiro256plus_engine has to be unsigned.");

	static_assert(std::is_unsigned_v<decltype(DefaultSeed4)>,
				  "The type for the default seed of xoshiro256plus_engine has to be unsigned.");


public:

	// Required type definition for compatibility reasons with C++ standard library.

	/// Type used for the state.
	using state_type = uint64_t;

	/// Type used for the result.
	using result_type = ResultType;

private:

	/// Defines a type to hold values that will represent the engine state. The xoshiro256plus
	/// algorithm needs 4 values for state.
	struct state_struct
	{
		///  The first seed.
		state_type seed_1;
		///  The second seed.
		state_type seed_2;
		///  The third seed.
		state_type seed_3;
		///  The fourth seed.
		state_type seed_4;

		/// Default constructor with default seed values.
		state_struct()
		{
			// default seed for xoshiro256plus
			seed_1 = DefaultSeed1;
			seed_2 = DefaultSeed2;
			seed_3 = DefaultSeed3;
			seed_4 = DefaultSeed4;
		}

		/// Constructor with given seed values.
		/// @param[in] seed1 The first seed.
		/// @param[in] seed2 The second seed.
		/// @param[in] seed3 The third seed.
		/// @param[in] seed4 The fourth seed.
		/// @return The current internal state.
		state_struct(state_type seed1, state_type seed2, state_type seed3, state_type seed4)
		{
			seed_1 = seed1;
			seed_2 = seed2;
			seed_3 = seed3;
			seed_4 = seed4;
		}

		/// Equality operator.
		/// @param[in] other Another state_struct to compare.
		/// @return If the two states are equal or not.
		[[nodiscard]]
		bool operator==(const state_struct& other) const
		{
			return seed_1 == other.seed_1 && seed_2 == other.seed_2 &&
				   seed_3 == other.seed_3 && seed_4 == other.seed_4;
		}

		/// Inequality operator.
		/// @param[in] other Another state_struct to compare.
		/// @return If the two states are inequal or not.
		[[nodiscard]]
		bool operator!=(const state_struct& other) const
		{
			return seed_1 != other.seed_1 || seed_2 != other.seed_2 ||
				   seed_3 != other.seed_3 || seed_4 != other.seed_4;
		}
	};

	/// The engine state.
	state_struct _state;

public:

	// ============================================================================================
	// XOSHIRO256PLUS_ENGINE - Constructor with no parameters. It will use default seed values.
	// ============================================================================================

	/// Constructor with no parameters. It will use default seed values.
	xoshiro256plus_engine()
	{
		_state = state_struct();
	}

	// ============================================================================================
	// XOSHIRO256PLUS_ENGINE - Constructor with a single seed value. It will use default seed
	//                         values except one seed value which will be the given value.
	// ============================================================================================

	/// Constructor with a single seed value. It will use default seed values except one seed value
	/// which will be the given value.
	/// @param[in] value A single seed value.
	xoshiro256plus_engine(state_type value)
	{
		state_struct new_state;
		new_state.seed_1 = value;
		_state = new_state;
	}

	// ============================================================================================
	// XOSHIRO256PLUS_ENGINE - Constructor with multiple seed values.
	// ============================================================================================

	/// Constructor with multiple seed values.
	/// @param[in] seed1 The first seed.
	/// @param[in] seed2 The second seed.
	/// @param[in] seed1 The third seed.
	/// @param[in] seed2 The fourth seed.
	xoshiro256plus_engine(state_type seed1, state_type seed2, state_type seed3, state_type seed4)
	{
		state_struct new_state(seed1, seed2, seed3, seed4);
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
	// XOSHIRO256PLUS_ENGINE - Copy constructor that copies the state of another random engine of
	//                         the same type.
	// ============================================================================================

	/// Copy constructor that copies the state of another random engine of the same type.
	/// @param[in] other Another random engine.
	xoshiro256plus_engine(const xoshiro256plus_engine& other)
	{
		seed(other.state());
	}

	// ============================================================================================
	// OPERATOR= - Copy assignment operator that copies the state of another random engine of the
	//             same type.
	// ============================================================================================

	/// Copy assignment operator that copies the state of another random engine of the same type.
	/// @param[in] other Another random engine.
	[[nodiscard]]
	xoshiro256plus_engine& operator= (const xoshiro256plus_engine& other)
	{
		seed(other.state());
		return *this;
	}

	// ============================================================================================
	// SEED - Set the seed by copying the seed values of another random engine of the same type.
	// ============================================================================================

	/// Set the seed by copying the seed values of another random engine of the same type.
	/// @param[in] other Another random engine.
	void seed(const xoshiro256plus_engine& other) { _state = other.state(); }

	// ============================================================================================
	// SEED - Set the seed state to the default seed values.
	// ============================================================================================

	/// Set the seed state to the default seed values.
	void seed() { _state = state_struct(); }

	// ============================================================================================
	// SEED - Seed the random engine to the default seed values except the one given seed value.
	// ============================================================================================

	/// Seed the random engine to the default seed values except the one given seed value.
	/// @param[in] seed_value A single seed value.
	void seed(state_type seed_value)
	{
		auto new_state = state_struct();
		new_state.seed_2 = seed_value;
		_state = new_state;
	}

	// ============================================================================================
	// SEED - Seed the random engine with a multiple seed values.
	// ============================================================================================

	/// Seed the random engine with a multiple seed values.
	/// @param[in] seed1 The first seed.
	/// @param[in] seed2 The second seed.
	/// @param[in] seed3 The third seed.
	/// @param[in] seed4 The fourth seed.
	void seed(state_type seed1, state_type seed2, state_type seed3, state_type seed4)
	{
		state_struct new_state(seed1, seed2, seed3, seed4);
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
#if defined(__clang__)
	__attribute__((no_sanitize("integer")))
#endif
	result_type operator()()
	{
		// ----------------------------------------------------------------------------------------
		// xoshiro256plus algorithm
		// ----------------------------------------------------------------------------------------
		state_type result = _state.seed_1 + _state.seed_2 + _state.seed_3 +
							_state.seed_4;
		const state_type stored_seed = _state.seed_2 << 17;
		_state.seed_3 ^= _state.seed_1;
		_state.seed_4 ^= _state.seed_2;
		_state.seed_2 ^= _state.seed_3;
		_state.seed_1 ^= _state.seed_4;
		_state.seed_3 ^= stored_seed;
		_state.seed_4 = (_state.seed_4 << 45) | (_state.seed_4 >> (64 - 45));
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
	operator<< (std::basic_ostream<CharType, Traits>& os, const xoshiro256plus_engine& rngen)
	{
		state_struct current_state = rngen._state;
		os << current_state.seed_1 << ' ' << current_state.seed_2 << ' ' <<current_state.seed_3 
		   << ' ' << current_state.seed_4;
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
	operator>> (std::basic_istream<CharType, Traits>& is, xoshiro256plus_engine& rngen)
	{
		state_type seed1;
		state_type seed2;
		state_type seed3;
		state_type seed4;
		is >> seed1 >> seed2 >> seed3 >> seed4;
		rngen.seed(seed1, seed2, seed3, seed4);
		return is;
	}

	// ============================================================================================
	// OPERATOR== - Equality operator.
	// ============================================================================================
	
	/// Equality operator.
	/// @param[in] rhs A random number generation engine to compare for equality.
	/// @param[in] lhs A random number generation engine to compare for equality.
	[[nodiscard]]
	friend bool operator==(const xoshiro256plus_engine& rhs, const xoshiro256plus_engine& lhs)
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
	friend bool operator!=(const xoshiro256plus_engine& rhs, const xoshiro256plus_engine& lhs)
	{
		return !(rhs == lhs);
	}
};

// ================================================================================================
// XOSHIRO256PLUS        - Typedef of xoshiro256plus_engine random number generator engine with 
//                         default types and default seed values for easier usage.
// ================================================================================================

/// The xoshiro256plus random number generator is extremely fast with very good quality
/// randomness. It is nearly three times faster than Mersenne Twister (std::mt19937_64) while also
/// having better randomness and a smaller footprint. Compared to xoroshiro128plus is 8% to 20%
/// slower and has larger footprint but it has larger period and is better suited for higher levels
/// of parallelism when using multiple instances. It is not cryptographically secure. 
using xoshiro256plus = xoshiro256plus_engine<uint64_t,
	  0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c>;


} // namespace mtl end

