// tests by Michael Trikergiotis
// 28/05/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <type_traits>        // std::is_copy_constructible, std::is_move_constructible

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/utility.hpp" 
// MTL_ASSERT_MSG, [@class] mtl::no_copy, [@class] mtl::no_move, [@class] mtl::no_copy_move


// ------------------------------------------------------------------------------------------------
// MTL_ASSERT_MSG
// ------------------------------------------------------------------------------------------------

TEST_CASE("MTL_ASSERT_MSG")
{
    bool successfull_execution = false;

    // check that MTL_ASSERT_MSG and assert have matching funcitonality, because MTL_ASSERT_MSG
    // is just assert with a message
    assert(1 > 0);
    MTL_ASSERT_MSG(1 > 0, "1 should be larger than 0.");
    
    // chekc a const variable
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
    
    

    // if we reached this point means all the previous code executed succesfully
    successfull_execution = true;
    REQUIRE_EQ(successfull_execution, true);
}

// ------------------------------------------------------------------------------------------------
// mtl::no_copy
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::no_copy")
{
    struct normal_class {};
    REQUIRE_EQ(std::is_copy_constructible_v<normal_class>, true);
    struct no_copy_class : mtl::no_copy {};
    REQUIRE_EQ(std::is_copy_constructible_v<no_copy_class>, false);

}

// ------------------------------------------------------------------------------------------------
// mtl::no_move
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::no_move")
{
    struct normal_class {};
    REQUIRE_EQ(std::is_move_constructible_v<normal_class>, true);
    struct no_move_class : mtl::no_move {};
    REQUIRE_EQ(std::is_move_constructible_v<no_move_class>, false);
}

// ------------------------------------------------------------------------------------------------
// mtl::no_copy_move
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::no_copy_move")
{
    struct normal_class {};
    REQUIRE_EQ(std::is_copy_constructible_v<normal_class>, true);
    REQUIRE_EQ(std::is_move_constructible_v<normal_class>, true);
    struct no_copy_move_class : mtl::no_copy_move {};
    REQUIRE_EQ(std::is_copy_constructible_v<no_copy_move_class>, false);
    REQUIRE_EQ(std::is_move_constructible_v<no_copy_move_class>, false);
}