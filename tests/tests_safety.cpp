// tests by Michael Trikergiotis
// 31/05/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 

#include <algorithm>   // std::equal, std::all_of, std::equal
#include <iterator>    // std::next
#include <vector>      // std::vector
#include <deque>       // std::deque
#include <array>       // std::array
#include <list>        // std::list
#include <string>      // std::string
#include <numeric>     // std::iota


// Disable some of the asserts in mtl so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/safety.hpp" 
// mtl::safe_copy, mtl::safe_copy_n


// ------------------------------------------------------------------------------------------------
// mtl::safe_copy
// ------------------------------------------------------------------------------------------------


// same type containers

TEST_CASE("mtl::safe_copy with empty containers of the same type")
{
    constexpr size_t size = 0;
    std::vector<int> vi1(size);
    std::array<int, size> ai1 {};
    std::deque<int> di1(size);
    std::list<int> li1(size);

    std::vector<int> vi2(size);
    std::array<int, size> ai2 {};
    std::deque<int> di2(size);
    std::list<int> li2(size);

    bool success = mtl::safe_copy(vi1, vi2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai1, ai2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);

    REQUIRE_EQ(vi1.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai1.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di1.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li1.size(), size);
    REQUIRE_EQ(li2.size(), size);

    REQUIRE_EQ(vi1.size(), vi2.size());
    REQUIRE_EQ(ai1.size(), ai2.size());
    REQUIRE_EQ(di1.size(), di2.size());
    REQUIRE_EQ(li1.size(), li2.size());

    REQUIRE_EQ((vi1 == vi2), true);
    REQUIRE_EQ((ai1 == ai2), true);
    REQUIRE_EQ((di1 == di2), true);
    REQUIRE_EQ((li1 == li2), true);
}


