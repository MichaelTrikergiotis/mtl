// tests by Michael Trikergiotis
// 28/05/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <iterator> // std::advance
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <deque>
#include <list>
#include <set>
#include <map>


// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/container.hpp" 
// mtl::reserve, mtl::push_back, mtl::emplace_back, mtl::slice, mtl::slice_n


// ------------------------------------------------------------------------------------------------
// mtl::reserve
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::reserve for containers<int> that have reserve")
{
    std::vector<int> vi;
    std::unordered_set<int> usi;
    std::unordered_map<int, int> umi;
    const size_t usi_starting_bucket_count = usi.bucket_count();
    const size_t umi_starting_bucket_count = umi.bucket_count();
    REQUIRE_EQ(vi.size(), 0);
    REQUIRE_EQ(usi.size(), 0);
    REQUIRE_EQ(umi.size(), 0);
    REQUIRE_EQ(vi.capacity(), 0);
    constexpr size_t size = 100;
    mtl::reserve(vi, size);
    mtl::reserve(usi, size);
    mtl::reserve(umi, size);
    REQUIRE_EQ(vi.size(), 0);
    REQUIRE_EQ(usi.size(), 0);
    REQUIRE_EQ(umi.size(), 0);
    REQUIRE_GE(vi.capacity(), size);
    REQUIRE_GE(usi.bucket_count(), size);
    REQUIRE_GE(umi.bucket_count(), size);
    REQUIRE_NE(usi.bucket_count(), usi_starting_bucket_count);
    REQUIRE_NE(umi.bucket_count(), umi_starting_bucket_count);
}


TEST_CASE("mtl::reserve for containers<std::string> that have reserve")
{
    std::vector<std::string> v;
    std::unordered_set<std::string> us;
    std::unordered_map<std::string, std::string> um;
    const size_t us_starting_bucket_count = us.bucket_count();
    const size_t um_starting_bucket_count = um.bucket_count();
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    REQUIRE_EQ(um.size(), 0);
    REQUIRE_EQ(v.capacity(), 0);
    constexpr size_t size = 100;
    mtl::reserve(v, size);
    mtl::reserve(us, size);
    mtl::reserve(um, size);
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    REQUIRE_EQ(um.size(), 0);
    REQUIRE_GE(v.capacity(), size);
    REQUIRE_GE(us.bucket_count(), size);
    REQUIRE_GE(um.bucket_count(), size);
    REQUIRE_NE(us.bucket_count(), us_starting_bucket_count);
    REQUIRE_NE(um.bucket_count(), um_starting_bucket_count);
}


TEST_CASE("mtl::reserve for containers<int> that don't have reserve")
{
    std::deque<int> d;
    std::list<int> l;
    std::set<int> s;
    std::map<int, int> m;
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(m.size(), 0);
    constexpr size_t size = 100;
    mtl::reserve(d, size);
    mtl::reserve(l, size);
    mtl::reserve(s, size);
    mtl::reserve(m, size);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(m.size(), 0);  
}

TEST_CASE("mtl::reserve for containers<std::string> that don't have reserve")
{
    std::deque<std::string> d;
    std::list<std::string> l;
    std::set<std::string> s;
    std::map<std::string, std::string> m;
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(m.size(), 0);
    constexpr size_t size = 100;
    mtl::reserve(d, size);
    mtl::reserve(l, size);
    mtl::reserve(s, size);
    mtl::reserve(m, size);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(m.size(), 0);  
}


