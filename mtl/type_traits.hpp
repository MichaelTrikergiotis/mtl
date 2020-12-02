#pragma once
// type traits by Michael Trikergiotis
// 26/03/2018
// 
// Header for type traits used to make template metaprogramming easier and more expresive.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "definitions.hpp" // various definitions
#include <array>           // std::array
#include <vector>          // std::vector
#include <deque>           // std::deque
#include <forward_list>    // std::forward_list
#include <list>            // std::list
#include <set>             // std::set, std::multiset
#include <map>             // std::map, std::multimap
#include <unordered_set>   // std::unordered_set, std::unordered_multiset
#include <unordered_map>   // std::unordered_map, std::unordered_map
#include <stack>           // std::stack
#include <queue>           // std::queue, std::priority_queue
#include <utility>         // std::pair
#include <iterator>        // std::input_iterator_tag, std::output_iterator_tag, 
						   // std::iterator_traits
#include <type_traits>     // std::false_type, std::true_type, std::enable_if_t, std::conditional,
                           // std::integral_constant, std::is_base_of_v, std::is_same_v,
						   // std::is_convertible_v, std::remove_cv_t, std::remove_reference_t



namespace mtl
{

// ================================================================================================
// ARE_SAME - Returns if a type is the same as all the types in a parameter pack.
// ================================================================================================

namespace detail
{

template <typename... Args>
struct are_same_impl : std::true_type {};

template <typename Type, typename... Args>
struct are_same_impl<Type, Args...> :
std::conditional<Type::value, are_same_impl<Args...>, std::false_type>::type {};

} // namespace detail end

/// Returns if a type is the same as all the types in a parameter pack.
template <typename Type, typename... Args>
struct are_same : detail::are_same_impl<std::is_same<Type, Args>...> {};

/// Returns if a type is the same as all the types in a parameter pack. Helper type.
template <typename Type, typename... Args>
constexpr bool are_same_v = are_same<Type, Args...>::value;


// ================================================================================================
// HAS_RESERVE      - Detects if the given type has the reserve function.
// ================================================================================================

/// Returns a boolean whether the type has the reserve function or not.
template<typename Type, typename = void>
struct has_reserve : std::false_type {};

/// Returns a boolean whether the type has the reserve function or not.
template<typename Type>
struct has_reserve<Type, std::enable_if_t<
std::is_same_v<decltype(std::declval<Type>().reserve(std::declval<typename Type::size_type>())),
void>>> : std::true_type {};


/// Returns a boolean whether the type has the reserve function or not. Helper type that allows you
/// to use elide the ::value at the end.
template<typename Type>
constexpr bool has_reserve_v = has_reserve<Type>::value;




// ================================================================================================
// HAS_PUSH_BACK  - Detects if the type has the push_back function.
// ================================================================================================

/// Returns a boolean whether the type has the push_back function or not.
template<typename Type, typename = void>
struct has_push_back : std::false_type {};

/// Returns a boolean whether the type has the push_back function or not.
template<typename Type>
struct has_push_back<Type, std::enable_if_t<
std::is_same_v<decltype(std::declval<Type>().push_back(std::declval<typename Type::value_type>())),
void>>> : std::true_type {};

/// Returns a boolean whether the type has the push_back function or not. Helper type that allows
/// you to elide the ::value at the end.
template<typename Type>
constexpr bool has_push_back_v = has_push_back<Type>::value;



// ================================================================================================
// HAS_EMPLACE_BACK - Detects if the type has the emplace_back function.
// ================================================================================================

namespace detail
{

// Actual implementation has_emplace_back that detects if the type has the emplace_back function.
template<typename Type, typename FunctionSignature, typename = void>
struct has_emplace_back_detector : std::false_type {};


// Actual implementation has_emplace_back that detects if the type has the emplace_back function.
template<typename Type, typename FunctionSignature, typename... Args>
struct has_emplace_back_detector<Type, FunctionSignature(Args...),
typename std::enable_if_t<
// check if a function with the given signature exists, we are looking if the function
// emplace_back exists for the given container type
std::is_convertible_v<decltype(std::declval<Type>().emplace_back(std::declval<Args>()...)),
FunctionSignature> ||
// since we don't care about the return type we match with void, and since everything matches with
// the return type will match no matter what
std::is_same_v<FunctionSignature, void>>> : std::true_type {};


// Detects if the type has the emplace_back function. The adapter specifically adapts to the
// desired function signature so we don't have to type it from the caller.
template<typename Type>
struct has_emplace_back_adapter
{
	static constexpr bool value =
	std::integral_constant<bool, has_emplace_back_detector
	<Type, void(typename Type::value_type)>::value>::value;
};

}  //  namespace detail


/// Detects if the type has the emplace_back function.
template<typename Type>
struct has_emplace_back
{
	static constexpr bool value = detail::has_emplace_back_adapter<Type>::value;
};


/// Detects if the type has the emplace_back function. Helper type that allows you to elide 
/// the ::value at the end.
template<typename Type>
constexpr bool has_emplace_back_v = has_emplace_back<Type>::value;



// ================================================================================================
// HAS_SIZE   - Detects if a type has a size function.
// HAS_SIZE_V - Helper that allows you to elide the ::value at the end.
// ================================================================================================

/// Returns a boolean whether the type has the size function or not.
template<typename Type, typename = void>
struct has_size : std::false_type {};

/// Returns a boolean whether the type has the size function or not.
template<typename Type>
struct has_size<Type, std::enable_if_t<
std::is_same_v<decltype(std::declval<Type>().size()), size_t>>> : std::true_type {};

/// Returns a boolean whether the type has the size function or not. Helper that allows you to
/// elide the ::value at the end.
template<typename Type>
constexpr bool has_size_v = has_size<Type>::value;




// ================================================================================================
// HAS_FIND    - Detects if the type has the find function.
// HAS_FIND_V  - Helper that allows you to elide the ::value at the end.
// ================================================================================================

namespace detail
{

// Actual implementation has_find that detects if the type has the find function.
template<typename Type, typename FunctionSignature, typename = void>
struct has_find_detector : std::false_type {};


// Actual implementation has_find that detects if the type has the find function.
template<typename Type, typename FunctionSignature, typename ItemType>
struct has_find_detector<Type, FunctionSignature(ItemType),
typename std::enable_if_t<
// check if a function with the given signature exists, we are looking if the function
// find exists for the given type
std::is_convertible_v<decltype(std::declval<Type>().find(std::declval<ItemType>())),
FunctionSignature> ||
// since we don't care about the return type we match with void, and since everything matches with
// void the return type will match no matter what
std::is_same_v<FunctionSignature, void>>> : std::true_type {};


// Detects if the type has the find function. The adapter specifically adapts to the
// desired function signature so we don't have to type it from the caller.
template<typename Type, typename = void >
struct has_find_adapter
{
    static constexpr bool value =
	std::integral_constant<bool, has_find_detector
	<Type, void(typename Type::value_type)>::value>::value;  
};

// Detects if the type::value_type is a pair and if the type has the find function. The
//  adapter specifically adapts to the desired function signature so we don't have to type it from
// the caller.
template<typename Type>
// struct has_find_adapter<Type, std::enable_if_t<is_std_pair_v<typename Type::value_type>>>
struct has_find_adapter<Type, std::enable_if_t<
std::is_same_v<typename Type::value_type, 
std::pair<typename Type::value_type::first_type, typename Type::value_type::second_type>>>>
{
    static constexpr bool value =
    // makes it work for std::set<std::pair<T, T>>, std::multiset<std::pair<T, T>> etc.
	std::integral_constant<bool, has_find_detector
	<Type, void(typename Type::value_type)>::value>::value ||
    // makes it work for std::map<T1, T2>, std::unordered_map<T1, T2> etc.
    std::integral_constant<bool, has_find_detector
	<Type, void(typename Type::value_type::first_type)>::value>::value;   
};


}  //  namespace detail


/// Detects if the type has the find function.
template<typename Type>
struct has_find
{
	static constexpr bool value = detail::has_find_adapter<Type>::value;
};


/// Detects if the type has the find function. Helper type that allows you to elide the ::value
/// at the end.
template<typename Type>
constexpr bool has_find_v = has_find<Type>::value;




// ================================================================================================
// IS_SINT      - Detects if a type is a signed integer.
// IS_SINT_V    - Helper that allows you to elide the ::value at the end.
// IS_UINT      - Detects if a type is an unsigned integer
// IS_UINT_V    - Helper that allows you to elide the ::value at the end.
// IS_INT       - Detects if a type is signed or unsigned integer.
// IS_INT_V     - Helper that allows you to elide the ::value at the end.
// IS_FLOAT     - Detects if a type is float, double or long double.
// IS_FLOAT_V   - Helper that allows you to elide the ::value at the end.
// IS_NUMBER    - Detects if a type is a number.
// IS_NUMBER_V  - Helper that allows you to elide the ::value at the end.
// IS_CHAR      - Detects if a type is char or unsigned char.
// IS_CHAR_V    - Helper that allows you to elide the ::value at the end.
// ================================================================================================

/// Returns a boolean whether the type is signed integer. Accepted types are int8_t, short, int, 
/// long, long long.
template<typename Type>
struct is_sint : std::integral_constant<bool,
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, int8_t> ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, short>  ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, int>    ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, long>   ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, long long>> {};


/// Returns a boolean whether the type is signed integer. Accepted types are int8_t, short, int,
/// long, long long. Helper that allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_sint_v = is_sint<Type>::value;


/// Returns a boolean whether the type is unsigned integer. Accepted types are uint8_t, 
/// unsigned short, unsigned int, unsigned long, unsigned long long.
template<typename Type>
struct is_uint : std::integral_constant<bool, 
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, uint8_t>        ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, unsigned short> ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, unsigned int>   ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, unsigned long>  ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, unsigned long long>> {};


/// Returns a boolean whether the type is unsigned integer. Accepted types are uint8_t, 
/// unsigned short, unsigned int, unsigned long, unsigned long long. Helper type that helps you
/// elide the ::value at the end.
template<typename Type>
constexpr bool is_uint_v = is_uint<Type>::value;


/// Returns a boolean whether the type is a signed or unsigned integer. Accepted types are int8_t, 
/// short, int, long, long long, uint8_t, unsigned short, unsigned int, unsigned long and 
/// unsigned long long. 
template<typename Type>
struct is_int : std::integral_constant<bool, is_sint_v<Type> || is_uint_v<Type>> {};


/// Returns a boolean whether the type is a signed or unsigned integer. Accepted types are int8_t, 
/// short, int, long, long long, uint8_t, unsigned short, unsigned int, unsigned long and 
/// unsigned long long. Helper that allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_int_v = is_int<Type>::value;


/// Returns a boolean whether the type is a floating point number. Accepted types are float,
/// double and long double.
template<typename Type>
struct is_float : std::integral_constant<bool, 
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, float>  ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, double> ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, long double>> {};


/// Returns a boolean whether the type is a floating point number. Accepted types are float,
/// double and long double. Helper that allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_float_v = is_float<Type>::value;



/// Returns a boolean whether the type is singed or unsigned integer or a floating point number.
/// Accepted types are int8_t, short, int, long, long long, uint8_t, unsigned short, unsigned int, 
/// unsigned long, unsigned long long, float, double, long double.
template<typename Type>
struct is_number : std::integral_constant<bool, is_int_v<Type> || is_float_v<Type>> {};


/// Returns a boolean whether the type is singed or unsigned integer or a floating point number.
/// Accepted types are int8_t, short, int, long, long long, uint8_t, unsigned short, unsigned int, 
/// unsigned long, unsigned long long, float, double, long double. Helper that allows you to elide
/// the ::value at the end.
template<typename Type>
constexpr bool is_number_v = is_number<Type>::value;


/// Returns a boolean whether the type is char or unsigned char.
template<typename Type>
struct is_char : std::integral_constant<bool,
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, char> ||
std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, unsigned char>> {};

/// Returns a boolean whether the type is char or unsigned char. Helper that allows you to elide 
/// the ::value at the end.
template<typename Type>
constexpr bool is_char_v = is_char<Type>::value;

// ================================================================================================
// IS_STD_ARRAY    - Detects if the container is an std::array.
// IS_STD_ARRAY_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::vector.
template<typename Type>
struct is_std_array : std::false_type {};

/// Detects if the container is an std::vector.
template<typename Type, const size_t Size>
struct is_std_array<typename std::array<Type, Size> > : std::true_type {};

/// Detects if the container is an std::vector. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_array_v = is_std_array<Type>::value;



// ================================================================================================
// IS_STD_VECTOR    - Detects if the container is an std::vector.
// IS_STD_VECTOR_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::vector.
template<typename Type>
struct is_std_vector : std::false_type {};

/// Detects if the container is an std::vector.
template<typename Type>
struct is_std_vector<std::vector<Type>> : std::true_type {};

/// Detects if the container is an std::vector. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_vector_v = is_std_vector<Type>::value;



// ================================================================================================
// IS_STD_DEQUE    - Detects if the container is an std::deque.
// IS_STD_DEQUE_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::vector.
template<typename Type>
struct is_std_deque : std::false_type {};

/// Detects if the container is an std::vector.
template<typename Type>
struct is_std_deque<std::deque<Type>> : std::true_type {};

/// Detects if the container is an std::vector. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_deque_v = is_std_deque<Type>::value;



// ================================================================================================
// IS_STD_FORWARD_LIST    - Detects if the container is an std::forward_list.
// IS_STD_FORWARD_LIST_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::forward_list.
template<typename Type>
struct is_std_forward_list : std::false_type {};

/// Detects if the container is an std::forward_list.
template<typename Type>
struct is_std_forward_list<std::forward_list<Type>> : std::true_type {};

/// Detects if the container is an std::forward_list. Helper type that allows you to elide the
/// ::value at the end.
template<typename Type>
constexpr bool is_std_forward_list_v = is_std_forward_list<Type>::value;



// ================================================================================================
// IS_STD_LIST    - Detects if the container is an std::list.
// IS_STD_LIST_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::list.
template<typename Type>
struct is_std_list : std::false_type {};

/// Detects if the container is an std::list.
template<typename Type>
struct is_std_list<std::list<Type>> : std::true_type {};

/// Detects if the container is an std::list. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_list_v = is_std_list<Type>::value;



// ================================================================================================
// IS_STD_SET    - Detects if the container is an std::set.
// IS_STD_SET_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::set.
template<typename Type>
struct is_std_set : std::false_type {};

/// Detects if the container is an std::set.
template<typename Type>
struct is_std_set<std::set<Type>> : std::true_type {};

/// Detects if the container is an std::set. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_set_v = is_std_set<Type>::value;



// ================================================================================================
// IS_STD_MULTISET    - Detects if the container is an std::multiset.
// IS_STD_MULTISET_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::multiset.
template<typename Type>
struct is_std_multiset : std::false_type {};

/// Detects if the container is an std::multiset.
template<typename Type>
struct is_std_multiset<std::multiset<Type>> : std::true_type {};

/// Detects if the container is an std::multiset. Helper type that allows you to elide the 
/// ::value at the end.
template<typename Type>
constexpr bool is_std_multiset_v = is_std_multiset<Type>::value;



// ================================================================================================
// IS_STD_MAP    - Detects if the container is an std::map.
// IS_STD_MAP_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::map.
template<typename = void, typename = void>
struct is_std_map : std::false_type {};

/// Detects if the container is an std::map.
template<typename Type1, typename Type2>
struct is_std_map<std::map<Type1, Type2> > : std::true_type {};

/// Detects if the container is an std::map. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_map_v = is_std_map<Type>::value;



// ================================================================================================
// IS_STD_MULTIMAP    - Detects if the container is an std::multimap.
// IS_STD_MULTIMAP_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::multimap.
template<typename = void, typename = void>
struct is_std_multimap : std::false_type {};

/// Detects if the container is an std::multimap.
template<typename Type1, typename Type2>
struct is_std_multimap<std::multimap<Type1, Type2> > : std::true_type {};

/// Detects if the container is an std::multimap. Helper type that allows you to elide the 
/// ::value at the end.
template<typename Type>
constexpr bool is_std_multimap_v = is_std_multimap<Type>::value;



// ================================================================================================
// IS_STD_UNORDERED_SET    - Detects if the container is an std::unordered_set.
// IS_STD_UNORDERED_SET_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::unordered_set.
template<typename Type>
struct is_std_unordered_set : std::false_type {};

/// Detects if the container is an std::unordered_set.
template<typename Type>
struct is_std_unordered_set<std::unordered_set<Type>> : std::true_type {};

/// Detects if the container is an std::unordered_set. Helper type that allows you to elide the
/// ::value at the end.
template<typename Type>
constexpr bool is_std_unordered_set_v = is_std_unordered_set<Type>::value;



// ================================================================================================
// IS_STD_UNORDERED_MAP    - Detects if the container is an std::unordered_map.
// IS_STD_UNORDERED_MAP_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::unordered_map.
template<typename = void, typename = void>
struct is_std_unordered_map : std::false_type {};

/// Detects if the container is an std::unordered_map.
template<typename Type1, typename Type2>
struct is_std_unordered_map<std::unordered_map<Type1, Type2> > : std::true_type {};

/// Detects if the container is an std::unordered_map. Helper type that allows you to elide the
/// ::value at the end.
template<typename Type>
constexpr bool is_std_unordered_map_v = is_std_unordered_map<Type>::value;



// ================================================================================================
// IS_STD_UNORDERED_MULTISET    - Detects if the container is an std::unordered_mutliset.
// IS_STD_UNORDERED_MULTISET_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::unordered_multiset.
template<typename Type>
struct is_std_unordered_multiset : std::false_type {};

/// Detects if the container is an std::unordered_multiset.
template<typename Type>
struct is_std_unordered_multiset<std::unordered_multiset<Type>> : std::true_type {};

/// Detects if the container is an std::unordered_multiset. Helper type that allows you to elide
/// the ::value at the end.
template<typename Type>
constexpr bool is_std_unordered_multiset_v = is_std_unordered_multiset<Type>::value;



// ================================================================================================
// IS_STD_UNORDERED_MULTIMAP    - Detects if the container is an std::unordered_multimap.
// IS_STD_UNORDERED_MULTIMAP_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::unordered_multimap.
template<typename = void, typename = void>
struct is_std_unordered_multimap : std::false_type {};

/// Detects if the container is an std::unordered_multimap.
template<typename Type1, typename Type2>
struct is_std_unordered_multimap<std::unordered_multimap<Type1, Type2> > : std::true_type {};

/// Detects if the container is an std::unordered_multimap. Helper type that allows you to elide
/// the ::value at the end.
template<typename Type>
constexpr bool is_std_unordered_multimap_v = is_std_unordered_multimap<Type>::value;



// ================================================================================================
// IS_STD_STACK    - Detects if the container is an std::stack.
// IS_STD_STACK_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::stack.
template<typename Type>
struct is_std_stack : std::false_type {};

/// Detects if the container is an std::stack.
template<typename Type>
struct is_std_stack<std::stack<Type>> : std::true_type {};

/// Detects if the container is an std::stack. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_stack_v = is_std_stack<Type>::value;



// ================================================================================================
// IS_STD_QUEUE    - Detects if the container is an std::queue.
// IS_STD_QUEUE_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::queue.
template<typename Type>
struct is_std_queue : std::false_type {};

/// Detects if the container is an std::queue.
template<typename Type>
struct is_std_queue<std::queue<Type>> : std::true_type {};

/// Detects if the container is an std::queue. Helper type that allows you to elide the ::value 
/// at the end.
template<typename Type>
constexpr bool is_std_queue_v = is_std_queue<Type>::value;



// ================================================================================================
// IS_STD_PRIORITY_QUEUE    - Detects if the container is an std::priority_queue.
// IS_STD_PRIORITY_QUEUE_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is an std::priority_queue.
template<typename Type>
struct is_std_priority_queue : std::false_type {};

/// Detects if the container is an std::priority_queue.
template<typename Type>
struct is_std_priority_queue<std::priority_queue<Type>> : std::true_type {};

/// Detects if the container is an std::priority_queue. Helper type that allows you to elide the
/// ::value at the end.
template<typename Type>
constexpr bool is_std_priority_queue_v = is_std_priority_queue<Type>::value;



// ================================================================================================
// IS_STD_CONTAINER    - Detects if the container is an any of the standard containers.
// IS_STD_CONTAINER_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the container is any of the standard library containers.
template<typename Type, typename Enable = void>
struct is_std_container : std::false_type {};


/// Detects if the container is any of the standard library containers.
template<typename Type>
struct is_std_container<Type, std::enable_if_t<is_std_array_v<Type> || is_std_vector_v<Type> ||
                        is_std_deque_v<Type> ||is_std_forward_list_v<Type> || 
						is_std_list_v<Type> || is_std_set_v<Type> ||is_std_map_v<Type> ||
						is_std_multiset_v<Type> ||  is_std_multimap_v<Type> ||
						is_std_unordered_set_v<Type> || is_std_unordered_map_v<Type> ||
						is_std_unordered_multiset_v<Type> || is_std_unordered_multimap_v<Type> ||
						is_std_stack_v<Type> || is_std_queue_v<Type> ||
						is_std_priority_queue_v<Type>>> : std::true_type {};
   
                        
/// Detects if the container is any of the standard library containers. Helper type that allows 
/// you to elide the ::value at the end.
template<typename Type>
constexpr bool is_std_container_v = is_std_container<Type>::value;



// ================================================================================================
// IS_STD_PAIR    - Detects if the given type is an std::pair.
// IS_STD_PAIR_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the type is an std::pair.
template<typename Type, typename = void>
struct is_std_pair : std::false_type {};

/// Detects if the type is an std::pair.
template<typename Type>
struct is_std_pair<Type, 
std::enable_if_t<std::is_same_v<Type,
std::remove_cv_t<std::remove_reference_t<std::pair<typename Type::first_type,
typename Type::second_type>>>>>> : std::true_type {};

/// Detects if the type is an std::pair. Helper type that allows you to elide the ::value.
template<typename Type>
constexpr bool is_std_pair_v = is_std_pair<Type>::value;




// ================================================================================================
// IS_STD_STRING    - Detects if the type is an std::string.
// IS_STD_STRING_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the type is an std::string.
template<typename Type>
struct is_std_string
{
	static constexpr bool value = std::is_same_v<std::remove_cv_t<std::remove_reference_t<Type>>, 
												 std::string>;
};

/// Detects if the type is an std::string. Helper type that allows you to elide the ::value.
/// at the end.
template<typename Type>
constexpr bool is_std_string_v = is_std_string<Type>::value;



// ================================================================================================
// IS_C_STRING    - Detects if the type is an c style string, either char* or const char*.
// IS_C_STRING_V  - Helper type that allows you to elide the ::value at the end.
// ================================================================================================

/// Detects if the type is an c style string, either char* or const char*.
template<typename Type>
struct is_c_string :
std::integral_constant<bool,
std::is_same<const char*, typename std::decay<Type>::type>::value ||
std::is_same<char*, typename std::decay<Type>::type>::value> {};


/// Detects if the type is an c style string, either char* or const char*. Helper type that allows
/// you to elide the ::value at the end.
template<typename Type>
constexpr bool is_c_string_v = is_c_string<Type>::value;


// ================================================================================================
// IS_INPUT_ITERATOR    - Checks if a type is an input iterator.
// IS_INPUT_ITERATOR_V  - Helper that allows you to elide the ::value at the end.
// IS_OUTPUT_ITERATOR   - Checks if a type is an ouput iterator.
// IS_OUTPUT_ITERATOR_V - Helper that allows you to elide the ::value at the end.
// IS_ITERATOR          - Checks if a type is an iterator.
// IS_ITERATOR_V        - Helper that allows you to elide the ::value at the end.
// ================================================================================================

/// Checks if a type is an input iterator.
template <typename, typename Enable = void> struct is_input_iterator : std::false_type {};

/// Checks if a type is an input iterator.
template <typename Type>
struct is_input_iterator
<Type, typename std::enable_if_t<
std::is_base_of_v<
std::input_iterator_tag, typename std::iterator_traits<Type>::iterator_category>>> :
std::true_type{};

/// Checks if a type is an input iterator. Helper that allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_input_iterator_v = is_input_iterator<Type>::value;




/// Checks if a type is an ouput iterator.
template <typename, typename Enable = void> struct is_output_iterator : std::false_type {};

/// Checks if a type is an ouput iterator.
template <typename Type>
struct is_output_iterator
<Type, typename std::enable_if_t<
std::is_base_of_v<
std::output_iterator_tag, typename std::iterator_traits<Type>::iterator_category>>> :
std::true_type {};

/// Checks if a type is an ouput iterator. Helper that allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_output_iterator_v = is_output_iterator<Type>::value;




/// Checks if a type is an iterator. Both input and output iterators pass this check.
template <typename, typename Enable = void> struct is_iterator : std::false_type {};

// Checks if a type is an iterator. Both input and output iterators pass this check.
template <typename Type>
struct is_iterator
<Type, typename std::enable_if_t<is_input_iterator_v<Type> || is_output_iterator_v<Type>>> :
std::true_type {};

/// Checks if a type is an iterator. Both input and output iterators pass this check. Helper that
/// allows you to elide the ::value at the end.
template<typename Type>
constexpr bool is_iterator_v = is_iterator<Type>::value;






} // namespace mtl end