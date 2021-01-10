// tests by Michael Trikergiotis
// 28/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <string>     // std::string
#include <utility>    // std::pair, std::make_pair
#include <limits>     // std::numeric_limits
#include <stdexcept>  // std::invalid_argument, std::overflow_error


// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/conversion.hpp" 
// mtl::to_num, mtl::to_num_noex, mtl::numeric_cast, mtl::numeric_cast_noex, 
// mtl::rounding_cast, mtl::rounding_cast_noex


// ------------------------------------------------------------------------------------------------
// setup min and max variables for the tests
// ------------------------------------------------------------------------------------------------
constexpr auto i8_min = std::numeric_limits<int8_t>::min();
constexpr auto i8_max = std::numeric_limits<int8_t>::max();

constexpr auto i16_min = std::numeric_limits<int16_t>::min();
constexpr auto i16_max = std::numeric_limits<int16_t>::max();

constexpr auto i32_min = std::numeric_limits<int32_t>::min();
constexpr auto i32_max = std::numeric_limits<int32_t>::max();

constexpr auto i64_min = std::numeric_limits<int64_t>::min();
constexpr auto i64_max = std::numeric_limits<int64_t>::max();

constexpr auto ui8_min = std::numeric_limits<uint8_t>::min();
constexpr auto ui8_max = std::numeric_limits<uint8_t>::max();

constexpr auto ui16_min = std::numeric_limits<uint16_t>::min();
constexpr auto ui16_max = std::numeric_limits<uint16_t>::max();

constexpr auto ui32_min = std::numeric_limits<uint32_t>::min();
constexpr auto ui32_max = std::numeric_limits<uint32_t>::max();

constexpr auto ui64_min = std::numeric_limits<uint64_t>::min();
constexpr auto ui64_max = std::numeric_limits<uint64_t>::max();

// for floating point type numbers lowest possible number you have to use lowest instead of min
constexpr auto f_min = std::numeric_limits<float>::lowest();
constexpr auto f_max = std::numeric_limits<float>::max();

constexpr auto d_min = std::numeric_limits<double>::lowest();
constexpr auto d_max = std::numeric_limits<double>::max();

constexpr auto ld_min = std::numeric_limits<long double>::lowest();
constexpr auto ld_max = std::numeric_limits<long double>::max();







// -----------------------------------------------------------------------------
// mtl::to_num
// -----------------------------------------------------------------------------


