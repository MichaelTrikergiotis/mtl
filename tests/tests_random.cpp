// tests by Michael Trikergiotis
// 02/06/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <vector>
#include <list>
#include <set>
#include <algorithm> // std:all_of
#include <numeric>
#include <string>
#include "../mtl/xoroshiro128plus.hpp" // mtl::xoroshiro128plus

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/random.hpp" 
// mtl::rng, mtl::random_choice, mtl::shuffle


// --------------------------------------------------------------------
// mtl::rng
// --------------------------------------------------------------------

TEST_CASE("mtl::rng with int check various functions")
{
    std::vector<int> values;
    mtl::rng<int> rand(10, 100);
    REQUIRE_EQ(rand.min(), 10);
    REQUIRE_EQ(rand.max(), 100);
    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 10, true);
        REQUIRE_EQ(value <= 100, true);
        values.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    std::vector<int> values2;
    rand.set_min_max(1050, 3999);
    REQUIRE_EQ(rand.min(), 1050);
    REQUIRE_EQ(rand.max(), 3999);
    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 1050, true);
        REQUIRE_EQ(value <= 3999, true);
        values2.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values2)
    {
        bool all_same2 = std::all_of(values2.begin(), values2.end(),[&i] (auto x){return x == i;});
        REQUIRE_EQ(all_same2, false);
    }

    REQUIRE_EQ(values.empty(), false);
    REQUIRE_EQ(values2.empty(), false);
    // check the two resulting containers with different min and max are differrent
    REQUIRE_NE(values, values2);
}

TEST_CASE("mtl::rng with int trying to set different seeds")
{
    mtl::rng<int> rand1(1, 1000000);
    mtl::rng<int> rand2(2, 1000000);
    // set the same one see to both
    REQUIRE_NOTHROW(rand1.seed(1003344));    
    REQUIRE_NOTHROW(rand2.seed(1003344));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand1.seed_random());
    REQUIRE_NOTHROW(rand2.seed_random());
    int value1 = 0;
    int value2 = 0;
    REQUIRE_NOTHROW(value1 = rand1.next());
    REQUIRE_NOTHROW(value2 = rand2.next());
    REQUIRE_NE(value1, value2);


    mtl::rng<int> rand3(1, 1000000);
    mtl::rng<int> rand4(2, 1000000);
    // set the same two seeds to both
    REQUIRE_NOTHROW(rand3.seed(1003344, 248899));
    REQUIRE_NOTHROW(rand4.seed(1003344, 248899));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand3.seed_random());
    REQUIRE_NOTHROW(rand4.seed_random());
    int value3 = 0;
    int value4 = 0;
    REQUIRE_NOTHROW(value3 = rand3.next());
    REQUIRE_NOTHROW(value4 = rand4.next());
    REQUIRE_NE(value3, value4);
}



TEST_CASE("mtl::rng with float check various functions")
{
    std::vector<float> values;
    mtl::rng<float> rand(10.0f, 100.0f);
    
    // approximately equal
    REQUIRE_GT(rand.min(),   9.999f);
    REQUIRE_LT(rand.min(),  10.001f);
    REQUIRE_GT(rand.max(),  99.999f);
    REQUIRE_LT(rand.max(), 100.001f);

    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 10.0f, true);
        REQUIRE_EQ(value <= 100.0f, true);
        values.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01f)) && (x > (i - 0.01f)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    std::vector<float> values2;
    rand.set_min_max(1050.0f, 3999.0f);
    // approximately equal
    REQUIRE_GT(rand.min(), 1049.999f);
    REQUIRE_LT(rand.min(), 1050.001f);
    REQUIRE_GT(rand.max(), 3998.999f);
    REQUIRE_LT(rand.max(), 3999.001f);

    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 1050.0f, true);
        REQUIRE_EQ(value <= 3999.0f, true);
        values2.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values2)
    {
        bool all_same = std::all_of(values2.begin(), values2.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01f)) && (x > (i - 0.01f)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(values.empty(), false);
    REQUIRE_EQ(values2.empty(), false);
    // check the two resulting containers with different min and max are differrent
    REQUIRE_NE(values, values2);
}

TEST_CASE("mtl::rng with float trying to set different seeds")
{
    mtl::rng<float> rand1(1.0f, 1000000.0f);
    mtl::rng<float> rand2(2.0f, 1000000.0f);
    // set the same one see to both
    REQUIRE_NOTHROW(rand1.seed(1003344));
    REQUIRE_NOTHROW(rand2.seed(1003344));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand1.seed_random());
    REQUIRE_NOTHROW(rand2.seed_random());
    float value1 = 0.0f;
    float value2 = 0.0f;
    REQUIRE_NOTHROW(value1 = rand1.next());
    REQUIRE_NOTHROW(value2 = rand2.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value1_int = static_cast<int64_t>(value1);
    int64_t value2_int = static_cast<int64_t>(value2);
    REQUIRE_NE(value1_int, value2_int);


    mtl::rng<float> rand3(1.0f, 1000000.0f);
    mtl::rng<float> rand4(2.0f, 1000000.0f);
    // set the same two seeds to both
    REQUIRE_NOTHROW(rand3.seed(1003344, 248899));
    REQUIRE_NOTHROW(rand4.seed(1003344, 248899));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand3.seed_random());
    REQUIRE_NOTHROW(rand4.seed_random());
    float value3 = 0.0f;
    float value4 = 0.0f;
    REQUIRE_NOTHROW(value3 = rand3.next());
    REQUIRE_NOTHROW(value4 = rand4.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value3_int = static_cast<int64_t>(value3);
    int64_t value4_int = static_cast<int64_t>(value4);
    REQUIRE_NE(value3_int, value4_int);
}




