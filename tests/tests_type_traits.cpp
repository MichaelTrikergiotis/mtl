// tests by Michael Trikergiotis
// 02/06/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp"
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
#include <iterator>
#include <type_traits> // std::add_lvalue_reference_t, std::add_rvalue_reference_t

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/type_traits.hpp" 
// mtl::are_same, mtl::has_reserve, 
// mtl::has_push_back, mtl::has_emplace_back, mtl::has_size, mtl::has_find, mtl::is_sint, 
// mtl::is_uint, mtl::is_int, mtl::is_float, mtl::is_number, mtl::is_char, mtl::is_std_array, 
// mtl::is_std_vector, mtl::is_std_deque, mtl::is_std_forward_list, mtl::is_std_list, 
// mtl::is_std_set, mtl::is_std_multiset, mtl::is_std_map, mtl::is_std_multimap, 
// mtl::is_std_unordered_set, mtl::is_std_unordered_map, mtl::is_std_unordered_multiset, 
// mtl::is_std_unordered_multimap, mtl::is_std_stack, mtl::is_std_queue, 
// mtl::is_std_priority_queue, mtl::is_std_container, mtl::is_std_pair, mtl::is_std_string, 
// mtl::is_c_string, mtl::is_input_iterator, mtl::is_output_iterator, mtl::is_iterator



// ------------------------------------------------------------------------------------------------
// mtl::are_same
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::are_same")
{
    REQUIRE_EQ((mtl::are_same<int, int, int>::value), true);
    REQUIRE_EQ((mtl::are_same<float, float, float>::value), true);
    REQUIRE_EQ((mtl::are_same<double, double, double>::value), true);

    REQUIRE_EQ((mtl::are_same<bool, int, int>::value), false);
    REQUIRE_EQ((mtl::are_same<bool, float, float>::value), false);
    REQUIRE_EQ((mtl::are_same<bool, double, double>::value), false);
    
    REQUIRE_EQ((mtl::are_same<bool, float, int>::value), false);
    REQUIRE_EQ((mtl::are_same<bool, double, float>::value), false);
    REQUIRE_EQ((mtl::are_same<bool, int, double>::value), false);

    REQUIRE_EQ((mtl::are_same<std::vector<int>, std::vector<int>, std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::are_same<std::vector<float>, std::vector<float>, std::vector<float>>::value), 
                true);
    REQUIRE_EQ((mtl::are_same<std::vector<double>, 
                std::vector<double>, std::vector<double>>::value), true);

    REQUIRE_EQ((mtl::are_same<std::vector<int>, std::vector<float>, std::vector<int>>::value), 
                false);
    REQUIRE_EQ((mtl::are_same<std::vector<int>, std::vector<float>, std::vector<double>>::value),
                false);
    REQUIRE_EQ((mtl::are_same<bool, std::vector<int>, std::vector<int>>::value), false);   
}

TEST_CASE("mtl::are_same_v")
{
    REQUIRE_EQ((mtl::are_same_v<int, int, int>), true);
    REQUIRE_EQ((mtl::are_same_v<float, float, float>), true);
    REQUIRE_EQ((mtl::are_same_v<double, double, double>), true);

    REQUIRE_EQ((mtl::are_same_v<bool, int, int>), false);
    REQUIRE_EQ((mtl::are_same_v<bool, float, float>), false);
    REQUIRE_EQ((mtl::are_same_v<bool, double, double>), false);
    
    REQUIRE_EQ((mtl::are_same_v<bool, float, int>), false);
    REQUIRE_EQ((mtl::are_same_v<bool, double, float>), false);
    REQUIRE_EQ((mtl::are_same_v<bool, int, double>), false);

    REQUIRE_EQ((mtl::are_same_v<std::vector<int>, std::vector<int>, std::vector<int>>), true);
    REQUIRE_EQ((mtl::are_same_v<std::vector<float>, std::vector<float>, std::vector<float>>), 
                true);
    REQUIRE_EQ((mtl::are_same_v<std::vector<double>, std::vector<double>, std::vector<double>>), 
                true);

    REQUIRE_EQ((mtl::are_same_v<std::vector<int>, std::vector<float>, std::vector<int>>), false);
    REQUIRE_EQ((mtl::are_same_v<std::vector<int>, std::vector<float>, std::vector<double>>), 
                false);
    REQUIRE_EQ((mtl::are_same_v<bool, std::vector<int>, std::vector<int>>), false);   
}




// ------------------------------------------------------------------------------------------------
// mtl::has_reserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::has_reserve")
{
    REQUIRE_EQ((mtl::has_reserve<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_set<int>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_multiset<int>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_map<int, int>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_multimap<int, int>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::vector<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_set<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_multiset<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_map<std::string, std::string>>::value), true);
    REQUIRE_EQ((mtl::has_reserve<std::unordered_multimap<std::string, std::string>>::value), true);

    REQUIRE_EQ((mtl::has_reserve<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::has_reserve<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::has_reserve<std::list<int>>::value), false);
    REQUIRE_EQ((mtl::has_reserve<std::set<int>>::value), false);
    REQUIRE_EQ((mtl::has_reserve<std::map<int, int>>::value), false);
}

TEST_CASE("mtl::has_reserve_v")
{
    REQUIRE_EQ((mtl::has_reserve_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_set<int>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_multiset<int>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_map<int, int>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_multimap<int, int>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::vector<std::string>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_set<std::string>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_multiset<std::string>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_map<std::string, std::string>>), true);
    REQUIRE_EQ((mtl::has_reserve_v<std::unordered_multimap<std::string, std::string>>), true);

    REQUIRE_EQ((mtl::has_reserve_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::has_reserve_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::has_reserve_v<std::list<int>>), false);
    REQUIRE_EQ((mtl::has_reserve_v<std::set<int>>), false);
    REQUIRE_EQ((mtl::has_reserve_v<std::map<int, int>>), false);
}

// ------------------------------------------------------------------------------------------------
// mtl::has_push_back
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::has_push_back")
{
    REQUIRE_EQ((mtl::has_push_back<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::has_push_back<std::deque<int>>::value), true);
    REQUIRE_EQ((mtl::has_push_back<std::list<int>>::value), true);
    REQUIRE_EQ((mtl::has_push_back<std::vector<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_push_back<std::deque<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_push_back<std::list<std::string>>::value), true);
    
    REQUIRE_EQ((mtl::has_push_back<std::set<int>>::value), false);
    REQUIRE_EQ((mtl::has_push_back<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::has_push_back<std::map<int, int>>::value), false);
    REQUIRE_EQ((mtl::has_push_back<std::set<std::string>>::value), false);
    REQUIRE_EQ((mtl::has_push_back<std::array<std::string, 4>>::value), false);
    REQUIRE_EQ((mtl::has_push_back<std::map<std::string, std::string>>::value), false);
}