TEST_CASE("mtl::to_num floating point types with scientific notation")
{
    std::string number = "4.0e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with scientific notation without zeros")
{
    std::string number = "4.e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with scientific notation, capital E")
{
    std::string number = "4.0E2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with incorrect character, whole part")
{
    std::string number = "k4.0e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_THROWS_AS(f = mtl::to_num(number), std::invalid_argument);
    REQUIRE_THROWS_AS(d = mtl::to_num(number), std::invalid_argument);
    REQUIRE_THROWS_AS(ld = mtl::to_num(number), std::invalid_argument);

    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with incorrect character, demical part")
{
    std::string number = "4.0g2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_THROWS_AS(f = mtl::to_num(number), std::invalid_argument);
    REQUIRE_THROWS_AS(d = mtl::to_num(number), std::invalid_argument);
    REQUIRE_THROWS_AS(ld = mtl::to_num(number), std::invalid_argument);

    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with scientific notation, starting + symbol")
{
    std::string number = "+4.0e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with scientific notation, + symbol notation")
{
    std::string number = "4.0e+2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point types with scientific notation, negative number")
{
    std::string number = "-4.0e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = -400.0F;
    double d2 = -400.0;
    long double ld2 = -400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point with scientific notation, negative in the notation")
{
    std::string number = "4.0e-2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 0.04F;
    double d2 = 0.04;
    long double ld2 = 0.04L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}


TEST_CASE("mtl::to_num floating point types with scientific notation, not round")
{
    std::string number = "3.1432e2";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 314.32F;
    double d2 = 314.32;
    long double ld2 = 314.32L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point not round")
{
    std::string number = "314.32";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 314.32F;
    double d2 = 314.32;
    long double ld2 = 314.32L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num floating point not round")
{
    std::string number = "3104.092";
    float f = 0.0f;
    double d = 0.0;
    long double ld = 0.0L;
    REQUIRE_NOTHROW(f = mtl::to_num(number));
    REQUIRE_NOTHROW(d = mtl::to_num(number));
    REQUIRE_NOTHROW(ld = mtl::to_num(number));

    float f2 = 3104.092F;
    double d2 = 3104.092;
    long double ld2 = 3104.092L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num with int8_t/int16_t/int32_t/int64_t etc. types")
{
    std::string number = "10";
    int8_t     i8 = mtl::to_num(number);
    int16_t   i16 = mtl::to_num(number);
    int32_t   i32 = mtl::to_num(number);
    int64_t   i64 = mtl::to_num(number);
    uint8_t   ui8 = mtl::to_num(number);
    uint16_t ui16 = mtl::to_num(number);
    uint32_t ui32 = mtl::to_num(number);
    uint64_t ui64 = mtl::to_num(number);

    int8_t     i8_2 = static_cast<int8_t>(10);
    int16_t   i16_2 = static_cast<int16_t>(10);
    int32_t   i32_2 = static_cast<int32_t>(10);
    int64_t   i64_2 = static_cast<int64_t>(10);
    uint8_t   ui8_2 = static_cast<uint8_t>(10);
    uint16_t ui16_2 = static_cast<uint16_t>(10);
    uint32_t ui32_2 = static_cast<uint32_t>(10);
    uint64_t ui64_2 = static_cast<uint64_t>(10);

    CHECK_EQ(i8, i8_2);
    CHECK_EQ(i16, i16_2);
    CHECK_EQ(i32, i32_2);
    CHECK_EQ(i64, i64_2);
    CHECK_EQ(ui8, ui8_2);
    CHECK_EQ(ui16, ui16_2);
    CHECK_EQ(ui32, ui32_2);
    CHECK_EQ(ui64, ui64_2);
}

TEST_CASE("mtl::to_num")
{
    std::string number = "100";
    int i = mtl::to_num(number);
    long l = mtl::to_num(number);
    long long ll = mtl::to_num(number);
    unsigned int ui = mtl::to_num(number);
    unsigned long ul = mtl::to_num(number);
    unsigned long long ull = mtl::to_num(number);
    float f = mtl::to_num(number);
    double d = mtl::to_num(number);
    long double ld = mtl::to_num(number);

    int i2 = 100;
    long l2 = 100L;
    long long ll2 = 100LL;
    unsigned int ui2 = 100U;
    unsigned long ul2 = 100UL;
    unsigned long long ull2 = 100ULL;
    float f2 = 100.0F;
    double d2 = 100.0;
    long double ld2 = 100.0L;

    REQUIRE_EQ(i, i2);
    REQUIRE_EQ(l, l2);
    REQUIRE_EQ(ll, ll2);
    REQUIRE_EQ(ui, ui2);
    REQUIRE_EQ(ul, ul2);
    REQUIRE_EQ(ull, ull2);
    // floating point approximately equal
    REQUIRE_GT(f, f2 - 0.001f);
    REQUIRE_LT(f, f2 + 0.001f);
    REQUIRE_GT(d, d2 - 0.001);
    REQUIRE_LT(d, d2 + 0.001);
    REQUIRE_GT(ld, ld2 - 0.001L);
    REQUIRE_LT(ld, ld2 + 0.001L);
}

TEST_CASE("mtl::to_num not convertible because it is empty")
{
    std::string number = "";
    [[maybe_unused]] int i = 0;
    REQUIRE_THROWS((i = mtl::to_num(number)));
    [[maybe_unused]] long l = 0L;
    REQUIRE_THROWS(l = mtl::to_num(number));
    [[maybe_unused]] long long ll = 0LL;
    REQUIRE_THROWS(ll = mtl::to_num(number));
    [[maybe_unused]] unsigned int ui = 0U;
    REQUIRE_THROWS(ui = mtl::to_num(number));
    [[maybe_unused]] unsigned long ul = 0UL;
    REQUIRE_THROWS(ul = mtl::to_num(number));
    [[maybe_unused]] unsigned long long ull = 0ULL;
    REQUIRE_THROWS(ull = mtl::to_num(number));
    [[maybe_unused]] float f = 0.0F;
    REQUIRE_THROWS(f = mtl::to_num(number));
    [[maybe_unused]] double d = 0.0;
    REQUIRE_THROWS(d = mtl::to_num(number));
    [[maybe_unused]] long double ld = 0.0L;
    REQUIRE_THROWS(ld = mtl::to_num(number));

}

TEST_CASE("mtl::to_num not convertible value")
{
    std::string number = "Value that can't be converted.";
    [[maybe_unused]] int i = 0;
    REQUIRE_THROWS((i = mtl::to_num(number)));
    [[maybe_unused]] long l = 0L;
    REQUIRE_THROWS(l = mtl::to_num(number));
    [[maybe_unused]] long long ll = 0LL;
    REQUIRE_THROWS(ll = mtl::to_num(number));
    [[maybe_unused]] unsigned int ui = 0U;
    REQUIRE_THROWS(ui = mtl::to_num(number));
    [[maybe_unused]] unsigned long ul = 0UL;
    REQUIRE_THROWS(ul = mtl::to_num(number));
    [[maybe_unused]] unsigned long long ull = 0ULL;
    REQUIRE_THROWS(ull = mtl::to_num(number));
    [[maybe_unused]] float f = 0.0F;
    REQUIRE_THROWS(f = mtl::to_num(number));
    [[maybe_unused]] double d = 0.0;
    REQUIRE_THROWS(d = mtl::to_num(number));
    [[maybe_unused]] long double ld = 0.0L;
    REQUIRE_THROWS(ld = mtl::to_num(number));

}





// -----------------------------------------------------------------------------
// mtl::to_num_noex with bool
// -----------------------------------------------------------------------------


TEST_CASE("mtl::to_num_noex floating point types with scientific notation")
{
    std::string number = "4.0e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point types with scientific notation, without zeroes")
{
    std::string number = "4.e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point types with scientific notation, capital E")
{
    std::string number = "4.0E2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point with with incorrect character, whole part")
{
    std::string number = "h4.0e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);

    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point with with incorrect character, demical part")
{
    std::string number = "4.0te2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);

    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}


TEST_CASE("mtl::to_num_noex floating point with scientific notation, starting + symbol")
{
    std::string number = "+4.0e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point with scientific notation, + symbol in notation")
{
    std::string number = "4.0e+2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 400.0F;
    double d2 = 400.0;
    long double ld2 = 400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point with scientific notation, negative number")
{
    std::string number = "-4.0e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = -400.0F;
    double d2 = -400.0;
    long double ld2 = -400.0L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point with scientific notation, - symbol in notation")
{
    std::string number = "4.0e-2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 0.04F;
    double d2 = 0.04;
    long double ld2 = 0.04L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}


TEST_CASE("mtl::to_num_noex floating point types with scientific notation, not round")
{
    std::string number = "3.1432e2";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 314.32F;
    double d2 = 314.32;
    long double ld2 = 314.32L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point not round")
{
    std::string number = "314.32";
    bool success = false;
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    float f2 = 314.32F;
    double d2 = 314.32;
    long double ld2 = 314.32L;

    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f, (f2 + 0.01F));
    REQUIRE_LT(d, (d2 + 0.01));
    REQUIRE_LT(ld, (ld2 + 0.01L));
    REQUIRE_GT(f, (f2 - 0.01F));
    REQUIRE_GT(d, (d2 - 0.01));
    REQUIRE_GT(ld, (ld2 - 0.01L));
}


TEST_CASE("mtl::to_num_noex with int8_t/int16_t/int32_t/int64_t etc. types")
{
    std::string number = "10";
    bool success = false;
    int8_t     i8 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    int16_t   i16 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    int32_t   i32 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    int64_t   i64 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    uint8_t   ui8 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    uint16_t ui16 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    uint32_t ui32 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    uint64_t ui64 = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    int8_t     i8_2 = static_cast<int8_t>(10);
    int16_t   i16_2 = static_cast<int16_t>(10);
    int32_t   i32_2 = static_cast<int32_t>(10);
    int64_t   i64_2 = static_cast<int64_t>(10);
    uint8_t   ui8_2 = static_cast<uint8_t>(10);
    uint16_t ui16_2 = static_cast<uint16_t>(10);
    uint32_t ui32_2 = static_cast<uint32_t>(10);
    uint64_t ui64_2 = static_cast<uint64_t>(10);

    REQUIRE_EQ(i8, i8_2);
    REQUIRE_EQ(i16, i16_2);
    REQUIRE_EQ(i32, i32_2);
    REQUIRE_EQ(i64, i64_2);
    REQUIRE_EQ(ui8, ui8_2);
    REQUIRE_EQ(ui16, ui16_2);
    REQUIRE_EQ(ui32, ui32_2);
    REQUIRE_EQ(ui64, ui64_2);
}


TEST_CASE("mtl::to_num_noex")
{
    std::string number = "100";
    bool success = false;
    int i = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long l = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long long ll = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    unsigned int ui = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    unsigned long ul = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    unsigned long long ull = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, true);

    int i2 = 100;
    long l2 = 100L;
    long long ll2 = 100LL;
    unsigned int ui2 = 100U;
    unsigned long ul2 = 100UL;
    unsigned long long ull2 = 100ULL;
    float f2 = 100.0F;
    double d2 = 100.0;
    long double ld2 = 100.0L;

    REQUIRE_EQ(i, i2);
    REQUIRE_EQ(l, l2);
    REQUIRE_EQ(ll, ll2);
    REQUIRE_EQ(ui, ui2);
    REQUIRE_EQ(ul, ul2);
    REQUIRE_EQ(ull, ull2);
    // floating point approximately equal
    REQUIRE_GT(f, f2 - 0.001f);
    REQUIRE_LT(f, f2 + 0.001f);
    REQUIRE_GT(d, d2 - 0.001);
    REQUIRE_LT(d, d2 + 0.001);
    REQUIRE_GT(ld, ld2 - 0.001L);
    REQUIRE_LT(ld, ld2 + 0.001L);
}

TEST_CASE("mtl::to_num_noex not convertible because it is empty")
{
    std::string number = "";
    bool success = true;
    int i = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long l = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long long ll = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned int ui = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned long ul = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned long long ull = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);

    int i2 = 0;
    long l2 = 0L;
    long long ll2 = 0LL;
    unsigned int ui2 = 0U;
    unsigned long ul2 = 0UL;
    unsigned long long ull2 = 0ULL;
    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // even when it is not convertible the number is set to 0 with mtl::to_num_noex
    REQUIRE_EQ(i, i2);
    REQUIRE_EQ(l, l2);
    REQUIRE_EQ(ll, ll2);
    REQUIRE_EQ(ui, ui2);
    REQUIRE_EQ(ul, ul2);
    REQUIRE_EQ(ull, ull2);
    // floating point approximately equal
    REQUIRE_GT(f, f2 - 0.001f);
    REQUIRE_LT(f, f2 + 0.001f);
    REQUIRE_GT(d, d2 - 0.001);
    REQUIRE_LT(d, d2 + 0.001);
    REQUIRE_GT(ld, ld2 - 0.001L);
    REQUIRE_LT(ld, ld2 + 0.001L);
}

TEST_CASE("mtl::to_num_noex not convertible value")
{
    std::string number = "Value that can't be converted.";
    bool success = true;
    int i = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long l = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long long ll = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned int ui = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned long ul = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    unsigned long long ull = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    float f = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    double d = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);
    long double ld = mtl::to_num_noex(number, success);
    REQUIRE_EQ(success, false);

    int i2 = 0;
    long l2 = 0L;
    long long ll2 = 0LL;
    unsigned int ui2 = 0U;
    unsigned long ul2 = 0UL;
    unsigned long long ull2 = 0ULL;
    float f2 = 0.0F;
    double d2 = 0.0;
    long double ld2 = 0.0L;

    // even when it is not convertible the number is set to 0 with mtl::to_num_noex
    REQUIRE_EQ(i, i2);
    REQUIRE_EQ(l, l2);
    REQUIRE_EQ(ll, ll2);
    REQUIRE_EQ(ui, ui2);
    REQUIRE_EQ(ul, ul2);
    REQUIRE_EQ(ull, ull2);
    // floating point approximately equal
    REQUIRE_GT(f, f2 - 0.001f);
    REQUIRE_LT(f, f2 + 0.001f);
    REQUIRE_GT(d, d2 - 0.001);
    REQUIRE_LT(d, d2 + 0.001);
    REQUIRE_GT(ld, ld2 - 0.001L);
    REQUIRE_LT(ld, ld2 + 0.001L);
}


// -----------------------------------------------------------------------------
// mtl::to_num_noex with std::pair
// -----------------------------------------------------------------------------

TEST_CASE("mtl::to_num_noex with std::pair, floating point types with scientific notation")
{
    std::string number = "4.0e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(400.0F, true);
    auto d2 = std::make_pair<double, bool>(400.0, true);
    auto ld2 = std::make_pair<long double, bool>(400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point with scientific notation, no zeroes")
{
    std::string number = "4.e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(400.0F, true);
    auto d2 = std::make_pair<double, bool>(400.0, true);
    auto ld2 = std::make_pair<long double, bool>(400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point with scientific notation, capital E")
{
    std::string number = "4.0E2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(400.0F, true);
    auto d2 = std::make_pair<double, bool>(400.0, true);
    auto ld2 = std::make_pair<long double, bool>(400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point, incorrect character, whole part")
{
    std::string number = "j4.0e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);

    auto f2 = std::make_pair<float, bool>(0.0F, false);
    auto d2 = std::make_pair<double, bool>(0.0, false);
    auto ld2 = std::make_pair<long double, bool>(0.0L, false);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point incorrect character, demical part")
{
    std::string number = "4.0je2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);

    auto f2 = std::make_pair<float, bool>(0.0F, false);
    auto d2 = std::make_pair<double, bool>(0.0, false);
    auto ld2 = std::make_pair<long double, bool>(0.0L, false);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}


TEST_CASE("mtl::to_num_noex std::pair, floating point scientific notation, starting +")
{
    std::string number = "+4.0e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(400.0F, true);
    auto d2 = std::make_pair<double, bool>(400.0, true);
    auto ld2 = std::make_pair<long double, bool>(400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point, scientific notation, containing +")
{
    std::string number = "4.0e+2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(400.0F, true);
    auto d2 = std::make_pair<double, bool>(400.0, true);
    auto ld2 = std::make_pair<long double, bool>(400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point with scientific notation, negative")
{
    std::string number = "-4.0e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(-400.0F, true);
    auto d2 = std::make_pair<double, bool>(-400.0, true);
    auto ld2 = std::make_pair<long double, bool>(-400.0L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex std::pair, floating point scientific notation, contains -")
{
    std::string number = "4.0e-2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(0.04F, true);
    auto d2 = std::make_pair<double, bool>(0.04, true);
    auto ld2 = std::make_pair<long double, bool>(0.04L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}




TEST_CASE("mtl::to_num_noex with std::pair, floating point scientific notation, not round")
{
    std::string number = "3.1432e2";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(314.32F, true);
    auto d2 = std::make_pair<double, bool>(314.32, true);
    auto ld2 = std::make_pair<long double, bool>(314.32L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}

TEST_CASE("mtl::to_num_noex floating point not round")
{
    std::string number = "314.32";
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);

    auto f2 = std::make_pair<float, bool>(314.32F, true);
    auto d2 = std::make_pair<double, bool>(314.32, true);
    auto ld2 = std::make_pair<long double, bool>(314.32L, true);

    REQUIRE_EQ(f.second, f2.second);
    REQUIRE_EQ(d.second, d2.second);
    REQUIRE_EQ(ld.second, ld2.second);
    // due to floating point numbers not being exact we have to do approximately equal
    // instead of equal
    REQUIRE_LT(f.first, (f2.first + 0.01F));
    REQUIRE_LT(d.first, (d2.first + 0.01));
    REQUIRE_LT(ld.first, (ld2.first + 0.01L));
    REQUIRE_GT(f.first, (f2.first - 0.01F));
    REQUIRE_GT(d.first, (d2.first - 0.01));
    REQUIRE_GT(ld.first, (ld2.first - 0.01L));
}


TEST_CASE("mtl::to_num_noex with std::pair with int8_t/int16_t/int32_t/int64_t etc. types")
{
    std::string number = "10";
    std::pair<int8_t, bool>     i8 = mtl::to_num_noex(number);
    REQUIRE_EQ(i8.second, true);
    std::pair<int16_t, bool>   i16 = mtl::to_num_noex(number);
    REQUIRE_EQ(i16.second, true);
    std::pair<int32_t, bool>   i32 = mtl::to_num_noex(number);
    REQUIRE_EQ(i32.second, true);
    std::pair<int64_t, bool>   i64 = mtl::to_num_noex(number);
    REQUIRE_EQ(i64.second, true);
    std::pair<uint8_t, bool>   ui8 = mtl::to_num_noex(number);
    REQUIRE_EQ(ui8.second, true);
    std::pair<uint16_t, bool> ui16 = mtl::to_num_noex(number);
    REQUIRE_EQ(ui16.second, true);
    std::pair<uint32_t, bool> ui32 = mtl::to_num_noex(number);
    REQUIRE_EQ(ui32.second, true);
    std::pair<uint64_t, bool> ui64 = mtl::to_num_noex(number);
    REQUIRE_EQ(ui64.second, true);

    int8_t     i8_2 = static_cast<int8_t>(10);
    int16_t   i16_2 = static_cast<int16_t>(10);
    int32_t   i32_2 = static_cast<int32_t>(10);
    int64_t   i64_2 = static_cast<int64_t>(10);
    uint8_t   ui8_2 = static_cast<uint8_t>(10);
    uint16_t ui16_2 = static_cast<uint16_t>(10);
    uint32_t ui32_2 = static_cast<uint32_t>(10);
    uint64_t ui64_2 = static_cast<uint64_t>(10);

    REQUIRE_EQ(i8.first, i8_2);
    REQUIRE_EQ(i16.first, i16_2);
    REQUIRE_EQ(i32.first, i32_2);
    REQUIRE_EQ(i64.first, i64_2);
    REQUIRE_EQ(ui8.first, ui8_2);
    REQUIRE_EQ(ui16.first, ui16_2);
    REQUIRE_EQ(ui32.first, ui32_2);
    REQUIRE_EQ(ui64.first, ui64_2);
}


TEST_CASE("mtl::to_num_noex with std::pair")
{
    std::string number = "100";

    std::pair<int, bool> i = mtl::to_num_noex(number);
    REQUIRE_EQ(i.second, true);
    std::pair<long, bool> l = mtl::to_num_noex(number);
    REQUIRE_EQ(l.second, true);
    std::pair<long long, bool> ll = mtl::to_num_noex(number);
    REQUIRE_EQ(ll.second, true);
    std::pair<unsigned int, bool> ui = mtl::to_num_noex(number);
    REQUIRE_EQ(ui.second, true);
    std::pair<unsigned long, bool>  ul = mtl::to_num_noex(number);
    REQUIRE_EQ(ul.second, true);
    std::pair<unsigned long long, bool> ull = mtl::to_num_noex(number);
    REQUIRE_EQ(ull.second, true);
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, true);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(d.second, true);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(ld.second, true);

    auto i2 = std::make_pair<int, bool>(100, true);
    auto l2 = std::make_pair<long, bool>(100L, true);
    auto ll2 = std::make_pair<long long, bool>(100LL, true);
    auto ui2 = std::make_pair<unsigned int, bool>(100U, true);
    auto ul2 = std::make_pair<unsigned long, bool>(100UL, true);
    auto ull2 = std::make_pair<unsigned long long, bool>(100ULL, true);
    auto f2 = std::make_pair<float, bool>(100.0F, true);
    auto d2 = std::make_pair<double, bool>(100.0, true);
    auto ld2 = std::make_pair<long double, bool>(100.0L, true);

    REQUIRE_EQ(i.first, i2.first);
    REQUIRE_EQ(i.second, i2.second);

    REQUIRE_EQ(l.first, l2.first);
    REQUIRE_EQ(l.second, l2.second);

    REQUIRE_EQ(ll.first, ll2.first);
    REQUIRE_EQ(ll.second, ll2.second);

    REQUIRE_EQ(ui.first, ui2.first);
    REQUIRE_EQ(ui.second, ui2.second);

    REQUIRE_EQ(ul.first, ul2.first);
    REQUIRE_EQ(ul.second, ul2.second);

    REQUIRE_EQ(ull.first, ull.first);
    REQUIRE_EQ(ull.second, ull2.second);


    // floating point approximately equal
    REQUIRE_GT(f.first, f2.first - 0.001f);
    REQUIRE_LT(f.first, f2.first + 0.001f);
    REQUIRE_GT(f.second, f2.second - 0.001f);
    REQUIRE_LT(f.second, f2.second + 0.001f);

    REQUIRE_GT(d.first, d2.first - 0.001);
    REQUIRE_LT(d.first, d2.first + 0.001);
    REQUIRE_GT(d.second, d2.second - 0.001);
    REQUIRE_LT(d.second, d2.second + 0.001);

    REQUIRE_GT(ld.first, ld2.first - 0.001L);
    REQUIRE_LT(ld.first, ld2.first + 0.001L);
    REQUIRE_GT(ld.second, ld2.second - 0.001L);
    REQUIRE_LT(ld.second, ld2.second + 0.001L);
}



TEST_CASE("mtl::to_num_noex with std::pair not convertible because it is empty")
{
    std::string number = "";

    std::pair<int, bool> i = mtl::to_num_noex(number);
    REQUIRE_EQ(i.second, false);
    std::pair<long, bool> l = mtl::to_num_noex(number);
    REQUIRE_EQ(l.second, false);
    std::pair<long long, bool> ll = mtl::to_num_noex(number);
    REQUIRE_EQ(ll.second, false);
    std::pair<unsigned int, bool> ui = mtl::to_num_noex(number);
    REQUIRE_EQ(ui.second, false);
    std::pair<unsigned long, bool>  ul = mtl::to_num_noex(number);
    REQUIRE_EQ(ul.second, false);
    std::pair<unsigned long long, bool> ull = mtl::to_num_noex(number);
    REQUIRE_EQ(ull.second, false);
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(d.second, false);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(ld.second, false);

    auto i2 = std::make_pair<int, bool>(0, false);
    auto l2 = std::make_pair<long, bool>(0L, false);
    auto ll2 = std::make_pair<long long, bool>(0LL, false);
    auto ui2 = std::make_pair<unsigned int, bool>(0U, false);
    auto ul2 = std::make_pair<unsigned long, bool>(0UL, false);
    auto ull2 = std::make_pair<unsigned long long, bool>(0ULL, false);
    auto f2 = std::make_pair<float, bool>(0.0F, false);
    auto d2 = std::make_pair<double, bool>(0.0, false);
    auto ld2 = std::make_pair<long double, bool>(0.0L, false);

    REQUIRE_EQ(i.first, i2.first);
    REQUIRE_EQ(i.second, i2.second);

    REQUIRE_EQ(l.first, l2.first);
    REQUIRE_EQ(l.second, l2.second);

    REQUIRE_EQ(ll.first, ll2.first);
    REQUIRE_EQ(ll.second, ll2.second);

    REQUIRE_EQ(ui.first, ui2.first);
    REQUIRE_EQ(ui.second, ui2.second);

    REQUIRE_EQ(ul.first, ul2.first);
    REQUIRE_EQ(ul.second, ul2.second);

    REQUIRE_EQ(ull.first, ull.first);
    REQUIRE_EQ(ull.second, ull2.second);

    // floating point approximately equal
    REQUIRE_GT(f.first, f2.first - 0.001f);
    REQUIRE_LT(f.first, f2.first + 0.001f);
    REQUIRE_GT(f.second, f2.second - 0.001f);
    REQUIRE_LT(f.second, f2.second + 0.001f);

    REQUIRE_GT(d.first, d2.first - 0.001);
    REQUIRE_LT(d.first, d2.first + 0.001);
    REQUIRE_GT(d.second, d2.second - 0.001);
    REQUIRE_LT(d.second, d2.second + 0.001);

    REQUIRE_GT(ld.first, ld2.first - 0.001L);
    REQUIRE_LT(ld.first, ld2.first + 0.001L);
    REQUIRE_GT(ld.second, ld2.second - 0.001L);
    REQUIRE_LT(ld.second, ld2.second + 0.001L);
}


TEST_CASE("mtl::to_num_noex with std::pair not convertible value")
{
    std::string number = "Value that can't be converted.";

    std::pair<int, bool> i = mtl::to_num_noex(number);
    REQUIRE_EQ(i.second, false);
    std::pair<long, bool> l = mtl::to_num_noex(number);
    REQUIRE_EQ(l.second, false);
    std::pair<long long, bool> ll = mtl::to_num_noex(number);
    REQUIRE_EQ(ll.second, false);
    std::pair<unsigned int, bool> ui = mtl::to_num_noex(number);
    REQUIRE_EQ(ui.second, false);
    std::pair<unsigned long, bool>  ul = mtl::to_num_noex(number);
    REQUIRE_EQ(ul.second, false);
    std::pair<unsigned long long, bool> ull = mtl::to_num_noex(number);
    REQUIRE_EQ(ull.second, false);
    std::pair<float, bool> f = mtl::to_num_noex(number);
    REQUIRE_EQ(f.second, false);
    std::pair<double, bool> d = mtl::to_num_noex(number);
    REQUIRE_EQ(d.second, false);
    std::pair<long double, bool> ld = mtl::to_num_noex(number);
    REQUIRE_EQ(ld.second, false);

    auto i2 = std::make_pair<int, bool>(0, false);
    auto l2 = std::make_pair<long, bool>(0L, false);
    auto ll2 = std::make_pair<long long, bool>(0LL, false);
    auto ui2 = std::make_pair<unsigned int, bool>(0U, false);
    auto ul2 = std::make_pair<unsigned long, bool>(0UL, false);
    auto ull2 = std::make_pair<unsigned long long, bool>(0ULL, false);
    auto f2 = std::make_pair<float, bool>(0.0F, false);
    auto d2 = std::make_pair<double, bool>(0.0, false);
    auto ld2 = std::make_pair<long double, bool>(0.0L, false);

    REQUIRE_EQ(i.first, i2.first);
    REQUIRE_EQ(i.second, i2.second);

    REQUIRE_EQ(l.first, l2.first);
    REQUIRE_EQ(l.second, l2.second);

    REQUIRE_EQ(ll.first, ll2.first);
    REQUIRE_EQ(ll.second, ll2.second);

    REQUIRE_EQ(ui.first, ui2.first);
    REQUIRE_EQ(ui.second, ui2.second);

    REQUIRE_EQ(ul.first, ul2.first);
    REQUIRE_EQ(ul.second, ul2.second);

    REQUIRE_EQ(ull.first, ull.first);
    REQUIRE_EQ(ull.second, ull2.second);

    // floating point approximately equal
    REQUIRE_GT(f.first, f2.first - 0.001f);
    REQUIRE_LT(f.first, f2.first + 0.001f);
    REQUIRE_GT(f.second, f2.second - 0.001f);
    REQUIRE_LT(f.second, f2.second + 0.001f);

    REQUIRE_GT(d.first, d2.first - 0.001);
    REQUIRE_LT(d.first, d2.first + 0.001);
    REQUIRE_GT(d.second, d2.second - 0.001);
    REQUIRE_LT(d.second, d2.second + 0.001);

    REQUIRE_GT(ld.first, ld2.first - 0.001L);
    REQUIRE_LT(ld.first, ld2.first + 0.001L);
    REQUIRE_GT(ld.second, ld2.second - 0.001L);
    REQUIRE_LT(ld.second, ld2.second + 0.001L);
}






// ------------------------------------------------------------------------------------------------
// mtl::numeric_cast
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::numeric_cast to int8_t")
{
    // set result type for the test case
    using test_type = int8_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to int16_t")
{
    // set result type for the test case
    using test_type = int16_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}

TEST_CASE("mtl::numeric_cast to int32_t")
{
    // set result type for the test case
    using test_type = int32_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to int64_t")
{
    // set result type for the test case
    using test_type = int64_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}



TEST_CASE("mtl::numeric_cast to uint8_t")
{
    // set result type for the test case
    using test_type = uint8_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to uint16_t")
{
    // set result type for the test case
    using test_type = uint16_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}



TEST_CASE("mtl::numeric_cast to uint32_t")
{
    // set result type for the test case
    using test_type = uint32_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to uint64_t")
{
    // set result type for the test case
    using test_type = uint64_t;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to float")
{
    // set result type for the test case
    using test_type = float;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to double")
{
    // set result type for the test case
    using test_type = double;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(d_max)));

    // Because double and long double are the exact same size in MSVC this shouldn't throw for MSVC
    // but should throw for other compilers.
    // stackoverflow.com/a/7120740
#if defined(_MSC_VER)
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ld_max)));
#else
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_THROWS((result = mtl::numeric_cast<test_type>(ld_max)));
#endif

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}


TEST_CASE("mtl::numeric_cast to long double")
{
    // set result type for the test case
    using test_type = long double;
    // set result to zero for the given type
    [[maybe_unused]]test_type result = static_cast<test_type>(0);

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(i64_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui8_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui16_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui32_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ui64_max)));


    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(f_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(d_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(d_max)));

    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ld_min)));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(ld_max)));

    // static_cast int32_t to float then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<float>(i32_max))));

    // static_cast int32_t to double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<double>(i32_max))));

    // static_cast int32_t to long double then use mtl::numeric_cast
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_min))));
    CHECK_NOTHROW((result = mtl::numeric_cast<test_type>(static_cast<long double>(i32_max))));
}






// ------------------------------------------------------------------------------------------------
// mtl::numeric_cast_noex
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::numeric_cast_noex to int8_t")
{
    // set result type for the test case
    using test_type = int8_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
}



TEST_CASE("mtl::numeric_cast_noex to int16_t")
{
    // set result type for the test case
    using test_type = int16_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
}


TEST_CASE("mtl::numeric_cast_noex to int32_t")
{
    // set result type for the test case
    using test_type = int32_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
}


TEST_CASE("mtl::numeric_cast_noex to int64_t")
{
    // set result type for the test case
    using test_type = int64_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
}





TEST_CASE("mtl::numeric_cast_noex to uint8_t")
{
    // set result type for the test case
    using test_type = uint8_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
}



TEST_CASE("mtl::numeric_cast_noex to uint16_t")
{
    // set result type for the test case
    using test_type = uint16_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(success, true);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(success, true);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
}


TEST_CASE("mtl::numeric_cast_noex to uint32_t")
{
    // set result type for the test case
    using test_type = uint32_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
}


TEST_CASE("mtl::numeric_cast_noex to uint64_t")
{
    // set result type for the test case
    using test_type = uint64_t;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(result, zero);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, false);
    CHECK_EQ(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_NE(result, zero);
}




TEST_CASE("mtl::numeric_cast_noex to float")
{
    // set result type for the test case
    using test_type = float;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    test_type approx_zero = 0.001f;
    test_type approx_zero_negative = -0.001f;

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, false);
    // approximately equal to zero
    CHECK_LT(result, approx_zero);
    CHECK_GT(result, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, false);
    // approximately equal to zero
    CHECK_LT(result, approx_zero);
    CHECK_GT(result, approx_zero_negative);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    // approximately equal to zero
    CHECK_LT(result, approx_zero);
    CHECK_GT(result, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    // approximately equal to zero
    CHECK_LT(result, approx_zero);
    CHECK_GT(result, approx_zero_negative);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);
}




TEST_CASE("mtl::numeric_cast_noex to double")
{
    // set result type for the test case
    using test_type = double;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    test_type approx_zero = 0.001;
    test_type approx_zero_negative = -0.001;

    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);


    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // Because double and long double are the exact same size in MSVC this tests results will be
    // different for MSVC than it is for other compilers.
    // stackoverflow.com/a/7120740
#if defined(_MSC_VER)
    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, approx_zero_negative);   
#else
    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, false);
    CHECK_GT(result, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, false);
    CHECK_GT(result, approx_zero_negative);
#endif

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);
}

TEST_CASE("mtl::numeric_cast_noex to long double")
{
    // set result type for the test case
    using test_type = long double;
    // set result to zero for the given type
    test_type result = static_cast<test_type>(0);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);


    bool success = false;
    result = mtl::numeric_cast_noex<test_type>(i8_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min, success);
    // approximately equal
    CHECK_GT(result, zero - 0.01l);
    CHECK_LT(result, zero + 0.01l);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min, success);
    // approximately equal
    CHECK_GT(result, zero - 0.01l);
    CHECK_LT(result, zero + 0.01l);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min, success);
    CHECK_GT(result, zero - 0.01l);
    CHECK_LT(result, zero + 0.01l);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min, success);
    CHECK_GT(result, zero - 0.01l);
    CHECK_LT(result, zero + 0.01l);
    CHECK_EQ(success, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min, success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max, success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min), success);
    CHECK_EQ(success, true);
    CHECK_LT(result, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max), success);
    CHECK_EQ(success, true);
    CHECK_GT(result, zero);
}





