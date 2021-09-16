// tests by Michael Trikergiotis
// 28/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.



#include "doctest_include.hpp" 
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::milliseconds


#include "../mtl/stopwatch.hpp" 
// [@class] mtl::chrono::stopwatch, mtl::chrono::stopwatch::start, mtl::chrono::stopwatch::stop,
// mtl::chrono::stopwatch::reset, mtl::chrono::stopwatch::restart, 
// mtl::chrono::stopwatch::elapsed_minutes, mtl::chrono::stopwatch::elapsed_seconds,
// mtl::chrono::stopwatch::elapsed_milli, mtl::chrono::stopwatch::elapsed_micro,
// mtl::chrono::stopwatch::elapsed_nano






// Put the current thread to sleep for the specified amount of milliseconds.
void sleep_for_ms([[maybe_unused]]size_t value_ms)
{
    // we need to use [[maybe_unused]] on the argument because clang-tidy will see nothing inside
    // this function and will otherwise complain about an unused variable

    // workaround for a known bug with clang-tidy (LLVM-11) and clang-tidy (LLVM-12)
    // https://bugs.llvm.org/show_bug.cgi?id=47511
    // the bug is reported as fixed with clang-tidy (LLVM 13.0.0-rc1)
    // https://reviews.llvm.org/D99181
#ifndef __clang_analyzer__

    // sleep for the given amount of milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(value_ms));

#endif // __clang_analyzer__ end

}


// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::start
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::stop
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::reset
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::restart
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::elapsed_minutes
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::elapsed_seconds
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::elapsed_milli
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::elapsed_micro
// ------------------------------------------------------------------------------------------------
// mtl::chrono::stopwatch::elapsed_nano
// ------------------------------------------------------------------------------------------------



TEST_CASE("mtl::chrono::stopwatch, all elapsed functions")
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


TEST_CASE("mtl::chrono::stopwatch, start and stop functions")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(5);
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


TEST_CASE("mtl::chrono::stopwatch, start and stop functions, start multiple times")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(1);
    sw.start();
    sleep_for_ms(1);
    sw.start();
    sleep_for_ms(1);
    sw.start();
    sleep_for_ms(5);
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


TEST_CASE("mtl::chrono::stopwatch, start and stop functions, stop multiple times")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(1);
    sw.stop();
    sleep_for_ms(1);
    sw.stop();
    sleep_for_ms(1);
    sw.stop();
    sleep_for_ms(5);
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


TEST_CASE("mtl::chrono::stopwatch, start and stop functions, start and stop multiple times")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(1);
    sw.stop();
    sw.start();
    sleep_for_ms(1);
    sw.stop();
    sw.start();
    sleep_for_ms(1);
    sw.stop();
    sw.start();
    sleep_for_ms(5);
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


TEST_CASE("mtl::chrono::stopwatch, reset function")
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


TEST_CASE("mtl::chrono::stopwatch, reset function, reset multiple times")
{
    mtl::chrono::stopwatch sw;
    sw.reset();
    sw.reset();
    sw.reset();
    sw.reset();
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


TEST_CASE("mtl::chrono::stopwatch, reset function after start and stop")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(1);
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


TEST_CASE("mtl::chrono::stopwatch, reset function after start and stop, reset multiple times")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(1);
    sw.stop();
    sw.reset();
    sw.reset();
    sw.reset();
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


TEST_CASE("mtl::chrono::stopwatch, restart function after start and stop")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    // allow almost no delay between start and stop
    sw.stop();
    sw.restart();
    // add at least 5ms delay after restart
    sleep_for_ms(5);
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


TEST_CASE("mtl::chrono::stopwatch, basic timing test 10ms")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(10);
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


TEST_CASE("mtl::chrono::stopwatch, basic timing test 20ms")
{
    mtl::chrono::stopwatch sw;
    sw.start();
    sleep_for_ms(20);
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