TEST_CASE("mtl::has_push_back_v")
{
    REQUIRE_EQ((mtl::has_push_back_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::has_push_back_v<std::deque<int>>), true);
    REQUIRE_EQ((mtl::has_push_back_v<std::list<int>>), true);
    REQUIRE_EQ((mtl::has_push_back_v<std::vector<std::string>>), true);
    REQUIRE_EQ((mtl::has_push_back_v<std::deque<std::string>>), true);
    REQUIRE_EQ((mtl::has_push_back_v<std::list<std::string>>), true);
    
    REQUIRE_EQ((mtl::has_push_back_v<std::set<int>>), false);
    REQUIRE_EQ((mtl::has_push_back_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::has_push_back_v<std::map<int, int>>), false);
    REQUIRE_EQ((mtl::has_push_back_v<std::set<std::string>>), false);
    REQUIRE_EQ((mtl::has_push_back_v<std::array<std::string, 4>>), false);
    REQUIRE_EQ((mtl::has_push_back_v<std::map<std::string, std::string>>), false);
}


// ------------------------------------------------------------------------------------------------
// mtl::has_emplace_back
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::has_emplace_back")
{
    REQUIRE_EQ((mtl::has_emplace_back<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::has_emplace_back<std::deque<int>>::value), true);
    REQUIRE_EQ((mtl::has_emplace_back<std::list<int>>::value), true);
    REQUIRE_EQ((mtl::has_emplace_back<std::vector<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_emplace_back<std::deque<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_emplace_back<std::list<std::string>>::value), true);
    
    REQUIRE_EQ((mtl::has_emplace_back<std::set<int>>::value), false);
    REQUIRE_EQ((mtl::has_emplace_back<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::has_emplace_back<std::map<int, int>>::value), false);
    REQUIRE_EQ((mtl::has_emplace_back<std::set<std::string>>::value), false);
    REQUIRE_EQ((mtl::has_emplace_back<std::array<std::string, 4>>::value), false);
    REQUIRE_EQ((mtl::has_emplace_back<std::map<std::string, std::string>>::value), false);
}


TEST_CASE("mtl::has_emplace_back_v")
{
    REQUIRE_EQ((mtl::has_emplace_back_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::deque<int>>), true);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::list<int>>), true);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::vector<std::string>>), true);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::deque<std::string>>), true);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::list<std::string>>), true);
    
    REQUIRE_EQ((mtl::has_emplace_back_v<std::set<int>>), false);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::map<int, int>>), false);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::set<std::string>>), false);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::array<std::string, 4>>), false);
    REQUIRE_EQ((mtl::has_emplace_back_v<std::map<std::string, std::string>>), false);
}





// ------------------------------------------------------------------------------------------------
// mtl::has_size
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::has_size")
{
    REQUIRE_EQ((mtl::has_size<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::deque<int>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::list<int>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::vector<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::deque<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::list<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::set<int>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::array<int, 4>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::map<int, int>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::set<std::string>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::array<std::string, 4>>::value), true);
    REQUIRE_EQ((mtl::has_size<std::map<std::string, std::string>>::value), true);

    REQUIRE_EQ((mtl::has_size<std::forward_list<std::string>>::value), false);
}


TEST_CASE("mtl::has_size_v")
{
    REQUIRE_EQ((mtl::has_size_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::deque<int>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::list<int>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::vector<std::string>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::deque<std::string>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::list<std::string>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::set<int>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::array<int, 4>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::map<int, int>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::set<std::string>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::array<std::string, 4>>), true);
    REQUIRE_EQ((mtl::has_size_v<std::map<std::string, std::string>>), true);

    REQUIRE_EQ((mtl::has_size_v<std::forward_list<std::string>>), false);
}


// ------------------------------------------------------------------------------------------------
// mtl::has_find
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::has_find")
{
    CHECK_EQ(mtl::has_find<std::vector<int>>::value, false);
    CHECK_EQ(mtl::has_find<std::vector<std::pair<int, char>>>::value, false);
    CHECK_EQ(mtl::has_find<std::deque<int>>::value, false);
    CHECK_EQ(mtl::has_find<std::deque<std::pair<int, char>>>::value, false);
    CHECK_EQ(mtl::has_find<std::list<int>>::value, false);
    CHECK_EQ(mtl::has_find<std::list<std::pair<int, char>>>::value, false);
    CHECK_EQ(mtl::has_find<std::array<int, 4>>::value, false);
    CHECK_EQ(mtl::has_find<std::array<std::pair<int, char>, 4>>::value, false);

    CHECK_EQ(mtl::has_find<std::set<int>>::value, true);
    CHECK_EQ(mtl::has_find<std::multiset<int>>::value, true);

    CHECK_EQ(mtl::has_find<std::map<int, int>>::value, true);
    CHECK_EQ(mtl::has_find<std::multimap<int, std::string>>::value, true);

    CHECK_EQ(mtl::has_find<std::unordered_set<int>>::value, true);
    CHECK_EQ(mtl::has_find<std::unordered_multiset<int>>::value, true);

    CHECK_EQ(mtl::has_find<std::unordered_map<int, int>>::value, true);
    CHECK_EQ(mtl::has_find<std::unordered_multimap<int, std::string>>::value, true);
}


TEST_CASE("mtl::has_find_v")
{
    CHECK_EQ(mtl::has_find_v<std::vector<int>>, false);
    CHECK_EQ(mtl::has_find_v<std::vector<std::pair<int, char>>>, false);
    CHECK_EQ(mtl::has_find_v<std::deque<int>>, false);
    CHECK_EQ(mtl::has_find_v<std::deque<std::pair<int, char>>>, false);
    CHECK_EQ(mtl::has_find_v<std::list<int>>, false);
    CHECK_EQ(mtl::has_find_v<std::list<std::pair<int, char>>>, false);
    CHECK_EQ(mtl::has_find_v<std::array<int, 4>>, false);
    CHECK_EQ(mtl::has_find_v<std::array<std::pair<int, char>, 4>>, false);

    CHECK_EQ(mtl::has_find_v<std::set<int>>, true);
    CHECK_EQ(mtl::has_find_v<std::multiset<int>>, true);

    CHECK_EQ(mtl::has_find_v<std::map<int, int>>, true);
    CHECK_EQ(mtl::has_find_v<std::multimap<int, std::string>>, true);

    CHECK_EQ(mtl::has_find_v<std::unordered_set<int>>, true);
    CHECK_EQ(mtl::has_find_v<std::unordered_multiset<int>>, true);

    CHECK_EQ(mtl::has_find_v<std::unordered_map<int, int>>, true);
    CHECK_EQ(mtl::has_find_v<std::unordered_multimap<int, std::string>>, true);
}