// ------------------------------------------------------------------------------------------------
// mtl::numeric_cast_noex with std::pair
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::numeric_cast_noex with std::pair to int8_t")
{
    // set result type for the test case
    using test_type = int8_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
}



TEST_CASE("mtl::numeric_cast_noex with std::pair to int16_t")
{
    // set result type for the test case
    using test_type = int16_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
}


TEST_CASE("mtl::numeric_cast_noex with std::pair to int32_t")
{
    // set result type for the test case
    using test_type = int32_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
}


TEST_CASE("mtl::numeric_cast_noex with std::pair to int64_t")
{
    // set result type for the test case
    using test_type = int64_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
}




TEST_CASE("mtl::numeric_cast_noex with std::pair to uint8_t")
{
    // set result type for the test case
    using test_type = uint8_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
}



TEST_CASE("mtl::numeric_cast_noex with std::pair to uint16_t")
{
    // set result type for the test case
    using test_type = uint16_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
}


TEST_CASE("mtl::numeric_cast_noex with std::pair to uint32_t")
{
    // set result type for the test case
    using test_type = uint32_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
}


TEST_CASE("mtl::numeric_cast_noex with std::pair to uint64_t")
{
    // set result type for the test case
    using test_type = uint64_t;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, false);
    CHECK_EQ(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_NE(result.first, zero);
}