TEST_CASE("mtl::safe_copy with containers of the same type")
{
    constexpr size_t size = 100;
    std::vector<int> vi1(size);
    std::array<int, size> ai1 {};
    std::deque<int> di1(size);
    std::list<int> li1(size);
    std::iota(vi1.begin(), vi1.end(), 10);
    std::iota(ai1.begin(), ai1.end(), 10);
    std::iota(di1.begin(), di1.end(), 10);
    std::iota(li1.begin(), li1.end(), 10);

    std::vector<int> vi2(size);
    std::array<int, size> ai2 {};
    std::deque<int> di2(size);
    std::list<int> li2(size);

    bool success = mtl::safe_copy(vi1, vi2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai1, ai2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(li1, li2);
    REQUIRE_EQ(success, true);

    REQUIRE_EQ(vi1.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai1.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di1.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li1.size(), size);
    REQUIRE_EQ(li2.size(), size);

    REQUIRE_EQ(vi1.size(), vi2.size());
    REQUIRE_EQ(ai1.size(), ai2.size());
    REQUIRE_EQ(di1.size(), di2.size());
    REQUIRE_EQ(li1.size(), li2.size());

    REQUIRE_EQ((vi1 == vi2), true);
    REQUIRE_EQ((ai1 == ai2), true);
    REQUIRE_EQ((di1 == di2), true);
    REQUIRE_EQ((li1 == li2), true);
}

TEST_CASE("mtl::safe_copy with containers of the same type but invalid size")
{
    constexpr size_t size = 100;
    std::vector<int> vi1(size);
    std::array<int, size> ai1 {};
    std::deque<int> di1(size);
    std::list<int> li1(size);
    std::iota(vi1.begin(), vi1.end(), 10);
    std::iota(ai1.begin(), ai1.end(), 10);
    std::iota(di1.begin(), di1.end(), 10);
    std::iota(li1.begin(), li1.end(), 10);

    constexpr size_t smaller_size = size - 1;

    // make sure the the containers are filled with 0s
    std::vector<int> vi2(smaller_size, 0);
    std::deque<int> di2(smaller_size, 0);
    std::list<int> li2(smaller_size, 0);
    std::array<int, smaller_size> ai2 {};
    ai2.fill(0);

    // the mtl::safe_copy will fail and return false because the destination is smaller
    bool success = mtl::safe_copy(vi1, vi2);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(ai1, ai2);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(li1, li2);
    REQUIRE_EQ(success, false);

    REQUIRE_EQ(vi1.size(), size);  
    REQUIRE_EQ(ai1.size(), size);
    REQUIRE_EQ(di1.size(), size);
    REQUIRE_EQ(li1.size(), size);

    REQUIRE_EQ(vi2.size(), smaller_size);
    REQUIRE_EQ(ai2.size(), smaller_size);
    REQUIRE_EQ(di2.size(), smaller_size);
    REQUIRE_EQ(li2.size(), smaller_size);
    
    

    REQUIRE_NE(vi1.size(), vi2.size());
    REQUIRE_NE(ai1.size(), ai2.size());
    REQUIRE_NE(di1.size(), di2.size());
    REQUIRE_NE(li1.size(), li2.size());

    REQUIRE_EQ((vi1 == vi2), false);
    // we have to use std::equal because std::arrays of difference size can't be compared with ==,
    // it is safe to use std::equal on different sized containers because we are using the C++ 14
    // std::equal version where you pass 4 iterators
    REQUIRE_EQ((std::equal(ai1.begin(), ai1.end(), ai2.begin(), ai2.end())) , false);
    REQUIRE_EQ((di1 == di2), false);
    REQUIRE_EQ((li1 == li2), false);

    // check that all the destination containers still contain only zeros
    REQUIRE_EQ((std::all_of(vi2.begin(), vi2.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(ai2.begin(), ai2.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(di2.begin(), di2.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(li2.begin(), li2.end(), [](auto x) { return x == 0; })), true);
}




TEST_CASE("mtl::safe_copy with empty containers of std::string")
{
    constexpr size_t size = 0;
    std::vector<std::string> vi1(size);
    std::array<std::string, size> ai1 {};
    std::deque<std::string> di1(size);
    std::list<std::string> li1(size);

    std::vector<std::string> vi2(size);
    std::array<std::string, size> ai2 {};
    std::deque<std::string> di2(size);
    std::list<std::string> li2(size);

    bool success = mtl::safe_copy(vi1, vi2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai1, ai2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);

    REQUIRE_EQ(vi1.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai1.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di1.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li1.size(), size);
    REQUIRE_EQ(li2.size(), size);

    REQUIRE_EQ(vi1.size(), vi2.size());
    REQUIRE_EQ(ai1.size(), ai2.size());
    REQUIRE_EQ(di1.size(), di2.size());
    REQUIRE_EQ(li1.size(), li2.size());

    REQUIRE_EQ((vi1 == vi2), true);
    REQUIRE_EQ((ai1 == ai2), true);
    REQUIRE_EQ((di1 == di2), true);
    REQUIRE_EQ((li1 == li2), true);
}


TEST_CASE("mtl::safe_copy with containers of std::string")
{
    constexpr size_t size = 3;
    std::vector<std::string> vi1 { "Bill", "Nick", "Maria"};
    std::array<std::string, size> ai1 { "Bill", "Nick", "Maria"};
    std::deque<std::string> di1 { "Bill", "Nick", "Maria"};
    std::list<std::string> li1 { "Bill", "Nick", "Maria"};


    std::vector<std::string> vi2 (size);
    std::array<std::string, size> ai2 {};
    std::deque<std::string> di2 (size);
    std::list<std::string> li2 (size);

    bool success = mtl::safe_copy(vi1, vi2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai1, ai2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di1, di2);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(li1, li2);
    REQUIRE_EQ(success, true);

    REQUIRE_EQ(vi1.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai1.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di1.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li1.size(), size);
    REQUIRE_EQ(li2.size(), size);

    REQUIRE_EQ(vi1.size(), vi2.size());
    REQUIRE_EQ(ai1.size(), ai2.size());
    REQUIRE_EQ(di1.size(), di2.size());
    REQUIRE_EQ(li1.size(), li2.size());

    REQUIRE_EQ((vi1 == vi2), true);
    REQUIRE_EQ((ai1 == ai2), true);
    REQUIRE_EQ((di1 == di2), true);
    REQUIRE_EQ((li1 == li2), true);
}


// different type containers


TEST_CASE("mtl::safe_copy with empty containers")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    bool success = mtl::safe_copy(vi, ai);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, di);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, li);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);


    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}

