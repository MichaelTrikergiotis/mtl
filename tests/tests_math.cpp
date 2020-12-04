// tests by Michael Trikergiotis
// 31/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <vector>    // std::vector
#include <stdexcept> // std::invalid_argument


// some functions perform division and if one of specific paramter is zero it can cause division
// by zero but by defining the following macro all functions that support this macro will throw an
// exception instead of trying to divide by zero
#define MTL_DIV_ZERO_THROW

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/math.hpp" 
// mtl::approx_equal_abs, mtl::approx_equal_rel, mtl::approx_equal_comb,
// mtl::percent_whole, mtl::percent_portion, mtl::percent


// ------------------------------------------------------------------------------------------------
// mtl::approx_equal_abs
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::approx_equal_abs with float without providing the absolute value")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_abs(f1, f2), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009f, 1.0f), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010f, 1.0f), false);
    REQUIRE_EQ(mtl::approx_equal_abs(100000.0009f, 100000.0f), true);
    REQUIRE_EQ(mtl::approx_equal_abs(100000.010f, 100000.0f), false);
}

TEST_CASE("mtl::approx_equal_abs with float")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_abs(f1, f2, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009f, 1.0f, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010f, 1.0f, 0.0009999999f), false);
    REQUIRE_EQ(mtl::approx_equal_abs(100000.0009f, 100000.0f, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_abs(100000.010f, 100000.0f, 0.0009999999f), false);
}

TEST_CASE("mtl::approx_equal_abs with double without providing the absolute value")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_abs(d1, d2), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009, 1.0), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010, 1.0), false);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.0009, 10000000.0), true);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.010, 10000000.0), false);
}

TEST_CASE("mtl::approx_equal_abs with double")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_abs(d1, d2, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009, 1.0, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010, 1.0, 0.0009999999), false);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.0009, 10000000.0, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.010, 10000000.0, 0.0009999999), false);
}

TEST_CASE("mtl::approx_equal_abs with long double without providing the absolute value")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_abs(d1, d2), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009L, 1.0L), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010L, 1.0L), false);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.0009L, 10000000.0L), true);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.010L, 10000000.0L), false);
}

TEST_CASE("mtl::approx_equal_abs with long double")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_abs(d1, d2, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0009L, 1.0L, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_abs(1.0010L, 1.0L, 0.0009999999L), false);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.0009L, 10000000.0L, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_abs(10000000.010L, 10000000.0L, 0.0009999999L), false);
}




// ------------------------------------------------------------------------------------------------
// mtl::approx_equal_rel
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::approx_equal_rel with float without providing the relative value")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_rel(f1, f2), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009f, 1.0f), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010f, 1.0f), false);
    REQUIRE_EQ(mtl::approx_equal_rel(100000.0009f, 100000.0f), true);
    REQUIRE_EQ(mtl::approx_equal_rel(100000.010f, 100000.0f), true);
}

TEST_CASE("mtl::approx_equal_rel with float")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_rel(f1, f2, 0.0000099999f), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009f, 1.0f, 0.0000099999f), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010f, 1.0f, 0.0000099999f), false);
    REQUIRE_EQ(mtl::approx_equal_rel(100000.0009f, 100000.0f, 0.0000099999f), true);
    REQUIRE_EQ(mtl::approx_equal_rel(100000.010f, 100000.0f, 0.0000099999f), true);
}

TEST_CASE("mtl::approx_equal_rel with double without providing the relative value")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_rel(d1, d2), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009, 1.0), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010, 1.0), false);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.0009, 10000000.0), true);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.010, 10000000.0), true);
}

TEST_CASE("mtl::approx_equal_rel with double")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_rel(d1, d2, 0.0000099999), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009, 1.0, 0.0000099999), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010, 1.0, 0.0000099999), false);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.0009, 10000000.0, 0.0000099999), true);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.010, 10000000.0, 0.0000099999), true);
}

TEST_CASE("mtl::approx_equal_rel with long double without providing the relative value")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_rel(d1, d2), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009L, 1.0L), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010L, 1.0L), false);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.0009L, 10000000.0L), true);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.010L, 10000000.0L), true);
}