TEST_CASE("mtl::numeric_cast_noex with std::pair to float")
{
    // set result type for the test case
    using test_type = float;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    test_type approx_zero = 0.001f;
    test_type approx_zero_negative = -0.001f;

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);
}



TEST_CASE("mtl::numeric_cast_noex with std::pair to double")
{
    // set result type for the test case
    using test_type = double;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    test_type approx_zero = 0.001;
    test_type approx_zero_negative = -0.001;

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // because double and long double are the exact same size in MSVC this tests results will be
    // different for MSVC than it is for other compilers
    // stackoverflow.com/a/7120740
#if defined(_MSC_VER)
    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, true);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_LT(result.first, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, true);
    // approximately equal
    CHECK_GT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);
#else
    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, false);
    // approximately equal
    CHECK_LT(result.first, approx_zero);
    CHECK_GT(result.first, approx_zero_negative);
#endif

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);
}



TEST_CASE("mtl::numeric_cast_noex with std::pair to long double")
{
    // set result type for the test case
    using test_type = long double;
    // set result to zero for the given type and boolean to false
    auto result = std::pair<test_type, bool>(static_cast<test_type>(0), false);

    // set a number of test_type to represent 0
    test_type zero = static_cast<test_type>(0);

    test_type approx_zero = 0.001L;

    result = mtl::numeric_cast_noex<test_type>(i8_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i16_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i32_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(i64_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(i64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);
    

    result = mtl::numeric_cast_noex<test_type>(ui8_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui8_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui16_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui16_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui32_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui32_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ui64_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, approx_zero);
    result = mtl::numeric_cast_noex<test_type>(ui64_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);


    result = mtl::numeric_cast_noex<test_type>(f_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(f_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(d_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(d_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    result = mtl::numeric_cast_noex<test_type>(ld_min);
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(ld_max);
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to float then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<float>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);

    // static_cast int32_t to long double then use mtl::numeric_cast_noex
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_min));
    CHECK_EQ(result.second, true);
    CHECK_LT(result.first, zero);
    result = mtl::numeric_cast_noex<test_type>(static_cast<long double>(i32_max));
    CHECK_EQ(result.second, true);
    CHECK_GT(result.first, zero);
}





// simple cases

TEST_CASE("mtl::numeric_cast")
{
    float f = 3.6f;
    int i1 = mtl::numeric_cast<int>(f);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1, 3);
    REQUIRE_EQ(i2, 3);
    REQUIRE_EQ(i1, i2);
    float res = 1.2f;
    double d = mtl::numeric_cast<double>(res);
    REQUIRE_LT(d, 1.21);
    REQUIRE_GT(d, 1.19);

    // we setup a case where the test case throws
    long long int li = 300000000000L;
    short result = 0;
    REQUIRE_THROWS(result = mtl::numeric_cast<short>(li));
    REQUIRE_EQ((result == static_cast<short>(0)), true);
}


TEST_CASE("mtl::numeric_cast_noex with std::pair return")
{
    float f = 3.6f;
    std::pair<int, bool> i1 = mtl::numeric_cast_noex<int>(f);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1.first, 3);
    REQUIRE_EQ(i2, 3);
    REQUIRE_EQ(i1.first, i2);
    REQUIRE_EQ(i1.second, true);
    float res = 1.2f;
    std::pair<double, bool> d = mtl::numeric_cast_noex<double>(res);
    REQUIRE_LT(d.first, 1.21);
    REQUIRE_GT(d.first, 1.19);
    REQUIRE_EQ(d.second, true);

    // we setup a case where the cast should fail
    long long int li = 300000000000L;
    std::pair<short, bool> si = mtl::numeric_cast_noex<short>(li);
    REQUIRE_EQ(si.first, 0);
    REQUIRE_EQ(si.second, false);
}


TEST_CASE("mtl::numeric_cast_noex")
{
    bool success = false;
    float f = 3.6f;
    int i1 = mtl::numeric_cast_noex<int>(f, success);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1, 3);
    REQUIRE_EQ(i2, 3);
    REQUIRE_EQ(i1, i2);
    REQUIRE_EQ(success, true);
    bool success2 = false;
    float res = 1.2f;
    double d = mtl::numeric_cast_noex<double>(res, success2);
    REQUIRE_LT(d, 1.21);
    REQUIRE_GT(d, 1.19);
    REQUIRE_EQ(success2, true);

    // we setup a case where the cast should fail
    bool success3 = true;

    long long int li = 300000000000L;
    short si = mtl::numeric_cast_noex<short>(li, success3);
    REQUIRE_EQ(si, 0);
    REQUIRE_EQ(success3, false);
}