// ------------------------------------------------------------------------------------------------
// mtl::is_sint
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_sint")
{
    REQUIRE_EQ(mtl::is_sint<int>::value, true);
    REQUIRE_EQ(mtl::is_sint<unsigned int>::value, false);
    REQUIRE_EQ(mtl::is_sint<char>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::vector<int>>::value, false);

    REQUIRE_EQ(mtl::is_sint<int8_t>::value, true);
    REQUIRE_EQ(mtl::is_sint<int16_t>::value, true);
    REQUIRE_EQ(mtl::is_sint<int32_t>::value, true);
    REQUIRE_EQ(mtl::is_sint<int64_t>::value, true);
    REQUIRE_EQ(mtl::is_sint<short>::value, true);
    REQUIRE_EQ(mtl::is_sint<long int>::value, true);
    REQUIRE_EQ(mtl::is_sint<long long int>::value, true);

    REQUIRE_EQ(mtl::is_sint<uint8_t>::value, false);
    REQUIRE_EQ(mtl::is_sint<uint16_t>::value, false);
    REQUIRE_EQ(mtl::is_sint<uint32_t>::value, false);
    REQUIRE_EQ(mtl::is_sint<uint64_t>::value, false);
    REQUIRE_EQ(mtl::is_sint<unsigned short>::value, false);
    REQUIRE_EQ(mtl::is_sint<unsigned long int>::value, false);
    REQUIRE_EQ(mtl::is_sint<unsigned long long int>::value, false);
}

TEST_CASE("mtl::is_sint_v")
{
    REQUIRE_EQ(mtl::is_sint_v<int>, true);
    REQUIRE_EQ(mtl::is_sint_v<unsigned int>, false);
    REQUIRE_EQ(mtl::is_sint_v<char>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::vector<int>>, false);

    REQUIRE_EQ(mtl::is_sint_v<int8_t>, true);
    REQUIRE_EQ(mtl::is_sint_v<int16_t>, true);
    REQUIRE_EQ(mtl::is_sint_v<int32_t>, true);
    REQUIRE_EQ(mtl::is_sint_v<int64_t>, true);
    REQUIRE_EQ(mtl::is_sint_v<short>, true);
    REQUIRE_EQ(mtl::is_sint_v<long int>, true);
    REQUIRE_EQ(mtl::is_sint_v<long long int>, true);

    REQUIRE_EQ(mtl::is_sint_v<uint8_t>, false);
    REQUIRE_EQ(mtl::is_sint_v<uint16_t>, false);
    REQUIRE_EQ(mtl::is_sint_v<uint32_t>, false);
    REQUIRE_EQ(mtl::is_sint_v<uint64_t>, false);
    REQUIRE_EQ(mtl::is_sint_v<unsigned short>, false);
    REQUIRE_EQ(mtl::is_sint_v<unsigned long int>, false);
    REQUIRE_EQ(mtl::is_sint_v<unsigned long long int>, false);
}

TEST_CASE("mtl::is_sint, lvalue references")
{
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<std::vector<int>>>::value, false);

    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<uint8_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<uint16_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<uint32_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<uint64_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<unsigned short>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<unsigned long int>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_lvalue_reference_t<unsigned long long int>>::value, false);
}

TEST_CASE("mtl::is_sint_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<std::vector<int>>>, false);

    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<uint8_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<uint16_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<uint32_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<uint64_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<unsigned short>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<unsigned long int>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_lvalue_reference_t<unsigned long long int>>, false);
}


TEST_CASE("mtl::is_sint, rvalue references")
{
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<std::vector<int>>>::value, false);

    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<uint8_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<uint16_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<uint32_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<uint64_t>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<unsigned short>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<unsigned long int>>::value, false);
    REQUIRE_EQ(mtl::is_sint<std::add_rvalue_reference_t<unsigned long long int>>::value, false);
}

TEST_CASE("mtl::is_sint_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<std::vector<int>>>, false);

    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<uint8_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<uint16_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<uint32_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<uint64_t>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<unsigned short>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<unsigned long int>>, false);
    REQUIRE_EQ(mtl::is_sint_v<std::add_rvalue_reference_t<unsigned long long int>>, false);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_uint
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_uint")
{
    REQUIRE_EQ(mtl::is_uint<int>::value, false);
    REQUIRE_EQ(mtl::is_uint<unsigned int>::value, true);
    REQUIRE_EQ(mtl::is_uint<char>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::vector<unsigned int>>::value, false);

    REQUIRE_EQ(mtl::is_uint<int8_t>::value, false);
    REQUIRE_EQ(mtl::is_uint<int16_t>::value, false);
    REQUIRE_EQ(mtl::is_uint<int32_t>::value, false);
    REQUIRE_EQ(mtl::is_uint<int64_t>::value, false);
    REQUIRE_EQ(mtl::is_uint<short>::value, false);
    REQUIRE_EQ(mtl::is_uint<long int>::value, false);
    REQUIRE_EQ(mtl::is_uint<long long int>::value, false);

    REQUIRE_EQ(mtl::is_uint<uint8_t>::value, true);
    REQUIRE_EQ(mtl::is_uint<uint16_t>::value, true);
    REQUIRE_EQ(mtl::is_uint<uint32_t>::value, true);
    REQUIRE_EQ(mtl::is_uint<uint64_t>::value, true);
    REQUIRE_EQ(mtl::is_uint<unsigned short>::value, true);
    REQUIRE_EQ(mtl::is_uint<unsigned long int>::value, true);
    REQUIRE_EQ(mtl::is_uint<unsigned long long int>::value, true);
}

TEST_CASE("mtl::is_uint_v")
{
    REQUIRE_EQ(mtl::is_uint_v<int>, false);
    REQUIRE_EQ(mtl::is_uint_v<unsigned int>, true);
    REQUIRE_EQ(mtl::is_uint_v<char>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::vector<unsigned int>>, false);

    REQUIRE_EQ(mtl::is_uint_v<int8_t>, false);
    REQUIRE_EQ(mtl::is_uint_v<int16_t>, false);
    REQUIRE_EQ(mtl::is_uint_v<int32_t>, false);
    REQUIRE_EQ(mtl::is_uint_v<int64_t>, false);
    REQUIRE_EQ(mtl::is_uint_v<short>, false);
    REQUIRE_EQ(mtl::is_uint_v<long int>, false);
    REQUIRE_EQ(mtl::is_uint_v<long long int>, false);

    REQUIRE_EQ(mtl::is_uint_v<uint8_t>, true);
    REQUIRE_EQ(mtl::is_uint_v<uint16_t>, true);
    REQUIRE_EQ(mtl::is_uint_v<uint32_t>, true);
    REQUIRE_EQ(mtl::is_uint_v<uint64_t>, true);
    REQUIRE_EQ(mtl::is_uint_v<unsigned short>, true);
    REQUIRE_EQ(mtl::is_uint_v<unsigned long int>, true);
    REQUIRE_EQ(mtl::is_uint_v<unsigned long long int>, true);
}