TEST_CASE("mtl::safe_copy with containers")
{
    constexpr size_t size = 100;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);
    std::iota(vi.begin(), vi.end(), 10);

    bool success = mtl::safe_copy(vi, ai);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, di);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, li);
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}




TEST_CASE("mtl::safe_copy with empty containers of std::string")
{
    constexpr size_t size = 0;
    std::vector<std::string> vi(size);
    std::array<std::string, size> ai {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);

    bool success = mtl::safe_copy(vi, ai);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, di);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, li);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);


    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy with containers of std::string")
{
    constexpr size_t size = 3;
    std::vector<std::string> vi { "Bill", "Nick", "Maria"};
    std::array<std::string, size> ai {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);


    bool success = mtl::safe_copy(vi, ai);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, di);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi, li);
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::safe_copy with iterators
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::safe_copy with empty containers of the same type using iterators ")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::vector<int> vi2(size);
    std::array<int, size> ai {};
    std::array<int, size> ai2 {};
    std::deque<int> di(size);
    std::deque<int> di2(size);
    std::list<int> li(size);
    std::list<int> li2(size);

    bool success = mtl::safe_copy(vi.begin(), vi.end(), vi2.begin(), vi2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai.begin(), ai.end(), ai2.begin(), ai2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di.begin(), di.end(), di2.begin(), di2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(li.begin(), li.end(), li2.begin(), li2.end());
    REQUIRE_EQ(success, true);
    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li2.size(), size);

    // make sure the originals and the copies contain the same elements
    REQUIRE_EQ((vi == vi2), true);
    REQUIRE_EQ((ai == ai2), true);
    REQUIRE_EQ((di == di2), true);
    REQUIRE_EQ((li == li2), true);
}