// ------------------------------------------------------------------------------------------------
// mtl::push_back
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::push_back for containers<int> that have push_back")
{
    std::vector<int> v;
    std::deque<int> d;
    std::list<int> l;
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    mtl::push_back(v, 111);
    mtl::push_back(d, 111);
    mtl::push_back(l, 111);
    REQUIRE_EQ(v.size(), 1);
    REQUIRE_EQ(d.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(v.at(0), 111);
    REQUIRE_EQ(d.at(0), 111);
    REQUIRE_EQ(l.front(), 111);
    const int i = 222;
    mtl::push_back(v, i);
    mtl::push_back(d, i);
    mtl::push_back(l, i);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(v.size(), 2);
    REQUIRE_EQ(d.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(v.at(1), i);
    REQUIRE_EQ(d.at(1), i);
    REQUIRE_EQ(*lit, i);
}

TEST_CASE("mtl::push_back for containers<std::string> that have push_back")
{
    std::vector<std::string> v;
    std::deque<std::string> d;
    std::list<std::string> l;
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    mtl::push_back(v, "111");
    mtl::push_back(d, "111");
    mtl::push_back(l, "111");
    REQUIRE_EQ(v.size(), 1);
    REQUIRE_EQ(d.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(v.at(0), std::string("111"));
    REQUIRE_EQ(d.at(0), std::string("111"));
    REQUIRE_EQ(l.front(), std::string("111"));
    std::string i = "222";
    mtl::push_back(v, i);
    mtl::push_back(d, i);
    mtl::push_back(l, i);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(v.size(), 2);
    REQUIRE_EQ(d.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(v.at(1), i);
    REQUIRE_EQ(d.at(1), i);
    REQUIRE_EQ(*lit, i);
}

TEST_CASE("mtl::push_back for containers<int> that don't have push_back")
{
    std::list<int> l;
    std::set<int> s;
    std::unordered_set<int> us;
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    mtl::push_back(s, 111);
    mtl::push_back(l, 111);
    mtl::push_back(us, 111);
    REQUIRE_EQ(s.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(us.size(), 1);
    REQUIRE_EQ(*(l.begin()), 111);
    REQUIRE_EQ(s.find(111) != s.end(), true);
    REQUIRE_EQ(us.find(111) != us.end(), true);

    const int i = 222;
    mtl::push_back(s, i);
    mtl::push_back(l, i);
    mtl::push_back(us, i);
    REQUIRE_EQ(s.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(us.size(), 2);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(*lit, 222);
    REQUIRE_EQ(s.find(222) != s.end(), true);
    REQUIRE_EQ(us.find(222) != us.end(), true);
}

TEST_CASE("mtl::push_back for containers<std::string> that don't have push_back")
{
    std::list<std::string> l;
    std::set<std::string> s;
    std::unordered_set<std::string> us;
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    mtl::push_back(s, std::string("111"));
    mtl::push_back(l, std::string("111"));
    mtl::push_back(us, std::string("111"));
    REQUIRE_EQ(s.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(us.size(), 1);
    REQUIRE_EQ(*(l.begin()), std::string("111"));
    REQUIRE_EQ(s.find(std::string("111")) != s.end(), true);
    REQUIRE_EQ(us.find(std::string("111")) != us.end(), true);

    std::string i = "222";
    mtl::push_back(s, i);
    mtl::push_back(l, i);
    mtl::push_back(us, i);
    REQUIRE_EQ(s.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(us.size(), 2);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(*lit, std::string("222"));
    REQUIRE_EQ(s.find(std::string("222")) != s.end(), true);
    REQUIRE_EQ(us.find(std::string("222")) != us.end(), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::emplace_back
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::emplace_back for containers<int> that have emplace_back")
{
    std::vector<int> v;
    std::deque<int> d;
    std::list<int> l;
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    mtl::emplace_back(v, 111);
    mtl::emplace_back(d, 111);
    mtl::emplace_back(l, 111);
    REQUIRE_EQ(v.size(), 1);
    REQUIRE_EQ(d.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(v.at(0), 111);
    REQUIRE_EQ(d.at(0), 111);
    REQUIRE_EQ(l.front(), 111);
    const int i = 222;
    mtl::emplace_back(v, i);
    mtl::emplace_back(d, i);
    mtl::emplace_back(l, i);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(v.size(), 2);
    REQUIRE_EQ(d.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(v.at(1), i);
    REQUIRE_EQ(d.at(1), i);
    REQUIRE_EQ(*lit, i);
}

TEST_CASE("mtl::emplace_back for containers<std::string> that have emplace_back")
{
    std::vector<std::string> v;
    std::deque<std::string> d;
    std::list<std::string> l;
    REQUIRE_EQ(v.size(), 0);
    REQUIRE_EQ(d.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    mtl::emplace_back(v, "111");
    mtl::emplace_back(d, "111");
    mtl::emplace_back(l, "111");
    REQUIRE_EQ(v.size(), 1);
    REQUIRE_EQ(d.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(v.at(0), std::string("111"));
    REQUIRE_EQ(d.at(0), std::string("111"));
    REQUIRE_EQ(l.front(), std::string("111"));
    std::string i = "222";
    mtl::emplace_back(v, i);
    mtl::emplace_back(d, i);
    mtl::emplace_back(l, i);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(v.size(), 2);
    REQUIRE_EQ(d.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(v.at(1), i);
    REQUIRE_EQ(d.at(1), i);
    REQUIRE_EQ(*lit, i);
}

TEST_CASE("mtl::emplace_back for containers<int> that don't have emplace_back")
{
    std::list<int> l;
    std::set<int> s;
    std::unordered_set<int> us;
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    mtl::emplace_back(s, 111);
    mtl::emplace_back(l, 111);
    mtl::emplace_back(us, 111);
    REQUIRE_EQ(s.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(us.size(), 1);
    REQUIRE_EQ(*(l.begin()), 111);
    REQUIRE_EQ(s.find(111) != s.end(), true);
    REQUIRE_EQ(us.find(111) != us.end(), true);

    const int i = 222;
    mtl::emplace_back(s, i);
    mtl::emplace_back(l, i);
    mtl::emplace_back(us, i);
    REQUIRE_EQ(s.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(us.size(), 2);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(*lit, 222);
    REQUIRE_EQ(s.find(222) != s.end(), true);
    REQUIRE_EQ(us.find(222) != us.end(), true);
}

TEST_CASE("mtl::emplace_back for containers<std::string> that don't have emplace_back")
{
    std::list<std::string> l;
    std::set<std::string> s;
    std::unordered_set<std::string> us;
    REQUIRE_EQ(s.size(), 0);
    REQUIRE_EQ(l.size(), 0);
    REQUIRE_EQ(us.size(), 0);
    mtl::emplace_back(s, std::string("111"));
    mtl::emplace_back(l, std::string("111"));
    mtl::emplace_back(us, std::string("111"));
    REQUIRE_EQ(s.size(), 1);
    REQUIRE_EQ(l.size(), 1);
    REQUIRE_EQ(us.size(), 1);
    REQUIRE_EQ(*(l.begin()), std::string("111"));
    REQUIRE_EQ(s.find(std::string("111")) != s.end(), true);
    REQUIRE_EQ(us.find(std::string("111")) != us.end(), true);

    std::string i = "222";
    mtl::emplace_back(s, i);
    mtl::emplace_back(l, i);
    mtl::emplace_back(us, i);
    REQUIRE_EQ(s.size(), 2);
    REQUIRE_EQ(l.size(), 2);
    REQUIRE_EQ(us.size(), 2);
    // get an iterator to the beginning of the list and move it one item forward
    auto lit = l.begin();
    std::advance(lit, 1);
    REQUIRE_EQ(*lit, std::string("222"));
    REQUIRE_EQ(s.find(std::string("222")) != s.end(), true);
    REQUIRE_EQ(us.find(std::string("222")) != us.end(), true);
}





// ------------------------------------------------------------------------------------------------
// mtl::slice
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::slice with empty std::vector<int>")
{
    std::vector<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::vector<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::vector<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::vector<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::vector<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::vector<int>")
{
    std::vector<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<int> bad1;
    CHECK_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::vector<int> bad2;
    CHECK_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::vector<int> bad3;
    CHECK_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::vector<int> bad4;
    CHECK_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::vector<int> bad5;
    CHECK_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    CHECK_EQ(good0.size(), 0);
    CHECK_EQ(good1.size(), 1);
    CHECK_EQ(good2.size(), 2);
    CHECK_EQ(good3.size(), 3);
    CHECK_EQ(good4.size(), 4);
    CHECK_EQ(good5.size(), 5);

    CHECK_EQ(good_none.size(), 0);
    CHECK_EQ(good_first.size(), 1);
    CHECK_EQ(good_second.size(), 1);
    CHECK_EQ(good_third.size(), 1);
    CHECK_EQ(good_fourth.size(), 1);
    CHECK_EQ(good_fifth.size(), 1);

    // check container contents
    std::vector<int> values1 {1};
    CHECK_EQ((good1 == values1), true);
    std::vector<int> values2 {1, 2};
    CHECK_EQ((good2 == values2), true);
    std::vector<int> values3 {1, 2, 3};
    CHECK_EQ((good3 == values3), true);
    std::vector<int> values4 {1, 2, 3, 4};
    CHECK_EQ((good4 == values4), true);
    std::vector<int> values5 {1, 2, 3, 4, 5};
    CHECK_EQ((good5 == values5), true);

    CHECK_EQ((good_first.at(0) == 1), true);
    CHECK_EQ((good_second.at(0) == 2), true);
    CHECK_EQ((good_third.at(0) == 3), true);
    CHECK_EQ((good_fourth.at(0) == 4), true);
    CHECK_EQ((good_fifth.at(0) == 5), true);
}

TEST_CASE("mtl::slice with empty std::vector<std::string>")
{
    std::vector<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::vector<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::vector<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::vector<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::vector<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::vector<std::string>")
{
    std::vector<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::vector<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::vector<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::vector<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::vector<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::vector<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::vector<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::vector<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::vector<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::vector<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == std::string("1")), true);
    REQUIRE_EQ((good_second.at(0) == std::string("2")), true);
    REQUIRE_EQ((good_third.at(0) == std::string("3")), true);
    REQUIRE_EQ((good_fourth.at(0) == std::string("4")), true);
    REQUIRE_EQ((good_fifth.at(0) == std::string("5")), true);
}




TEST_CASE("mtl::slice with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}




TEST_CASE("mtl::slice with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::deque<int>")
{
    std::deque<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::deque<int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::deque<int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::deque<int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::deque<int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::deque<int> values1 {1};
    REQUIRE_EQ((good1 == values1), true);
    std::deque<int> values2 {1, 2};
    REQUIRE_EQ((good2 == values2), true);
    std::deque<int> values3 {1, 2, 3};
    REQUIRE_EQ((good3 == values3), true);
    std::deque<int> values4 {1, 2, 3, 4};
    REQUIRE_EQ((good4 == values4), true);
    std::deque<int> values5 {1, 2, 3, 4, 5};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == 1), true);
    REQUIRE_EQ((good_second.at(0) == 2), true);
    REQUIRE_EQ((good_third.at(0) == 3), true);
    REQUIRE_EQ((good_fourth.at(0) == 4), true);
    REQUIRE_EQ((good_fifth.at(0) == 5), true);
}

TEST_CASE("mtl::slice with empty std::deque<std::string>")
{
    std::deque<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::deque<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::deque<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::deque<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::deque<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::deque<std::string>")
{
    std::deque<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::deque<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::deque<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::deque<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::deque<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::deque<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::deque<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::deque<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::deque<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::deque<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == std::string("1")), true);
    REQUIRE_EQ((good_second.at(0) == std::string("2")), true);
    REQUIRE_EQ((good_third.at(0) == std::string("3")), true);
    REQUIRE_EQ((good_fourth.at(0) == std::string("4")), true);
    REQUIRE_EQ((good_fifth.at(0) == std::string("5")), true);
}

TEST_CASE("mtl::slice with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}





TEST_CASE("mtl::slice with empty std::set<int>")
{
    std::set<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::set<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::set<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::set<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::set<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::set<int>")
{
    std::set<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::set<int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::set<int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::set<int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::set<int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::set<int> values1 {1};
    REQUIRE_EQ((good1 == values1), true);
    std::set<int> values2 {1, 2};
    REQUIRE_EQ((good2 == values2), true);
    std::set<int> values3 {1, 2, 3};
    REQUIRE_EQ((good3 == values3), true);
    std::set<int> values4 {1, 2, 3, 4};
    REQUIRE_EQ((good4 == values4), true);
    std::set<int> values5 {1, 2, 3, 4, 5};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((*good_first.begin() == 1), true);
    REQUIRE_EQ((*good_second.begin() == 2), true);
    REQUIRE_EQ((*good_third.begin() == 3), true);
    REQUIRE_EQ((*good_fourth.begin() == 4), true);
    REQUIRE_EQ((*good_fifth.begin() == 5), true);
}

TEST_CASE("mtl::slice with empty std::set<std::string>")
{
    std::set<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::set<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::set<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::set<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::set<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::set<std::string>")
{
    std::set<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::set<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::set<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::set<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::set<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::set<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::set<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::set<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::set<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::set<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((*good_first.begin()  == std::string("1")), true);
    REQUIRE_EQ((*good_second.begin() == std::string("2")), true);
    REQUIRE_EQ((*good_third.begin()  == std::string("3")), true);
    REQUIRE_EQ((*good_fourth.begin() == std::string("4")), true);
    REQUIRE_EQ((*good_fifth.begin()  == std::string("5")), true);
}






TEST_CASE("mtl::slice with empty std::map<int, int>")
{
    std::map<int, int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<int, int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::map<int, int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::map<int, int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::map<int, int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::map<int, int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::map<int, int>")
{
    std::map<int, int> values;
    values[1] = 1;
    values[2] = 2;
    values[3] = 3;
    values[4] = 4;
    values[5] = 5;

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<int, int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::map<int, int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::map<int, int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::map<int, int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::map<int, int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::map<int, int> values1 {{1, 1} };
    REQUIRE_EQ((good1 == values1), true);
    std::map<int, int> values2 {{1, 1}, {2, 2}};
    REQUIRE_EQ((good2 == values2), true);
    std::map<int, int> values3 {{1, 1}, {2, 2}, {3, 3}};
    REQUIRE_EQ((good3 == values3), true);
    std::map<int, int> values4 {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    REQUIRE_EQ((good4 == values4), true);
    std::map<int, int> values5 {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first[1] == 1), true);
    REQUIRE_EQ((good_second[2] == 2), true);
    REQUIRE_EQ((good_third[3] == 3), true);
    REQUIRE_EQ((good_fourth[4] == 4), true);
    REQUIRE_EQ((good_fifth[5] == 5), true);
}

TEST_CASE("mtl::slice with empty std::map<std::string, std::string>")
{
    std::map<std::string, std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<std::string, std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice(values, 10, 10)));
    std::map<std::string, std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice(values, 0, 10)));
    std::map<std::string, std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice(values, 10, 5)));
    std::map<std::string, std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice(values, 0, 1)));
    std::map<std::string, std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice with std::map<std::string, std::string>")
{
    std::map<std::string, std::string> values;
    values["1"] = "1";
    values["2"] = "2";
    values["3"] = "3";
    values["4"] = "4";
    values["5"] = "5";

    // ask for valid range of values
    auto good0 = mtl::slice(values, 0, 0);
    auto good1 = mtl::slice(values, 0, 1);
    auto good2 = mtl::slice(values, 0, 2);
    auto good3 = mtl::slice(values, 0, 3);
    auto good4 = mtl::slice(values, 0, 4);
    auto good5 = mtl::slice(values, 0, 5);

    auto good_none   = mtl::slice(values, 0, 0);
    auto good_first  = mtl::slice(values, 0, 1);
    auto good_second = mtl::slice(values, 1, 2);
    auto good_third  = mtl::slice(values, 2, 3);
    auto good_fourth = mtl::slice(values, 3, 4);
    auto good_fifth  = mtl::slice(values, 4, 5);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<std::string, std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice(values, 10, 10)));
    std::map<std::string, std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice(values, 0, 10)));
    std::map<std::string, std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice(values, 10, 5)));
    std::map<std::string, std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice(values, 5, 0)));
    std::map<std::string, std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::map<std::string, std::string> values1 {{"1", "1"}};
    REQUIRE_EQ((good1 == values1), true);
    std::map<std::string, std::string> values2 {{"1", "1"}, {"2", "2"}};
    REQUIRE_EQ((good2 == values2), true);
    std::map<std::string, std::string> values3 {{"1", "1"}, {"2", "2"}, {"3", "3"}};
    REQUIRE_EQ((good3 == values3), true);
    std::map<std::string, std::string> values4 {{"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"}};
    REQUIRE_EQ((good4 == values4), true);
    std::map<std::string, std::string> values5 
    {{"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"}, {"5", "5"}};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first["1"]  == std::string("1")), true);
    REQUIRE_EQ((good_second["2"] == std::string("2")), true);
    REQUIRE_EQ((good_third["3"]  == std::string("3")), true);
    REQUIRE_EQ((good_fourth["4"] == std::string("4")), true);
    REQUIRE_EQ((good_fifth["5"]  == std::string("5")), true);
}






// ------------------------------------------------------------------------------------------------
// mtl::slice_n
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::slice_n with empty std::vector<int>")
{
    std::vector<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::vector<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::vector<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::vector<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::vector<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::vector<int>")
{
    std::vector<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::vector<int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::vector<int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::vector<int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::vector<int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::vector<int> values1 {1};
    REQUIRE_EQ((good1 == values1), true);
    std::vector<int> values2 {1, 2};
    REQUIRE_EQ((good2 == values2), true);
    std::vector<int> values3 {1, 2, 3};
    REQUIRE_EQ((good3 == values3), true);
    std::vector<int> values4 {1, 2, 3, 4};
    REQUIRE_EQ((good4 == values4), true);
    std::vector<int> values5 {1, 2, 3, 4, 5};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == 1), true);
    REQUIRE_EQ((good_second.at(0) == 2), true);
    REQUIRE_EQ((good_third.at(0) == 3), true);
    REQUIRE_EQ((good_fourth.at(0) == 4), true);
    REQUIRE_EQ((good_fifth.at(0) == 5), true);
}

TEST_CASE("mtl::slice_n with empty std::vector<std::string>")
{
    std::vector<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::vector<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::vector<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::vector<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::vector<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::vector<std::string>")
{
    std::vector<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::vector<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::vector<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::vector<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::vector<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::vector<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::vector<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::vector<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::vector<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::vector<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::vector<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == std::string("1")), true);
    REQUIRE_EQ((good_second.at(0) == std::string("2")), true);
    REQUIRE_EQ((good_third.at(0) == std::string("3")), true);
    REQUIRE_EQ((good_fourth.at(0) == std::string("4")), true);
    REQUIRE_EQ((good_fifth.at(0) == std::string("5")), true);
}