TEST_CASE("mtl::rng with double check various functions")
{
    std::vector<double> values;
    mtl::rng<double> rand(10.0, 100.0);
    // approximately equal
    REQUIRE_GT(rand.min(),   9.999);
    REQUIRE_LT(rand.min(),  10.001);
    REQUIRE_GT(rand.max(),  99.999);
    REQUIRE_LT(rand.max(), 100.001);

    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 10.0, true);
        REQUIRE_EQ(value <= 100.0, true);
        values.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01)) && (x > (i - 0.01)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    std::vector<double> values2;
    rand.set_min_max(1050.0, 3999.0);
    // approximately equal
    REQUIRE_GT(rand.min(), 1049.999);
    REQUIRE_LT(rand.min(), 1050.001);
    REQUIRE_GT(rand.max(), 3998.999);
    REQUIRE_LT(rand.max(), 3999.001);
    for(int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 1050.0, true);
        REQUIRE_EQ(value <= 3999.0, true);
        values2.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values2)
    {
        bool all_same = std::all_of(values2.begin(), values2.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01)) && (x > (i - 0.01)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(values.empty(), false);
    REQUIRE_EQ(values2.empty(), false);
    // check the two resulting containers with different min and max are differrent
    REQUIRE_NE(values, values2);
}

TEST_CASE("mtl::rng with double trying to set different seeds")
{
    mtl::rng<double> rand1(1.0, 1000000.0);
    mtl::rng<double> rand2(2.0, 1000000.0);
    // set the same one see to both
    REQUIRE_NOTHROW(rand1.seed(1003344));
    REQUIRE_NOTHROW(rand2.seed(1003344));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand1.seed_random());
    REQUIRE_NOTHROW(rand2.seed_random());
    double value1 = 0.0;
    double value2 = 0.0;
    REQUIRE_NOTHROW(value1 = rand1.next());
    REQUIRE_NOTHROW(value2 = rand2.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value1_int = static_cast<int64_t>(value1);
    int64_t value2_int = static_cast<int64_t>(value2);
    REQUIRE_NE(value1_int, value2_int);


    mtl::rng<double> rand3(1.0, 1000000.0);
    mtl::rng<double> rand4(2.0, 1000000.0);
    // set the same two seeds to both
    REQUIRE_NOTHROW(rand3.seed(1003344, 248899));
    REQUIRE_NOTHROW(rand4.seed(1003344, 248899));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand3.seed_random());
    REQUIRE_NOTHROW(rand4.seed_random());
    double value3 = 0.0;
    double value4 = 0.0;
    REQUIRE_NOTHROW(value3 = rand3.next());
    REQUIRE_NOTHROW(value4 = rand4.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value3_int = static_cast<int64_t>(value3);
    int64_t value4_int = static_cast<int64_t>(value4);
    REQUIRE_NE(value3_int, value4_int);
}