// ------------------------------------------------------------------------------------------------
// mtl::rounding_cast
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::rounding_cast with int return type with below min values")
{
    int below = 0;
    long double below_min = static_cast<long double>(std::numeric_limits<int>::lowest())-1;
    REQUIRE_THROWS_AS(below = mtl::rounding_cast(below_min), std::overflow_error);
    CHECK_EQ(below, 0);
}

TEST_CASE("mtl::rounding_cast with long return type with below min values")
{
    long below = 0;
    long double below_min = static_cast<long double>(std::numeric_limits<long>::lowest())-1;
    REQUIRE_THROWS_AS(below = mtl::rounding_cast(below_min), std::overflow_error);
    CHECK_EQ(below, 0);
}

TEST_CASE("mtl::rounding_cast with long long return type with below min values")
{
    long long below = 0;
    long double below_min = 0.0L;
    below_min = static_cast<long double>(std::numeric_limits<long long>::lowest()) - 1025;  
    CHECK_THROWS_AS(below = mtl::rounding_cast(below_min), std::overflow_error);
    CHECK_EQ(below, 0);
}


TEST_CASE("mtl::rounding_cast with int return type with above max values")
{
    int above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<int>::max())+1;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}

TEST_CASE("mtl::rounding_cast with long return type with above max values")
{
    long above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<long>::max())+1;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}