TEST_CASE("mtl::safe_copy with empty containers using iterators ")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    bool success = mtl::safe_copy(vi.begin(), vi.end(), ai.begin(), ai.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), di.begin(), di.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), li.begin(), li.end());
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy with containers of the same type using iterators ")
{
    constexpr size_t size = 20;
    std::vector<int> vi(size);
    std::vector<int> vi2(size);
    std::array<int, size> ai {};
    std::array<int, size> ai2 {};
    std::deque<int> di(size);
    std::deque<int> di2(size);
    std::list<int> li(size);
    std::list<int> li2(size);

    // fill the original containers with some numbers
    std::iota(vi.begin(), vi.end(), 100);
    std::iota(ai.begin(), ai.end(), 100);
    std::iota(di.begin(), di.end(), 100);
    std::iota(li.begin(), li.end(), 100);


    bool success = mtl::safe_copy(vi.begin(), vi.end(), vi2.begin(), vi2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(ai.begin(), ai.end(), ai2.begin(), ai2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(di.begin(), di.end(), di2.begin(), di2.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(li.begin(), li.end(), li2.begin(), li2.end());
    REQUIRE_EQ(success, true);
    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li2.size(), size);

    // make sure the originals and the copies contain the same elements
    REQUIRE_EQ((vi == vi2), true);
    REQUIRE_EQ((ai == ai2), true);
    REQUIRE_EQ((di == di2), true);
    REQUIRE_EQ((li == li2), true);
}

TEST_CASE("mtl::safe_copy with containers of the same type passing incorrect iterators")
{
    constexpr size_t size = 20;
    
    std::vector<int> vi(size, 0);
    std::vector<int> vi2(size, 0);
    std::array<int, size> ai {};
    std::array<int, size> ai2 {};  
    ai.fill(0);
    ai2.fill(0);

    // fill the original containers with some numbers
    std::iota(vi.begin(), vi.end(), 100);
    std::iota(ai.begin(), ai.end(), 100);

    // with incorrect iterator for input
    bool success = mtl::safe_copy(vi.end(), vi.begin(), vi2.begin(), vi2.end());
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(ai.end(), ai.begin(), ai2.begin(), ai2.end());
    REQUIRE_EQ(success, false);
    
    
    // with incorrect iterator for output
    success = mtl::safe_copy(vi.begin(), vi.end(), vi2.end(), vi2.begin());
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(ai.begin(), ai.end(), ai2.end(), ai2.begin());
    REQUIRE_EQ(success, false);
    


    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    

    REQUIRE_EQ((vi == vi2), false);
    REQUIRE_EQ((ai == ai2), false);
    
    // make sure the original's still are zeroed out
    REQUIRE_EQ((std::all_of(vi2.begin(), vi2.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(ai2.begin(), ai2.end(), [](auto x) { return x == 0; })), true);
}

TEST_CASE("mtl::safe_copy with same type containers using iterators, destination invalid size")
{
    constexpr size_t size = 10;
    
    std::vector<int> vi(size);
    std::deque<int> di(size);
    std::list<int> li(size);
    std::array<int, size> ai {};

    // make sure the originals are filled with
    constexpr size_t smaller_size = 9;
    std::vector<int> vi2(smaller_size);
    std::array<int, smaller_size> ai2 {};
    std::deque<int> di2(smaller_size);
    std::list<int> li2(smaller_size);

    // fill the original containers with some numbers
    std::iota(vi.begin(), vi.end(), 100);
    std::iota(ai.begin(), ai.end(), 100);
    std::iota(di.begin(), di.end(), 100);
    std::iota(li.begin(), li.end(), 100);

    // the mtl::safe_copy will fail and return false because the destination is smaller
    bool success = mtl::safe_copy(vi.begin(), vi.end(), vi2.begin(), vi2.end());
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(ai.begin(), ai.end(), ai2.begin(), ai2.end());
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(di.begin(), di.end(), di2.begin(), di2.end());
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy(li.begin(), li.end(), li2.begin(), li2.end());
    REQUIRE_EQ(success, false);
    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), smaller_size);
    REQUIRE_EQ(ai2.size(), smaller_size);
    REQUIRE_EQ(di2.size(), smaller_size);
    REQUIRE_EQ(li2.size(), smaller_size);

    REQUIRE_EQ((vi == vi2), false);
    // we have to use std::equal because std::arrays of difference size can't be compared with ==,
    // it is safe to use std::equal on different sized containers because we are using the C++ 14
    // std::equal version where you pass 4 iterators
    REQUIRE_EQ((std::equal(ai.begin(), ai.end(), ai2.begin(), ai2.end())) , false);
    REQUIRE_EQ((di == di2), false);
    REQUIRE_EQ((li == li2), false);
}


TEST_CASE("mtl::safe_copy with iterators")
{
    constexpr size_t size = 100;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);
    std::iota(vi.begin(), vi.end(), 10);

    bool success = mtl::safe_copy(vi.begin(), vi.end(), ai.begin(), ai.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), di.begin(), di.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), li.begin(), li.end());
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy with empty containers of std::string using iterators")
{
    constexpr size_t size = 0;
    std::vector<std::string> vi(size);
    std::array<std::string, size> ai {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);

    bool success = mtl::safe_copy(vi.begin(), vi.end(), ai.begin(), ai.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), di.begin(), di.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), li.begin(), li.end());
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy with iterators and std::string")
{
    constexpr size_t size = 3;
    std::vector<std::string> vi { "Bill", "Nick", "Maria"};
    std::array<std::string, size> ai  {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);

    bool success = mtl::safe_copy(vi.begin(), vi.end(), ai.begin(), ai.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), di.begin(), di.end());
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy(vi.begin(), vi.end(), li.begin(), li.end());
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::safe_copy_n
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::safe_copy_n with empty containers of the same type")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai  {};
    std::deque<int> di(size);
    std::list<int> li(size);

    std::vector<int> vi2(size);
    std::array<int, size> ai2  {};
    std::deque<int> di2(size);
    std::list<int> li2(size);

    bool success = mtl::safe_copy_n(vi, vi2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(ai, ai2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(di, di2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(li, li2, 0, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li2.size(), size);
    

    REQUIRE_EQ((vi == vi2), true);
    REQUIRE_EQ((ai == ai2), true);
    REQUIRE_EQ((li == li2), true);
    REQUIRE_EQ((li == li2), true);
}

TEST_CASE("mtl::safe_copy_n with containers of the same type")
{
    constexpr size_t size = 10;
    std::vector<int> vi(size);
    std::array<int, size> ai  {};
    std::deque<int> di(size);
    std::list<int> li(size);

    // fill the original containers with numbers
    std::iota(vi.begin(), vi.end(), 300);
    std::iota(ai.begin(), ai.end(), 300);
    std::iota(di.begin(), di.end(), 300);
    std::iota(li.begin(), li.end(), 300);

    std::vector<int> vi2(size);
    std::array<int, size> ai2 {};
    std::deque<int> di2(size);
    std::list<int> li2(size);

    bool success = mtl::safe_copy_n(vi, vi2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(ai, ai2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(di, di2, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(li, li2, 0, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), size);
    REQUIRE_EQ(ai2.size(), size);
    REQUIRE_EQ(di2.size(), size);
    REQUIRE_EQ(li2.size(), size);
    

    REQUIRE_EQ((vi == vi2), true);
    REQUIRE_EQ((ai == ai2), true);
    REQUIRE_EQ((li == li2), true);
    REQUIRE_EQ((li == li2), true);
}

TEST_CASE("mtl::safe_copy_n with containers of the same type, invalid destination size")
{
    constexpr size_t size = 10;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    // fill the original containers with numbers
    std::iota(vi.begin(), vi.end(), 300);
    std::iota(ai.begin(), ai.end(), 300);
    std::iota(di.begin(), di.end(), 300);
    std::iota(li.begin(), li.end(), 300);

    // make sure the destination containers are filled with zeros and the destination is smaller
    constexpr size_t smaller_size = 9;
    std::vector<int> vi2(smaller_size);
    std::array<int, smaller_size> ai2 {};
    std::deque<int> di2(smaller_size);
    std::list<int> li2(smaller_size);

    bool success = mtl::safe_copy_n(vi, vi2, 0, size);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(ai, ai2, 0, size);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(di, di2, 0, size);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(li, li2, 0, size);
    REQUIRE_EQ(success, false);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    REQUIRE_EQ(vi2.size(), smaller_size);
    REQUIRE_EQ(ai2.size(), smaller_size);
    REQUIRE_EQ(di2.size(), smaller_size);
    REQUIRE_EQ(li2.size(), smaller_size);
    

    REQUIRE_EQ((vi == vi2), false);
    // we have to use std::equal because std::arrays of difference size can't be compared with ==,
    // it is safe to use std::equal on different sized containers because we are using the C++ 14
    // std::equal version where you pass 4 iterators
    REQUIRE_EQ((std::equal(ai.begin(), ai.end(), ai2.begin(), ai2.end())) , false);
    REQUIRE_EQ((li == li2), false);
    REQUIRE_EQ((li == li2), false);
}

TEST_CASE("mtl::safe_copy_n with empty containers")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    bool success = mtl::safe_copy_n(vi, ai, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 0, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}

TEST_CASE("mtl::safe_copy_n with empty containers and invalid starting position but 0 size")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    bool success = mtl::safe_copy_n(vi, ai, 5, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 5, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 5, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}

TEST_CASE("mtl::safe_copy_n with empty containers and valid starting position but invalid size")
{
    constexpr size_t size = 0;
    // make sure everything is filled with zeros
    std::vector<int> vi(size, 0);
    std::deque<int> di(size, 0);
    std::list<int> li(size, 0);
    std::array<int, size> ai {};
    ai.fill(0);

    // fill the std::vector with some numbers
    std::iota(vi.begin(), vi.end(), 400);

    

    bool success = mtl::safe_copy_n(vi, ai, 0, size + 20);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, di, 0, size + 20);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, li, 0, size + 20);
    REQUIRE_EQ(success, false);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
}

TEST_CASE("mtl::safe_copy_n with invalid starting position")
{
    constexpr size_t size = 10;
    // make sure all containers are filled with zeros
    std::vector<int> vi(size, 0);
    std::deque<int> di(size, 0);
    std::list<int> li(size, 0);
    std::array<int, size> ai {};
    ai.fill(0);

    // fill the vector with some numbers
    std::iota(vi.begin(), vi.end(), 200);


    bool success = mtl::safe_copy_n(vi, ai, 10, size);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, di, 10, size);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, li, 10, size);
    REQUIRE_EQ(success, false);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), false);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), false);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), false);

    // make sure the other containers are still filled with zeros
    REQUIRE_EQ((std::all_of(ai.begin(), ai.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(di.begin(), di.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(li.begin(), li.end(), [](auto x) { return x == 0; })), true);
}



TEST_CASE("mtl::safe_copy_n with empty containers and more items than available")
{
    constexpr size_t size = 0;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);

    bool success = mtl::safe_copy_n(vi, ai, 0, size + 10);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, di, 0, size + 10);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, li, 0, size + 10);
    REQUIRE_EQ(success, false);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}