TEST_CASE("mtl::is_uint, lvalue references")
{
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<std::vector<unsigned int>>>::value, false);

    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<int8_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<int16_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<int32_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<int64_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<short>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<long int>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<long long int>>::value, false);

    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_lvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_uint_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<std::vector<unsigned int>>>, false);

    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<int8_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<int16_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<int32_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<int64_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<short>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<long int>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<long long int>>, false);

    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_lvalue_reference_t<unsigned long long int>>, true);
}


TEST_CASE("mtl::is_uint, rvalue references")
{
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<std::vector<unsigned int>>>::value, false);

    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<int8_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<int16_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<int32_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<int64_t>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<short>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<long int>>::value, false);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<long long int>>::value, false);

    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_uint<std::add_rvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_uint_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<std::vector<unsigned int>>>, false);

    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<int8_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<int16_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<int32_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<int64_t>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<short>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<long int>>, false);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<long long int>>, false);

    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_uint_v<std::add_rvalue_reference_t<unsigned long long int>>, true);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_int
// ------------------------------------------------------------------------------------------------
TEST_CASE("mtl::is_int")
{
    REQUIRE_EQ(mtl::is_int<int>::value, true);
    REQUIRE_EQ(mtl::is_int<unsigned int>::value, true);
    REQUIRE_EQ(mtl::is_int<char>::value, false);
    REQUIRE_EQ(mtl::is_int<std::vector<int>>::value, false);

    REQUIRE_EQ(mtl::is_int<int8_t>::value, true);
    REQUIRE_EQ(mtl::is_int<int16_t>::value, true);
    REQUIRE_EQ(mtl::is_int<int32_t>::value, true);
    REQUIRE_EQ(mtl::is_int<int64_t>::value, true);
    REQUIRE_EQ(mtl::is_int<short>::value, true);
    REQUIRE_EQ(mtl::is_int<long int>::value, true);
    REQUIRE_EQ(mtl::is_int<long long int>::value, true);

    REQUIRE_EQ(mtl::is_int<uint8_t>::value, true);
    REQUIRE_EQ(mtl::is_int<uint16_t>::value, true);
    REQUIRE_EQ(mtl::is_int<uint32_t>::value, true);
    REQUIRE_EQ(mtl::is_int<uint64_t>::value, true);
    REQUIRE_EQ(mtl::is_int<unsigned short>::value, true);
    REQUIRE_EQ(mtl::is_int<unsigned long int>::value, true);
    REQUIRE_EQ(mtl::is_int<unsigned long long int>::value, true);
}

TEST_CASE("mtl::is_int_v")
{
    REQUIRE_EQ(mtl::is_int_v<int>, true);
    REQUIRE_EQ(mtl::is_int_v<unsigned int>, true);
    REQUIRE_EQ(mtl::is_int_v<char>, false);
    REQUIRE_EQ(mtl::is_int_v<std::vector<int>>, false);

    REQUIRE_EQ(mtl::is_int_v<int8_t>, true);
    REQUIRE_EQ(mtl::is_int_v<int16_t>, true);
    REQUIRE_EQ(mtl::is_int_v<int32_t>, true);
    REQUIRE_EQ(mtl::is_int_v<int64_t>, true);
    REQUIRE_EQ(mtl::is_int_v<short>, true);
    REQUIRE_EQ(mtl::is_int_v<long int>, true);
    REQUIRE_EQ(mtl::is_int_v<long long int>, true);

    REQUIRE_EQ(mtl::is_int_v<uint8_t>, true);
    REQUIRE_EQ(mtl::is_int_v<uint16_t>, true);
    REQUIRE_EQ(mtl::is_int_v<uint32_t>, true);
    REQUIRE_EQ(mtl::is_int_v<uint64_t>, true);
    REQUIRE_EQ(mtl::is_int_v<unsigned short>, true);
    REQUIRE_EQ(mtl::is_int_v<unsigned long int>, true);
    REQUIRE_EQ(mtl::is_int_v<unsigned long long int>, true);
}

TEST_CASE("mtl::is_int, lvalue references")
{
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<std::vector<int>>>::value, false);

    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_lvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_int_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<std::vector<int>>>, false);

    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_lvalue_reference_t<unsigned long long int>>, true);
}

TEST_CASE("mtl::is_int, rvalue references")
{
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<std::vector<int>>>::value, false);

    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_int<std::add_rvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_int_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<std::vector<int>>>, false);

    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_int_v<std::add_rvalue_reference_t<unsigned long long int>>, true);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_float
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_float")
{
    REQUIRE_EQ(mtl::is_float<int>::value, false);
    REQUIRE_EQ(mtl::is_float<unsigned int>::value, false);
    REQUIRE_EQ(mtl::is_float<char>::value, false);
    REQUIRE_EQ(mtl::is_float<float>::value, true);
    REQUIRE_EQ(mtl::is_float<double>::value, true);
    REQUIRE_EQ(mtl::is_float<std::vector<float>>::value, false);
}

TEST_CASE("mtl::is_float_v")
{
    REQUIRE_EQ(mtl::is_float_v<int>, false);
    REQUIRE_EQ(mtl::is_float_v<unsigned int>, false);
    REQUIRE_EQ(mtl::is_float_v<char>, false);
    REQUIRE_EQ(mtl::is_float_v<float>, true);
    REQUIRE_EQ(mtl::is_float_v<double>, true);
    REQUIRE_EQ(mtl::is_float_v<std::vector<float>>, false);
}

TEST_CASE("mtl::is_float, lvalue references")
{
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<float>>::value, true);
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<double>>::value, true);
    REQUIRE_EQ(mtl::is_float<std::add_lvalue_reference_t<std::vector<float>>>::value, false);
}

TEST_CASE("mtl::is_float_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<float>>, true);
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<double>>, true);
    REQUIRE_EQ(mtl::is_float_v<std::add_lvalue_reference_t<std::vector<float>>>, false);
}

TEST_CASE("mtl::is_float, rvalue references")
{
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<float>>::value, true);
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<double>>::value, true);
    REQUIRE_EQ(mtl::is_float<std::add_rvalue_reference_t<std::vector<float>>>::value, false);
}

TEST_CASE("mtl::is_float_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<float>>, true);
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<double>>, true);
    REQUIRE_EQ(mtl::is_float_v<std::add_rvalue_reference_t<std::vector<float>>>, false);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_number