TEST_CASE("mtl::rng with long double check various functions")
{
    std::vector<long double> values;
    mtl::rng<long double> rand(10.0l, 100.0l);
    // approximately equal
    REQUIRE_GT(rand.min(), 9.999l);
    REQUIRE_LT(rand.min(), 10.001l);
    REQUIRE_GT(rand.max(), 99.999l);
    REQUIRE_LT(rand.max(), 100.001l);

    for (int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 10.0l, true);
        REQUIRE_EQ(value <= 100.0l, true);
        values.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values)
    {
        bool all_same = std::all_of(values.begin(), values.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01l)) && (x > (i - 0.01l)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    std::vector<long double> values2;
    rand.set_min_max(1050.0l, 3999.0l);
    // approximately equal
    REQUIRE_GT(rand.min(), 1049.999l);
    REQUIRE_LT(rand.min(), 1050.001l);
    REQUIRE_GT(rand.max(), 3998.999l);
    REQUIRE_LT(rand.max(), 3999.001l);
    for (int i = 0; i < 100; i++)
    {
        auto value = rand.next();
        REQUIRE_EQ(value >= 1050.0l, true);
        REQUIRE_EQ(value <= 3999.0l, true);
        values2.push_back(value);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : values2)
    {
        bool all_same = std::all_of(values2.begin(), values2.end(), [&i](auto x) 
                                    {
                                       bool same = false;
                                       // approximate equality for floating point type numbers
                                       if ((x < (i + 0.01l)) && (x > (i - 0.01l)))
                                       {
                                           same = true;
                                       }
                                       return same;
                                    });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(values.empty(), false);
    REQUIRE_EQ(values2.empty(), false);
    // check the two resulting containers with different min and max are differrent
    REQUIRE_NE(values, values2);
}

TEST_CASE("mtl::rng with long double trying to set different seeds")
{
    mtl::rng<long double> rand1(1.0l, 1000000.0l);
    mtl::rng<long double> rand2(2.0l, 1000000.0l);
    // set the same one see to both
    REQUIRE_NOTHROW(rand1.seed(1003344));
    REQUIRE_NOTHROW(rand2.seed(1003344));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand1.seed_random());
    REQUIRE_NOTHROW(rand2.seed_random());
    long double value1 = 0.0l;
    long double value2 = 0.0l;
    REQUIRE_NOTHROW(value1 = rand1.next());
    REQUIRE_NOTHROW(value2 = rand2.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value1_int = static_cast<int64_t>(value1);
    int64_t value2_int = static_cast<int64_t>(value2);
    REQUIRE_NE(value1_int, value2_int);


    mtl::rng<long double> rand3(1.0l, 1000000.0l);
    mtl::rng<long double> rand4(2.0l, 1000000.0l);
    // set the same two seeds to both
    REQUIRE_NOTHROW(rand3.seed(1003344, 248899));
    REQUIRE_NOTHROW(rand4.seed(1003344, 248899));
    // then try to randomize the seeds of both and expect the results to be different values
    REQUIRE_NOTHROW(rand3.seed_random());
    REQUIRE_NOTHROW(rand4.seed_random());
    long double value3 = 0.0l;
    long double value4 = 0.0l;
    REQUIRE_NOTHROW(value3 = rand3.next());
    REQUIRE_NOTHROW(value4 = rand4.next());
    // check the values are not equal which is harder for floating point type because we can't
    // compare for exact equality without compiler complaining, we instead convert them to int64
    // and compare those, in our current test we don't care if we are slightly inexact due to
    // rounding errors when casting
    int64_t value3_int = static_cast<int64_t>(value3);
    int64_t value4_int = static_cast<int64_t>(value4);
    REQUIRE_NE(value3_int, value4_int);
}

// --------------------------------------------------------------------
// mtl::rng matching mtl::xoroshiro128plus results
// --------------------------------------------------------------------

TEST_CASE("mtl::rng<int32_t> matching mtl::xoroshiro128plus + std::uniform_int_distribution")
{
    const size_t reps =  100;
    using num_type =  int32_t;
    num_type min   = -10000;
    num_type max   =  10000;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc); 
    
    mtl::xoroshiro128plus xs128p;
    std::uniform_int_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num  = dist(xs128p);
        CHECK_EQ(rng_num, xs_num);
    }
}

TEST_CASE("mtl::rng<int64_t> matching mtl::xoroshiro128plus + std::uniform_int_distribution")
{
    const size_t reps =  100;
    using num_type =  int64_t;
    num_type min   = -10000;
    num_type max   =  10000;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_int_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        CHECK_EQ(rng_num, xs_num);
    }
}

TEST_CASE("mtl::rng<uint32_t> matching mtl::xoroshiro128plus + std::uniform_int_distribution")
{
    const size_t reps =  100;
    using num_type = uint32_t;
    num_type min   = 100;
    num_type max   = 10000;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_int_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        CHECK_EQ(rng_num, xs_num);
    }
}

TEST_CASE("mtl::rng<uint64_t> matching mtl::xoroshiro128plus + std::uniform_int_distribution")
{
    const size_t reps =  100;
    using num_type = uint64_t;
    num_type min   = 100;
    num_type max   = 10000;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_int_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        CHECK_EQ(rng_num, xs_num);
    }
}

TEST_CASE("mtl::rng<float> matching mtl::xoroshiro128plus + std::uniform_real_distribution")
{
    const size_t reps =  100;
    using num_type =  float;
    num_type min   = -10000.0f;
    num_type max   =  10000.0f;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_real_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        // floating point type approximate equality
        CHECK_LT(rng_num - 0.01f, xs_num);
        CHECK_GT(rng_num + 0.01f, xs_num);
    }
}

TEST_CASE("mtl::rng<double> matching mtl::xoroshiro128plus + std::uniform_real_distribution")
{
    const size_t reps =  100;
    using num_type =  double;
    num_type min   = -10000.0;
    num_type max   =  10000.0;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_real_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        // floating point type approximate equality
        CHECK_LT(rng_num - 0.01, xs_num);
        CHECK_GT(rng_num + 0.01, xs_num);
    }
}

TEST_CASE("mtl::rng<long double> matching mtl::xoroshiro128plus + std::uniform_real_distribution")
{
    const size_t reps =  100;
    using num_type    =  long double;
    num_type min      = -10000.0l;
    num_type max      =  10000.0l;

    mtl::rng<num_type> rng(min, max);
    // use the default seeds that mtl::xoroshiro128plus uses
    rng.seed(0xdf900294d8f554a5, 0x170865df4b3201fc);

    mtl::xoroshiro128plus xs128p;
    std::uniform_real_distribution<num_type> dist(min, max);

    for (size_t i = 0; i < reps; i++)
    {
        auto rng_num = rng.next();
        auto xs_num = dist(xs128p);
        // floating point type approximate equality
        CHECK_LT(rng_num - 0.01l, xs_num);
        CHECK_GT(rng_num + 0.01l, xs_num);
    }
}




