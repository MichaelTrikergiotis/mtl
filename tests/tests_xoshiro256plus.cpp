// tests by Michael Trikergiotis
// 28/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <vector>
#include <limits>
#include <sstream>
#include <random>    // std::uniform_int_distribution, std::uniform_real_distribution
#include <algorithm> // std::count_if, std::all_of
#include <utility>   // std::move

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/xoshiro256plus.hpp" 
// [@class] mtl::xoshiro256plus_engine, mtl::xoshiro256plus_engine::xoshiro256plus_engine,
// mtl::xoshiro256plus_engine::operator=, mtl::xoshiro256plus_engine::seed, 
// mtl::xoshiro256plus_engine::min, mtl::xoshiro256plus_engine::max,
// mtl::xoshiro256plus_engine::operator(), mtl::xoshiro256plus_engine::generate,
// mtl::xoshiro256plus_engine::discard, mtl::xoshiro256plus_engine::operator<<,
// mtl::xoshiro256plus_engine::operator>>, mtl::xoshiro256plus_engine::operator==,
// mtl::xoshiro256plus_engine::operator!=, [@class] mtl::xoshiro256plus





// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::xoshiro256plus_engine
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator=
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::seed
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::min
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::max
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator()
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::generate
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::discard
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator<<
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator>>
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator==
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus_engine::operator!=
// ------------------------------------------------------------------------------------------------
// mtl::xoshiro256plus
// ------------------------------------------------------------------------------------------------

using mtl_rng_engine_test = mtl::xoshiro256plus;

TEST_CASE("equality operator")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2;
    REQUIRE_EQ((x1 == x2), false);
}

TEST_CASE("inequality operator")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2;


    REQUIRE_EQ((x1 != x2), true);
}

TEST_CASE("copy constructor")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2(x1);
    REQUIRE_EQ((x1 == x2), true);

    x1.discard(10);
    REQUIRE_EQ((x1 == x2), false);
}

TEST_CASE("move constructor")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x_move;
    x_move.discard(10);
    mtl_rng_engine_test x2 (std::move(x_move));
    REQUIRE_EQ((x1 == x2), true);
    
    x1.discard(10);
    REQUIRE_EQ((x1 == x2), false);
}

TEST_CASE("move assignment operator")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x_move;
    x_move.discard(10);
    mtl_rng_engine_test x2 = std::move(x_move);
    REQUIRE_EQ((x1 == x2), true);
    
    x1.discard(10);
    REQUIRE_EQ((x1 == x2), false);
}

TEST_CASE("constructor with one seed value")
{
    auto seed = 14254277390595747963UL;
    mtl_rng_engine_test x1(seed);
    mtl_rng_engine_test x2(seed);

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("constructor with two seed values")
{
    auto seed1 = 14254277390595747963UL;
    auto seed2 = 508793785532536663UL;
    mtl_rng_engine_test x1(seed1, seed2);
    mtl_rng_engine_test x2(seed1, seed2);

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("constructor with four seed values")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("constructor with different first seed values")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532636663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("constructor with different second seed values")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 12713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("constructor with different third seed values")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 12254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("constructor with different fourth seed values")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9543376823279757380UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}



TEST_CASE("constructor with four seed values, difference operator")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 != x2), false);
}

TEST_CASE("constructor with different first seed values, difference operator")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532636663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 != x2), true);
}

TEST_CASE("constructor with different second seed values, difference operator")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 12713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 != x2), true);
}

TEST_CASE("constructor with different third seed values, difference operator")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 12254277390595747963UL,
                           9143376823279757380UL);

    REQUIRE_EQ((x1 != x2), true);
}

TEST_CASE("constructor with different fourth seed values, difference operator")
{
    mtl_rng_engine_test x1(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9143376823279757380UL);
    mtl_rng_engine_test x2(508793785532536663UL, 13713535390190520406UL, 14254277390595747963UL,
                           9543376823279757380UL);

    REQUIRE_EQ((x1 != x2), true);
}





TEST_CASE("discard")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2;
    x2.discard(10);

    REQUIRE_EQ((x1 == x2), true);
}

TEST_CASE("generate, generated numbers compared to expected")
{
    mtl_rng_engine_test x1;
    std::vector<uint64_t> numbers
    {
        15040012402420052908UL, 18047360190796303877UL, 1541254178677746322UL, 
        12880916797698765452UL, 14190777270071492990UL, 7631271090292547620UL,
        15159564118061801931UL, 1762365250610007155UL, 17648358432920555780UL,
        4852895841127278456UL
    };
    std::vector<uint64_t> results(10);
    x1.generate(results.begin(), results.end());

    REQUIRE_EQ(numbers, results);
}

