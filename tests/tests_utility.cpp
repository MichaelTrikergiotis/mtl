// tests by Michael Trikergiotis
// 28/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <utility>            // std::move
#include <type_traits>        // std::is_copy_constructible_v, std::is_move_constructible_v,
                              // std::is_copy_assignable_v, std::is_move_assignable_v


#include "../mtl/utility.hpp" 
// MTL_ASSERT_MSG, [@class] mtl::no_copy, [@class] mtl::no_move


// ------------------------------------------------------------------------------------------------
// MTL_ASSERT_MSG
// ------------------------------------------------------------------------------------------------

TEST_CASE("MTL_ASSERT_MSG")
{
    bool successfull_execution = false;

    // check that MTL_ASSERT_MSG and assert have matching functionality, because MTL_ASSERT_MSG
    // is just assert with a message
    assert(1 > 0);
    MTL_ASSERT_MSG(1 > 0, "1 should be larger than 0.");
    
    // check a const variable
    [[maybe_unused]]const int x = 150;
    assert(x == 150);
    MTL_ASSERT_MSG(x == 150, "The variable should be equal to 150.");
    
    // check a constexpr variable
    [[maybe_unused]]constexpr int y = -999;
    assert(y == -999);
    MTL_ASSERT_MSG(y == -999, "The variable should be equal to -999.");

    // check with negation of the checked condition
    [[maybe_unused]]const int z = 10;
    assert(!(z < 10));
    MTL_ASSERT_MSG(!(z < 10), "The variable should be smaller than 10");

    
    [[maybe_unused]]const int ten = 10;
    assert(ten > 9);
    assert(ten >= 10);
    assert(ten == 10);
    MTL_ASSERT_MSG(ten > 9, "The variable should be larger than 9.");
    MTL_ASSERT_MSG(ten >= 10, "The variable should be larger or equal to 10.");
    MTL_ASSERT_MSG(ten == 10, "The variable should be equal to 10.");

    // check that MTL_ASSERT_MSG works with variables that are not const or constexpr
    int number = 0;
    for(int i = 0; i < 10; i++)
    {
        // check a non-const variable using MTL_ASSERT_MSG
        MTL_ASSERT_MSG(number == i, "The variable checked is incorrect.");
        // make sure the number we are checking is correct
        REQUIRE_EQ((number == i), true);
        number++;
    }
    
    

    // if we reached this point means all the previous code executed successfully
    successfull_execution = true;
    REQUIRE_EQ(successfull_execution, true);
}

// ------------------------------------------------------------------------------------------------
// mtl::no_copy
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::no_copy")
{
    class normal_class {};
    REQUIRE_EQ(std::is_copy_constructible_v<normal_class>, true);
    REQUIRE_EQ(std::is_move_constructible_v<normal_class>, true);
    REQUIRE_EQ(std::is_copy_assignable_v<normal_class>, true);
    REQUIRE_EQ(std::is_move_assignable_v<normal_class>, true);
    class no_copy_class : mtl::no_copy {};
    REQUIRE_EQ(std::is_copy_constructible_v<no_copy_class>, false);
    REQUIRE_EQ(std::is_move_constructible_v<no_copy_class>, true);
    REQUIRE_EQ(std::is_copy_assignable_v<no_copy_class>, false);
    REQUIRE_EQ(std::is_move_assignable_v<no_copy_class>, true);

    // test that it can be move constructed and move assigned
    [[maybe_unused]] no_copy_class ncc1;
    [[maybe_unused]] no_copy_class ncc2(std::move(ncc1));
    [[maybe_unused]] no_copy_class ncc3;
    [[maybe_unused]] no_copy_class ncc4 = std::move(ncc3);
}

// ------------------------------------------------------------------------------------------------
// mtl::no_move
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::no_move")
{
    class normal_class {};
    REQUIRE_EQ(std::is_copy_constructible_v<normal_class>, true);
    REQUIRE_EQ(std::is_move_constructible_v<normal_class>, true);
    REQUIRE_EQ(std::is_copy_assignable_v<normal_class>, true);
    REQUIRE_EQ(std::is_move_assignable_v<normal_class>, true);
    class no_move_class : mtl::no_move {};
    CHECK_EQ(std::is_copy_constructible_v<no_move_class>, false);
    CHECK_EQ(std::is_move_constructible_v<no_move_class>, false);
    CHECK_EQ(std::is_copy_assignable_v<no_move_class>, false);
    CHECK_EQ(std::is_move_assignable_v<no_move_class>, false);
}