TEST_CASE("mtl::approx_equal_rel with long double")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_rel(d1, d2, 0.0000099999L), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0009L, 1.0L, 0.0000099999L), false);
    REQUIRE_EQ(mtl::approx_equal_rel(1.0010L, 1.0L, 0.0000099999L), false);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.0009L, 10000000.0L, 0.0000099999L), true);
    REQUIRE_EQ(mtl::approx_equal_rel(10000000.010L, 10000000.0L, 0.0000099999L), true);
}



// ------------------------------------------------------------------------------------------------
// mtl::approx_equal_comb
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::approx_equal_comb with float without providing the relative or abs value")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_comb(f1, f2), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009f, 1.0f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010f, 1.0f), false);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.0009f, 100000.0f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.010f, 100000.0f), true);
}

TEST_CASE("mtl::approx_equal_comb with float without relative")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_comb(f1, f2, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009f, 1.0f, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010f, 1.0f, 0.0009999999f), false);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.0009f, 100000.0f, 0.0009999999f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.010f, 100000.0f, 0.0009999999f), true);
}

TEST_CASE("mtl::approx_equal_comb with float")
{
    float f1 = 10.0009f;
    float f2 = 10.0f;
    REQUIRE_EQ(mtl::approx_equal_comb(f1, f2, 0.0009999999f, 0.0000099999f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009f, 1.0f, 0.0009999999f, 0.0000099999f), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010f, 1.0f, 0.0009999999f, 0.0000099999f), false);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.0009f, 100000.0f, 0.0009999999f, 0.0000099999f), 
                                      true);
    REQUIRE_EQ(mtl::approx_equal_comb(100000.010f, 100000.0f, 0.0009999999f, 0.0000099999f), true);
}


TEST_CASE("mtl::approx_equal_comb with double without providing the relative or abs value")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009, 1.0), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010, 1.0), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009, 10000000.0), true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010, 10000000.0), true);
}

TEST_CASE("mtl::approx_equal_comb with double without providing the relative value")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009, 1.0, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010, 1.0, 0.0009999999), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009, 10000000.0, 0.0009999999), true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010, 10000000.0, 0.0009999999), true);
}

TEST_CASE("mtl::approx_equal_comb with double")
{
    double d1 = 10.0009;
    double d2 = 10.0;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2, 0.0009999999, 0.0000099999), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009, 1.0, 0.0009999999, 0.0000099999), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010, 1.0, 0.0009999999, 0.0000099999), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009, 10000000.0, 0.0009999999, 0.0000099999), 
                                      true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010, 10000000.0, 0.0009999999, 0.0000099999), true);
}



TEST_CASE("mtl::approx_equal_comb with long double without providing the relative or abs value")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009L, 1.0L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010L, 1.0L), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009L, 10000000.0L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010L, 10000000.0L), true);
}

TEST_CASE("mtl::approx_equal_comb with long double without providing the relative value")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009L, 1.0L, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010L, 1.0L, 0.0009999999L), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009L, 10000000.0L, 0.0009999999L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010L, 10000000.0L, 0.0009999999L), true);
}

TEST_CASE("mtl::approx_equal_comb with long double")
{
    long double d1 = 10.0009L;
    long double d2 = 10.0L;
    REQUIRE_EQ(mtl::approx_equal_comb(d1, d2, 0.0009999999L, 0.0000099999L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0009L, 1.0L, 0.0009999999L, 0.0000099999L), true);
    REQUIRE_EQ(mtl::approx_equal_comb(1.0010L, 1.0L, 0.0009999999L, 0.0000099999L), false);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.0009L, 10000000.0L, 0.0009999999L, 0.0000099999L), 
                                      true);
    REQUIRE_EQ(mtl::approx_equal_comb(10000000.010L, 10000000.0L, 0.0009999999L, 0.0000099999L), 
                                      true);
}