TEST_CASE("generate, generated numbers from two different instances")
{
    mtl_rng_engine_test x1;
    mtl_rng_engine_test x2;
    std::vector<uint64_t> results1(10);
    std::vector<uint64_t> results2(10);
    x1.generate(results1.begin(), results1.end());
    x2.generate(results2.begin(), results2.end());
    REQUIRE_EQ(results1, results2);
}


TEST_CASE("operator(), generated numbers compared to expected")
{
    mtl_rng_engine_test x1;
    std::vector<uint64_t> numbers
    {
        15040012402420052908UL, 18047360190796303877UL, 1541254178677746322UL, 
        12880916797698765452UL, 14190777270071492990UL, 7631271090292547620UL,
        15159564118061801931UL, 1762365250610007155UL, 17648358432920555780UL,
        4852895841127278456UL
    };
    std::vector<uint64_t> results(10);
    for (auto& i : results)
    {
        i = x1();
    }

    REQUIRE_EQ(numbers, results);
}

TEST_CASE("operator(), generated numbers from two different instances")
{
    mtl_rng_engine_test x1;
    mtl_rng_engine_test x2;
    std::vector<uint64_t> results1(10);
    std::vector<uint64_t> results2(10);
    for (auto& i : results1)
    {
        i = x1();
    }
    for (auto& i : results2)
    {
        i = x2();
    }
    REQUIRE_EQ(results1, results2);
}

TEST_CASE("discard and generate, generated numbers from two different instances")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2;
    std::vector<uint64_t> unwanted(10);
    x2.generate(unwanted.begin(), unwanted.end());
    auto x1_result = x1();
    auto x2_result = x2();
    REQUIRE_EQ(x1_result, x2_result);
}

TEST_CASE("discard and operator(), generated numbers from two different instances")
{
    mtl_rng_engine_test x1;
    x1.discard(10);
    mtl_rng_engine_test x2;
    std::vector<uint64_t> unwanted(10);
    for (auto& i : unwanted)
    {
        i = x2();
    }
    auto x1_result = x1();
    auto x2_result = x2();
    REQUIRE_EQ(x1_result, x2_result);
}



TEST_CASE("min")
{
    mtl_rng_engine_test x1;
    REQUIRE_EQ(std::numeric_limits<uint64_t>::min(), x1.min());
}

TEST_CASE("max")
{
    mtl_rng_engine_test x1;
    REQUIRE_EQ(std::numeric_limits<uint64_t>::max(), x1.max());
}

TEST_CASE("changing seed")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(16590098645626663609UL);
    mtl_rng_engine_test x2;
    x2.seed(7055232833321683523UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("changing two seeds")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(16590098645626663609UL, 9143376823279757380UL);
    mtl_rng_engine_test x2;
    x2.seed(7055232833321683523UL, 7055232833321683523UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("changing multiple seed values")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(1914114301168679702UL, 9143376823279757380UL, 16590098645626663609UL, 
            7055232833321683523UL);
    mtl_rng_engine_test x2;
    x2.seed(1353117381024009193UL, 7143376003279757380UL, 7055232833321683523UL, 
            13713535390190520406UL);

    REQUIRE_EQ((x1 == x2), false);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), false);
}

TEST_CASE("changing default seed and setting default seed again")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(1914114301168679702UL);
    // setting the default again
    x1.seed();
    mtl_rng_engine_test x2;
    x2.seed(7055232833321683523UL);
    x2.seed();

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("changing two default seeds and setting default seed again")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(1914114301168679702UL, 13713535390190520406UL);
    // setting the default again
    x1.seed();
    mtl_rng_engine_test x2;
    x2.seed(7055232833321683523UL, 16590098645626663609UL);
    x2.seed();

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("changing multiple default seed values and setting default seed values again")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(16590098645626663609UL, 13713535390190520406UL, 16590098645626663609UL, 
            7055232833321683523UL);
    // setting the default again
    x1.seed();
    mtl_rng_engine_test x2;
    x2.seed(508793785532536663UL, 14254277390595747963UL, 7055232833321683523UL, 
            16590098645626663609UL);
    x2.seed();

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("copying seed values from another engine")
{
    mtl_rng_engine_test x1;
    // changing the default
    x1.seed(14254277390595747963UL, 16590098645626663609UL, 13713535390190520406UL, 
            508793785532536663UL);
    mtl_rng_engine_test x2;
    x2.seed(x1);

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("operator << to grab seed values")
{
    mtl_rng_engine_test x1;
    std::stringstream ss;
    ss << x1;
    std::string result = "1733541517147835066 15395012609548302636 12202545078643706282";
    result += " 4155657270789760540";
    REQUIRE_EQ(result, ss.str());
}


TEST_CASE("operator >> used to set seed values")
{
    mtl_rng_engine_test x1;
    x1.seed(7055232833321683523UL, 13713535390190520406UL, 14254277390595747963UL,
            16590098645626663609UL);
    mtl_rng_engine_test x2;

    std::stringstream ss;
    ss << 7055232833321683523UL << " " << 13713535390190520406UL << " " << 14254277390595747963UL;
    ss << " " << 16590098645626663609UL;
    ss >> x2;

    REQUIRE_EQ((x1 == x2), true);

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x2());
    }
    REQUIRE_EQ((values1 == values2), true);
}