TEST_CASE("mtl::safe_copy_n with more items than available")
{
    constexpr size_t size = 10;
    // make sure all containers are filled with zeros
    std::vector<int> vi(size, 0);
    std::deque<int> di(size, 0);
    std::list<int> li(size, 0);
    std::array<int, size> ai {};
    ai.fill(0);

    // fill the vector with some numbers
    std::iota(vi.begin(), vi.end(), 200);


    bool success = mtl::safe_copy_n(vi, ai, 0, size + 100);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, di, 0, size + 100);
    REQUIRE_EQ(success, false);
    success = mtl::safe_copy_n(vi, li, 0, size + 100);
    REQUIRE_EQ(success, false);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), false);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), false);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), false);

    // make sure the other containers are still filled with zeros
    REQUIRE_EQ((std::all_of(ai.begin(), ai.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(di.begin(), di.end(), [](auto x) { return x == 0; })), true);
    REQUIRE_EQ((std::all_of(li.begin(), li.end(), [](auto x) { return x == 0; })), true);
}



TEST_CASE("mtl::safe_copy_n with starting position and less items than total")
{
    constexpr size_t size = 10;
    // create a container to copy from that is bigger than the destination
    std::vector<int> vi(size+10);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);
    std::iota(vi.begin(), vi.end(), 10);


    bool success = mtl::safe_copy_n(vi, ai, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 0, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size+10);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    
    // get an iterator for the items that match, as the container is bigger than the destination
    auto it = std::next(vi.begin(), 10);
    REQUIRE_EQ((std::equal(vi.begin(), it, ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), it, di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), it, li.begin(), li.end())), true);
}




