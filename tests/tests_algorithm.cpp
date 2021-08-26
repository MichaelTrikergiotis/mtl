// tests by Michael Trikergiotis
// 06/06/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <list>           // std::list
#include <vector>         // std::vector
#include <deque>          // std::deque
#include <set>            // std::set
#include <unordered_set>  // std::unordered_set
#include <map>            // std::map
#include <unordered_map>  // std::unordered_map
#include <string>         // std::string
#include <sstream>        // std::stringstream
#include <tuple>          // std::tuple
#include <utility>        // std::pair, std::make_pair
#include <stdexcept>      // std::invalid_argument
#include <cstddef>        // std::ptrdiff_t
#include <iterator>       // std::ostream_iterator, std::back_insert_iterator
#include <functional>     // std::equal_to, std::less
#include <algorithm>      // std::sort, std::count, std::for_each


#include "../mtl/algorithm.hpp"
// mtl::not_unique_inclusive, mtl::not_unique_exclusive, mtl::not_unique, 
// mtl::keep_duplicates_inclusive, mtl::keep_duplicates_exclusive, mtl::keep_duplicates,
// mtl::keep_duplicates_inclusive_sorted, mtl::keep_duplicates_exclusive_sorted, 
// mtl::keep_duplicates_sorted, mtl::keep_duplicates_inclusive_preserve, 
// mtl::keep_duplicates_exclusive_preserve, mtl::keep_duplicates_preserve,
// mtl::rem_duplicates_sorted, mtl::rem_duplicates, mtl::rem_duplicates_preserve, mtl::contains, 
// mtl::contains_all, mtl::contains_all_sorted, mtl::for_each, mtl::for_adj_pairs,
// mtl::for_all_pairs, mtl::fill_range, mtl::range