// ------------------------------------------------------------------------------------------------
TEST_CASE("mtl::is_number")
{
    REQUIRE_EQ(mtl::is_number<int>::value, true);
    REQUIRE_EQ(mtl::is_number<unsigned int>::value, true);
    REQUIRE_EQ(mtl::is_number<char>::value, false);
    REQUIRE_EQ(mtl::is_number<float>::value, true);
    REQUIRE_EQ(mtl::is_number<double>::value, true);
    REQUIRE_EQ(mtl::is_number<std::vector<float>>::value, false);

    REQUIRE_EQ(mtl::is_number<int8_t>::value, true);
    REQUIRE_EQ(mtl::is_number<int16_t>::value, true);
    REQUIRE_EQ(mtl::is_number<int32_t>::value, true);
    REQUIRE_EQ(mtl::is_number<int64_t>::value, true);
    REQUIRE_EQ(mtl::is_number<short>::value, true);
    REQUIRE_EQ(mtl::is_number<long int>::value, true);
    REQUIRE_EQ(mtl::is_number<long long int>::value, true);

    REQUIRE_EQ(mtl::is_number<uint8_t>::value, true);
    REQUIRE_EQ(mtl::is_number<uint16_t>::value, true);
    REQUIRE_EQ(mtl::is_number<uint32_t>::value, true);
    REQUIRE_EQ(mtl::is_number<uint64_t>::value, true);
    REQUIRE_EQ(mtl::is_number<unsigned short>::value, true);
    REQUIRE_EQ(mtl::is_number<unsigned long int>::value, true);
    REQUIRE_EQ(mtl::is_number<unsigned long long int>::value, true);
}

TEST_CASE("mtl::is_number_v")
{
    REQUIRE_EQ(mtl::is_number_v<int>, true);
    REQUIRE_EQ(mtl::is_number_v<unsigned int>, true);
    REQUIRE_EQ(mtl::is_number_v<char>, false);
    REQUIRE_EQ(mtl::is_number_v<float>, true);
    REQUIRE_EQ(mtl::is_number_v<double>, true);
    REQUIRE_EQ(mtl::is_number_v<std::vector<float>>, false);

    REQUIRE_EQ(mtl::is_number_v<int8_t>, true);
    REQUIRE_EQ(mtl::is_number_v<int16_t>, true);
    REQUIRE_EQ(mtl::is_number_v<int32_t>, true);
    REQUIRE_EQ(mtl::is_number_v<int64_t>, true);
    REQUIRE_EQ(mtl::is_number_v<short>, true);
    REQUIRE_EQ(mtl::is_number_v<long int>, true);
    REQUIRE_EQ(mtl::is_number_v<long long int>, true);

    REQUIRE_EQ(mtl::is_number_v<uint8_t>, true);
    REQUIRE_EQ(mtl::is_number_v<uint16_t>, true);
    REQUIRE_EQ(mtl::is_number_v<uint32_t>, true);
    REQUIRE_EQ(mtl::is_number_v<uint64_t>, true);
    REQUIRE_EQ(mtl::is_number_v<unsigned short>, true);
    REQUIRE_EQ(mtl::is_number_v<unsigned long int>, true);
    REQUIRE_EQ(mtl::is_number_v<unsigned long long int>, true);
}


TEST_CASE("mtl::is_number, lvalue references")
{
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<float>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<double>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<std::vector<float>>>::value, false);

    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_lvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_number_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<float>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<double>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<std::vector<float>>>, false);

    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_lvalue_reference_t<unsigned long long int>>, true);
}


TEST_CASE("mtl::is_number, rvalue references")
{
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<unsigned int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<char>>::value, false);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<float>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<double>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<std::vector<float>>>::value, false);

    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<int8_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<int16_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<int32_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<int64_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<short>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<long int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<long long int>>::value, true);

    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<uint8_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<uint16_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<uint32_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<uint64_t>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<unsigned short>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<unsigned long int>>::value, true);
    REQUIRE_EQ(mtl::is_number<std::add_rvalue_reference_t<unsigned long long int>>::value, true);
}

TEST_CASE("mtl::is_number_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<unsigned int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<char>>, false);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<float>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<double>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<std::vector<float>>>, false);

    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<int8_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<int16_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<int32_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<int64_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<short>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<long int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<long long int>>, true);

    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<uint8_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<uint16_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<uint32_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<uint64_t>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<unsigned short>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<unsigned long int>>, true);
    REQUIRE_EQ(mtl::is_number_v<std::add_rvalue_reference_t<unsigned long long int>>, true);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_char
// ------------------------------------------------------------------------------------------------
TEST_CASE("mtl::is_char")
{
    REQUIRE_EQ(mtl::is_char<int>::value, false);
    REQUIRE_EQ(mtl::is_char<unsigned int>::value, false);
    REQUIRE_EQ(mtl::is_char<char>::value, true);
    REQUIRE_EQ(mtl::is_char<unsigned char>::value, true);
    REQUIRE_EQ(mtl::is_char<float>::value, false);
    REQUIRE_EQ(mtl::is_char<double>::value, false);
    REQUIRE_EQ(mtl::is_char<std::vector<float>>::value, false);
}

TEST_CASE("mtl::is_char_v")
{
    REQUIRE_EQ(mtl::is_char_v<int>, false);
    REQUIRE_EQ(mtl::is_char_v<unsigned int>, false);
    REQUIRE_EQ(mtl::is_char_v<char>, true);
    REQUIRE_EQ(mtl::is_char_v<unsigned char>, true);
    REQUIRE_EQ(mtl::is_char_v<float>, false);
    REQUIRE_EQ(mtl::is_char_v<double>, false);
    REQUIRE_EQ(mtl::is_char_v<std::vector<float>>, false);
}

TEST_CASE("mtl::is_char, lvalue references")
{
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<char>>::value, true);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<unsigned char>>::value, true);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<float>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<double>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_lvalue_reference_t<std::vector<float>>>::value, false);
}

TEST_CASE("mtl::is_char_v, lvalue references")
{
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<char>>, true);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<unsigned char>>, true);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<float>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<double>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_lvalue_reference_t<std::vector<float>>>, false);
}

TEST_CASE("mtl::is_char, rvalue references")
{
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<int>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<unsigned int>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<char>>::value, true);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<unsigned char>>::value, true);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<float>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<double>>::value, false);
    REQUIRE_EQ(mtl::is_char<std::add_rvalue_reference_t<std::vector<float>>>::value, false);
}