TEST_CASE("mtl::safe_copy_n with containers and starting position and number of items")
{
    constexpr size_t size = 100;
    std::vector<int> vi(size);
    std::array<int, size> ai {};
    std::deque<int> di(size);
    std::list<int> li(size);
    std::iota(vi.begin(), vi.end(), 10);

    bool success = mtl::safe_copy_n(vi, ai, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 0, size);
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy_n with empty containers of std::string and starting position")
{
    constexpr size_t size = 0;
    std::vector<std::string> vi(size);
    std::array<std::string, size> ai {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);

    bool success = mtl::safe_copy_n(vi, ai, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 0, size);
    REQUIRE_EQ(success, true);

    

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);
    

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}


TEST_CASE("mtl::safe_copy_n with containers of std::string and starting position")
{
    constexpr size_t size = 3;
    std::vector<std::string> vi { "Bill", "Nick", "Maria"};
    std::array<std::string, size> ai {};
    std::deque<std::string> di(size);
    std::list<std::string> li(size);

    bool success = mtl::safe_copy_n(vi, ai, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, di, 0, size);
    REQUIRE_EQ(success, true);
    success = mtl::safe_copy_n(vi, li, 0, size);
    REQUIRE_EQ(success, true);

    // just be sure it didn't added or removed any elements
    REQUIRE_EQ(vi.size(), size);
    REQUIRE_EQ(ai.size(), size);
    REQUIRE_EQ(di.size(), size);
    REQUIRE_EQ(li.size(), size);

    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), ai.begin(), ai.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), di.begin(), di.end())), true);
    REQUIRE_EQ((std::equal(vi.begin(), vi.end(), li.begin(), li.end())), true);
}