TEST_CASE("mtl::rounding_cast with long long return type with above max values")
{
    long long above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<long long>::max())+1025;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}



TEST_CASE("mtl::rounding_cast with int32_t return type")
{
    float f = 3.6f;
    int32_t i1 = mtl::rounding_cast(f);
    int32_t i2 = static_cast<int32_t>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);

    // we setup a case where the test case throws
    long double ld = std::numeric_limits<long double>::max();
    int32_t failed_int = 0;
    REQUIRE_THROWS((failed_int = mtl::rounding_cast(ld)));
    REQUIRE_EQ((failed_int == 0), true);
}

TEST_CASE("mtl::rounding_cast with int64_t return type")
{
    float f = 3.6f;
    int64_t i1 = mtl::rounding_cast(f);
    int64_t i2 = static_cast<int64_t>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);

    // we setup a case where the test case throws
    long double ld = std::numeric_limits<long double>::max();
    int64_t x = 0;
    REQUIRE_THROWS((x = mtl::rounding_cast(ld)));
    REQUIRE_EQ((x == 0), true);

    long long x_long = 0;
    REQUIRE_THROWS((x_long = mtl::rounding_cast(ld)));
    REQUIRE_EQ((x_long == 0), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::rounding_cast_noex
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::rounding_cast_noex with int return type with below min values")
{
    int below = 0;
    bool success = true;
    long double below_min = static_cast<long double>(std::numeric_limits<int>::lowest())-1;
    below = mtl::rounding_cast_noex(below_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(below, 0);
}

TEST_CASE("mtl::rounding_cast_noex with long return type with below min values")
{
    long below = 0;
    bool success = true;
    long double below_min = static_cast<long double>(std::numeric_limits<long>::lowest())-1;
    below = mtl::rounding_cast_noex(below_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(below, 0);
}

TEST_CASE("mtl::rounding_cast_noex with long long return type with below min values")
{
    long long below = 0;
    bool success = true;
    long double below_min = 0.0L;
    below_min = static_cast<long double>(std::numeric_limits<long long>::lowest()) - 1025;
    below = mtl::rounding_cast_noex(below_min, success);
    CHECK_EQ(success, false);
    CHECK_EQ(below, 0);
}


TEST_CASE("mtl::rounding_cast_noex with int return type with above max values")
{
    int above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<int>::max())+1;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}

TEST_CASE("mtl::rounding_cast_noex with long return type with above max values")
{
    long above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<long>::max())+1;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}

TEST_CASE("mtl::rounding_cast_noex with long long return type with above max values")
{
    long long above = 0;
    long double above_max = static_cast<long double>(std::numeric_limits<long long>::max())+1025;
    REQUIRE_THROWS_AS(above = mtl::rounding_cast(above_max), std::overflow_error);
    CHECK_EQ(above, 0);
}



TEST_CASE("mtl::rounding_cast_noex with int32_t return type")
{
    bool success = false;
    float f = 3.6f;
    int32_t i1 = mtl::rounding_cast_noex(f, success);
    int32_t i2 = static_cast<int32_t>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);
    REQUIRE_EQ(success, true);

    // we setup a case where the cast should fail
    bool success2 = false;
    long double ld = std::numeric_limits<long double>::max();
    int32_t failed_int = mtl::rounding_cast_noex(ld, success2);

    REQUIRE_EQ(failed_int, 0);
    REQUIRE_EQ(success2, false);
}