TEST_CASE("mtl::slice_n with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}




TEST_CASE("mtl::slice_n with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::deque<int>")
{
    std::deque<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::deque<int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::deque<int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::deque<int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::deque<int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::deque<int> values1 {1};
    REQUIRE_EQ((good1 == values1), true);
    std::deque<int> values2 {1, 2};
    REQUIRE_EQ((good2 == values2), true);
    std::deque<int> values3 {1, 2, 3};
    REQUIRE_EQ((good3 == values3), true);
    std::deque<int> values4 {1, 2, 3, 4};
    REQUIRE_EQ((good4 == values4), true);
    std::deque<int> values5 {1, 2, 3, 4, 5};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == 1), true);
    REQUIRE_EQ((good_second.at(0) == 2), true);
    REQUIRE_EQ((good_third.at(0) == 3), true);
    REQUIRE_EQ((good_fourth.at(0) == 4), true);
    REQUIRE_EQ((good_fifth.at(0) == 5), true);
}

TEST_CASE("mtl::slice_n with empty std::deque<std::string>")
{
    std::deque<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::deque<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::deque<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::deque<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::deque<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::deque<std::string>")
{
    std::deque<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::deque<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::deque<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::deque<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::deque<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::deque<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::deque<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::deque<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::deque<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::deque<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first.at(0) == std::string("1")), true);
    REQUIRE_EQ((good_second.at(0) == std::string("2")), true);
    REQUIRE_EQ((good_third.at(0) == std::string("3")), true);
    REQUIRE_EQ((good_fourth.at(0) == std::string("4")), true);
    REQUIRE_EQ((good_fifth.at(0) == std::string("5")), true);
}