// ------------------------------------------------------------------------------------------------
// mtl::not_unique_inclusive
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::not_unique_inclusive for empty std::vector")
{
    std::vector<int> numbers;
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 1 element")
{
    std::vector<int> numbers{ 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 2 elements")
{
    std::vector<int> numbers{ 3, 4 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Maria" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 3 elements")
{
    std::vector<int> numbers{ 3, 4, 5 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Maria", "John" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 4 elements")
{
    std::vector<int> numbers{ 3, 4, 5, 1 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Maria", "John", "Bill" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 2 duplicate elements")
{
    std::vector<int> numbers{ 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Peter" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Peter", "Peter" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 3 duplicate elements")
{
    std::vector<int> numbers{ 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Peter", "Peter" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Peter", "Peter", "Peter" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector, 4 duplicate elements")
{
    std::vector<int> numbers{ 3, 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Peter", "Peter", "Peter" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Peter", "Peter", "Peter", "Peter" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive with custom predicate for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end(), 
                                          std::equal_to<std::string>{}), names.end());
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    std::sort(custom_con.begin(), custom_con.end(), [](const auto& rhs, const auto& lhs)
                                                    {
                                                        return rhs.x < lhs.x;
                                                    });

    custom_con.erase(mtl::not_unique_inclusive(custom_con.begin(), custom_con.end(), 
                                               [](const auto& rhs, const auto& lhs)
                                               {
                                                   return rhs.x == lhs.x;
                                               }), custom_con.end());
   
    std::vector<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::not_unique_inclusive for empty std::list")
{
    std::list<int> numbers;
    numbers.sort();
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	names.sort();
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	names.sort();
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end()), names.end());
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive with custom predicate for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique_inclusive(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	names.sort();
    names.erase(mtl::not_unique_inclusive(names.begin(), names.end(), 
                                          std::equal_to<std::string>{}), names.end());
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_inclusive with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });

    custom_con.erase(mtl::not_unique_inclusive(custom_con.begin(), custom_con.end(), 
                                               [](const auto& rhs, const auto& lhs)
                                               {
                                                   return rhs.x == lhs.x;
                                               }), custom_con.end());
   
    std::list<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::not_unique_exclusive
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::not_unique_exclusive for empty std::vector")
{
    std::vector<int> numbers;
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 1 element")
{
    std::vector<int> numbers { 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 2 elements")
{
    std::vector<int> numbers { 3, 4 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 3 elements")
{
    std::vector<int> numbers { 3, 4, 5 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria", "Nick" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 4 elements")
{
    std::vector<int> numbers { 3, 4, 5, 1 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria", "John", "Bill" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 2 duplicate elements")
{
    std::vector<int> numbers { 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 3 duplicate elements")
{
    std::vector<int> numbers { 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob", "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector, 4 duplicate elements")
{
    std::vector<int> numbers { 3, 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob", "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob", "Bob", "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive with custom predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end(), 
                                          std::equal_to<std::string>{}), names.end());
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    std::sort(custom_con.begin(), custom_con.end(), [](const auto& rhs, const auto& lhs)
                                                    {
                                                        return rhs.x < lhs.x;
                                                    });

    custom_con.erase(mtl::not_unique_exclusive(custom_con.begin(), custom_con.end(), 
                                               [](const auto& rhs, const auto& lhs)
                                               {
                                                   return rhs.x == lhs.x;
                                               }), custom_con.end());
   
    std::vector<custom_class> desired_result {c1, c1, c2, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::not_unique_exclusive for empty std::list")
{
    std::list<int> numbers;
    numbers.sort();
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	names.sort();
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	names.sort();
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end()), names.end());
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive with custom predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique_exclusive(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	names.sort();
    names.erase(mtl::not_unique_exclusive(names.begin(), names.end(), 
                                          std::equal_to<std::string>{}), names.end());
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique_exclusive with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });

    custom_con.erase(mtl::not_unique_exclusive(custom_con.begin(), custom_con.end(), 
                                               [](const auto& rhs, const auto& lhs)
                                               {
                                                   return rhs.x == lhs.x;
                                               }), custom_con.end());
   
    std::list<custom_class> desired_result {c1, c1, c2, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::not_unique
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::not_unique for empty std::vector")
{
    std::vector<int> numbers;
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 1 element")
{
    std::vector<int> numbers { 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 2 elements")
{
    std::vector<int> numbers { 3, 4 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 3 elements")
{
    std::vector<int> numbers { 3, 4, 5 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria", "John" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 4 elements")
{
    std::vector<int> numbers { 3, 4, 5, 1 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Maria", "John", "Bill" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 2 duplicate elements")
{
    std::vector<int> numbers { 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 3 duplicate elements")
{
    std::vector<int> numbers { 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector, 4 duplicate elements")
{
    std::vector<int> numbers { 3, 3, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results { 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Bob", "Bob", "Bob" };
    std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names { "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique with custom predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	std::sort(names.begin(), names.end());
    names.erase(mtl::not_unique(names.begin(), names.end(), std::equal_to<std::string>{}),
                names.end());
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    std::sort(custom_con.begin(), custom_con.end(), [](const auto& rhs, const auto& lhs)
                                                    {
                                                        return rhs.x < lhs.x;
                                                    });

    custom_con.erase(mtl::not_unique(custom_con.begin(), custom_con.end(), 
                                     [](const auto& rhs, const auto& lhs)
                                     {
                                         return rhs.x == lhs.x;
                                     }), custom_con.end());
   
    std::vector<custom_class> desired_result {c1, c2, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::not_unique for empty std::list")
{
    std::list<int> numbers;
    numbers.sort();
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	names.sort();
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end()), numbers.end());
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	names.sort();
    names.erase(mtl::not_unique(names.begin(), names.end()), names.end());
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique with custom predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    numbers.sort();
    numbers.erase(mtl::not_unique(numbers.begin(), numbers.end(), std::equal_to<int>{}),
                  numbers.end());
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	names.sort();
    names.erase(mtl::not_unique(names.begin(), names.end(), std::equal_to<std::string>{}),
                names.end());
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::not_unique with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });

    custom_con.erase(mtl::not_unique(custom_con.begin(), custom_con.end(), 
                                     [](const auto& rhs, const auto& lhs)
                                     {
                                         return rhs.x == lhs.x;
                                     }), custom_con.end());
   
    std::list<custom_class> desired_result {c1, c2, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_inclusive
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_inclusive for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates_inclusive(numbers);
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	mtl::keep_duplicates_inclusive(names);
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive(numbers);
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive(names);
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive with custom comparator and predicate for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive(numbers, std::less<int>{}, std::equal_to<int>{});
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers  == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive with custom comp and pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_inclusive(custom_con, 
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x < lhs.x;
                                   },
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x == lhs.x;
                                   });
   
    std::vector<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}


TEST_CASE("mtl::keep_duplicates_inclusive for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates_inclusive(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	mtl::keep_duplicates_inclusive(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive(numbers);
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive(names);
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive with custom comparator and predicate for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive(numbers, std::less<int>{}, std::equal_to<int>{});
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers  == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive with custom comp and pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_inclusive(custom_con, 
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x < lhs.x;
                                   },
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x == lhs.x;
                                   });
   
    std::list<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};
    
    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_exclusive
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_exclusive for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates_exclusive(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	mtl::keep_duplicates_exclusive(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive(numbers);
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive(names);
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive with custom comparator and predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive(numbers, std::less<int>{}, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive with custom comp and pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_exclusive(custom_con, 
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x < lhs.x;
                                   },
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x == lhs.x;
                                   });
   
    std::vector<custom_class> desired_result {c1, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_exclusive for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates_exclusive(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	mtl::keep_duplicates_exclusive(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive(numbers);
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive(names);
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive with custom comparator and predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive(numbers, std::less<int>{}, std::equal_to<int>{});
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_exclusive with custom comp and pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_exclusive(custom_con, 
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x < lhs.x;
                                   },
                                   [](const auto& rhs, const auto& lhs)
                                   {
                                       return rhs.x == lhs.x;
                                   });
   
    std::list<custom_class> desired_result {c1, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	mtl::keep_duplicates(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates(numbers);
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates(names);
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates with custom comparator and custom predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates(numbers, std::less<int>{}, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates with custom comparator and predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates(custom_con, 
                         [](const auto& rhs, const auto& lhs)
                         {
                             return rhs.x < lhs.x;
                         },
                         [](const auto& rhs, const auto& lhs)
                         {
                             return rhs.x == lhs.x;
                         });
   
    std::vector<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	mtl::keep_duplicates(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates(numbers);
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates(names);
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates with custom comparator and custom predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates(numbers, std::less<int>{}, std::equal_to<int>{});
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}



TEST_CASE("mtl::keep_duplicates with custom comparator and predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates(custom_con, 
                         [](const auto& rhs, const auto& lhs)
                         {
                             return rhs.x < lhs.x;
                         },
                         [](const auto& rhs, const auto& lhs)
                         {
                             return rhs.x == lhs.x;
                         });
   
    std::list<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}




// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_inclusive_sorted 
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_inclusive_sorted for empty std::vector")
{
    std::vector<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_inclusive_sorted(numbers);
    std::vector<int> results ;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_inclusive_sorted(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_inclusive_sorted(numbers);
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_inclusive_sorted(names);
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted with custom predicate for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_inclusive_sorted(numbers, std::equal_to<int>{});
    std::vector<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_inclusive_sorted(names, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    std::sort(custom_con.begin(), custom_con.end(),
              [](const auto& rhs, const auto& lhs)
              {
                  return rhs.x < lhs.x;
              });
    mtl::keep_duplicates_inclusive_sorted(custom_con, 
                                          [](const auto& rhs, const auto& lhs)
                                          {
                                              return rhs.x == lhs.x;
                                          });
   
    std::vector<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted for empty std::list")
{
    std::list<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_inclusive_sorted(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_inclusive_sorted(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_inclusive_sorted(numbers);
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_inclusive_sorted(names);
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted with custom predicate for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_inclusive_sorted(numbers, std::equal_to<int>{});
    std::list<int> results { 1, 1, 2, 2, 3, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_inclusive_sorted(names, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Joe", "Maria", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_sorted with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });
    mtl::keep_duplicates_inclusive_sorted(custom_con, 
                                          [](const auto& rhs, const auto& lhs)
                                          {
                                              return rhs.x == lhs.x;
                                          });
   
    std::list<custom_class> desired_result {c1, c1, c1, c2, c2, c3, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_exclusive_sorted
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_exclusive_sorted for empty std::vector")
{
    std::vector<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_exclusive_sorted(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_exclusive_sorted(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_exclusive_sorted(numbers);
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_exclusive_sorted(names);
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted with custom predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_exclusive_sorted(numbers, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_exclusive_sorted(names,  std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    std::sort(custom_con.begin(), custom_con.end(), [](const auto& rhs, const auto& lhs)
                                                    {
                                                        return rhs.x < lhs.x;
                                                    });
    mtl::keep_duplicates_exclusive_sorted(custom_con, 
                                          [](const auto& rhs, const auto& lhs)
                                          {
                                              return rhs.x == lhs.x;
                                          });
   
    std::vector<custom_class> desired_result {c1, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted for empty std::list")
{
    std::list<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_exclusive_sorted(numbers);
    std::list<int> results ;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_exclusive_sorted(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_exclusive_sorted(numbers);
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_exclusive_sorted(names);
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted with custom predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_exclusive_sorted(numbers, std::equal_to<int>{});
    std::list<int> results {1, 2, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_exclusive_sorted(names,  std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_sorted with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });
    mtl::keep_duplicates_exclusive_sorted(custom_con, 
                                          [](const auto& rhs, const auto& lhs)
                                          {
                                              return rhs.x == lhs.x;
                                          });
   
    std::list<custom_class> desired_result {c1, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_sorted
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_sorted for empty std::vector")
{
    std::vector<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_sorted(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_sorted(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_sorted(numbers);
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_sorted(names);
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted with custom comparator and predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::keep_duplicates_sorted(numbers, std::less<int>{}, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
	mtl::keep_duplicates_sorted(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted with custom comp and pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    std::sort(custom_con.begin(), custom_con.end(), [](const auto& rhs, const auto& lhs)
                                                    {
                                                        return rhs.x < lhs.x;
                                                    });
    mtl::keep_duplicates_sorted(custom_con, 
                                [](const auto& rhs, const auto& lhs)
                                {
                                    return rhs.x < lhs.x;
                                },
                                [](const auto& rhs, const auto& lhs)
                                {
                                    return rhs.x == lhs.x;
                                });
   
    std::vector<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_sorted for empty std::list")
{
    std::list<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_sorted(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_sorted(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_sorted(numbers);
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_sorted(names);
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted with custom comparator and predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::keep_duplicates_sorted(numbers, std::less<int>{}, std::equal_to<int>{});
    std::list<int> results {1, 2, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
	mtl::keep_duplicates_sorted(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Joe", "Mac"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_sorted with custom comp and pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    // algorithms ending with _sorted require the container to be sorted
    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });
    mtl::keep_duplicates_sorted(custom_con, 
                                [](const auto& rhs, const auto& lhs)
                                {
                                    return rhs.x < lhs.x;
                                },
                                [](const auto& rhs, const auto& lhs)
                                {
                                    return rhs.x == lhs.x;
                                });
   
    std::list<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_inclusive_preserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_inclusive_preserve for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates_inclusive_preserve(numbers);
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    
    std::vector<std::string> names;
	mtl::keep_duplicates_inclusive_preserve(names);
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_preserve for std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive_preserve(numbers);
    std::vector<int> results { 3, 1, 2, 2, 1, 3, 3 };
    CHECK_EQ((numbers == results), true);

    
    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive_preserve(names);
    std::vector<std::string> results_names {"Maria", "Bob", "Joe", "Joe", "Bob", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_inclusive_preserve custom predicate std::vector")
{
    std::vector<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive_preserve(numbers, std::equal_to<int>{});
    std::vector<int> results { 3, 1, 2, 2, 1, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive_preserve(names, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Maria", "Bob", "Joe", "Joe", "Bob", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_inclusive_preserve with custom pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_inclusive_preserve(custom_con, 
                                            [](const auto& rhs, const auto& lhs)
                                            {
                                                return rhs.x == lhs.x;
                                            });
   
    std::vector<custom_class> desired_result {c1, c2, c3, c3, c2, c1, c1};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_inclusive_preserve for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates_inclusive_preserve(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    
    std::list<std::string> names;
	mtl::keep_duplicates_inclusive_preserve(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_preserve for std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive_preserve(numbers);
    std::list<int> results { 3, 1, 2, 2, 1, 3, 3 };
    CHECK_EQ((numbers == results), true);

    
    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive_preserve(names);
    std::list<std::string> results_names {"Maria", "Bob", "Joe", "Joe", "Bob", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_inclusive_preserve custom predicate std::list")
{
    std::list<int> numbers{ 5, 4, 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_inclusive_preserve(numbers, std::equal_to<int>{});
    std::list<int> results { 3, 1, 2, 2, 1, 3, 3 };
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Peter", "Nick", "Maria", "Bob", "Joe", "Joe", "Bob",
                                     "Maria", "Maria" };
	mtl::keep_duplicates_inclusive_preserve(names, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Maria", "Bob", "Joe", "Joe", "Bob", "Maria", "Maria"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_inclusive_preserve with custom pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_inclusive_preserve(custom_con, 
                                            [](const auto& rhs, const auto& lhs)
                                            {
                                                return rhs.x == lhs.x;
                                            });
   
    std::list<custom_class> desired_result {c1, c2, c3, c3, c2, c1, c1};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_exclusive_preserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_exclusive_preserve for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates_exclusive_preserve(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive_preserve(names);
    std::vector<std::string> results_names {"Joe", "Mac", "Bob", "Bob"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_preserve for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive_preserve(numbers);
    std::vector<int> results {2, 1, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive_preserve(names);
    std::vector<std::string> results_names {"Joe", "Mac", "Bob", "Bob"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_exclusive_preserve custom comparator and predicate std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::vector<int> results {2, 1, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive_preserve(names, std::hash<std::string>{}, 
                                            std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Joe", "Mac", "Bob", "Bob"};
    CHECK_EQ((names == results_names), true);

}



TEST_CASE("mtl::keep_duplicates_exclusive_preserve custom hash / pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_exclusive_preserve(custom_con, 
                                            [](const auto& element)
                                            {
                                                return std::hash<int>{}(element.x);
                                            },
                                            [](const auto& rhs, const auto& lhs)
                                            {
                                                return rhs.x == lhs.x;
                                            });
   
    std::vector<custom_class> desired_result {c3, c2, c1, c1};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_exclusive_preserve for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates_exclusive_preserve(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	mtl::keep_duplicates_exclusive_preserve(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_preserve for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive_preserve(numbers);
    std::list<int> results {2, 1, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive_preserve(names);
    std::list<std::string> results_names {"Joe", "Mac", "Bob", "Bob"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_exclusive_preserve custom comparator and predicate std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3 };
    mtl::keep_duplicates_exclusive_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::list<int> results {2, 1, 3, 3};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_exclusive_preserve(names, std::hash<std::string>{}, 
                                            std::equal_to<std::string>{});
    std::list<std::string> results_names {"Joe", "Mac", "Bob", "Bob"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_exclusive_preserve custom hash / pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_exclusive_preserve(custom_con, 
                                            [](const auto& element)
                                            {
                                                return std::hash<int>{}(element.x);
                                            },
                                            [](const auto& rhs, const auto& lhs)
                                            {
                                                return rhs.x == lhs.x;
                                            });
   
    std::list<custom_class> desired_result {c3, c2, c1, c1};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}



// ------------------------------------------------------------------------------------------------
// mtl::keep_duplicates_preserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::keep_duplicates_preserve for empty std::vector")
{
    std::vector<int> numbers;
    mtl::keep_duplicates_preserve(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
	mtl::keep_duplicates_preserve(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_preserve for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3, 4, 5 };
    mtl::keep_duplicates_preserve(numbers);
    std::vector<int> results {3, 1, 2};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_preserve(names);
    std::vector<std::string> results_names {"Bob", "Mac", "Joe"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_preserve with custom comparator and predicate for std::vector")
{
    std::vector<int> numbers { 3, 1, 2, 2, 1, 3, 3, 4, 5 };
    mtl::keep_duplicates_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::vector<int> results {3, 1, 2};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_preserve(names, std::hash<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names {"Bob", "Mac", "Joe"};
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_preserve with custom hash and pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_preserve(custom_con, 
                                  [](const auto& element)
                                  {
                                      return std::hash<int>{}(element.x);
                                  },
                                  [](const auto& rhs, const auto& lhs)
                                  {
                                      return rhs.x == lhs.x;
                                  });
   
    std::vector<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::keep_duplicates_preserve for empty std::list")
{
    std::list<int> numbers;
    mtl::keep_duplicates_preserve(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
	mtl::keep_duplicates_preserve(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::keep_duplicates_preserve for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3, 4, 5 };
    mtl::keep_duplicates_preserve(numbers);
    std::list<int> results {3, 1, 2};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_preserve(names);
    std::list<std::string> results_names {"Bob", "Mac", "Joe"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_preserve with custom comparator and predicate for std::list")
{
    std::list<int> numbers { 3, 1, 2, 2, 1, 3, 3, 4, 5 };
    mtl::keep_duplicates_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::list<int> results {3, 1, 2};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names { "Bob", "Mac", "Joe", "Joe", "Mac", "Bob", "Bob" };
	mtl::keep_duplicates_preserve(names, std::hash<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names {"Bob", "Mac", "Joe"};
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::keep_duplicates_preserve with custom hash and pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::keep_duplicates_preserve(custom_con, 
                                  [](const auto& element)
                                  {
                                      return std::hash<int>{}(element.x);
                                  },
                                  [](const auto& rhs, const auto& lhs)
                                  {
                                      return rhs.x == lhs.x;
                                  });
   
    std::list<custom_class> desired_result {c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::rem_duplicates_sorted
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::rem_duplicates_sorted for empty std::vector")
{
    std::vector<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::rem_duplicates_sorted(numbers);
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
    mtl::rem_duplicates_sorted(names);
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::rem_duplicates_sorted(numbers);
    std::vector<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
    mtl::rem_duplicates_sorted(names);
    std::vector<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted with custom predicate for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    // algorithms ending with _sorted require the container to be sorted
    std::sort(numbers.begin(), numbers.end());
    mtl::rem_duplicates_sorted(numbers, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    // algorithms ending with _sorted require the container to be sorted
    std::sort(names.begin(), names.end());
    mtl::rem_duplicates_sorted(names, std::equal_to<std::string>{});
    std::vector<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted with custom predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};
    // algorithms ending with _sorted require the container to be sorted
    std::sort(custom_con.begin(), custom_con.end(),
                                  [](const auto& rhs, const auto& lhs)
                                  {
                                      return rhs.x < lhs.x;
                                  });

    mtl::rem_duplicates_sorted(custom_con, 
                               [](const auto& rhs, const auto& lhs)
                               {
                                   return rhs.x == lhs.x;
                               });
   
    std::vector<custom_class> desired_result {c1, c2, c3, c4};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::rem_duplicates_sorted for empty std::list")
{
    std::list<int> numbers;
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::rem_duplicates_sorted(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
    mtl::rem_duplicates_sorted(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted for std::list")
{
    std::list<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::rem_duplicates_sorted(numbers);
    std::list<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
    mtl::rem_duplicates_sorted(names);
    std::list<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted with custom predicate for std::list")
{
    std::list<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    // algorithms ending with _sorted require the container to be sorted
    numbers.sort();
    mtl::rem_duplicates_sorted(numbers, std::equal_to<int>{});
    std::list<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    // algorithms ending with _sorted require the container to be sorted
    names.sort();
    mtl::rem_duplicates_sorted(names, std::equal_to<std::string>{});
    std::list<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_sorted with custom predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};
    // algorithms ending with _sorted require the container to be sorted
    custom_con.sort([](const auto& rhs, const auto& lhs)
                    {
                        return rhs.x < lhs.x;
                    });

    mtl::rem_duplicates_sorted(custom_con, 
                               [](const auto& rhs, const auto& lhs)
                               {
                                   return rhs.x == lhs.x;
                               });
   
    std::list<custom_class> desired_result {c1, c2, c3, c4};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::rem_duplicates
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::rem_duplicates for empty std::vector")
{
    std::vector<int> numbers;
    mtl::rem_duplicates(numbers);
    std::vector<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    mtl::rem_duplicates(names);
    std::vector<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates(numbers);
    std::vector<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates(names);
    std::vector<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates with custom predicate for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates(numbers, std::less<int>{}, std::equal_to<int>{});
    std::vector<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates with custom comp and pred, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::rem_duplicates(custom_con, 
                        [](const auto& rhs, const auto& lhs)
                        {
                            return rhs.x < lhs.x;
                        },
                        [](const auto& rhs, const auto& lhs)
                        {
                            return rhs.x == lhs.x;
                        });
   
    std::vector<custom_class> desired_result {c1, c2, c3, c4};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::rem_duplicates for empty std::list")
{
    std::list<int> numbers;
    mtl::rem_duplicates(numbers);
    std::list<int> results;
    CHECK_EQ(numbers.empty(), true);
    CHECK_EQ(results.empty(), true);
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    mtl::rem_duplicates(names);
    std::list<std::string> results_names;
    CHECK_EQ(names.empty(), true);
    CHECK_EQ(results_names.empty(), true);
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates with custom predicate for std::list")
{
    std::list<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates(numbers, std::less<int>{}, std::equal_to<int>{});
    std::list<int> results {1, 2, 3, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates(names, std::less<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names { "Bill", "Bob", "Joe" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates with custom comp and pred, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::rem_duplicates(custom_con, 
                        [](const auto& rhs, const auto& lhs)
                        {
                            return rhs.x < lhs.x;
                        },
                        [](const auto& rhs, const auto& lhs)
                        {
                            return rhs.x == lhs.x;
                        });
   
    std::list<custom_class> desired_result {c1, c2, c3, c4};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::rem_duplicates_preserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::rem_duplicates_preserve for empty std::vector")
{
    std::vector<int> numbers;
    mtl::rem_duplicates_preserve(numbers);
    std::vector<int> results;
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names;
    mtl::rem_duplicates_preserve(names);
    std::vector<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_preserve for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates_preserve(numbers);
    std::vector<int> results {2, 3, 1, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates_preserve(names);
    std::vector<std::string> results_names { "Bill", "Joe", "Bob" };
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::rem_duplicates_preserve with custom predicate for std::vector")
{
    std::vector<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::vector<int> results {2, 3, 1, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::vector<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates_preserve(names, std::hash<std::string>{}, std::equal_to<std::string>{});
    std::vector<std::string> results_names { "Bill", "Joe", "Bob" };
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_preserve with custom hash and predicate, custom class, std::vector")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::vector<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::rem_duplicates_preserve(custom_con, 
                                 [](const auto& element)
                                 {
                                     return std::hash<int>{}(element.x);
                                 },
                                 [](const auto& rhs, const auto& lhs)
                                 {
                                     return rhs.x == lhs.x;
                                 });
   
    std::vector<custom_class> desired_result {c4, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        REQUIRE_EQ(custom_con[i].x, desired_result[i].x);
    }
}

TEST_CASE("mtl::rem_duplicates_preserve for empty std::list")
{
    std::list<int> numbers;
    mtl::rem_duplicates_preserve(numbers);
    std::list<int> results;
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names;
    mtl::rem_duplicates_preserve(names);
    std::list<std::string> results_names;
    CHECK_EQ((names == results_names), true);
}

TEST_CASE("mtl::rem_duplicates_preserve for std::list")
{
    std::list<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates_preserve(numbers);
    std::list<int> results {2, 3, 1, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates_preserve(names);
    std::list<std::string> results_names { "Bill", "Joe", "Bob" };
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::rem_duplicates_preserve with custom predicate for std::list")
{
    std::list<int> numbers {2, 3, 1, 1, 3, 2, 4, 5, 5, 5, 5, 2, 3};
    mtl::rem_duplicates_preserve(numbers, std::hash<int>{}, std::equal_to<int>{});
    std::list<int> results {2, 3, 1, 4, 5};
    CHECK_EQ((numbers == results), true);

    std::list<std::string> names {"Bill", "Joe", "Bob", "Joe", "Bob", "Joe", "Bill" };
    mtl::rem_duplicates_preserve(names, std::hash<std::string>{}, std::equal_to<std::string>{});
    std::list<std::string> results_names { "Bill", "Joe", "Bob" };
    CHECK_EQ((names == results_names), true);
}


TEST_CASE("mtl::rem_duplicates_preserve with custom hash and predicate, custom class, std::list")
{
    class custom_class 
    {
        public:
        int x = 0;
    };

    custom_class c1;
    c1.x = 1;
    custom_class c2;
    c2.x = 2;
    custom_class c3;
    c3.x = 3;
    custom_class c4;
    c4.x = 4;
    std::list<custom_class> custom_con {c4, c1, c2, c3, c3, c2, c1, c1};

    mtl::rem_duplicates_preserve(custom_con, 
                                 [](const auto& element)
                                 {
                                     return std::hash<int>{}(element.x);
                                 },
                                 [](const auto& rhs, const auto& lhs)
                                 {
                                     return rhs.x == lhs.x;
                                 });
   
    std::list<custom_class> desired_result {c4, c1, c2, c3};

    REQUIRE_EQ(custom_con.size(), desired_result.size());
    for(size_t i = 0; i < custom_con.size(); ++i)
    {
        auto cl_it = std::next(custom_con.begin(), static_cast<std::ptrdiff_t>(i));
        auto dr_it = std::next(desired_result.begin(), static_cast<std::ptrdiff_t>(i));
        REQUIRE_EQ(cl_it->x, dr_it->x);
    }
}



// ------------------------------------------------------------------------------------------------
// mtl::contains
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::contains for empty containers without find function")
{
    std::vector<int> vi;
    std::deque<int> di;
    std::list<int> li;
    
    CHECK_EQ(mtl::contains(vi, 3), false);
    CHECK_EQ(mtl::contains(di, 3), false);
    CHECK_EQ(mtl::contains(li, 3), false);

    CHECK_EQ(mtl::contains(vi, 333), false);
    CHECK_EQ(mtl::contains(di, 333), false);
    CHECK_EQ(mtl::contains(li, 333), false);
}

TEST_CASE("mtl::contains for containers without find function")
{
    std::vector<int> vi {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::deque<int> di (vi.begin(), vi.end());
    std::list<int> li (vi.begin(), vi.end());
    
    CHECK_EQ(mtl::contains(vi, 3), true);
    CHECK_EQ(mtl::contains(di, 3), true);
    CHECK_EQ(mtl::contains(li, 3), true);

    CHECK_EQ(mtl::contains(vi, 333), false);
    CHECK_EQ(mtl::contains(di, 333), false);
    CHECK_EQ(mtl::contains(li, 333), false);
}

TEST_CASE("mtl::contains for containers<std::string> without find function")
{
    std::vector<std::string> vi {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    std::deque<std::string> di (vi.begin(), vi.end());
    std::list<std::string> li (vi.begin(), vi.end());
    
    std::string three = "3";
    CHECK_EQ(mtl::contains(vi, three), true);
    CHECK_EQ(mtl::contains(di, three), true);
    CHECK_EQ(mtl::contains(li, three), true);

    std::string three33 = "333";
    CHECK_EQ(mtl::contains(vi, three33), false);
    CHECK_EQ(mtl::contains(di, three33), false);
    CHECK_EQ(mtl::contains(li, three33), false);
}


TEST_CASE("mtl::contains for empty containers with find function")
{
    std::set<int> si;
    std::multiset<int> msi;
    std::unordered_set<int> usi;
    std::unordered_multiset<int> umsi;

    std::map<int, int> mi;
    std::multimap<int, int> mmi;
    std::unordered_map<int, int> umi;
    std::unordered_multimap<int, int> ummi;  

    CHECK_EQ(mtl::contains(si, 3), false);  
    CHECK_EQ(mtl::contains(msi, 3), false);  
    CHECK_EQ(mtl::contains(usi, 3), false);  
    CHECK_EQ(mtl::contains(umsi, 3), false);  

    CHECK_EQ(mtl::contains(mi, 3), false);  
    CHECK_EQ(mtl::contains(mmi, 3), false);  
    CHECK_EQ(mtl::contains(umi, 3), false);  
    CHECK_EQ(mtl::contains(ummi, 3), false);  
}

TEST_CASE("mtl::contains for containers with find function")
{
    std::set<int> si {1, 2, 3};
    std::multiset<int> msi {1, 2, 3};
    std::unordered_set<int> usi {1, 2, 3};
    std::unordered_multiset<int> umsi {1, 2, 3};

    std::map<int, int> mi { {1, 11}, {2, 11}, {3, 11} };
    std::multimap<int, int> mmi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_map<int, int> umi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_multimap<int, int> ummi { {1, 11}, {2, 11}, {3, 11} };  

    CHECK_EQ(mtl::contains(si, 3), true);  
    CHECK_EQ(mtl::contains(msi, 3), true);  
    CHECK_EQ(mtl::contains(usi, 3), true);  
    CHECK_EQ(mtl::contains(umsi, 3), true);  

    CHECK_EQ(mtl::contains(mi, 3), true);  
    CHECK_EQ(mtl::contains(mmi, 3), true);  
    CHECK_EQ(mtl::contains(umi, 3), true);  
    CHECK_EQ(mtl::contains(ummi, 3), true);  


    CHECK_EQ(mtl::contains(si, 333), false);  
    CHECK_EQ(mtl::contains(msi, 333), false);  
    CHECK_EQ(mtl::contains(usi, 333), false);  
    CHECK_EQ(mtl::contains(umsi, 333), false);  

    CHECK_EQ(mtl::contains(mi, 333), false);  
    CHECK_EQ(mtl::contains(mmi, 333), false);  
    CHECK_EQ(mtl::contains(umi, 333), false);  
    CHECK_EQ(mtl::contains(ummi, 333), false);
}


TEST_CASE("mtl::contains for containers<std::string> with find function")
{
    std::set<std::string> si {"1", "2", "3"};
    std::multiset<std::string> msi {"1", "2", "3"};
    std::unordered_set<std::string> usi {"1", "2", "3"};
    std::unordered_multiset<std::string> umsi {"1", "2", "3"};

    std::map<std::string, std::string> mi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::multimap<std::string, std::string> mmi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_map<std::string, std::string> umi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_multimap<std::string, std::string> ummi { {"1", "11"}, {"2", "11"}, 
                                                             {"3", "11"} };

    std::string three = "3";
    CHECK_EQ(mtl::contains(si, three), true);  
    CHECK_EQ(mtl::contains(msi, three), true);  
    CHECK_EQ(mtl::contains(usi, three), true);  
    CHECK_EQ(mtl::contains(umsi, three), true);  

    CHECK_EQ(mtl::contains(mi, three), true);  
    CHECK_EQ(mtl::contains(mmi, three), true);  
    CHECK_EQ(mtl::contains(umi, three), true);  
    CHECK_EQ(mtl::contains(ummi, three), true);  

    std::string three33 = "333";
    CHECK_EQ(mtl::contains(si, three33), false);  
    CHECK_EQ(mtl::contains(msi, three33), false);  
    CHECK_EQ(mtl::contains(usi, three33), false);  
    CHECK_EQ(mtl::contains(umsi, three33), false);  

    CHECK_EQ(mtl::contains(mi, three33), false);  
    CHECK_EQ(mtl::contains(mmi, three33), false);  
    CHECK_EQ(mtl::contains(umi, three33), false);  
    CHECK_EQ(mtl::contains(ummi, three33), false);
}



// ------------------------------------------------------------------------------------------------
// mtl::contains_all
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::contains_all for empty containers without find function")
{
    std::vector<int> vi;
    std::deque<int> di;
    std::list<int> li;
    std::vector<int> numbers;
    
    CHECK_EQ(mtl::contains_all(vi, numbers), true);
    CHECK_EQ(mtl::contains_all(di, numbers), true);
    CHECK_EQ(mtl::contains_all(li, numbers), true);
}

TEST_CASE("mtl::contains_all for containers without find function")
{
    std::vector<int> vi {1, 2, 3, 4, 5};
    std::deque<int> di (vi.begin(), vi.end());
    std::list<int> li (vi.begin(), vi.end());
    std::vector<int> numbers { 3, 1, 5};
    
    CHECK_EQ(mtl::contains_all(vi, numbers), true);
    CHECK_EQ(mtl::contains_all(di, numbers), true);
    CHECK_EQ(mtl::contains_all(li, numbers), true);

    std::vector<int> other { 3, 1, 5, 333};
    
    CHECK_EQ(mtl::contains_all(vi, other), false);
    CHECK_EQ(mtl::contains_all(di, other), false);
    CHECK_EQ(mtl::contains_all(li, other), false);
}


TEST_CASE("mtl::contains_all for containers<std::string> without find function")
{
    std::vector<std::string> vi {"1", "2", "3", "4", "5"};
    std::deque<std::string> di (vi.begin(), vi.end());
    std::list<std::string> li (vi.begin(), vi.end());
    std::vector<std::string> numbers { "3", "1", "5"};
    
    CHECK_EQ(mtl::contains_all(vi, numbers), true);
    CHECK_EQ(mtl::contains_all(di, numbers), true);
    CHECK_EQ(mtl::contains_all(li, numbers), true);

    std::vector<std::string> other { "3", "1", "5", "555"};
    
    CHECK_EQ(mtl::contains_all(vi, other), false);
    CHECK_EQ(mtl::contains_all(di, other), false);
    CHECK_EQ(mtl::contains_all(li, other), false);
}






TEST_CASE("mtl::contains_all for empty containers with find function")
{
    std::set<int> si;
    std::multiset<int> msi;
    std::unordered_set<int> usi;
    std::unordered_multiset<int> umsi;

    std::map<int, int> mi;
    std::multimap<int, int> mmi;
    std::unordered_map<int, int> umi;
    std::unordered_multimap<int, int> ummi;  

    std::vector<int> numbers;

    CHECK_EQ(mtl::contains_all(si, numbers), true);  
    CHECK_EQ(mtl::contains_all(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all(ummi, numbers), true);  
}

TEST_CASE("mtl::contains_all for containers with find function")
{
    std::set<int> si {1, 2, 3};
    std::multiset<int> msi {1, 2, 3};
    std::unordered_set<int> usi {1, 2, 3};
    std::unordered_multiset<int> umsi {1, 2, 3};

    std::map<int, int> mi { {1, 11}, {2, 11}, {3, 11} };
    std::multimap<int, int> mmi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_map<int, int> umi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_multimap<int, int> ummi { {1, 11}, {2, 11}, {3, 11} };  

    std::vector<int> numbers {2, 3};

    CHECK_EQ(mtl::contains_all(si, numbers), true);  
    CHECK_EQ(mtl::contains_all(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all(ummi, numbers), true);  

    std::vector<int> other {2, 3, 333};

    CHECK_EQ(mtl::contains_all(si, other), false);  
    CHECK_EQ(mtl::contains_all(msi, other), false);  
    CHECK_EQ(mtl::contains_all(usi, other), false);  
    CHECK_EQ(mtl::contains_all(umsi, other), false);  

    CHECK_EQ(mtl::contains_all(mi, other), false);  
    CHECK_EQ(mtl::contains_all(mmi, other), false);  
    CHECK_EQ(mtl::contains_all(umi, other), false);  
    CHECK_EQ(mtl::contains_all(ummi, other), false);
}



TEST_CASE("mtl::contains_all for containers<std::string> with find function")
{
    std::set<std::string> si {"1", "2", "3"};
    std::multiset<std::string> msi (si.begin(), si.end());
    std::unordered_set<std::string> usi (si.begin(), si.end());
    std::unordered_multiset<std::string> umsi (si.begin(), si.end());

    std::map<std::string, std::string> mi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::multimap<std::string, std::string> mmi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_map<std::string, std::string> umi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_multimap<std::string, std::string> ummi {{"1", "11"}, {"2", "11"}, {"3", "11"}};

    std::vector<std::string> numbers {"2", "3"};

    CHECK_EQ(mtl::contains_all(si, numbers), true);  
    CHECK_EQ(mtl::contains_all(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all(ummi, numbers), true);  

    std::vector<std::string> other {"2", "3", "333"};

    CHECK_EQ(mtl::contains_all(si, other), false);  
    CHECK_EQ(mtl::contains_all(msi, other), false);  
    CHECK_EQ(mtl::contains_all(usi, other), false);  
    CHECK_EQ(mtl::contains_all(umsi, other), false);  

    CHECK_EQ(mtl::contains_all(mi, other), false);  
    CHECK_EQ(mtl::contains_all(mmi, other), false);  
    CHECK_EQ(mtl::contains_all(umi, other), false);  
    CHECK_EQ(mtl::contains_all(ummi, other), false);
}



// ------------------------------------------------------------------------------------------------
// mtl::contains_all_sorted
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::contains_all_sorted for empty containers without find function")
{
    std::vector<int> vi;
    std::deque<int> di;
    std::list<int> li;
    std::vector<int> numbers;
    
    CHECK_EQ(mtl::contains_all_sorted(vi, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(di, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(li, numbers), true);
}

TEST_CASE("mtl::contains_all_sorted for containers without find function")
{
    std::vector<int> vi {1, 2, 3, 4, 5};
    std::deque<int> di (vi.begin(), vi.end());
    std::list<int> li (vi.begin(), vi.end());
    std::vector<int> numbers { 1, 3, 5};
    
    CHECK_EQ(mtl::contains_all_sorted(vi, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(di, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(li, numbers), true);

    std::vector<int> other { 1, 3, 5, 333};
    
    CHECK_EQ(mtl::contains_all_sorted(vi, other), false);
    CHECK_EQ(mtl::contains_all_sorted(di, other), false);
    CHECK_EQ(mtl::contains_all_sorted(li, other), false);
}


TEST_CASE("mtl::contains_all_sorted for containers<std::string> without find function")
{
    std::vector<std::string> vi {"1", "2", "3", "4", "5"};
    std::deque<std::string> di (vi.begin(), vi.end());
    std::list<std::string> li (vi.begin(), vi.end());
    std::vector<std::string> numbers { "1", "3", "5"};
    
    CHECK_EQ(mtl::contains_all_sorted(vi, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(di, numbers), true);
    CHECK_EQ(mtl::contains_all_sorted(li, numbers), true);

    std::vector<std::string> other { "1", "3", "5", "555"};
    
    CHECK_EQ(mtl::contains_all_sorted(vi, other), false);
    CHECK_EQ(mtl::contains_all_sorted(di, other), false);
    CHECK_EQ(mtl::contains_all_sorted(li, other), false);
}



TEST_CASE("mtl::contains_all_sorted for empty containers with find function")
{
    std::set<int> si;
    std::multiset<int> msi;
    std::unordered_set<int> usi;
    std::unordered_multiset<int> umsi;

    std::map<int, int> mi;
    std::multimap<int, int> mmi;
    std::unordered_map<int, int> umi;
    std::unordered_multimap<int, int> ummi;  

    std::vector<int> numbers;

    CHECK_EQ(mtl::contains_all_sorted(si, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all_sorted(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(ummi, numbers), true);  
}

TEST_CASE("mtl::contains_all_sorted for containers with find function")
{
    std::set<int> si {1, 2, 3};
    std::multiset<int> msi {1, 2, 3};
    std::unordered_set<int> usi {1, 2, 3};
    std::unordered_multiset<int> umsi {1, 2, 3};

    std::map<int, int> mi { {1, 11}, {2, 11}, {3, 11} };
    std::multimap<int, int> mmi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_map<int, int> umi { {1, 11}, {2, 11}, {3, 11} };
    std::unordered_multimap<int, int> ummi { {1, 11}, {2, 11}, {3, 11} };  

    std::vector<int> numbers {2, 3};

    CHECK_EQ(mtl::contains_all_sorted(si, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all_sorted(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(ummi, numbers), true);  

    std::vector<int> other {2, 3, 333};

    CHECK_EQ(mtl::contains_all_sorted(si, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(msi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(usi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(umsi, other), false);  

    CHECK_EQ(mtl::contains_all_sorted(mi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(mmi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(umi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(ummi, other), false);
}





TEST_CASE("mtl::contains_all_sorted for containers<std::string> with find function")
{
    std::set<std::string> si {"1", "2", "3"};
    std::multiset<std::string> msi (si.begin(), si.end());
    std::unordered_set<std::string> usi (si.begin(), si.end());
    std::unordered_multiset<std::string> umsi (si.begin(), si.end());

    std::map<std::string, std::string> mi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::multimap<std::string, std::string> mmi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_map<std::string, std::string> umi { {"1", "11"}, {"2", "11"}, {"3", "11"} };
    std::unordered_multimap<std::string, std::string> ummi {{"1", "11"}, {"2", "11"}, {"3", "11"}};

    std::vector<std::string> numbers {"2", "3"};

    CHECK_EQ(mtl::contains_all_sorted(si, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(msi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(usi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umsi, numbers), true);  

    CHECK_EQ(mtl::contains_all_sorted(mi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(mmi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(umi, numbers), true);  
    CHECK_EQ(mtl::contains_all_sorted(ummi, numbers), true);  

    std::vector<std::string> other {"2", "3", "333"};

    CHECK_EQ(mtl::contains_all_sorted(si, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(msi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(usi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(umsi, other), false);  

    CHECK_EQ(mtl::contains_all_sorted(mi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(mmi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(umi, other), false);  
    CHECK_EQ(mtl::contains_all_sorted(ummi, other), false);
}




// ------------------------------------------------------------------------------------------------
// mtl::for_each
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::for_each results compared to std::for_each results with empty container")
{
    std::vector<int> v1;
    auto v2 = v1;
    int v1_total = 0;
    int v2_total = 0;
    const int desired_result = 0;
    mtl::for_each(v1.begin(), v1.end(), [&v1_total](auto x) { v1_total += x;});
    std::for_each(v2.begin(), v2.end(), [&v2_total](auto x) { v2_total += x;});
    CHECK_EQ((v1_total == desired_result), true);
    CHECK_EQ((v2_total == desired_result), true);
}

TEST_CASE("mtl::for_each results compared to std::for_each with empty container, modify")
{
    std::vector<int> v1;
    auto v2 = v1;
    std::vector<int> results;
    mtl::for_each(v1.begin(), v1.end(), [](auto& x) { x = x * 10;});
    std::for_each(v2.begin(), v2.end(), [](auto& x) { x = x * 10;});
    CHECK_EQ((v1 == v2), true);
    CHECK_EQ((v1 == results), true);
    CHECK_EQ((v2 == results), true);
}

TEST_CASE("mtl::for_each results compared to std::for_each results")
{
    std::vector<int> v1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};
    auto v2 = v1;
    int v1_total = 0;
    int v2_total = 0;
    const int desired_result = 55;
    mtl::for_each(v1.begin(), v1.end(), [&v1_total](auto x) { v1_total += x;});
    std::for_each(v2.begin(), v2.end(), [&v2_total](auto x) { v2_total += x;});
    CHECK_EQ((v1_total == desired_result), true);
    CHECK_EQ((v2_total == desired_result), true);
}

TEST_CASE("mtl::for_each results compared to std::for_each results, modify")
{
    std::vector<int> v1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};
    auto v2 = v1;
    std::vector<int> results {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    mtl::for_each(v1.begin(), v1.end(), [](auto& x) { x = x * 10;});
    std::for_each(v2.begin(), v2.end(), [](auto& x) { x = x * 10;});
    CHECK_EQ((v1 == v2), true);
    CHECK_EQ((v1 == results), true);
    CHECK_EQ((v2 == results), true);
}



TEST_CASE("mtl::for_each results compared to std::for_each results, std::string, modify")
{
    std::vector<std::string> v1 {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    auto v2 = v1;
    std::vector<std::string> results {"00", "11", "22", "33", "44", "55", "66", "77", "88", "99", 
                                      "1010"};
    mtl::for_each(v1.begin(), v1.end(), [](auto& x) { x += x;});
    std::for_each(v2.begin(), v2.end(), [](auto& x) { x += x;});
    CHECK_EQ((v1 == v2), true);
    CHECK_EQ((v1 == results), true);
    CHECK_EQ((v2 == results), true);
}


TEST_CASE("mtl::for_each with std::tuple of integers")
{
    auto tp = std::make_tuple(10, 20, 30, 40);
    int total = 0;
    mtl::for_each(tp, [&total](auto num) { total += num;});
    REQUIRE_EQ(total, 100);
}

TEST_CASE("mtl::for_each with const std::tuple of integers")
{
    const std::tuple<int, int, int, int> tp = std::make_tuple(10, 20, 30, 40);
    int total = 0;
    mtl::for_each(tp, [&total](auto num) { total += num;});
    REQUIRE_EQ(total, 100);
}

TEST_CASE("mtl::for_each with std::tuple of integers, ref")
{
    const int items = 10;
    const int desired_result = items * 100;
    int grand_total = 0;
    std::vector<std::tuple<int, int, int, int>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, 20, 30, 40);
        vt.emplace_back(tp);
    }
    
    for(auto& t : vt)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 100);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}

TEST_CASE("mtl::for_each with std::tuple of integers, const ref")
{
    const int items = 10;
    const int desired_result = items * 100;
    int grand_total = 0;
    std::vector<std::tuple<int, int, int, int>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, 20, 30, 40);
        vt.emplace_back(tp);
    }
    
    for(const auto& t : vt)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 100);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}

TEST_CASE("mtl::for_each with std::tuple of integers, modify")
{
    const int items = 10;
    const int desired_result = items * 1000;
    int grand_total = 0;
    std::vector<std::tuple<int, int, int, int>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, 20, 30, 40);
        vt.emplace_back(tp);
    }

    // modify elements
    for(auto& t : vt)
    {
        mtl::for_each(t, [](auto& num) { num = num * 10; });
    }
    
    for(const auto& t : vt)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 1000);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}



TEST_CASE("mtl::for_each with std::tuple of different types")
{
    auto tp = std::make_tuple(10, 'a', std::string("bcd"));
    std::stringstream ss;
    mtl::for_each(tp, [&ss](auto item) { ss << item;});
    std::string result = "10abcd";
    REQUIRE_EQ(ss.str(), result);
}

TEST_CASE("mtl::for_each with const std::tuple of different types")
{
    const std::tuple<int, char, std::string> tp = std::make_tuple(10, 'a', std::string("bcd"));
    std::stringstream ss;
    mtl::for_each(tp, [&ss](auto item) { ss << item;});
    std::string result = "10abcd";
    REQUIRE_EQ(ss.str(), result);
}


TEST_CASE("mtl::for_each with std::tuple of different types, ref")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "10abcd";
    }

    std::string combined_result;

    std::vector<std::tuple<int, char, std::string>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, 'a', std::string("bcd"));
        vt.emplace_back(tp);
    }
    

    for(auto& t : vt)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "10abcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}

TEST_CASE("mtl::for_each with std::tuple of different types, const ref")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "10abcd";
    }

    std::string combined_result;

    std::vector<std::tuple<int, char, std::string>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, 'a', std::string("bcd"));
        vt.emplace_back(tp);
    }
    

    for(const auto& t : vt)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "10abcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}

TEST_CASE("mtl::for_each with std::tuple of different types, modify")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "20aabcdbcd";
    }

    std::string combined_result;

    std::vector<std::tuple<int, std::string, std::string>> vt;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_tuple(10, "a", std::string("bcd"));
        vt.emplace_back(tp);
    }

    // modify elements
    for(auto& t : vt)
    {
        mtl::for_each(t, [](auto& item) { item += item; });
    }
    

    for(auto& t : vt)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "20aabcdbcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}




TEST_CASE("mtl::for_each with std::pair of integers")
{
    auto p = std::pair<int, int>(70 , 30);
    int total = 0;
    mtl::for_each(p, [&total](auto num) { total += num;});
    REQUIRE_EQ(total, 100);
}

TEST_CASE("mtl::for_each with const std::pair of integers")
{
    const std::pair<int, int> p = std::pair<int, int>(70 , 30);
    int total = 0;
    mtl::for_each(p, [&total](auto num) { total += num;});
    REQUIRE_EQ(total, 100);
}

TEST_CASE("mtl::for_each with std::pair of integers, ref")
{
    const int items = 10;
    const int desired_result = items * 100;
    int grand_total = 0;
    std::vector<std::pair<int, int>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::pair<int, int>(35, 65);
        vp.emplace_back(tp);
    }
    
    for(auto& t : vp)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 100);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}

TEST_CASE("mtl::for_each with std::pair of integers, const ref")
{
    const int items = 10;
    const int desired_result = items * 100;
    int grand_total = 0;
    std::vector<std::pair<int, int>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::pair<int, int>(35, 65);
        vp.emplace_back(tp);
    }
    
    for(auto& t : vp)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 100);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}

TEST_CASE("mtl::for_each with std::pair of integers, modify")
{
    const int items = 10;
    const int desired_result = items * 1000;
    int grand_total = 0;
    std::vector<std::pair<int, int>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::pair<int, int>(35, 65);
        vp.emplace_back(tp);
    }

    // modify elements
    for(auto& t : vp)
    {
        mtl::for_each(t, [](auto& num) { num = num * 10; });
    }
    
    for(const auto& t : vp)
    {
        int total = 0;
        mtl::for_each(t, [&total](auto num) { total += num;});
        REQUIRE_EQ(total, 1000);
        grand_total += total;
    }
    REQUIRE_EQ(grand_total, desired_result);
}



TEST_CASE("mtl::for_each with std::pair of different types")
{
    auto tp = std::make_pair(10, std::string("abcd"));
    std::stringstream ss;
    mtl::for_each(tp, [&ss](auto item) { ss << item;});
    std::string result = "10abcd";
    REQUIRE_EQ(ss.str(), result);
}

TEST_CASE("mtl::for_each with const std::pair of different types")
{
    const std::pair<int, std::string> tp = std::make_pair(10, std::string("abcd"));
    std::stringstream ss;
    mtl::for_each(tp, [&ss](auto item) { ss << item;});
    std::string result = "10abcd";
    REQUIRE_EQ(ss.str(), result);
}


TEST_CASE("mtl::for_each with std::pair of different types, ref")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "10abcd";
    }

    std::string combined_result;

    std::vector<std::pair<int, std::string>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_pair(10, std::string("abcd"));
        vp.emplace_back(tp);
    }
    

    for(auto& t : vp)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "10abcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}

TEST_CASE("mtl::for_each with std::pair of different types, const ref")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "10abcd";
    }

    std::string combined_result;

    std::vector<std::pair<int, std::string>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_pair(10, std::string("abcd"));
        vp.emplace_back(tp);
    }
    

    for(const auto& t : vp)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "10abcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}

TEST_CASE("mtl::for_each with std::pair of different types, modify")
{
    const int items = 10;
    
    std::string desired_result;
    for(int i = 0; i < items; i++)
    {
        desired_result += "20abcdabcd";
    }

    std::string combined_result;

    std::vector<std::pair<int, std::string>> vp;
    for(int i = 0; i < items; i++)
    {
        auto tp = std::make_pair(10, std::string("abcd"));
        vp.emplace_back(tp);
    }

    // modify elements
    for(auto& t : vp)
    {
        mtl::for_each(t, [](auto& item) { item += item; });
    }
    

    for(auto& t : vp)
    {
        std::stringstream ss;
        mtl::for_each(t, [&ss](auto item) { ss << item;});
        std::string result = "20abcdabcd";
        REQUIRE_EQ(ss.str(), result);
        combined_result += ss.str();
    }

    REQUIRE_EQ(combined_result, desired_result);
}

// ------------------------------------------------------------------------------------------------
// mtl::for_adj_pairs
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::for_adj_pairs for empty std::vector<int>, accumulation")
{

    std::vector<int> vi;
    int result = 0;
    int total = 0;
    mtl::for_adj_pairs(vi.begin(), vi.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
    REQUIRE_EQ(vi.empty(), true);
    REQUIRE_EQ(total, result);
}

TEST_CASE("mtl::for_adj_pairs for std::vector<int>, accumulation")
{

    std::vector<int> vi { 1, 2, 3, 4, 5 };
    int result = 3 + 5 + 7 + 9;
    int total = 0;
    mtl::for_adj_pairs(vi.begin(), vi.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
    REQUIRE_EQ(total, result);
}

TEST_CASE("mtl::for_adj_pairs for std::vector<int>")
{
    std::vector<int> vi { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };
    mtl::for_adj_pairs(vi.begin(), vi.end(), [](auto rhs, auto lhs)
                       {
                          REQUIRE_EQ((rhs+lhs), 3);
                       });

}

TEST_CASE("mtl::for_adj_pairs for std::vector<std::string>")
{
    std::vector<std::string> vs { "aa", "b", "cc", "d", "ee" };
    mtl::for_adj_pairs(vs.begin(), vs.end(), [](auto rhs, auto lhs)
                       {
                          std::string combined = rhs + lhs;
                          REQUIRE_EQ(combined.size(), static_cast<size_t>(3));
                       });

}


TEST_CASE("mtl::for_adj_pairs for std::list<int>, accumulation")
{

    std::list<int> li { 1, 2, 3, 4, 5 };
    int result = 3 + 5 + 7 + 9;
    int total = 0;
    mtl::for_adj_pairs(li.begin(), li.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
    REQUIRE_EQ(total, result);
}

TEST_CASE("mtl::for_adj_pairs for std::list<int>")
{
    std::list<int> li { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 };
    mtl::for_adj_pairs(li.begin(), li.end(), [](auto rhs, auto lhs)
                       {
                          REQUIRE_EQ((rhs+lhs), 3);
                       });

}

TEST_CASE("mtl::for_adj_pairs for std::list<std::string>")
{
    std::list<std::string> ls { "aa", "b", "cc", "d", "ee" };
    mtl::for_adj_pairs(ls.begin(), ls.end(), [](auto rhs, auto lhs)
                       {
                          std::string combined = rhs + lhs;
                          REQUIRE_EQ(combined.size(), static_cast<size_t>(3));
                       });

}


// ------------------------------------------------------------------------------------------------
// mtl::for_all_pairs
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::for_all_pairs for empty std::vector<int>, accumulation")
{
    std::vector<int> vi;
    int result = 0;
    int total = 0;
    mtl::for_all_pairs(vi.begin(), vi.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
   REQUIRE_EQ(vi.empty(), true);
   REQUIRE_EQ(total, result);
}

TEST_CASE("mtl::for_all_pairs for std::vector<int>, accumulation")
{
    std::vector<int> vi { 1, 2, 3, 4 };
    int result = (1 + 2 + 1 + 3 + 1 + 4) + (2 + 3 + 2 + 4) + ( 3 + 4);
    int total = 0;
    mtl::for_all_pairs(vi.begin(), vi.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
   REQUIRE_EQ(total, result);
}


TEST_CASE("mtl::for_all_pairs for std::vector<int>, even")
{
    std::vector<int> vi { 2, 4, 6, 8, 10 };
    mtl::for_all_pairs(vi.begin(), vi.end(), [](auto rhs, auto lhs)
                       {
                          REQUIRE_EQ(((rhs+lhs) % 2 == 0), true);
                       });

}

TEST_CASE("mtl::for_all_pairs for std::vector<std::string>")
{
    std::vector<std::string> vs { "aa", "bb", "cc" };
    std::string combined;
    std::string result = "aabbaaccbbcc";
    mtl::for_all_pairs(vs.begin(), vs.end(), [&combined](auto rhs, auto lhs)
                       {
                           combined += rhs + lhs;
                       });
    REQUIRE_EQ(combined, result);
}


TEST_CASE("mtl::for_all_pairs for std::list<int>, accumulation")
{
    std::list<int> li { 1, 2, 3, 4 };
    int result = (1 + 2 + 1 + 3 + 1 + 4) + (2 + 3 + 2 + 4) + ( 3 + 4);
    int total = 0;
    mtl::for_all_pairs(li.begin(), li.end(), [&total](auto rhs, auto lhs)
                       {
                          total += rhs + lhs;
                       });
   REQUIRE_EQ(total, result);
}


TEST_CASE("mtl::for_all_pairs for std::list<int>, even")
{
    std::list<int> li { 2, 4, 6, 8, 10 };
    mtl::for_all_pairs(li.begin(), li.end(), [](auto rhs, auto lhs)
                       {
                          REQUIRE_EQ(((rhs+lhs) % 2 == 0), true);
                       });

}

TEST_CASE("mtl::for_all_pairs for std::list<std::string>")
{
    std::list<std::string> ls { "aa", "bb", "cc" };
    std::string combined;
    std::string result = "aabbaaccbbcc";
    mtl::for_all_pairs(ls.begin(), ls.end(), [&combined](auto rhs, auto lhs)
                       {
                           combined += rhs + lhs;
                       });
    REQUIRE_EQ(combined, result);
}





// ------------------------------------------------------------------------------------------------
// mtl::fill_range
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::fill_range with empty range")
{
    constexpr size_t size = 10;
    std::vector<int> sequence;
    std::vector<int> vi(size, 1);
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::ptrdiff_t ones = std::count(vi.begin(), vi.end(), 1);
    CHECK_EQ(sequence.empty(), true);
    CHECK_EQ(vi.empty(), false);
    CHECK_EQ(vi.size(), size);
    CHECK_EQ(static_cast<size_t>(ones), size);
}

TEST_CASE("mtl::fill_range with empty container")
{
    constexpr size_t size = 0;
    std::vector<int> sequence {1, 2, 3, 4, 5};
    std::vector<int> vi;
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::ptrdiff_t ones = std::count(vi.begin(), vi.end(), 1);
    CHECK_EQ(sequence.empty(), false);
    CHECK_EQ(vi.empty(), true);
    CHECK_EQ(vi.size(), size);
    CHECK_EQ(static_cast<size_t>(ones), size);
}

TEST_CASE("mtl::fill_range with empty range and empty container")
{
    constexpr size_t size = 0;
    std::vector<int> sequence;
    std::vector<int> vi;
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::ptrdiff_t ones = std::count(vi.begin(), vi.end(), 1);
    CHECK_EQ(sequence.empty(), true);
    CHECK_EQ(vi.empty(), true);
    CHECK_EQ(vi.size(), size);
    CHECK_EQ(static_cast<size_t>(ones), size);
}

TEST_CASE("mtl::fill_range with smaller input larger ouput")
{
    constexpr size_t size = 50;
    std::vector<int> sequence {1, 2, 3, 4, 5};
    std::vector<int> vi(size);
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::ptrdiff_t ones = std::count(vi.begin(), vi.end(), 1);
    std::ptrdiff_t twos = std::count(vi.begin(), vi.end(), 2);
    std::ptrdiff_t threes = std::count(vi.begin(), vi.end(), 3);
    std::ptrdiff_t fours = std::count(vi.begin(), vi.end(), 4);
    std::ptrdiff_t fives = std::count(vi.begin(), vi.end(), 5);
    REQUIRE_EQ(ones, 10);
    REQUIRE_EQ(twos, 10);
    REQUIRE_EQ(threes, 10);
    REQUIRE_EQ(fours,  10);
    REQUIRE_EQ(fives,  10);
}

TEST_CASE("mtl::fill_range with same size input and ouput")
{
    std::vector<int> sequence {1, 2, 3, 4, 5};
    std::vector<int> vi(sequence.size());
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    REQUIRE_EQ(sequence.size(), vi.size());
    REQUIRE_EQ((sequence == vi), true);
}

TEST_CASE("mtl::fill_range with larger input and smaller ouput")
{
    std::vector<int> sequence {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<int> vi(5);
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::vector<int> match {1, 2, 3, 4, 5};
    REQUIRE_NE(vi.size(), sequence.size());
    REQUIRE_EQ(vi.size(), match.size());
    REQUIRE_EQ((match  == vi), true);
}

TEST_CASE("mtl::fill_range with std::string with smaller input larger ouput")
{
    constexpr size_t size = 50;
    std::vector<std::string> sequence {"1", "2", "3", "4", "5"};
    std::vector<std::string> vi(size);
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::ptrdiff_t ones = std::count(vi.begin(), vi.end(), std::string("1"));
    std::ptrdiff_t twos = std::count(vi.begin(), vi.end(), std::string("2"));
    std::ptrdiff_t threes = std::count(vi.begin(), vi.end(), std::string("3"));
    std::ptrdiff_t fours = std::count(vi.begin(), vi.end(), std::string("4"));
    std::ptrdiff_t fives = std::count(vi.begin(), vi.end(), std::string("5"));
    REQUIRE_EQ(ones, 10);
    REQUIRE_EQ(twos, 10);
    REQUIRE_EQ(threes, 10);
    REQUIRE_EQ(fours,  10);
    REQUIRE_EQ(fives,  10);
}

TEST_CASE("mtl::fill_range with std::string with same size input and ouput")
{
    std::vector<std::string> sequence {"1", "2", "3", "4", "5"};
    std::vector<std::string> vi(sequence.size());
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    REQUIRE_EQ(sequence.size(), vi.size());
    REQUIRE_EQ((sequence == vi), true);
}

TEST_CASE("mtl::fill_range with std::string with larger input and smaller ouput")
{
    std::vector<std::string> sequence {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    std::vector<std::string> vi(5);
    mtl::fill_range(sequence.begin(), sequence.end(), vi.begin(), vi.end());
    std::vector<std::string> match {"1", "2", "3", "4", "5"};
    REQUIRE_NE(vi.size(), sequence.size());
    REQUIRE_EQ(vi.size(), match.size());
    REQUIRE_EQ((match == vi), true);
}




// ------------------------------------------------------------------------------------------------
// mtl::range
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::range with empty range")
{
    int total = 0;
    for(auto number : mtl::range(0, 0)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(1, 1)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(2, 2)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(3, 3)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(5, 5)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(555, 555)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(-1, -1)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(-2, -2)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(-3, -3)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(-5, -5)) { total += number; }
    REQUIRE_EQ(total, 0); 

    for(auto number : mtl::range(-555, -555)) { total += number; }
    REQUIRE_EQ(total, 0);
}

TEST_CASE("mtl::range with int")
{
    int total = 0;
    for(auto number : mtl::range(1, 5)) { total += number; }
    REQUIRE_EQ(total, 10); 
}

TEST_CASE("mtl::range with float")
{
    float total = 0.0f;
    for(auto number : mtl::range(1.0f, 5.0f)) { total += number; }
    // approximate equality instead of equality because although the total's decimal part is 0 
    // gcc/clang with the flag -Wfloat-equal may complain about floating point comparison
    REQUIRE_LT(total, 10.0f + 0.01f); 
    REQUIRE_GT(total, 10.0f - 0.01f); 
}

TEST_CASE("mtl::range with double")
{
    double total = 0.0;
    for(auto number : mtl::range(1.0, 5.0)) { total += number; }
    // approximate equality instead of equality because although the total's decimal part is 0 
    // gcc/clang with the flag -Wfloat-equal may complain about floating point comparison
    REQUIRE_LT(total, 10.0 + 0.01); 
    REQUIRE_GT(total, 10.0 - 0.01);  
}

TEST_CASE("mtl::range with step")
{
    int total = 0;
    for(auto number : mtl::range(10, 50, 2)) { total += number; }
    REQUIRE_EQ(total, 580); 
}

TEST_CASE("mtl::range with positive to negative with negative step")
{
    int total = 0;
    for(auto number : mtl::range(10, -20, -1)) { total += number; }
    REQUIRE_EQ(total, -155); 
}

TEST_CASE("mtl::range with negative to negative with negative step")
{
    int total = 0;
    for(auto number : mtl::range(-10, -20, -2)) { total += number; }
    REQUIRE_EQ(total, -90); 
}

TEST_CASE("mtl::range with std::copy/std::ostream_iterator")
{
    auto r = mtl::range(10, 110, 10);
    std::stringstream ss;
    std::copy(r.begin(), r.end(), std::ostream_iterator<int>(ss, ", "));
    std::string result = "10, 20, 30, 40, 50, 60, 70, 80, 90, 100, ";
    REQUIRE_EQ(ss.str(), result);
}  

TEST_CASE("mtl::range with std::copy/std::back_insert_iterator")
{
    auto r = mtl::range(10, 110, 10);
    std::vector<int> values;
    std::copy(r.begin(), r.end(), std::back_insert_iterator<std::vector<int>>(values));
    std::vector<int> result {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    REQUIRE_EQ(values.size(), result.size());
    REQUIRE_EQ((values == result), true);
} 


TEST_CASE("mtl::range check equality and enequality operators")
{
    // positive to positive number with positive steppings
    auto one_three  = mtl::range(1, 3);
    auto one_three_ = mtl::range(1, 3);
    auto two_three  = mtl::range(2, 3);
    CHECK_EQ((one_three == one_three_), true);
    CHECK_EQ((one_three != one_three_), false);
    CHECK_EQ((one_three == two_three), false);
    CHECK_EQ((one_three != two_three), true);

    auto zero_ten    = mtl::range(0, 10);
    auto zero_ten_   = mtl::range(0, 10);
    auto zero_twenty = mtl::range(0, 20);
    CHECK_EQ((zero_ten == zero_ten_), true);
    CHECK_EQ((zero_ten != zero_ten_), false);
    CHECK_EQ((zero_ten == zero_twenty), false);
    CHECK_EQ((zero_ten != zero_twenty), true);
    
    auto step_two    = mtl::range(0, 10, 2);
    auto step_two_   = mtl::range(0, 10, 2);
    auto step_three  = mtl::range(0, 10, 3);
    CHECK_EQ((step_two == step_two_), true);
    CHECK_EQ((step_two != step_two_), false);
    CHECK_EQ((step_two == step_three), false);
    CHECK_EQ((step_two != step_three), true);



    // positive to negative number with negative steppings
    auto mone_three  = mtl::range(-1, -3, -1);
    auto mone_three_ = mtl::range(-1, -3, -1);
    auto mtwo_three  = mtl::range(-2, -3, -1);
    CHECK_EQ((mone_three == mone_three_), true);
    CHECK_EQ((mone_three != mone_three_), false);
    CHECK_EQ((mone_three == mtwo_three), false);
    CHECK_EQ((mone_three != mtwo_three), true);

    auto mfive_ten    = mtl::range(-5, -10, -1);
    auto mfive_ten_   = mtl::range(-5, -10, -1);
    auto mfive_twenty = mtl::range(-5, -20, -1);
    CHECK_EQ((mfive_ten == mfive_ten_), true);
    CHECK_EQ((mfive_ten != mfive_ten_), false);
    CHECK_EQ((mfive_ten == mfive_twenty), false);
    CHECK_EQ((mfive_ten != mfive_twenty), true);
    
    auto mstep_two    = mtl::range(-10, -20, -2);
    auto mstep_two_   = mtl::range(-10, -20, -2);
    auto mstep_three  = mtl::range(-10, -20, -3);
    CHECK_EQ((mstep_two == mstep_two_), true);
    CHECK_EQ((mstep_two != mstep_two_), false);
    CHECK_EQ((mstep_two == mstep_three), false);
    CHECK_EQ((mstep_two != mstep_three), true);



    // negative to positive numbers with positive steppings
    auto minus_133  = mtl::range(-133, 199);
    auto minus_133_ = mtl::range(-133, 199);
    auto minus_134  = mtl::range(-134, 199);
    CHECK_EQ((minus_133 == minus_133_), true);
    CHECK_EQ((minus_133 != minus_133_), false);
    CHECK_EQ((minus_133 == minus_134), false);
    CHECK_EQ((minus_133 != minus_134), true);

    auto minus_233_10  = mtl::range(-233, 10);
    auto minus_233_10_ = mtl::range(-233, 10);
    auto minus_233_11  = mtl::range(-233, 11);
    CHECK_EQ((minus_233_10 == minus_233_10_), true);
    CHECK_EQ((minus_233_10 != minus_233_10_), false);
    CHECK_EQ((minus_233_10 == minus_233_11), false);
    CHECK_EQ((minus_233_10 != minus_233_11), true);

    auto minus_333_two_step   = mtl::range(-333, 10, 2);
    auto minus_333_two_step_  = mtl::range(-333, 10, 2);
    auto minus_333_three_step = mtl::range(-333, 10, 3);
    CHECK_EQ((minus_333_two_step == minus_333_two_step_), true);
    CHECK_EQ((minus_333_two_step != minus_333_two_step_), false);
    CHECK_EQ((minus_333_two_step == minus_333_three_step), false);
    CHECK_EQ((minus_333_two_step != minus_333_three_step), true);



    // negative to negative numbers with negative steppings
    auto minus_44  = mtl::range(-44, -777, -1);
    auto minus_44_ = mtl::range(-44, -777, -1);
    auto minus_45  = mtl::range(-45, -777, -1);
    CHECK_EQ((minus_44 == minus_44_), true);
    CHECK_EQ((minus_44 != minus_44_), false);
    CHECK_EQ((minus_44 == minus_45), false);
    CHECK_EQ((minus_44 != minus_45), true);

    auto minus_55     = mtl::range(-55, -555, -1);
    auto minus_55_    = mtl::range(-55, -555, -1);
    auto minus_55_556 = mtl::range(-55, -556, -1);
    CHECK_EQ((minus_55 == minus_55_), true);
    CHECK_EQ((minus_55 != minus_55_), false);
    CHECK_EQ((minus_55 == minus_55_556), false);
    CHECK_EQ((minus_55 != minus_55_556), true);

    auto minus_66_m2_step   = mtl::range(-66, -100, -2);
    auto minus_66_m2_step_  = mtl::range(-66, -100, -2);
    auto minus_66_m4_step   = mtl::range(-66, -100, -4);
    CHECK_EQ((minus_66_m2_step == minus_66_m2_step_), true);
    CHECK_EQ((minus_66_m2_step != minus_66_m2_step_), false);
    CHECK_EQ((minus_66_m2_step == minus_66_m4_step), false);
    CHECK_EQ((minus_66_m2_step != minus_66_m4_step), true);
}


TEST_CASE("mtl::range with erroneous values that should throw")
{
    // create a variable for mtl::range type
    auto bad_range = mtl::range(0, 1);
    // this is the same as saying mtl::range(10, -20, 1) which of course is erroneous and throws
    REQUIRE_THROWS_AS(bad_range = mtl::range(10, -20),     std::invalid_argument);
    REQUIRE_THROWS_AS(bad_range = mtl::range(10, -20,  2), std::invalid_argument);
    REQUIRE_THROWS_AS(bad_range = mtl::range(10, -20, 10), std::invalid_argument);
    REQUIRE_THROWS_AS(bad_range = mtl::range(-10, 20, -2), std::invalid_argument);
    REQUIRE_THROWS_AS(bad_range = mtl::range(10, 20,  -2), std::invalid_argument);

    // because all cases that throwed shouldn't affect the resulting element we can check that the
    // original element is unaffected
    auto good_range = mtl::range(0, 1);

    REQUIRE_EQ((bad_range == good_range), true);
    REQUIRE_EQ((bad_range != good_range), false);
}