// --------------------------------------------------------------------
// mtl::random_choice
// --------------------------------------------------------------------

TEST_CASE("mtl::random_choice with empty containers<int>")
{
    std::vector<int> vi;
    std::list<int> li;
    std::set<int> si;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == vi.begin()), true);
        REQUIRE_EQ((result == vi.end()), true);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == li.begin()), true);
        REQUIRE_EQ((result == li.end()), true);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == si.begin()), true);
        REQUIRE_EQ((result == si.end()), true);
    }
}

TEST_CASE("mtl::random_choice with containers<int>")
{
    std::vector<int> vi { 1, 2, 3, 4, 5 };
    std::list<int> li { 1, 2, 3, 4, 5 };
    std::set<int> si { 1, 2, 3, 4, 5 };
    std::vector<int> vi_v;
    std::list<int> li_v;
    std::set<int> si_v;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi);
        vi_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(vi.begin(), vi.end(), *result) != vi.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : vi)
    {
        bool all_same = std::all_of(vi_v.begin(), vi_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    

    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li);
        li_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(li.begin(), li.end(), *result) != li.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : li)
    {
        bool all_same = std::all_of(li_v.begin(), li_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si);
        si_v.insert(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(si.begin(), si.end(), *result) != si.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : si)
    {
        bool all_same = std::all_of(si_v.begin(), si_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(vi.empty(), false);
    REQUIRE_EQ(li.empty(), false);
    REQUIRE_EQ(si.empty(), false);
    REQUIRE_EQ(vi_v.empty(), false);
    REQUIRE_EQ(li_v.empty(), false);
    REQUIRE_EQ(si_v.empty(), false);
}

TEST_CASE("mtl::random_choice with empty containers<std::string>")
{
    std::vector<std::string> vi;
    std::list<std::string> li;
    std::set<std::string> si;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == vi.begin()), true);
        REQUIRE_EQ((result == vi.end()), true);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == li.begin()), true);
        REQUIRE_EQ((result == li.end()), true);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si);
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == si.begin()), true);
        REQUIRE_EQ((result == si.end()), true);
    }
}

TEST_CASE("mtl::random_choice with containers<std::string>")
{
    std::vector<std::string> vi { "1", "2", "3", "4", "5" };
    std::list<std::string> li { "1", "2", "3", "4", "5" };
    std::set<std::string> si { "1", "2", "3", "4", "5" };
    std::vector<std::string> vi_v;
    std::list<std::string> li_v;
    std::set<std::string> si_v;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi);
        vi_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(vi.begin(), vi.end(), *result) != vi.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : vi)
    {
        bool all_same = std::all_of(vi_v.begin(), vi_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li);
        li_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(li.begin(), li.end(), *result) != li.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : li)
    {
        bool all_same = std::all_of(li_v.begin(), li_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si);
        si_v.insert(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(si.begin(), si.end(), *result) != si.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : si)
    {
        bool all_same = std::all_of(si_v.begin(), si_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(vi.empty(), false);
    REQUIRE_EQ(li.empty(), false);
    REQUIRE_EQ(si.empty(), false);
    REQUIRE_EQ(vi_v.empty(), false);
    REQUIRE_EQ(li_v.empty(), false);
    REQUIRE_EQ(si_v.empty(), false);
}




TEST_CASE("mtl::random_choice with empty container with iterators of int")
{
    std::vector<int> vi;
    std::list<int> li;
    std::set<int> si;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi.begin(), vi.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == vi.begin()), true);
        REQUIRE_EQ((result == vi.end()), true);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li.begin(), li.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == li.begin()), true);
        REQUIRE_EQ((result == li.end()), true);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si.begin(), si.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == si.begin()), true);
        REQUIRE_EQ((result == si.end()), true);
    }
}

TEST_CASE("mtl::random_choice with iterators of int")
{
    std::vector<int> vi { 1, 2, 3, 4, 5 };
    std::list<int> li { 1, 2, 3, 4, 5 };
    std::set<int> si { 1, 2, 3, 4, 5 };
    std::vector<int> vi_v;
    std::list<int> li_v;
    std::set<int> si_v;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi.begin(), vi.end());
        vi_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(vi.begin(), vi.end(), *result) != vi.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : vi)
    {
        bool all_same = std::all_of(vi_v.begin(), vi_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li.begin(), li.end());
        li_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(li.begin(), li.end(), *result) != li.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : li)
    {
        bool all_same = std::all_of(li_v.begin(), li_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si.begin(), si.end());
        si_v.insert(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(si.begin(), si.end(), *result) != si.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : si)
    {
        bool all_same = std::all_of(si_v.begin(), si_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(vi.empty(), false);
    REQUIRE_EQ(li.empty(), false);
    REQUIRE_EQ(si.empty(), false);
    REQUIRE_EQ(vi_v.empty(), false);
    REQUIRE_EQ(li_v.empty(), false);
    REQUIRE_EQ(si_v.empty(), false);
}



TEST_CASE("mtl::random_choice with empty container with iterators of std::string")
{
    std::vector<std::string> vi;
    std::list<std::string> li;
    std::set<std::string> si;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi.begin(), vi.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == vi.begin()), true);
        REQUIRE_EQ((result == vi.end()), true);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li.begin(), li.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == li.begin()), true);
        REQUIRE_EQ((result == li.end()), true);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si.begin(), si.end());
        // check that the iterator is same as the begin/end iterator
        REQUIRE_EQ((result == si.begin()), true);
        REQUIRE_EQ((result == si.end()), true);
    }
}