TEST_CASE("using engine with different default seed values")
{
    mtl_rng_engine_test x1;
    mtl::xoshiro256plus_engine<uint64_t, 9143376823279757380UL, 7055232833321683523UL, 
                                         13713535390190520406UL, 508793785532536663UL> x_eng;
    REQUIRE_NE(x1(), x_eng());
    x1.discard(10);
    x_eng.discard(10);
    REQUIRE_NE(x1(), x_eng());

    size_t size = 100;
    std::vector<uint64_t> values1;
    values1.reserve(size);
    std::vector<uint64_t> values2;
    values2.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
        values1.emplace_back(x1());
        values2.emplace_back(x_eng());
    }
    REQUIRE_EQ((values1 == values2), false);
}


TEST_CASE("random engine with std::uniform_int_distribution<int>, check for min max bounds")
{
    const size_t size = 100;
    const int min = 10;
    const int max = 100;
    std::vector<int> values;
    values.reserve(size);
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        auto value = dist(x1);
        CHECK_EQ((value >= min), true);
        CHECK_EQ((value <= max), true);
        values.emplace_back(value);
    }

    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<int> tests")
{
    const size_t size = 1000;
    const int min = 10;
    const int max = 100;
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<int> values;
    values.reserve(size);
    
    for(size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values set to 0
    std::ptrdiff_t zero_count = std::count_if(values.begin(), values.end(), [](auto x)
                                              { 
                                                  return x == 0;
                                              } );
    REQUIRE_EQ(zero_count, 0); 

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x < min;
                                             } );
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x > max;
                                             } );
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x == min;
                                             } );
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x == max;
                                             } );
    REQUIRE_LT(count_max, percent);


    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}


TEST_CASE("random engine with std::uniform_int_distribution<int> with negative min, bounds")
{
    const size_t size = 100;
    const int min = -1000;
    const int max = 1000;
    std::vector<int> values;
    values.reserve(size);
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        auto value = dist(x1);
        CHECK_EQ((value >= min), true);
        CHECK_EQ((value <= max), true);
        values.emplace_back(value);
    }

    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<int> tests with negative min")
{
    const size_t size = 1000;
    const int min = -1000;
    const int max = 1000;
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<int> values;
    values.reserve(size);
    
    for(size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x < min;
                                             } );
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x > max;
                                             } );
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x == min;
                                             } );
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x == max;
                                             } );
    REQUIRE_LT(count_max, percent);


    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<int> with negative numbers, bounds")
{
    const size_t size = 100;
    const int min = -1000;
    const int max = -10;
    std::vector<int> values;
    values.reserve(size);
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        auto value = dist(x1);
        CHECK_EQ((value >= min), true);
        CHECK_EQ((value <= max), true);
        values.emplace_back(value);
    }

    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<int> tests with negative numbers")
{
    const size_t size = 1000;
    const int min = -1000;
    const int max = -10;
    std::uniform_int_distribution<int> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<int> values;
    values.reserve(size);
    
    for(size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x < min;
                                             } );
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x > max;
                                             } );
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x == min;
                                             } );
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x == max;
                                             } );
    REQUIRE_LT(count_max, percent);


    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}



TEST_CASE("random engine with std::uniform_int_distribution<unsigned int>, min max bounds")
{
    const size_t size = 100;
    const unsigned int min = 10;
    const unsigned int max = 100;
    std::vector<unsigned int> values;
    values.reserve(size);
    std::uniform_int_distribution<unsigned int> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        auto value = dist(x1);
        CHECK_EQ((value >= min), true);
        CHECK_EQ((value <= max), true);
        values.emplace_back(value);
    }


    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<unsigned int> tests")
{
    const size_t size = 1000;
    const unsigned int min = 10;
    const unsigned int max = 100;
    std::uniform_int_distribution<unsigned int> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<unsigned int> values;
    values.reserve(size);
    
    for(size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values set to 0
    std::ptrdiff_t zero_count = std::count_if(values.begin(), values.end(), [](auto x)
                                              { 
                                                  return x == 0;
                                              } );
    REQUIRE_EQ(zero_count, 0); 

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x < min;
                                             } );
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x > max;
                                             } );
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             { 
                                                 return x == min;
                                             } );
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             { 
                                                 return x == max;
                                             } );
    REQUIRE_LT(count_max, percent);

    REQUIRE_EQ(values.empty(), false);
    
    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
}