// ------------------------------------------------------------------------------------------------
// mtl::percent_whole
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::percent_whole float")
{
    float v1 = mtl::percent_whole(100.0f, 10.0f);
    REQUIRE_GT(v1, 9.99f);
    REQUIRE_LT(v1, 10.01f);
    float v2 = mtl::percent_whole(10.0f, 10.0f);
    REQUIRE_GT(v2, 99.99f);
    REQUIRE_LT(v2, 100.01f);
    float v3 = mtl::percent_whole(1.0f, 10.0f);
    REQUIRE_GT(v3, 999.99f);
    REQUIRE_LT(v3, 1000.01f);

    
    float v4 = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    float result = 0.0f;
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0f, 10.0f), std::invalid_argument);
    REQUIRE_GT(v4, -0.01f);
    REQUIRE_LT(v4, 0.01f);
    REQUIRE_GT(result, 0.0f - 0.01f);
    REQUIRE_LT(result, 0.0f + 0.01f);
    
    float v5 = 0.0f;
    result = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0f, 0.0f), std::invalid_argument);
    REQUIRE_GT(v5, -0.01f);
    REQUIRE_LT(v5, 0.01f);
    REQUIRE_GT(result, 0.0f - 0.01f);
    REQUIRE_LT(result, 0.0f + 0.01f);


    float v6 = mtl::percent_whole(10.0f, 0.0f);
    REQUIRE_GT(v6, -0.01f);
    REQUIRE_LT(v6, 0.01f);
    float v7 = mtl::percent_whole(1.0f, 100.0f);
    REQUIRE_GT(v7, 9999.01f);
    REQUIRE_LT(v7, 10000.01f);
    float v8 = mtl::percent_whole(0.1f, 100.0f);
    REQUIRE_GT(v8, 99999.01f);
    REQUIRE_LT(v8, 100000.01f);

    float v9 = mtl::percent_whole(-10.0f, 10.0f);
    CHECK_GT(v9, -100.01l);
    CHECK_LT(v9, -99.99l);
    float v10 = mtl::percent_whole(10.0f, 10.0f);
    CHECK_GT(v10, 99.99f);
    CHECK_LT(v10, 100.01f);
    float v11 = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(v11 = mtl::percent_whole(0.0f, 10.0f), std::invalid_argument);
    CHECK_GT(v11, -0.01f);
    CHECK_LT(v11,  0.01f);
    
    // ---------
    constexpr float portion = 11.11f;

    std::vector<float> percent
    { 10.1f, 10.2f, 10.3f, 10.4f, 10.5f, 10.6f, 10.7f, 10.8f, 10.9f, 11.0f };

    std::vector<float> excepted
    { 109.99999f, 108.92157f, 107.86407f, 106.82693f, 105.80952f,  104.81131f, 103.83177f, 
      102.87037f, 101.92661f, 100.99999f };

    std::vector<float> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_whole(perc, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01f, value);
        CHECK_GT(excepted[i] + 0.01f, value);
    }   
}

TEST_CASE("mtl::percent_whole double")
{
    double v1 = mtl::percent_whole(100.0, 10.0);
    REQUIRE_GT(v1, 9.99);
    REQUIRE_LT(v1, 10.01);
    double v2 = mtl::percent_whole(10.0, 10.0);
    REQUIRE_GT(v2, 99.99);
    REQUIRE_LT(v2, 100.01);
    double v3 = mtl::percent_whole(1.0, 10.0);
    REQUIRE_GT(v3, 999.99);
    REQUIRE_LT(v3, 1000.01);

    
    double v4 = 0.0;
    double result = 0.0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0, 10.0), std::invalid_argument);
    REQUIRE_GT(v4, -0.01);
    REQUIRE_LT(v4, 0.01);
    REQUIRE_GT(result, 0.0 - 0.01);
    REQUIRE_LT(result, 0.0 + 0.01);
    
    double v5 = 0.0;
    result = 0.0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0, 0.0), std::invalid_argument);
    REQUIRE_GT(v5, -0.01);
    REQUIRE_LT(v5, 0.01);
    REQUIRE_GT(result, 0.0 - 0.01);
    REQUIRE_LT(result, 0.0 + 0.01);


    double v6 = mtl::percent_whole(10.0, 0.0);
    REQUIRE_GT(v6, -0.01);
    REQUIRE_LT(v6, 0.01);
    double v7 = mtl::percent_whole(1.0, 100.0);
    REQUIRE_GT(v7, 9999.01);
    REQUIRE_LT(v7, 10000.01);
    double v8 = mtl::percent_whole(0.1, 100.0);
    REQUIRE_GT(v8, 99999.01);
    REQUIRE_LT(v8, 100000.01);
    
    double v9 = mtl::percent_whole(-10.0, 10.0);
    CHECK_GT(v9, -100.01);
    CHECK_LT(v9, -99.99);
    double v10 = mtl::percent_whole(10.0, 10.0);
    CHECK_GT(v10, 99.99);
    CHECK_LT(v10, 100.01);
    double v11 = 0.0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(v11 = mtl::percent_whole(0.0, 10.0), std::invalid_argument);
    CHECK_GT(v11, -0.01);
    CHECK_LT(v11, 0.01);

    // ---------
    constexpr double portion = 11.11;

    std::vector<double> percent
    { 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9, 11.0 };

    std::vector<double> excepted
    { 109.99999, 108.92157, 107.86407, 106.82693, 105.80952,  104.81131, 103.83177,
      102.87037, 101.92661, 100.99999 };

    std::vector<double> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_whole(perc, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01, value);
        CHECK_GT(excepted[i] + 0.01, value);
    }
}