TEST_CASE("mtl::random_choice with iterators of std::string")
{
    std::vector<std::string> vi { "1", "2", "3", "4", "5" };
    std::list<std::string> li { "1", "2", "3", "4", "5" };
    std::set<std::string> si { "1", "2", "3", "4", "5" };
    std::vector<std::string> vi_v;
    std::list<std::string> li_v;
    std::set<std::string> si_v;

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(vi.begin(), vi.end());
        vi_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(vi.begin(), vi.end(), *result) != vi.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : vi)
    {
        bool all_same = std::all_of(vi_v.begin(), vi_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }
    
    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(li.begin(), li.end());
        li_v.push_back(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(li.begin(), li.end(), *result) != li.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : li)
    {
        bool all_same = std::all_of(li_v.begin(), li_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    for(int i = 0; i < 10; i++)
    {
        // make a random choice from the container
        auto result = mtl::random_choice(si.begin(), si.end());
        si_v.insert(*result);
        // check that the value found exists within the container
        auto found = false;
        if(std::find(si.begin(), si.end(), *result) != si.end())
        {
            found = true;
        }
        REQUIRE_EQ(found, true);
    }

    // check that all values are not the same and there is some variance
    for(const auto& i : si)
    {
        bool all_same = std::all_of(si_v.begin(), si_v.end(), [&i](auto x) { return x == i; });
        REQUIRE_EQ(all_same, false);
    }

    REQUIRE_EQ(vi.empty(), false);
    REQUIRE_EQ(li.empty(), false);
    REQUIRE_EQ(si.empty(), false);
    REQUIRE_EQ(vi_v.empty(), false);
    REQUIRE_EQ(li_v.empty(), false);
    REQUIRE_EQ(si_v.empty(), false);
}




// --------------------------------------------------------------------
// mtl::shuffle with containers
// --------------------------------------------------------------------

TEST_CASE("mtl::shuffle with empty std::vector<numbers>")
{
    std::vector<int32_t> vi_32;
    std::vector<int64_t> vi_64;
    std::vector<uint32_t> vi_32u;
    std::vector<uint64_t> vi_64u;
    std::vector<float> vf;
    std::vector<double> vd;
    std::vector<long double> vld;

    REQUIRE_NOTHROW(mtl::shuffle(vi_32));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64));
    REQUIRE_NOTHROW(mtl::shuffle(vi_32u));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64u));
    REQUIRE_NOTHROW(mtl::shuffle(vf));
    REQUIRE_NOTHROW(mtl::shuffle(vd));
    REQUIRE_NOTHROW(mtl::shuffle(vld));


    REQUIRE_EQ(vi_32.empty(), true);
    REQUIRE_EQ(vi_64.empty(), true);
    REQUIRE_EQ(vi_32u.empty(), true);
    REQUIRE_EQ(vi_64u.empty(), true);
    REQUIRE_EQ(vf.empty(), true);
    REQUIRE_EQ(vd.empty(), true);
    REQUIRE_EQ(vld.empty(), true);
}

TEST_CASE("mtl::shuffle with empty std::list<numbers>")
{
    std::list<int32_t> li_32;
    std::list<int64_t> li_64;
    std::list<uint32_t> li_32u;
    std::list<uint64_t> li_64u;
    std::list<float> lf;
    std::list<double> ld;
    std::list<long double> lld;

    REQUIRE_NOTHROW(mtl::shuffle(li_32));
    REQUIRE_NOTHROW(mtl::shuffle(li_64));
    REQUIRE_NOTHROW(mtl::shuffle(li_32u));
    REQUIRE_NOTHROW(mtl::shuffle(li_64u));
    REQUIRE_NOTHROW(mtl::shuffle(lf));
    REQUIRE_NOTHROW(mtl::shuffle(ld));
    REQUIRE_NOTHROW(mtl::shuffle(lld));


    REQUIRE_EQ(li_32.empty(), true);
    REQUIRE_EQ(li_64.empty(), true);
    REQUIRE_EQ(li_32u.empty(), true);
    REQUIRE_EQ(li_64u.empty(), true);
    REQUIRE_EQ(lf.empty(), true);
    REQUIRE_EQ(ld.empty(), true);
    REQUIRE_EQ(lld.empty(), true);
}

