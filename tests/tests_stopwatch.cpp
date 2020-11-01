// tests by Michael Trikergiotis
// 28/05/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::milliseconds

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/stopwatch.hpp" 
// mtl::chrono::stopwatch

// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::chrono::stopwatch : All elapsed functions")
{
    mtl::chrono::stopwatch sw;
    // approximately equal
    CHECK_GT(sw.elapsed_nano(),    -0.001);
    CHECK_GT(sw.elapsed_micro(),   -0.001);
    CHECK_GT(sw.elapsed_milli(),   -0.001);
    CHECK_GT(sw.elapsed_seconds(), -0.001);
    CHECK_GT(sw.elapsed_minutes(), -0.001);

    CHECK_LT(sw.elapsed_nano(),     0.001);
    CHECK_LT(sw.elapsed_micro(),    0.001);
    CHECK_LT(sw.elapsed_milli(),    0.001);
    CHECK_LT(sw.elapsed_seconds(),  0.001);
    CHECK_LT(sw.elapsed_minutes(),  0.001);
}

TEST_CASE("mtl::chrono::stopwatch : Start and Stop function")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    sw.stop();
    // approximately equal
    CHECK_GT(sw.elapsed_nano(),    0.0);
    CHECK_GT(sw.elapsed_micro(),   0.0);
    CHECK_GT(sw.elapsed_milli(),   0.0);
    CHECK_GT(sw.elapsed_seconds(), 0.0);
    CHECK_GT(sw.elapsed_minutes(), 0.0);

    CHECK_EQ((sw.elapsed_nano() > 4000000), true);
    CHECK_EQ((sw.elapsed_micro() > 4000), true);
    CHECK_EQ((sw.elapsed_milli() > 4), true);
    CHECK_EQ((sw.elapsed_seconds() > 0.004), true);
    CHECK_EQ((sw.elapsed_minutes() > 0.000066667), true);
}

TEST_CASE("mtl::chrono::stopwatch : Reset function")
{
    mtl::chrono::stopwatch sw;
    sw.reset();
    // approximately equal
    CHECK_GT(sw.elapsed_nano(),    -0.001);
    CHECK_GT(sw.elapsed_micro(),   -0.001);
    CHECK_GT(sw.elapsed_milli(),   -0.001);
    CHECK_GT(sw.elapsed_seconds(), -0.001);
    CHECK_GT(sw.elapsed_minutes(), -0.001);

    CHECK_LT(sw.elapsed_nano(),     0.001);
    CHECK_LT(sw.elapsed_micro(),    0.001);
    CHECK_LT(sw.elapsed_milli(),    0.001);
    CHECK_LT(sw.elapsed_seconds(),  0.001);
    CHECK_LT(sw.elapsed_minutes(),  0.001);
}

TEST_CASE("mtl::chrono::stopwatch : Reset function after Start and Stop")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    sw.stop();
    sw.reset();
    // approximately equal
    CHECK_GT(sw.elapsed_nano(),    -0.001);
    CHECK_GT(sw.elapsed_micro(),   -0.001);
    CHECK_GT(sw.elapsed_milli(),   -0.001);
    CHECK_GT(sw.elapsed_seconds(), -0.001);
    CHECK_GT(sw.elapsed_minutes(), -0.001);

    CHECK_LT(sw.elapsed_nano(),     0.001);
    CHECK_LT(sw.elapsed_micro(),    0.001);
    CHECK_LT(sw.elapsed_milli(),    0.001);
    CHECK_LT(sw.elapsed_seconds(),  0.001);
    CHECK_LT(sw.elapsed_minutes(),  0.001);
}

TEST_CASE("mtl::chrono::stopwatch : Restart function after Start and Stop")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    // allow almost no delay between start and stop
    sw.stop();
    sw.restart();
    // add at least 5ms delay after restart
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    sw.stop();


    // time measures should be at more than 5ms passed
    REQUIRE_GT(sw.elapsed_nano(), 0.0);
    REQUIRE_GT(sw.elapsed_micro(), 0.0);
    REQUIRE_GT(sw.elapsed_milli(), 0.0);
    REQUIRE_GT(sw.elapsed_seconds(), 0.0);
    REQUIRE_GT(sw.elapsed_minutes(), 0.0);
    

    CHECK_EQ((sw.elapsed_nano() > 4000000), true);
    CHECK_EQ((sw.elapsed_micro() > 4000), true);
    CHECK_EQ((sw.elapsed_milli() > 4), true);
    CHECK_EQ((sw.elapsed_seconds() > 0.004), true);
    CHECK_EQ((sw.elapsed_minutes() > 0.000066667), true);
}

TEST_CASE("mtl::chrono::stopwatch : Basic timing test 10ms")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sw.stop();
    
    REQUIRE_GT(sw.elapsed_nano(), 0.0);
    REQUIRE_GT(sw.elapsed_micro(), 0.0);
    REQUIRE_GT(sw.elapsed_milli(), 0.0);
    REQUIRE_GT(sw.elapsed_seconds(), 0.0);
    REQUIRE_GT(sw.elapsed_minutes(), 0.0);

    REQUIRE_GT(sw.elapsed_nano(), 9e+6);
    REQUIRE_GT(sw.elapsed_micro(), 9000.0);
    REQUIRE_GT(sw.elapsed_milli(), 9.0);
    REQUIRE_GT(sw.elapsed_seconds(), 0.009);
    REQUIRE_GT(sw.elapsed_minutes(), 0.00015);    
}

TEST_CASE("mtl::chrono::stopwatch : Basic timing test 20ms")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    sw.stop();
    
    REQUIRE_GT(sw.elapsed_nano(), 0.0);
    REQUIRE_GT(sw.elapsed_micro(), 0.0);
    REQUIRE_GT(sw.elapsed_milli(), 0.0);
    REQUIRE_GT(sw.elapsed_seconds(), 0.0);
    REQUIRE_GT(sw.elapsed_minutes(), 0.0);


    REQUIRE_GT(sw.elapsed_nano(), 1.9e+7);
    REQUIRE_GT(sw.elapsed_micro(), 19000.0);
    REQUIRE_GT(sw.elapsed_milli(), 19);
    REQUIRE_GT(sw.elapsed_seconds(), 0.019);
    REQUIRE_GT(sw.elapsed_minutes(), 0.0003);
}