TEST_CASE("mtl::percent_whole long double")
{
    long double v1 = mtl::percent_whole(100.0l, 10.0l);
    REQUIRE_GT(v1, 9.99l);
    REQUIRE_LT(v1, 10.01l);
    long double v2 = mtl::percent_whole(10.0l, 10.0l);
    REQUIRE_GT(v2, 99.99l);
    REQUIRE_LT(v2, 100.01l);
    long double v3 = mtl::percent_whole(1.0l, 10.0l);
    REQUIRE_GT(v3, 999.99l);
    REQUIRE_LT(v3, 1000.01l);


    long double v4 = 0.0l;
    long double result = 0.0l;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0l, 10.0l), std::invalid_argument);
    REQUIRE_GT(v4, -0.01l);
    REQUIRE_LT(v4, 0.01l);
    REQUIRE_GT(result, 0.0l - 0.01l);
    REQUIRE_LT(result, 0.0l + 0.01l);

    long double v5 = 0.0l;
    result = 0.0l;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0.0l, 0.0l), std::invalid_argument);
    REQUIRE_GT(v5, -0.01l);
    REQUIRE_LT(v5, 0.01l);
    REQUIRE_GT(result, 0.0l - 0.01l);
    REQUIRE_LT(result, 0.0l + 0.01l);


    long double v6 = mtl::percent_whole(10.0l, 0.0l);
    REQUIRE_GT(v6, -0.01l);
    REQUIRE_LT(v6, 0.01l);
    long double v7 = mtl::percent_whole(1.0l, 100.0l);
    REQUIRE_GT(v7, 9999.01l);
    REQUIRE_LT(v7, 10000.01l);
    long double v8 = mtl::percent_whole(0.1l, 100.0l);
    REQUIRE_GT(v8, 99999.01l);
    REQUIRE_LT(v8, 100000.01l);

    
    long double v9 = mtl::percent_whole(-10.0l, 10.0l);
    CHECK_GT(v9, -100.01l);
    CHECK_LT(v9, -99.99l);
    long double v10 = mtl::percent_whole(10.0l, 10.0l);
    CHECK_GT(v10, 99.99l);
    CHECK_LT(v10, 100.01l);
    long double v11 = 0.0l;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(v11 = mtl::percent_whole(0.0l, 10.0l), std::invalid_argument);
    CHECK_GT(v11, -0.01l);
    CHECK_LT(v11, 0.01l);

    // ---------
    constexpr long double portion = 11.11l;

    std::vector<long double> percent
    { 10.1l, 10.2l, 10.3l, 10.4l, 10.5l, 10.6l, 10.7l, 10.8l, 10.9l, 11.0l };

    std::vector<long double> excepted
    { 109.99999l, 108.92157l, 107.86407l, 106.82693l, 105.80952l,  104.81131l, 103.83177l,
      102.87037l, 101.92661l, 100.99999l };

    std::vector<long double> results;
    results.reserve(percent.size());

    for(auto & perc : percent)
    {
        results.push_back(mtl::percent_whole(perc, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for(size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality lor float point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01l, value);
        CHECK_GT(excepted[i] + 0.01l, value);
    }
}

TEST_CASE("mtl::percent_whole int")
{
    int v1 = mtl::percent_whole(100, 10);
    REQUIRE_EQ(v1, 10);
    int v2 = mtl::percent_whole(10, 10);
    REQUIRE_EQ(v2, 100);
    int v3 = mtl::percent_whole(1, 10);
    REQUIRE_EQ(v3, 1000);
    
    
    int v4 = 0;
    int result = 0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0, 10), std::invalid_argument);
    REQUIRE_EQ(v4, 0);
    REQUIRE_EQ(result , 0);

    int v5 = 0;
    result = 0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent_whole(0, 0), std::invalid_argument);
    REQUIRE_EQ(v5, 0);
    REQUIRE_EQ(result , 0);


    int v6 = mtl::percent_whole(10, 0);
    REQUIRE_EQ(v6, 0);
    int v7 = mtl::percent_whole(1, 100);
    REQUIRE_EQ(v7, 10000);
    int v8 = mtl::percent_whole(1, 1000);
    REQUIRE_EQ(v8, 100000);

    int v9 = mtl::percent_whole(-10, 10);
    CHECK_EQ(v9, -100);
    int v10 = mtl::percent_whole(10, 10);
    CHECK_EQ(v10, 100);
    int v11 = 0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(v11 = mtl::percent_whole(0, 10), std::invalid_argument);
    CHECK_EQ(v11, 0);

    // ---------
    constexpr int portion = 11;

    std::vector<int> percent
    { 10, 11, 12, 13, 14, 15, 16,  17, 18, 19, 20 };

    std::vector<int> excepted
    { 110, 100, 92, 85, 79, 73, 69, 65, 61, 58, 55 };

    std::vector<int> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_whole(perc, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        CHECK_EQ(excepted[i], results[i]);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::percent_portion
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::percent_portion float")
{
    float v1 = mtl::percent_portion(100.0f, 10.0f);
    REQUIRE_GT(v1, 9.99f);
    REQUIRE_LT(v1, 10.01f);
    float v2 = mtl::percent_portion(10.0f, 10.0f);
    REQUIRE_GT(v2, 0.99f);
    REQUIRE_LT(v2, 1.01f);
    float v3 = mtl::percent_portion(1.0f, 10.0f);
    REQUIRE_GT(v3, 0.099f);
    REQUIRE_LT(v3, 0.11f);
    float v4 = mtl::percent_portion(0.0f, 10.0f);
    REQUIRE_GT(v4, -0.01f);
    REQUIRE_LT(v4, 0.01f);
    float v5 = mtl::percent_portion(10.0f, 0.0f);
    REQUIRE_GT(v5, -0.01f);
    REQUIRE_LT(v5, 0.01f);
    float v6 = mtl::percent_portion(0.0f, 0.0f);
    REQUIRE_GT(v6, -0.01f);
    REQUIRE_LT(v6, 0.01f);


    // ---------
    constexpr float whole = 2222.2222f;

    std::vector<float> percent
    { 10.1f, 10.2f, 10.3f, 10.4f, 10.5f, 10.6f, 10.7f, 10.8f, 10.9f, 11.0f };

    std::vector<float> excepted
    { 224.44444f, 226.66666f, 228.88889f, 231.11108f, 233.33331f, 235.55556f, 237.77777f,
      240.0f, 242.2222f, 244.44443f };

    std::vector<float> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_portion(whole, perc));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01f, value);
        CHECK_GT(excepted[i] + 0.01f, value);
    }
}