TEST_CASE("random engine with std::uniform_int_distribution<float>, check for min max bounds")
{
    const size_t size = 100;
    const float min = 10.0f;
    const float max = 100.0f;
    std::uniform_real_distribution<float> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        auto value = dist(x1);
        // we can't compare floating point type numbers with equality
        CHECK_EQ((value > (min - 0.001f)), true);
        CHECK_EQ((value < (max + 0.001f)), true);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<float> tests")
{
    const size_t size = 1000;
    const float min = 10.0f;
    const float max = 100.0f;
    std::uniform_real_distribution<float> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<float> values;
    values.reserve(size);

    for (size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values set to 0
    std::ptrdiff_t zero_count = std::count_if(values.begin(), values.end(), [](auto x)
                                              {
                                               // trick to compare with 0 without compilers
                                               // complaining about floating point number equality
                                               // comparison
                                                  return (!(x < 0.0f) && !(x > 0.0f));
                                              });
    REQUIRE_EQ(zero_count, 0);

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             {
                                                 return x < min;
                                             });
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             {
                                                 return x > max;
                                             });
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             {
                                                 // comparing float values with approx equality
                                                 if ((x >= min) && (x <= min + 0.01f))
                                                 {
                                                     return true;
                                                 }
                                                 return false;
                                             });
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             {
                                                 // comparing float values with approx equality
                                                 if ((x >= max - 0.01f) && (x <= max))
                                                 {
                                                     return true;
                                                 }
                                                 return false;
                                             });
    REQUIRE_LT(count_max, percent);
}

TEST_CASE("random engine with std::uniform_int_distribution<double>, check for min max bounds")
{
    const size_t size = 100;
    const double min = 10.0;
    const double max = 100.0;
    std::uniform_real_distribution<double> dist(min, max);
    mtl_rng_engine_test x1;
    for (size_t i = 0; i < size; i++)
    {
        // we can't compare floating point type numbers with equality
        auto value = dist(x1);
        CHECK_EQ((value > (min - 0.001)), true);
        CHECK_EQ((value < (max + 0.001)), true);
    }
}

TEST_CASE("random engine with std::uniform_int_distribution<double> tests")
{
    const size_t size = 1000;
    const double min = 10.0;
    const double max = 100.0;
    std::uniform_real_distribution<double> dist(min, max);
    mtl_rng_engine_test x1;
    std::vector<double> values;
    values.reserve(size);

    for (size_t i = 0; i < size; i++)
    {
        values.emplace_back(dist(x1));
    }

    // there should be no values set to 0
    std::ptrdiff_t zero_count = std::count_if(values.begin(), values.end(), [](auto x)
                                              {
                                                  // trick to compare with 0 without compilers
                                                  // complaining about floating point number
                                                  // equality comparison
                                                  return (!(x < 0.0) && !(x > 0.0));
                                              });
    REQUIRE_EQ(zero_count, 0);

    // there should be no values below min
    std::ptrdiff_t below_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             {
                                                 return x < min;
                                             });
    REQUIRE_EQ(below_min, 0);

    // there should be no values above max
    std::ptrdiff_t above_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             {
                                                 return x > max;
                                             });
    REQUIRE_EQ(above_max, 0);

    // the min value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t percent = static_cast<std::ptrdiff_t>(static_cast<double>(size) * 0.05);
    std::ptrdiff_t count_min = std::count_if(values.begin(), values.end(), [min](auto x)
                                             {
                                                 // comparing double values with approximate
                                                 // equality
                                                 if ((x >= min) && (x <= min + 0.01))
                                                 {
                                                     return true;
                                                 }
                                                 return false;
                                             });
    REQUIRE_LT(count_min, percent);

    // the max value should not appear more than a specific amount, keep in mind that uniform 
    // distributions are not perfectly uniform for such a small sample size, so we are using a
    // percentage value that is safe for the test not failing
    std::ptrdiff_t count_max = std::count_if(values.begin(), values.end(), [max](auto x)
                                             {
                                                 // comparing double values with approximate
                                                 // equality
                                                 if ((x >= max - 0.01) && (x <= max))
                                                 {
                                                     return true;
                                                 }
                                                 return false;
                                             });
    REQUIRE_LT(count_max, percent);
}