TEST_CASE("mtl::is_char_v, rvalue references")
{
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<int>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<unsigned int>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<char>>, true);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<unsigned char>>, true);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<float>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<double>>, false);
    REQUIRE_EQ(mtl::is_char_v<std::add_rvalue_reference_t<std::vector<float>>>, false);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_array
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_array")
{
    REQUIRE_EQ((mtl::is_std_array<int>::value), false);
    REQUIRE_EQ((mtl::is_std_array<std::array<int, 4>>::value), true);
    REQUIRE_EQ((mtl::is_std_array<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_array<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_array<std::list<int>>::value), false);    
}

TEST_CASE("mtl::is_std_array_v")
{
    REQUIRE_EQ((mtl::is_std_array_v<int>), false);
    REQUIRE_EQ((mtl::is_std_array_v<std::array<int, 4>>), true);
    REQUIRE_EQ((mtl::is_std_array_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_array_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_array_v<std::list<int>>), false);    
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_vector
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_vector")
{
    REQUIRE_EQ((mtl::is_std_vector<int>::value), false);
    REQUIRE_EQ((mtl::is_std_vector<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_vector<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::is_std_vector<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_vector<std::list<int>>::value), false);    
}

TEST_CASE("mtl::is_std_vector_v")
{
    REQUIRE_EQ((mtl::is_std_vector_v<int>), false);
    REQUIRE_EQ((mtl::is_std_vector_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_vector_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::is_std_vector_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_vector_v<std::list<int>>), false);    
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_deque
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_deque")
{
    REQUIRE_EQ((mtl::is_std_deque<int>::value), false);
    REQUIRE_EQ((mtl::is_std_deque<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_deque<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_deque<std::deque<int>>::value), true);
    REQUIRE_EQ((mtl::is_std_deque<std::list<int>>::value), false);    
}

TEST_CASE("mtl::is_std_deque_v")
{
    REQUIRE_EQ((mtl::is_std_deque_v<int>), false);
    REQUIRE_EQ((mtl::is_std_deque_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_deque_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_deque_v<std::deque<int>>), true);
    REQUIRE_EQ((mtl::is_std_deque_v<std::list<int>>), false);    
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_forward_list
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_forward_list")
{
    REQUIRE_EQ((mtl::is_std_forward_list<int>::value), false);
    REQUIRE_EQ((mtl::is_std_forward_list<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_forward_list<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_forward_list<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_forward_list<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_forward_list<std::forward_list<int>>::value), true);   
}

TEST_CASE("mtl::is_std_forward_list_v")
{
    REQUIRE_EQ((mtl::is_std_forward_list_v<int>), false);
    REQUIRE_EQ((mtl::is_std_forward_list_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_forward_list_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_forward_list_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_forward_list_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_forward_list_v<std::forward_list<int>>), true);   
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_list
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_list")
{
    REQUIRE_EQ((mtl::is_std_list<int>::value), false);
    REQUIRE_EQ((mtl::is_std_list<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_list<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_list<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_list<std::list<int>>::value), true);    
}

TEST_CASE("mtl::is_std_list_v")
{
    REQUIRE_EQ((mtl::is_std_list_v<int>), false);
    REQUIRE_EQ((mtl::is_std_list_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_list_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_list_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_list_v<std::list<int>>), true);    
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_set
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_set")
{
    REQUIRE_EQ((mtl::is_std_set<int>::value), false);
    REQUIRE_EQ((mtl::is_std_set<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_set<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_set<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_set<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_set<std::set<int>>::value), true);    
}

TEST_CASE("mtl::is_std_set_v")
{
    REQUIRE_EQ((mtl::is_std_set_v<int>), false);
    REQUIRE_EQ((mtl::is_std_set_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_set_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_set_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_set_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_set_v<std::set<int>>), true);  
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_multiset
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_multiset")
{
    REQUIRE_EQ((mtl::is_std_multiset<int>::value), false);
    REQUIRE_EQ((mtl::is_std_multiset<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_multiset<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_multiset<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_multiset<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_multiset<std::multiset<int>>::value), true);    
}

TEST_CASE("mtl::is_std_multiset_v")
{
    REQUIRE_EQ((mtl::is_std_multiset_v<int>), false);
    REQUIRE_EQ((mtl::is_std_multiset_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_multiset_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_multiset_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_multiset_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_multiset_v<std::multiset<int>>), true);  
}



// ------------------------------------------------------------------------------------------------
// mtl::is_std_map
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_map")
{
    REQUIRE_EQ((mtl::is_std_map<int>::value), false);
    REQUIRE_EQ((mtl::is_std_map<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_map<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_map<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_map<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_map<std::map<int, int>>::value), true);    
}

TEST_CASE("mtl::is_std_map_v")
{
    REQUIRE_EQ((mtl::is_std_map_v<int>), false);
    REQUIRE_EQ((mtl::is_std_map_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_map_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_map_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_map_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_map_v<std::map<int, int>>), true);  
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_multimap
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_multimap")
{
    REQUIRE_EQ((mtl::is_std_multimap<int>::value), false);
    REQUIRE_EQ((mtl::is_std_multimap<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_multimap<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_multimap<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_multimap<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_multimap<std::multimap<int, int>>::value), true);    
}

TEST_CASE("mtl::is_std_multimap_v")
{
    REQUIRE_EQ((mtl::is_std_multimap_v<int>), false);
    REQUIRE_EQ((mtl::is_std_multimap_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_multimap_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_multimap_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_multimap_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_multimap_v<std::multimap<int, int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_unordered_set
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_unordered_set")
{
    REQUIRE_EQ((mtl::is_std_unordered_set<int>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_set<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_set<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_set<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_set<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_unordered_set<std::unordered_set<int>>::value), true);    
}

TEST_CASE("mtl::is_std_unordered_set_v")
{
    REQUIRE_EQ((mtl::is_std_unordered_set_v<int>), false);
    REQUIRE_EQ((mtl::is_std_unordered_set_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_set_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_set_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_set_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_unordered_set_v<std::unordered_set<int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_unordered_multiset
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_unordered_multiset")
{
    REQUIRE_EQ((mtl::is_std_unordered_multiset<int>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_unordered_multiset<std::unordered_multiset<int>>::value), true);    
}

TEST_CASE("mtl::is_std_unordered_multiset_v")
{
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<int>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_unordered_multiset_v<std::unordered_multiset<int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_unordered_map
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_unordered_map")
{
    REQUIRE_EQ((mtl::is_std_unordered_map<int>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_map<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_map<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_map<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_map<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_unordered_map<std::unordered_map<int, int>>::value), true);    
}

TEST_CASE("mtl::is_std_unordered_map_v")
{
    REQUIRE_EQ((mtl::is_std_unordered_map_v<int>), false);
    REQUIRE_EQ((mtl::is_std_unordered_map_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_map_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_map_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_map_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_unordered_map_v<std::unordered_map<int, int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_unordered_multimap
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_unordered_multimap")
{
    REQUIRE_EQ((mtl::is_std_unordered_multimap<int>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_unordered_multimap<std::unordered_multimap<int, int>>::value),
                true);    
}

TEST_CASE("mtl::is_std_unordered_multimap_v")
{
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<int>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_unordered_multimap_v<std::unordered_multimap<int, int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_stack
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_stack")
{
    REQUIRE_EQ((mtl::is_std_stack<int>::value), false);
    REQUIRE_EQ((mtl::is_std_stack<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_stack<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_stack<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_stack<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_stack<std::stack<int>>::value), true);    
}

TEST_CASE("mtl::is_std_stack_v")
{
    REQUIRE_EQ((mtl::is_std_stack_v<int>), false);
    REQUIRE_EQ((mtl::is_std_stack_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_stack_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_stack_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_stack_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_stack_v<std::stack<int>>), true);  
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_queue
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_queue")
{
    REQUIRE_EQ((mtl::is_std_queue<int>::value), false);
    REQUIRE_EQ((mtl::is_std_queue<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_queue<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_queue<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_queue<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_queue<std::queue<int>>::value), true);    
}

TEST_CASE("mtl::is_std_queue_v")
{
    REQUIRE_EQ((mtl::is_std_queue_v<int>), false);
    REQUIRE_EQ((mtl::is_std_queue_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_queue_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_queue_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_queue_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_queue_v<std::queue<int>>), true);  
}

// ------------------------------------------------------------------------------------------------
// mtl::is_std_priority_queue
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_priority_queue")
{
    REQUIRE_EQ((mtl::is_std_priority_queue<int>::value), false);
    REQUIRE_EQ((mtl::is_std_priority_queue<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_priority_queue<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_priority_queue<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_priority_queue<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_priority_queue<std::priority_queue<int>>::value), true);    
}

TEST_CASE("mtl::is_std_priority_queue_v")
{
    REQUIRE_EQ((mtl::is_std_priority_queue_v<int>), false);
    REQUIRE_EQ((mtl::is_std_priority_queue_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_priority_queue_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_priority_queue_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_priority_queue_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_priority_queue_v<std::priority_queue<int>>), true);  
}


// ------------------------------------------------------------------------------------------------
// mtl::is_std_container
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_container")
{
    REQUIRE_EQ((mtl::is_std_container<int>::value), false);
    REQUIRE_EQ((mtl::is_std_container<std::array<int, 4>>::value), true);
    REQUIRE_EQ((mtl::is_std_container<std::vector<int>>::value), true);
    REQUIRE_EQ((mtl::is_std_container<std::deque<int>>::value), true);
    REQUIRE_EQ((mtl::is_std_container<std::list<int>>::value), true);    
 
}

TEST_CASE("mtl::is_std_container_v")
{
    REQUIRE_EQ((mtl::is_std_container_v<int>), false);
    REQUIRE_EQ((mtl::is_std_container_v<std::array<int, 4>>), true);
    REQUIRE_EQ((mtl::is_std_container_v<std::vector<int>>), true);
    REQUIRE_EQ((mtl::is_std_container_v<std::deque<int>>), true);
    REQUIRE_EQ((mtl::is_std_container_v<std::list<int>>), true);    
}







// ------------------------------------------------------------------------------------------------
// mtl::is_std_pair
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_pair")
{
    REQUIRE_EQ((mtl::is_std_pair<int>::value), false);
    REQUIRE_EQ((mtl::is_std_pair<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_pair<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_pair<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_pair<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_pair<std::string>::value), false);    
    REQUIRE_EQ((mtl::is_std_pair<char*>::value), false);    
    REQUIRE_EQ((mtl::is_std_pair<const char*>::value), false);    
    REQUIRE_EQ((mtl::is_std_pair<std::vector<char>>::value), false);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<int, int>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<float, int>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<float, float>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<std::string, int>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<std::string, std::string>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<bool, char>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<std::pair<int, char>, int>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<int, std::pair<char, bool>>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<std::vector<float>, char>>::value), true);
    REQUIRE_EQ((mtl::is_std_pair<std::pair<bool, std::list<float>>>::value), true);
}

TEST_CASE("mtl::is_std_pair_v")
{
    REQUIRE_EQ((mtl::is_std_pair_v<int>), false);
    REQUIRE_EQ((mtl::is_std_pair_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_pair_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_pair_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_pair_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_pair_v<std::string>), false);    
    REQUIRE_EQ((mtl::is_std_pair_v<char*>), false);    
    REQUIRE_EQ((mtl::is_std_pair_v<const char*>), false);    
    REQUIRE_EQ((mtl::is_std_pair_v<std::vector<char>>), false);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<int, int>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<float, int>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<float, float>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<std::string, int>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<std::string, std::string>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<bool, char>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<std::pair<int, char>, int>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<int, std::pair<char, bool>>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<std::vector<float>, char>>), true);
    REQUIRE_EQ((mtl::is_std_pair_v<std::pair<bool, std::list<float>>>), true);
}



// ------------------------------------------------------------------------------------------------
// mtl::is_std_string
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_std_string")
{
    REQUIRE_EQ((mtl::is_std_string<int>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_std_string<std::string>::value), true);    
    REQUIRE_EQ((mtl::is_std_string<char*>::value), false);    
    REQUIRE_EQ((mtl::is_std_string<const char*>::value), false);    
    REQUIRE_EQ((mtl::is_std_string<std::vector<char>>::value), false);
}

TEST_CASE("mtl::is_std_string_v")
{
    REQUIRE_EQ((mtl::is_std_string_v<int>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_std_string_v<std::string>), true);    
    REQUIRE_EQ((mtl::is_std_string_v<char*>), false);    
    REQUIRE_EQ((mtl::is_std_string_v<const char*>), false);    
    REQUIRE_EQ((mtl::is_std_string_v<std::vector<char>>), false);
}

TEST_CASE("mtl::is_std_string, lvalue references")
{
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::array<int, 4>>>::value), 
                false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::vector<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::deque<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::list<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::string>>::value), true);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<char*>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<const char*>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_lvalue_reference_t<std::vector<char>>>::value), false);
}

TEST_CASE("mtl::is_std_string_v, lvalue references")
{
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<int>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::array<int, 4>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::vector<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::deque<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::list<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::string>>), true);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<char*>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<const char*>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_lvalue_reference_t<std::vector<char>>>), false);
}

TEST_CASE("mtl::is_std_string, rvalue references")
{
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<int>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::array<int, 4>>>::value), 
                false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::vector<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::deque<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::list<int>>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::string>>::value), true);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<char*>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<const char*>>::value), false);
    REQUIRE_EQ((mtl::is_std_string<std::add_rvalue_reference_t<std::vector<char>>>::value), false);
}

TEST_CASE("mtl::is_std_string_v, rvalue references")
{
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<int>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::array<int, 4>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::vector<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::deque<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::list<int>>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::string>>), true);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<char*>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<const char*>>), false);
    REQUIRE_EQ((mtl::is_std_string_v<std::add_rvalue_reference_t<std::vector<char>>>), false);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_c_string
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::is_c_string")
{
    REQUIRE_EQ((mtl::is_c_string<int>::value), false);
    REQUIRE_EQ((mtl::is_c_string<std::array<int, 4>>::value), false);
    REQUIRE_EQ((mtl::is_c_string<std::vector<int>>::value), false);
    REQUIRE_EQ((mtl::is_c_string<std::deque<int>>::value), false);
    REQUIRE_EQ((mtl::is_c_string<std::list<int>>::value), false);    
    REQUIRE_EQ((mtl::is_c_string<std::string>::value), false);    
    REQUIRE_EQ((mtl::is_c_string<char*>::value), true);    
    REQUIRE_EQ((mtl::is_c_string<const char*>::value), true);    
    REQUIRE_EQ((mtl::is_c_string<std::vector<char>>::value), false);
}