TEST_CASE("mtl::percent_portion double")
{
    double v1 = mtl::percent_portion(100.0, 10.0);
    REQUIRE_GT(v1, 9.99);
    REQUIRE_LT(v1, 10.01);
    double v2 = mtl::percent_portion(10.0, 10.0);
    REQUIRE_GT(v2, 0.99);
    REQUIRE_LT(v2, 1.01);
    double v3 = mtl::percent_portion(1.0, 10.0);
    REQUIRE_GT(v3, 0.099);
    REQUIRE_LT(v3, 0.11);
    double v4 = mtl::percent_portion(0.0, 10.0);
    REQUIRE_GT(v4, -0.01);
    REQUIRE_LT(v4, 0.01);
    double v5 = mtl::percent_portion(10.0, 0.0);
    REQUIRE_GT(v5, -0.01);
    REQUIRE_LT(v5, 0.01);
    double v6 = mtl::percent_portion(0.0, 0.0);
    REQUIRE_GT(v6, -0.01);
    REQUIRE_LT(v6, 0.01);

    // ---------
    constexpr double whole = 2222.2222;

    std::vector<double> percent
    { 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9, 11.0 };

    std::vector<double> excepted
    { 224.44444, 226.66666, 228.88889, 231.11108, 233.33331, 235.55556, 237.77777,
      240.0, 242.2222, 244.44443 };

    std::vector<double> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_portion(whole, perc));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01, value);
        CHECK_GT(excepted[i] + 0.01, value);
    }
}