TEST_CASE("mtl::shuffle with std::vector<numbers>")
{
    std::vector<int32_t> vi_32(100);
    std::vector<int64_t> vi_64(100);
    std::vector<uint32_t> vi_32u(100);
    std::vector<uint64_t> vi_64u(100);
    std::vector<float> vf(100);
    std::vector<double> vd(100);
    std::vector<long double> vld(100);
    std::iota(vi_32.begin(), vi_32.end(), 10);
    std::iota(vi_64.begin(), vi_64.end(), 10);
    std::iota(vi_32u.begin(), vi_32u.end(), 10U);
    std::iota(vi_64u.begin(), vi_64u.end(), 10UL);
    std::iota(vf.begin(), vf.end(), 10.0f);
    std::iota(vd.begin(), vd.end(), 10.0);
    std::iota(vld.begin(), vld.end(), 10.0L);

    auto vi_32_copy = vi_32;
    auto vi_64_copy = vi_64;
    auto vi_32u_copy = vi_32u;
    auto vi_64u_copy = vi_64u;
    auto vf_copy = vf;
    auto vd_copy = vd;
    auto vld_copy = vld;


    REQUIRE_NOTHROW(mtl::shuffle(vi_32));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64));
    REQUIRE_NOTHROW(mtl::shuffle(vi_32u));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64u));
    REQUIRE_NOTHROW(mtl::shuffle(vf));
    REQUIRE_NOTHROW(mtl::shuffle(vd));
    REQUIRE_NOTHROW(mtl::shuffle(vld));


    REQUIRE_EQ(vi_32.empty(), false);
    REQUIRE_EQ(vi_64.empty(), false);
    REQUIRE_EQ(vi_32u.empty(), false);
    REQUIRE_EQ(vi_64u.empty(), false);
    REQUIRE_EQ(vf.empty(), false);
    REQUIRE_EQ(vd.empty(), false);
    REQUIRE_EQ(vld.empty(), false);

    // check that the shuffled are different from the originals
    REQUIRE_EQ((vi_32 == vi_32_copy), false);
    REQUIRE_EQ((vi_64 == vi_64_copy), false);
    REQUIRE_EQ((vi_32u == vi_32u_copy), false);
    REQUIRE_EQ((vi_64u == vi_64u_copy), false);
    REQUIRE_EQ((vf == vf_copy), false);
    REQUIRE_EQ((vd == vd_copy), false);
    REQUIRE_EQ((vld == vld_copy), false);
}


TEST_CASE("mtl::shuffle with std::list<numbers>")
{
    std::list<int32_t> li_32(100);
    std::list<int64_t> li_64(100);
    std::list<uint32_t> li_32u(100);
    std::list<uint64_t> li_64u(100);
    std::list<float> lf(100);
    std::list<double> ld(100);
    std::list<long double> lld(100);
    std::iota(li_32.begin(), li_32.end(), 10);
    std::iota(li_64.begin(), li_64.end(), 10);
    std::iota(li_32u.begin(), li_32u.end(), 10U);
    std::iota(li_64u.begin(), li_64u.end(), 10UL);
    std::iota(lf.begin(), lf.end(), 10.0f);
    std::iota(ld.begin(), ld.end(), 10.0);
    std::iota(lld.begin(), lld.end(), 10.0L);

    auto li_32_copy = li_32;
    auto li_64_copy = li_64;
    auto li_32u_copy = li_32u;
    auto li_64u_copy = li_64u;
    auto lf_copy = lf;
    auto ld_copy = ld;
    auto lld_copy = lld;


    REQUIRE_NOTHROW(mtl::shuffle(li_32));
    REQUIRE_NOTHROW(mtl::shuffle(li_64));
    REQUIRE_NOTHROW(mtl::shuffle(li_32u));
    REQUIRE_NOTHROW(mtl::shuffle(li_64u));
    REQUIRE_NOTHROW(mtl::shuffle(lf));
    REQUIRE_NOTHROW(mtl::shuffle(ld));
    REQUIRE_NOTHROW(mtl::shuffle(lld));


    REQUIRE_EQ(li_32.empty(), false);
    REQUIRE_EQ(li_64.empty(), false);
    REQUIRE_EQ(li_32u.empty(), false);
    REQUIRE_EQ(li_64u.empty(), false);
    REQUIRE_EQ(lf.empty(), false);
    REQUIRE_EQ(ld.empty(), false);
    REQUIRE_EQ(lld.empty(), false);

    // check that the shuffled are different from the originals
    REQUIRE_EQ((li_32 == li_32_copy), false);
    REQUIRE_EQ((li_64 == li_64_copy), false);
    REQUIRE_EQ((li_32u == li_32u_copy), false);
    REQUIRE_EQ((li_64u == li_64u_copy), false);
    REQUIRE_EQ((lf == lf_copy), false);
    REQUIRE_EQ((ld == ld_copy), false);
    REQUIRE_EQ((lld == lld_copy), false);
}