TEST_CASE("mtl::is_c_string_v")
{
    REQUIRE_EQ((mtl::is_c_string_v<int>), false);
    REQUIRE_EQ((mtl::is_c_string_v<std::array<int, 4>>), false);
    REQUIRE_EQ((mtl::is_c_string_v<std::vector<int>>), false);
    REQUIRE_EQ((mtl::is_c_string_v<std::deque<int>>), false);
    REQUIRE_EQ((mtl::is_c_string_v<std::list<int>>), false);    
    REQUIRE_EQ((mtl::is_c_string_v<std::string>), false);    
    REQUIRE_EQ((mtl::is_c_string_v<char*>), true);    
    REQUIRE_EQ((mtl::is_c_string_v<const char*>), true);    
    REQUIRE_EQ((mtl::is_c_string_v<std::vector<char>>), false);
}

// ------------------------------------------------------------------------------------------------
// mtl::is_input_iterator, mtl::is_output_iterator, mtl::is_iterator
// ------------------------------------------------------------------------------------------------

// Input iterator in a way that C++ 17 prefers it now that std::iterator is deprecated.
struct my_input_iterator
{
    using value_type = int ;
    using pointer = int* ;
    using reference = int& ;
    using difference_type = std::ptrdiff_t ;
    using iterator_category = std::input_iterator_tag ;
};