TEST_CASE("mtl::percent_portion long double")
{
    long double v1 = mtl::percent_portion(100.0l, 10.0l);
    REQUIRE_GT(v1, 9.99l);
    REQUIRE_LT(v1, 10.01l);
    long double v2 = mtl::percent_portion(10.0l, 10.0l);
    REQUIRE_GT(v2, 0.99l);
    REQUIRE_LT(v2, 1.01l);
    long double v3 = mtl::percent_portion(1.0l, 10.0l);
    REQUIRE_GT(v3, 0.099l);
    REQUIRE_LT(v3, 0.11l);
    long double v4 = mtl::percent_portion(0.0l, 10.0l);
    REQUIRE_GT(v4, -0.01l);
    REQUIRE_LT(v4, 0.01l);
    long double v5 = mtl::percent_portion(10.0l, 0.0l);
    REQUIRE_GT(v5, -0.01l);
    REQUIRE_LT(v5, 0.01l);
    long double v6 = mtl::percent_portion(0.0l, 0.0l);
    REQUIRE_GT(v6, -0.01l);
    REQUIRE_LT(v6, 0.01l);


    // ---------
    constexpr long double whole = 2222.2222l;

    std::vector<long double> percent
    { 10.1l, 10.2l, 10.3l, 10.4l, 10.5l, 10.6l, 10.7l, 10.8l, 10.9l, 11.0l };

    std::vector<long double> excepted
    { 224.44444l, 226.66666l, 228.88889l, 231.11108l, 233.33331l, 235.55556l, 237.77777l,
      240.0l, 242.2222l, 244.44443l };

    std::vector<long double> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_portion(whole, perc));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        // approximate equality lor float point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01l, value);
        CHECK_GT(excepted[i] + 0.01l, value);
    }
}