TEST_CASE("mtl::rounding_cast_noex with int64_t return type")
{
    bool success = false;
    float f = 3.6f;
    int64_t i1 = mtl::rounding_cast_noex(f, success);
    int64_t i2 = static_cast<int32_t>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);
    REQUIRE_EQ(success, true);

    // we setup a case where the cast should fail
    bool success2 = false;
    long double ld = std::numeric_limits<long double>::max();
    int64_t failed_int = mtl::rounding_cast_noex(ld, success2);

    REQUIRE_EQ(failed_int, 0);
    REQUIRE_EQ(success2, false);
}


TEST_CASE("mtl::rounding_cast_noex with pair int32_t return type")
{
    float f = 3.6f;
    std::pair<int32_t, bool> i1 = mtl::rounding_cast_noex(f);
    int32_t i2 = static_cast<int32_t>(f);
    REQUIRE_EQ(i1.first, 4);
    REQUIRE_EQ(i1.second, true);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1.first, i2);

    // we setup a case where the cast should fail
    long double ld = std::numeric_limits<long double>::max();
    std::pair<int32_t, bool> failed_int = mtl::rounding_cast_noex(ld);

    REQUIRE_EQ(failed_int.first, 0);
    REQUIRE_EQ(failed_int.first, false);
}

TEST_CASE("mtl::rounding_cast_noex with pair int64_t return type")
{
    float f = 3.6f;
    std::pair<int64_t, bool> i1 = mtl::rounding_cast_noex(f);
    int64_t i2 = static_cast<int64_t>(f);
    REQUIRE_EQ(i1.first, 4);
    REQUIRE_EQ(i1.second, true);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1.first, i2);

    // we setup a case where the cast should fail
    long double ld = std::numeric_limits<long double>::max();
    std::pair<int64_t, bool> failed_int = mtl::rounding_cast_noex(ld);

    REQUIRE_EQ(failed_int.first, 0);
    REQUIRE_EQ(failed_int.first, false);
}