TEST_CASE("mtl::slice_n with empty std::deque<int>")
{
    std::deque<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::deque<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::deque<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::deque<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::deque<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::deque<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}





TEST_CASE("mtl::slice_n with empty std::set<int>")
{
    std::set<int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::set<int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::set<int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::set<int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::set<int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::set<int>")
{
    std::set<int> values {1, 2, 3, 4, 5};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::set<int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::set<int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::set<int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::set<int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::set<int> values1 {1};
    REQUIRE_EQ((good1 == values1), true);
    std::set<int> values2 {1, 2};
    REQUIRE_EQ((good2 == values2), true);
    std::set<int> values3 {1, 2, 3};
    REQUIRE_EQ((good3 == values3), true);
    std::set<int> values4 {1, 2, 3, 4};
    REQUIRE_EQ((good4 == values4), true);
    std::set<int> values5 {1, 2, 3, 4, 5};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((*good_first.begin() == 1), true);
    REQUIRE_EQ((*good_second.begin() == 2), true);
    REQUIRE_EQ((*good_third.begin() == 3), true);
    REQUIRE_EQ((*good_fourth.begin() == 4), true);
    REQUIRE_EQ((*good_fifth.begin() == 5), true);
}

TEST_CASE("mtl::slice_n with empty std::set<std::string>")
{
    std::set<std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::set<std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::set<std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::set<std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::set<std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::set<std::string>")
{
    std::set<std::string> values {"1", "2", "3", "4", "5"};

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::set<std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::set<std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::set<std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::set<std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::set<std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::set<std::string> values1 {"1"};
    REQUIRE_EQ((good1 == values1), true);
    std::set<std::string> values2 {"1", "2"};
    REQUIRE_EQ((good2 == values2), true);
    std::set<std::string> values3 {"1", "2", "3"};
    REQUIRE_EQ((good3 == values3), true);
    std::set<std::string> values4 {"1", "2", "3", "4"};
    REQUIRE_EQ((good4 == values4), true);
    std::set<std::string> values5 {"1", "2", "3", "4", "5"};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((*good_first.begin()  == std::string("1")), true);
    REQUIRE_EQ((*good_second.begin() == std::string("2")), true);
    REQUIRE_EQ((*good_third.begin()  == std::string("3")), true);
    REQUIRE_EQ((*good_fourth.begin() == std::string("4")), true);
    REQUIRE_EQ((*good_fifth.begin()  == std::string("5")), true);
}






TEST_CASE("mtl::slice_n with empty std::map<int, int>")
{
    std::map<int, int> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<int, int> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::map<int, int> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::map<int, int> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::map<int, int> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::map<int, int> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::map<int, int>")
{
    std::map<int, int> values;
    values[1] = 1;
    values[2] = 2;
    values[3] = 3;
    values[4] = 4;
    values[5] = 5;

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<int, int> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::map<int, int> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::map<int, int> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::map<int, int> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::map<int, int> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::map<int, int> values1 {{1, 1} };
    REQUIRE_EQ((good1 == values1), true);
    std::map<int, int> values2 {{1, 1}, {2, 2}};
    REQUIRE_EQ((good2 == values2), true);
    std::map<int, int> values3 {{1, 1}, {2, 2}, {3, 3}};
    REQUIRE_EQ((good3 == values3), true);
    std::map<int, int> values4 {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    REQUIRE_EQ((good4 == values4), true);
    std::map<int, int> values5 {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first[1] == 1), true);
    REQUIRE_EQ((good_second[2] == 2), true);
    REQUIRE_EQ((good_third[3] == 3), true);
    REQUIRE_EQ((good_fourth[4] == 4), true);
    REQUIRE_EQ((good_fifth[5] == 5), true);
}

TEST_CASE("mtl::slice_n with empty std::map<std::string, std::string>")
{
    std::map<std::string, std::string> values;

    // ask for valid range of values
    auto slice1 = mtl::slice_n(values, 0, 0);
    
  
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<std::string, std::string> slice2;
    REQUIRE_THROWS((slice2 = mtl::slice_n(values, 10, 10)));
    std::map<std::string, std::string> slice3;
    REQUIRE_THROWS((slice3 = mtl::slice_n(values, 0, 10)));
    std::map<std::string, std::string> slice4;
    REQUIRE_THROWS((slice4 = mtl::slice_n(values, 10, 5)));
    std::map<std::string, std::string> slice5;
    REQUIRE_THROWS((slice5 = mtl::slice_n(values, 0, 1)));
    std::map<std::string, std::string> slice6;
    REQUIRE_THROWS((slice6 = mtl::slice_n(values, 1, 1)));

    // check container sizes
    REQUIRE_EQ(values.size(), 0);
    REQUIRE_EQ(slice1.size(), 0);
    REQUIRE_EQ(slice2.size(), 0);
    REQUIRE_EQ(slice3.size(), 0);
    REQUIRE_EQ(slice4.size(), 0);
    REQUIRE_EQ(slice5.size(), 0);
    REQUIRE_EQ(slice6.size(), 0);
}


TEST_CASE("mtl::slice_n with std::map<std::string, std::string>")
{
    std::map<std::string, std::string> values;
    values["1"] = "1";
    values["2"] = "2";
    values["3"] = "3";
    values["4"] = "4";
    values["5"] = "5";

    // ask for valid range of values
    auto good0 = mtl::slice_n(values, 0, 0);
    auto good1 = mtl::slice_n(values, 0, 1);
    auto good2 = mtl::slice_n(values, 0, 2);
    auto good3 = mtl::slice_n(values, 0, 3);
    auto good4 = mtl::slice_n(values, 0, 4);
    auto good5 = mtl::slice_n(values, 0, 5);

    auto good_none   = mtl::slice_n(values, 0, 0);
    auto good_first  = mtl::slice_n(values, 0, 1);
    auto good_second = mtl::slice_n(values, 1, 1);
    auto good_third  = mtl::slice_n(values, 2, 1);
    auto good_fourth = mtl::slice_n(values, 3, 1);
    auto good_fifth  = mtl::slice_n(values, 4, 1);
    
    
    // ask for invalid values that are out of range and check that an exception is thrown
    std::map<std::string, std::string> bad1;
    REQUIRE_THROWS((bad1 = mtl::slice_n(values, 10, 10)));
    std::map<std::string, std::string> bad2;
    REQUIRE_THROWS((bad2 = mtl::slice_n(values, 0, 10)));
    std::map<std::string, std::string> bad3;
    REQUIRE_THROWS((bad3 = mtl::slice_n(values, 10, 5)));
    std::map<std::string, std::string> bad4;
    REQUIRE_THROWS((bad4 = mtl::slice_n(values, 5, 0)));
    std::map<std::string, std::string> bad5;
    REQUIRE_THROWS((bad5 = mtl::slice_n(values, 5, 1)));


    // check container sizes
    REQUIRE_EQ(good0.size(), 0);
    REQUIRE_EQ(good1.size(), 1);
    REQUIRE_EQ(good2.size(), 2);
    REQUIRE_EQ(good3.size(), 3);
    REQUIRE_EQ(good4.size(), 4);
    REQUIRE_EQ(good5.size(), 5);

    REQUIRE_EQ(good_none.size(), 0);
    REQUIRE_EQ(good_first.size(), 1);
    REQUIRE_EQ(good_second.size(), 1);
    REQUIRE_EQ(good_third.size(), 1);
    REQUIRE_EQ(good_fourth.size(), 1);
    REQUIRE_EQ(good_fifth.size(), 1);

    // check container contents
    std::map<std::string, std::string> values1 {{"1", "1"}};
    REQUIRE_EQ((good1 == values1), true);
    std::map<std::string, std::string> values2 {{"1", "1"}, {"2", "2"}};
    REQUIRE_EQ((good2 == values2), true);
    std::map<std::string, std::string> values3 {{"1", "1"}, {"2", "2"}, {"3", "3"}};
    REQUIRE_EQ((good3 == values3), true);
    std::map<std::string, std::string> values4 {{"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"}};
    REQUIRE_EQ((good4 == values4), true);
    std::map<std::string, std::string> values5 
    {{"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"}, {"5", "5"}};
    REQUIRE_EQ((good5 == values5), true);

    REQUIRE_EQ((good_first["1"]  == std::string("1")), true);
    REQUIRE_EQ((good_second["2"] == std::string("2")), true);
    REQUIRE_EQ((good_third["3"]  == std::string("3")), true);
    REQUIRE_EQ((good_fourth["4"] == std::string("4")), true);
    REQUIRE_EQ((good_fifth["5"]  == std::string("5")), true);
}