TEST_CASE("mtl::shuffle with empty containers<std::string>")
{
    std::vector<std::string> v;
    std::list<std::string> l;

    REQUIRE_NOTHROW(mtl::shuffle(v));
    REQUIRE_NOTHROW(mtl::shuffle(l));

    REQUIRE_EQ(v.empty(), true);
    REQUIRE_EQ(l.empty(), true);
}

TEST_CASE("mtl::shuffle with containers<std::string>")
{
    constexpr size_t size = 100;
    std::vector<std::string> v;
    v.reserve(size);
    for (size_t i = 0; i < size; i++)
    {
        v.push_back(std::to_string(i));
    }
    std::list<std::string> l(v.begin(), v.end());

    auto v_shuffle = v;
    auto l_shuffle = l;

    REQUIRE_NOTHROW(mtl::shuffle(v_shuffle));
    REQUIRE_NOTHROW(mtl::shuffle(l_shuffle));

    // check that the shuffled are different from the non shuffled
    REQUIRE_EQ((v_shuffle == v), false);
    REQUIRE_EQ((l_shuffle == l), false);

    // shuffle the originals
    REQUIRE_NOTHROW(mtl::shuffle(v));
    REQUIRE_NOTHROW(mtl::shuffle(l));

    // check again that they are different even though they are both shuffled
    REQUIRE_EQ((v_shuffle == v), false);
    REQUIRE_EQ((l_shuffle == l), false);
}








// --------------------------------------------------------------------
// mtl::shuffle with iterators
// --------------------------------------------------------------------

TEST_CASE("mtl::shuffle with iterators with empty std::vector<numbers> ")
{
    std::vector<int32_t> vi_32;
    std::vector<int64_t> vi_64;
    std::vector<uint32_t> vi_32u;
    std::vector<uint64_t> vi_64u;
    std::vector<float> vf;
    std::vector<double> vd;
    std::vector<long double> vld;

    REQUIRE_NOTHROW(mtl::shuffle(vi_32.begin(), vi_32.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64.begin(), vi_64.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_32u.begin(), vi_32u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64u.begin(), vi_64u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vf.begin(), vf.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vd.begin(), vd.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vld.begin(), vld.end()));


    REQUIRE_EQ(vi_32.empty(), true);
    REQUIRE_EQ(vi_64.empty(), true);
    REQUIRE_EQ(vi_32u.empty(), true);
    REQUIRE_EQ(vi_64u.empty(), true);
    REQUIRE_EQ(vf.empty(), true);
    REQUIRE_EQ(vd.empty(), true);
    REQUIRE_EQ(vld.empty(), true);
}