TEST_CASE("mtl::rounding_cast with int return type")
{
    float f = 3.6f;
    int i1 = mtl::rounding_cast(f);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);

    // we setup a case where the test case throws
    long double ld = std::numeric_limits<long double>::max();
    int failed_int = 0;
    REQUIRE_THROWS((failed_int = mtl::rounding_cast(ld)));
    REQUIRE_EQ((failed_int == 0), true);
}

TEST_CASE("mtl::rounding_cast with long return type")
{
    float f = 3.6f;
    long i1 = mtl::rounding_cast(f);
    long i2 = static_cast<long>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);

    // we setup a case where the test case throws
    long double ld = std::numeric_limits<long double>::max();
    long failed_int = 0;
    REQUIRE_THROWS((failed_int = mtl::rounding_cast(ld)));   
    REQUIRE_EQ((failed_int == 0), true);
}

TEST_CASE("mtl::rounding_cast with long long return type")
{
    float f = 3.6f;
    long long i1 = mtl::rounding_cast(f);
    long long i2 = static_cast<long long>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);

    // we setup a case where the test case throws
    long double ld = std::numeric_limits<long double>::max();
    int x = 0;
    REQUIRE_THROWS((x = mtl::rounding_cast(ld)));
    REQUIRE_EQ((x == 0), true);
}


TEST_CASE("mtl::rounding_cast_noex with int return type")
{
    bool success = false;
    float f = 3.6f;
    int i1 = mtl::rounding_cast_noex(f, success);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);
    REQUIRE_EQ(success, true);

    // we setup a case where the cast should fail
    bool success2 = false;
    long double ld = std::numeric_limits<long double>::max();
    int failed_int = mtl::rounding_cast_noex(ld, success2);

    REQUIRE_EQ(failed_int, 0);
    REQUIRE_EQ(success2, false);
}


TEST_CASE("mtl::rounding_cast_noex with long return type")
{
    bool success = false;
    float f = 3.6f;
    long i1 = mtl::rounding_cast_noex(f, success);
    long i2 = static_cast<long>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);
    REQUIRE_EQ(success, true);

    // we setup a case where the cast should fail
    bool success2 = false;
    long double ld = std::numeric_limits<long double>::max();
    long failed_int = mtl::rounding_cast_noex(ld, success2);

    REQUIRE_EQ(failed_int, 0);
    REQUIRE_EQ(success2, false);
}

TEST_CASE("mtl::rounding_cast_noex with long long return type")
{
    bool success = false;
    float f = 3.6f;
    long long i1 = mtl::rounding_cast_noex(f, success);
    long long i2 = static_cast<long>(f);
    REQUIRE_EQ(i1, 4);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1, i2);
    REQUIRE_EQ(success, true);

    // we setup a case where the cast should fail
    bool success2 = false;
    long double ld = std::numeric_limits<long double>::max();
    long long failed_int = mtl::rounding_cast_noex(ld, success2);

    REQUIRE_EQ(failed_int, 0);
    REQUIRE_EQ(success2, false);
}


// ---------
TEST_CASE("mtl::rounding_cast_noex with std::pair<int, bool> return type with below min values")
{
    auto below = std::pair<int, bool>(0, true);
    long double below_min = static_cast<long double>(std::numeric_limits<int>::lowest())-1;
    below = mtl::rounding_cast_noex(below_min);
    CHECK_EQ(below.first, 0);
    CHECK_EQ(below.second, false);
}

TEST_CASE("mtl::rounding_cast_noex with std::pair<long, bool> return type with below min values")
{
    auto below = std::pair<long, bool>(0, true);
    long double below_min = static_cast<long double>(std::numeric_limits<long>::lowest())-1;
    below = mtl::rounding_cast_noex(below_min);
    CHECK_EQ(below.first, 0);
    CHECK_EQ(below.second, false);
}

TEST_CASE("mtl::rounding_cast_noex with std::pair<long long, bool> return type with below min")
{
    auto below = std::pair<long long, bool>(0, true);
    long double below_min = 0.0L;
    below_min = static_cast<long double>(std::numeric_limits<long long>::lowest()) - 1025;
    below = mtl::rounding_cast_noex(below_min);
    CHECK_EQ(below.first, 0);
    CHECK_EQ(below.second, false);
}


TEST_CASE("mtl::rounding_cast_noex with std::pair<int, bool> return type with above max values")
{
    auto above = std::pair<int, bool>(0, true);
    long double above_max = static_cast<long double>(std::numeric_limits<int>::max())+1;
    above = mtl::rounding_cast_noex(above_max);
    CHECK_EQ(above.first, 0);
    CHECK_EQ(above.second, false);
}

TEST_CASE("mtl::rounding_cast_noex with std::pair<long, bool> return type with above max values")
{
    auto above = std::pair<long, bool>(0, true);
    long double above_max = static_cast<long double>(std::numeric_limits<long>::max())+1;
    above = mtl::rounding_cast_noex(above_max);
    CHECK_EQ(above.first, 0);
    CHECK_EQ(above.second, false);
}

TEST_CASE("mtl::rounding_cast_noex with std::pair<long long, bool> return type with above max")
{
    auto above = std::pair<long long, bool>(0, true);
    long double above_max = static_cast<long double>(std::numeric_limits<long long>::max())+1025;
    above = mtl::rounding_cast_noex(above_max);
    CHECK_EQ(above.first, 0);
    CHECK_EQ(above.second, false);
}







TEST_CASE("mtl::rounding_cast_noex with pair int return type")
{
    float f = 3.6f;
    std::pair<int, bool> i1 = mtl::rounding_cast_noex(f);
    int i2 = static_cast<int>(f);
    REQUIRE_EQ(i1.first, 4);
    REQUIRE_EQ(i1.second, true);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1.first, i2);

    // we setup a case where the cast should fail
    long double ld = std::numeric_limits<long double>::max();
    std::pair<int, bool> failed_int = mtl::rounding_cast_noex(ld);

    REQUIRE_EQ(failed_int.first, 0);
    REQUIRE_EQ(failed_int.first, false);
}


TEST_CASE("mtl::rounding_cast_noex with pair long return type")
{
    float f = 3.6f;
    std::pair<long, bool> i1 = mtl::rounding_cast_noex(f);
    long i2 = static_cast<long>(f);
    REQUIRE_EQ(i1.first, 4);
    REQUIRE_EQ(i1.second, true);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1.first, i2);

    // we setup a case where the cast should fail
    long double ld = std::numeric_limits<long double>::max();
    std::pair<long, bool> failed_int = mtl::rounding_cast_noex(ld);

    REQUIRE_EQ(failed_int.first, 0);
    REQUIRE_EQ(failed_int.first, false);
}

TEST_CASE("mtl::rounding_cast_noex with pair long long return type")
{
    float f = 3.6f;
    std::pair<long long, bool> i1 = mtl::rounding_cast_noex(f);
    long long i2 = static_cast<long long>(f);
    REQUIRE_EQ(i1.first, 4);
    REQUIRE_EQ(i1.second, true);
    REQUIRE_EQ(i2, 3);
    REQUIRE_NE(i1.first, i2);

    // we setup a case where the cast should fail
    long double ld = std::numeric_limits<long double>::max();
    std::pair<long long, bool> failed_int = mtl::rounding_cast_noex(ld);

    REQUIRE_EQ(failed_int.first, 0);
    REQUIRE_EQ(failed_int.first, false);
}