// Output iterator in a way that C++ 17 prefers it now that std::iterator is deprecated.
struct my_output_iterator
{
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::output_iterator_tag;
};

// Bidirectional iterator in a way that C++ 17 prefers it now that std::iterator is deprecated.
struct my_bidir_terator
{
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
};

// Forward iterator in a way that C++ 17 prefers it now that std::iterator is deprecated.
struct my_forward_terator
{
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
};

// Random access iterator in a way that C++ 17 prefers it now that std::iterator is deprecated.
struct my_random_access_iterator
{
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
};


TEST_CASE("mtl::is_input_iterator")
{
    std::vector<int> vi;
    auto vi_it = vi.begin();
    REQUIRE_EQ((vi_it == vi.begin()), true);
    REQUIRE_EQ((mtl::is_input_iterator<decltype(vi_it)>::value), true);
    std::vector<std::string> vs;
    auto vs_it = vs.begin();
    REQUIRE_EQ((vs_it == vs.begin()), true);
    REQUIRE_EQ((mtl::is_input_iterator<decltype(vs_it)>::value), true);

    REQUIRE_EQ((mtl::is_input_iterator<int>::value),false);
    REQUIRE_EQ((mtl::is_input_iterator<std::vector<int>>::value), false);
    
    
    REQUIRE_EQ((mtl::is_input_iterator<my_input_iterator>::value), true);
    REQUIRE_EQ((mtl::is_input_iterator<my_output_iterator>::value), false);
    REQUIRE_EQ((mtl::is_input_iterator<my_bidir_terator>::value), true); 
    REQUIRE_EQ((mtl::is_input_iterator<my_forward_terator>::value), true);
    REQUIRE_EQ((mtl::is_input_iterator<my_random_access_iterator>::value), true);
}


TEST_CASE("mtl::is_output_iterator")
{
    std::vector<int> vi;
    auto vi_it = vi.begin();
    REQUIRE_EQ((vi_it == vi.begin()), true);
    REQUIRE_EQ((mtl::is_output_iterator<decltype(vi_it)>::value), false);
    std::vector<std::string> vs;
    auto vs_it = vs.begin();
    REQUIRE_EQ((vs_it == vs.begin()), true);
    REQUIRE_EQ((mtl::is_output_iterator<decltype(vs_it)>::value), false);

    REQUIRE_EQ((mtl::is_output_iterator<int>::value),false);
    REQUIRE_EQ((mtl::is_output_iterator<std::vector<int>>::value), false);


    REQUIRE_EQ((mtl::is_output_iterator<my_input_iterator>::value), false);
    REQUIRE_EQ((mtl::is_output_iterator<my_output_iterator>::value), true);
    REQUIRE_EQ((mtl::is_output_iterator<my_bidir_terator>::value), false);
    REQUIRE_EQ((mtl::is_output_iterator<my_forward_terator>::value), false);
    REQUIRE_EQ((mtl::is_output_iterator<my_random_access_iterator>::value), false);
}


TEST_CASE("mtl::is_iterator")
{
    std::vector<int> vi;
    auto vi_it = vi.begin();
    REQUIRE_EQ((vi_it == vi.begin()), true);
    REQUIRE_EQ((mtl::is_iterator<decltype(vi_it)>::value), true);
    std::vector<std::string> vs;
    auto vs_it = vs.begin();
    REQUIRE_EQ((vs_it == vs.begin()), true);
    REQUIRE_EQ((mtl::is_iterator<decltype(vs_it)>::value), true);

    REQUIRE_EQ((mtl::is_iterator<int>::value),false);
    REQUIRE_EQ((mtl::is_iterator<std::vector<int>>::value), false);


    REQUIRE_EQ((mtl::is_iterator<my_input_iterator>::value), true);
    REQUIRE_EQ((mtl::is_iterator<my_output_iterator>::value), true);
    REQUIRE_EQ((mtl::is_iterator<my_bidir_terator>::value), true);
    REQUIRE_EQ((mtl::is_iterator<my_forward_terator>::value), true);
    REQUIRE_EQ((mtl::is_iterator<my_random_access_iterator>::value), true);
}