TEST_CASE("mtl::percent_portion int")
{
    int v1 = mtl::percent_portion(100, 10);
    REQUIRE_EQ(v1, 10);
    int v2 = mtl::percent_portion(10, 10);
    REQUIRE_EQ(v2, 1);
    int v3 = mtl::percent_portion(1, 10);
    REQUIRE_EQ(v3, 0);
    int v4 = mtl::percent_portion(0, 10);
    REQUIRE_EQ(v4, 0);
    int v5 = mtl::percent_portion(10, 0);
    REQUIRE_EQ(v5, 0);
    int v6 = mtl::percent_portion(0, 0);
    REQUIRE_EQ(v6, 0);

    // ---------
    constexpr int whole = 2222;

    std::vector<int> percent
    { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    std::vector<int> excepted
    { 244, 267, 289, 311, 333, 356, 378, 400, 422, 444 };

    std::vector<int> results;
    results.reserve(percent.size());

    for (auto& perc : percent)
    {
        results.push_back(mtl::percent_portion(whole, perc));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < percent.size(); i++)
    {
        CHECK_EQ(excepted[i], results[i]);
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::percent
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::percent float")
{
    float v1 = mtl::percent(100.0f, 10.0f);
    REQUIRE_GT(v1, 9.99f);
    REQUIRE_LT(v1, 10.01f);
    float v2 = mtl::percent(10.0f, 10.0f);
    REQUIRE_GT(v2, 99.99f);
    REQUIRE_LT(v2, 100.01f);
    float v3 = mtl::percent(1.0f, 10.0f);
    REQUIRE_GT(v3, 999.99f);
    REQUIRE_LT(v3, 1000.01f);
    float v4 = mtl::percent(10.0f, 0.0f);
    REQUIRE_GT(v4, -0.01f);
    REQUIRE_LT(v4, 0.01f);

    
    float v5 = 0.0f;
    float result = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0f, 10.0f), std::invalid_argument);
    REQUIRE_GT(v5, -0.01f);
    REQUIRE_LT(v5,  0.01f);
    REQUIRE_GT(result, 0.0f - 0.01f);
    REQUIRE_LT(result, 0.0f + 0.01f);
    
    float v6 = 0.0f;
    result = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0f, 0.0f), std::invalid_argument);
    REQUIRE_GT(v6, -0.01f);
    REQUIRE_LT(v6, 0.01f);
    REQUIRE_GT(result, 0.0f - 0.01f);
    REQUIRE_LT(result, 0.0f + 0.01f);

    float v9 = mtl::percent(-10.0f, 10.0f);
    CHECK_GT(v9, -100.01l);
    CHECK_LT(v9, -99.99l);
    float v10 = mtl::percent(10.0f, 10.0f);
    CHECK_GT(v10, 99.99f);
    CHECK_LT(v10, 100.01f);
    float v11 = 0.0f;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(v11 = mtl::percent(0.0f, 10.0f), std::invalid_argument);
    CHECK_GT(v11, -0.01f);
    CHECK_LT(v11,  0.01f);

    // ---------
    constexpr float whole = 2222.2222f;

    std::vector<float> portions
    { 1001.1f, 1002.2f, 1003.3f, 1004.4f, 1005.5f, 1006.6f, 1007.7f, 1008.8f, 1009.9f, 1011.0f };

    std::vector<float> excepted
    { 45.0495f, 45.099f, 45.1485f, 45.198f, 45.2475f, 45.297f, 45.3465f,
      45.396f,  45.4455f, 45.495f };

    std::vector<float> results;
    results.reserve(portions.size());

    for (auto& portion : portions)
    {
        results.push_back(mtl::percent(whole, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < portions.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01f, value);
        CHECK_GT(excepted[i] + 0.01f, value);
    }
}