TEST_CASE("mtl::shuffle with iterators with empty std::list<numbers>")
{
    std::list<int32_t> li_32;
    std::list<int64_t> li_64;
    std::list<uint32_t> li_32u;
    std::list<uint64_t> li_64u;
    std::list<float> lf;
    std::list<double> ld;
    std::list<long double> lld;

    REQUIRE_NOTHROW(mtl::shuffle(li_32.begin(), li_32.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_64.begin(), li_64.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_32u.begin(), li_32u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_64u.begin(), li_64u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(lf.begin(), lf.end()));
    REQUIRE_NOTHROW(mtl::shuffle(ld.begin(), ld.end()));
    REQUIRE_NOTHROW(mtl::shuffle(lld.begin(), lld.end()));


    REQUIRE_EQ(li_32.empty(), true);
    REQUIRE_EQ(li_64.empty(), true);
    REQUIRE_EQ(li_32u.empty(), true);
    REQUIRE_EQ(li_64u.empty(), true);
    REQUIRE_EQ(lf.empty(), true);
    REQUIRE_EQ(ld.empty(), true);
    REQUIRE_EQ(lld.empty(), true);
}

TEST_CASE("mtl::shuffle with iterators with std::vector<numbers>")
{
    std::vector<int32_t> vi_32(100);
    std::vector<int64_t> vi_64(100);
    std::vector<uint32_t> vi_32u(100);
    std::vector<uint64_t> vi_64u(100);
    std::vector<float> vf(100);
    std::vector<double> vd(100);
    std::vector<long double> vld(100);
    std::iota(vi_32.begin(), vi_32.end(), 10);
    std::iota(vi_64.begin(), vi_64.end(), 10);
    std::iota(vi_32u.begin(), vi_32u.end(), 10U);
    std::iota(vi_64u.begin(), vi_64u.end(), 10UL);
    std::iota(vf.begin(), vf.end(), 10.0f);
    std::iota(vd.begin(), vd.end(), 10.0);
    std::iota(vld.begin(), vld.end(), 10.0L);

    auto vi_32_copy = vi_32;
    auto vi_64_copy = vi_64;
    auto vi_32u_copy = vi_32u;
    auto vi_64u_copy = vi_64u;
    auto vf_copy = vf;
    auto vd_copy = vd;
    auto vld_copy = vld;


    REQUIRE_NOTHROW(mtl::shuffle(vi_32.begin(), vi_32.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64.begin(), vi_64.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_32u.begin(), vi_32u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vi_64u.begin(), vi_64u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vf.begin(), vf.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vd.begin(), vd.end()));
    REQUIRE_NOTHROW(mtl::shuffle(vld.begin(), vld.end()));


    REQUIRE_EQ(vi_32.empty(), false);
    REQUIRE_EQ(vi_64.empty(), false);
    REQUIRE_EQ(vi_32u.empty(), false);
    REQUIRE_EQ(vi_64u.empty(), false);
    REQUIRE_EQ(vf.empty(), false);
    REQUIRE_EQ(vd.empty(), false);
    REQUIRE_EQ(vld.empty(), false);

    // check that the shuffled are different from the originals
    REQUIRE_EQ((vi_32 == vi_32_copy), false);
    REQUIRE_EQ((vi_64 == vi_64_copy), false);
    REQUIRE_EQ((vi_32u == vi_32u_copy), false);
    REQUIRE_EQ((vi_64u == vi_64u_copy), false);
    REQUIRE_EQ((vf == vf_copy), false);
    REQUIRE_EQ((vd == vd_copy), false);
    REQUIRE_EQ((vld == vld_copy), false);
}


TEST_CASE("mtl::shuffle with iterators with std::list<numbers>")
{
    std::list<int32_t> li_32(100);
    std::list<int64_t> li_64(100);
    std::list<uint32_t> li_32u(100);
    std::list<uint64_t> li_64u(100);
    std::list<float> lf(100);
    std::list<double> ld(100);
    std::list<long double> lld(100);
    std::iota(li_32.begin(), li_32.end(), 10);
    std::iota(li_64.begin(), li_64.end(), 10);
    std::iota(li_32u.begin(), li_32u.end(), 10U);
    std::iota(li_64u.begin(), li_64u.end(), 10UL);
    std::iota(lf.begin(), lf.end(), 10.0f);
    std::iota(ld.begin(), ld.end(), 10.0);
    std::iota(lld.begin(), lld.end(), 10.0L);

    auto li_32_copy = li_32;
    auto li_64_copy = li_64;
    auto li_32u_copy = li_32u;
    auto li_64u_copy = li_64u;
    auto lf_copy = lf;
    auto ld_copy = ld;
    auto lld_copy = lld;


    REQUIRE_NOTHROW(mtl::shuffle(li_32.begin(), li_32.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_64.begin(), li_64.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_32u.begin(), li_32u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(li_64u.begin(), li_64u.end()));
    REQUIRE_NOTHROW(mtl::shuffle(lf.begin(), lf.end()));
    REQUIRE_NOTHROW(mtl::shuffle(ld.begin(), ld.end()));
    REQUIRE_NOTHROW(mtl::shuffle(lld.begin(), lld.end()));


    REQUIRE_EQ(li_32.empty(), false);
    REQUIRE_EQ(li_64.empty(), false);
    REQUIRE_EQ(li_32u.empty(), false);
    REQUIRE_EQ(li_64u.empty(), false);
    REQUIRE_EQ(lf.empty(), false);
    REQUIRE_EQ(ld.empty(), false);
    REQUIRE_EQ(lld.empty(), false);

    // check that the shuffled are different from the originals
    REQUIRE_EQ((li_32 == li_32_copy), false);
    REQUIRE_EQ((li_64 == li_64_copy), false);
    REQUIRE_EQ((li_32u == li_32u_copy), false);
    REQUIRE_EQ((li_64u == li_64u_copy), false);
    REQUIRE_EQ((lf == lf_copy), false);
    REQUIRE_EQ((ld == ld_copy), false);
    REQUIRE_EQ((lld == lld_copy), false);
}


TEST_CASE("mtl::shuffle with iterators with empty containers<std::string>")
{
    std::vector<std::string> v;
    std::list<std::string> l;

    REQUIRE_NOTHROW(mtl::shuffle(v));
    REQUIRE_NOTHROW(mtl::shuffle(l));

    REQUIRE_EQ(v.empty(), true);
    REQUIRE_EQ(l.empty(), true);
}

TEST_CASE("mtl::shuffle with iterators with containers<std::string>")
{
    constexpr size_t size = 100;
    std::vector<std::string> v;
    v.reserve(size);
    for (size_t i = 0; i < size; i++)
    {
        v.push_back(std::to_string(i));
    }
    std::list<std::string> l(v.begin(), v.end());

    auto v_shuffle = v;
    auto l_shuffle = l;

    REQUIRE_NOTHROW(mtl::shuffle(v_shuffle));
    REQUIRE_NOTHROW(mtl::shuffle(l_shuffle));

    // check that the shuffled are different from the non shuffled
    REQUIRE_EQ((v_shuffle == v), false);
    REQUIRE_EQ((l_shuffle == l), false);

    // shuffle the originals
    REQUIRE_NOTHROW(mtl::shuffle(v));
    REQUIRE_NOTHROW(mtl::shuffle(l));

    // check again that they are different even though they are both shuffled
    REQUIRE_EQ((v_shuffle == v), false);
    REQUIRE_EQ((l_shuffle == l), false);
}