TEST_CASE("mtl::percent double")
{
    double v1 = mtl::percent(100.0, 10.0);
    REQUIRE_GT(v1, 9.99);
    REQUIRE_LT(v1, 10.01);
    double v2 = mtl::percent(10.0, 10.0);
    REQUIRE_GT(v2, 99.99);
    REQUIRE_LT(v2, 100.01);
    double v3 = mtl::percent(1.0, 10.0);
    REQUIRE_GT(v3, 999.99);
    REQUIRE_LT(v3, 1000.01);
    double v4 = mtl::percent(10.0, 0.0);
    REQUIRE_GT(v4, -0.01);
    REQUIRE_LT(v4, 0.01);

    
    double v5 = 0.0;
    double result = 0.0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0, 10.0), std::invalid_argument);
    REQUIRE_GT(v5, -0.01);
    REQUIRE_LT(v5, 0.01);
    REQUIRE_GT(result, 0.0 - 0.01);
    REQUIRE_LT(result, 0.0 + 0.01);
    
    double v6 = 0.0;
    result = 0.0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0, 0.0), std::invalid_argument);
    REQUIRE_GT(v6, -0.01);
    REQUIRE_LT(v6, 0.01);
    REQUIRE_GT(result, 0.0 - 0.01);
    REQUIRE_LT(result, 0.0 + 0.01);


    // ---------
    constexpr double whole = 2222.2222;

    std::vector<double> portions
    { 1001.1, 1002.2, 1003.3, 1004.4, 1005.5, 1006.6, 1007.7, 1008.8, 1009.9, 1011.0 };

    std::vector<double> excepted
    { 45.0495, 45.099, 45.1485, 45.198, 45.2475, 45.297, 45.3465,
      45.396,  45.4455, 45.495 };

    std::vector<double> results;
    results.reserve(portions.size());

    for (auto& portion : portions)
    {
        results.push_back(mtl::percent(whole, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < portions.size(); i++)
    {
        // approximate equality for floating point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01, value);
        CHECK_GT(excepted[i] + 0.01, value);
    }
}


TEST_CASE("mtl::percent long double")
{
    long double v1 = mtl::percent(100.0l, 10.0l);
    REQUIRE_GT(v1, 9.99l);
    REQUIRE_LT(v1, 10.01l);
    long double v2 = mtl::percent(10.0l, 10.0l);
    REQUIRE_GT(v2, 99.99l);
    REQUIRE_LT(v2, 100.01l);
    long double v3 = mtl::percent(1.0l, 10.0l);
    REQUIRE_GT(v3, 999.99l);
    REQUIRE_LT(v3, 1000.01l);
    long double v4 = mtl::percent(10.0l, 0.0l);
    REQUIRE_GT(v4, -0.99l);
    REQUIRE_LT(v4, 0.01l);


    long double v5 = 0.0l;
    long double result = 0.0l;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0l, 10.0l), std::invalid_argument);
    REQUIRE_GT(v5, -0.99l);
    REQUIRE_LT(v5, 0.01l);
    REQUIRE_GT(result, 0.0l - 0.01l);
    REQUIRE_LT(result, 0.0l + 0.01l);

    long double v6 = 0.0l;
    result = 0.0l;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0.0l, 0.0l), std::invalid_argument);
    REQUIRE_GT(v6, -0.01l);
    REQUIRE_LT(v6, 0.01l);
    REQUIRE_GT(result, 0.0l - 0.01l);
    REQUIRE_LT(result, 0.0l + 0.01l);

    // ---------
    constexpr long double whole = 2222.2222l;

    std::vector<long double> portions
    { 1001.1l, 1002.2l, 1003.3l, 1004.4l, 1005.5l, 1006.6l, 1007.7l, 1008.8l, 1009.9l, 1011.0l };

    std::vector<long double> excepted
    { 45.0495l, 45.099l, 45.1485l, 45.198l, 45.2475l, 45.297l, 45.3465l,
      45.396l,  45.4455l, 45.495l };

    std::vector<long double> results;
    results.reserve(portions.size());

    for (auto& portion : portions)
    {
        results.push_back(mtl::percent(whole, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < portions.size(); i++)
    {
        // approximate equality lor long doubleing point numbers
        auto value = results[i];
        CHECK_LT(excepted[i] - 0.01l, value);
        CHECK_GT(excepted[i] + 0.01l, value);
    }
}


TEST_CASE("mtl::percent int")
{
    int v1 = mtl::percent(100, 10);
    REQUIRE_EQ(v1, 10);
    int v2 = mtl::percent(10, 10);
    REQUIRE_EQ(v2, 100);
    int v3 = mtl::percent(1, 10);
    REQUIRE_EQ(v3, 1000);
    int v5 = mtl::percent(10, 0);
    REQUIRE_EQ(v5, 0);


    int v4 = 0;
    int result = 0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0, 10), std::invalid_argument);
    REQUIRE_EQ(v4, 0);
    REQUIRE_EQ(result, 0);

    int v6 = 0;
    result = 0;
    // division by zero, throws because MTL_DIV_ZERO_THROW was defined
    REQUIRE_THROWS_AS(result = mtl::percent(0, 0), std::invalid_argument);
    REQUIRE_EQ(v6, 0);
    REQUIRE_EQ(result, 0);

    // ---------
    constexpr int whole = 2222;

    std::vector<int> portions
    { 1011, 1022, 1033, 1044, 1055, 1066, 1077, 1088, 1099, 1111 };

    std::vector<int> excepted
    { 45, 46, 46, 47, 47, 48, 48, 49, 49, 50 };

    std::vector<int> results;
    results.reserve(portions.size());

    for (auto& portion : portions)
    {
        results.push_back(mtl::percent(whole, portion));
    }

    REQUIRE_EQ(excepted.size(), results.size());
    for (size_t i = 0; i < portions.size(); i++)
    {
        CHECK_EQ(excepted[i], results[i]);
    }
}