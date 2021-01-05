// tests by Michael Trikergiotis
// 05/06/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <string>
#include <vector>
#include <list>
#include <set>
#include <utility>   // std::pair
#include <stdexcept> // std::invalid_argument

// Disable some of the asserts in mtl so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/string.hpp"
// mtl::string::is_upper, mtl::string::is_lower, mtl::string::to_upper, mtl::string::to_lower,
// mtl::string::is_ascii, mtl::string::is_alphabetic, mtl::string::is_numeric, 
// mtl::string::is_alphanum,  mtl::string::contains, mtl::string::strip_front, 
// mtl::string::strip_back, mtl::string::strip, mtl::string::pad_front, mtl::string::pad_back,
// mtl::string::pad, mtl::string::to_string, mtl::string::join_all, mtl::string::join,
// mtl::string::split, mtl::string::replace, mtl::string::replace_all



// ------------------------------------------------------------------------------------------------
// Create some UTF8 strings to check if functions can handle UTF8 without problem.
// ------------------------------------------------------------------------------------------------


// We have to use reinterpret_cast<const char*>(u8"utf8_str") so the tests can be compiled for
// both C++ 17 and C++ 20 or later where the flag gcc/clang flag -fno-char8_t or the
// MSVC /Zc:char8_t- flag was not used. This is because C++ 20 introduced a breaking change,
// u8 string literals are now char8_t type instead of char_t type. 
// For more information check :
// http:// www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1423r3.html#reinterpret_cast
// https:// stackoverflow.com/a/57453713
// https:// docs.microsoft.com/en-us/cpp/overview/cpp-conformance-improvements?view=vs-2019#char8_t
const std::string only_ascii ("abcdefghijklmnopqrstABCDEFGHIJKLMNOPQRST");

const std::string one_nonascii 
(reinterpret_cast<const char*>(u8"abcdefghijklmnopqrst😊ABCDEFGHIJKLMNOPQRST"));
    
const std::string only_nonascii 
(reinterpret_cast<const char*>(u8"你好，世界 Γειά σου Κόσμε こんにちは世界"));
    
const std::string mixed_nonascii 
(reinterpret_cast<const char*>(u8"Hello world 你好，世界 Γειά σου Κόσμε こんにちは世界"));

const std::string one_nonascii_upper 
(reinterpret_cast<const char*>(u8"ABCDEFGHIJKLMNOPQRST😊ABCDEFGHIJKLMNOPQRST"));
    
const std::string only_nonascii_upper
(reinterpret_cast<const char*>(u8"你好，世界 Γειά σου Κόσμε こんにちは世界"));
    
const std::string mixed_nonascii_upper
(reinterpret_cast<const char*>(u8"HELLO WORLD 你好，世界 Γειά σου Κόσμε こんにちは世界"));

const std::string one_nonascii_lower 
(reinterpret_cast<const char*>(u8"abcdefghijklmnopqrst😊abcdefghijklmnopqrst"));
    
const std::string only_nonascii_lower
(reinterpret_cast<const char*>(u8"你好，世界 Γειά σου Κόσμε こんにちは世界"));
    
const std::string mixed_nonascii_lower
(reinterpret_cast<const char*>(u8"hello world 你好，世界 Γειά σου Κόσμε こんにちは世界"));

const std::string smiley (reinterpret_cast<const char*>(u8"😊"));
const std::string two_smileys (reinterpret_cast<const char*>(u8"😊😊"));
const std::string two_smileys_delimiter (reinterpret_cast<const char*>(u8"😊|😊"));
const std::string smiley_front_space (reinterpret_cast<const char*>(u8" 😊"));
const std::string smiley_back_space (reinterpret_cast<const char*>(u8"😊 "));
const std::string smiley_spaces (reinterpret_cast<const char*>(u8" 😊 "));





// ------------------------------------------------------------------------------------------------
// mtl::string::is_upper / mtl::string::is_lower
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::is_upper")
{
    char small_char = 'a';
    char big_char = 'A';
    CHECK_EQ(mtl::string::is_upper('a'), false);
    CHECK_EQ(mtl::string::is_upper(small_char), false);
    CHECK_EQ(mtl::string::is_upper('A'), true);
    CHECK_EQ(mtl::string::is_upper(big_char), true);

    std::string small_str = "aaaa";
    std::string big_str = "AAAA";
    std::string mixed_str = "aaaAAAaa";
    std::string numbers = "1111222";
    CHECK_EQ(mtl::string::is_upper(small_str), false);
    CHECK_EQ(mtl::string::is_upper(big_str), true);
    CHECK_EQ(mtl::string::is_upper(mixed_str), false);
    CHECK_EQ(mtl::string::is_upper(numbers), false);

    CHECK_EQ(mtl::string::is_upper(one_nonascii), false);
    CHECK_EQ(mtl::string::is_upper(only_nonascii), false);
    CHECK_EQ(mtl::string::is_upper(mixed_nonascii), false);
}


TEST_CASE("mtl::string::is_lower")
{
    char small_char = 'a';
    char big_char = 'A';
    CHECK_EQ(mtl::string::is_lower('a'), true);
    CHECK_EQ(mtl::string::is_lower(small_char), true);
    CHECK_EQ(mtl::string::is_lower('A'), false);
    CHECK_EQ(mtl::string::is_lower(big_char), false);

    char first_small = static_cast<char>(97);
    char last_small  = static_cast<char>(122);
    CHECK_EQ(mtl::string::is_lower(first_small), true);
    CHECK_EQ(mtl::string::is_lower(last_small), true);

    char some_small1 = static_cast<char>(98);
    char some_small2  = static_cast<char>(121);
    CHECK_EQ(mtl::string::is_lower(some_small1), true);
    CHECK_EQ(mtl::string::is_lower(some_small2), true);

    char not_small1 = static_cast<char>(96);
    char not_small2  = static_cast<char>(123);
    CHECK_EQ(mtl::string::is_lower(not_small1), false);
    CHECK_EQ(mtl::string::is_lower(not_small2), false);



    std::string small_str = "aaaa";
    std::string big_str = "AAAA";
    std::string mixed_str = "aaaAAAaa";
    std::string numbers = "1111222";
    CHECK_EQ(mtl::string::is_lower(small_str), true);
    CHECK_EQ(mtl::string::is_lower(big_str), false);
    CHECK_EQ(mtl::string::is_lower(mixed_str), false);
    CHECK_EQ(mtl::string::is_lower(numbers), false);

    CHECK_EQ(mtl::string::is_lower(one_nonascii), false);
    CHECK_EQ(mtl::string::is_lower(only_nonascii), false);
    CHECK_EQ(mtl::string::is_lower(mixed_nonascii), false);
}

// ------------------------------------------------------------------------------------------------
// mtl::string::to_upper / mtl::string::to_lower
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::to_upper")
{
    char small_char = 'a';
    char big_char = 'A';
    mtl::string::to_upper(small_char);
    CHECK_EQ(small_char, big_char);

    mtl::string::to_upper(big_char);
    CHECK_EQ(big_char, 'A');

    char num_c = '7';
    mtl::string::to_upper(num_c);
    CHECK_EQ(num_c, '7');

    std::string empty;
    std::string small_str = "aaaa";
    std::string big_str = "AAAA";
    std::string mixed_str = "aaAA";
    std::string numbers = "1111222";
    
    mtl::string::to_upper(empty);
    CHECK_EQ(empty, std::string());
    mtl::string::to_upper(small_str);
    CHECK_EQ(small_str, big_str);
    mtl::string::to_upper(mixed_str);
    CHECK_EQ(mixed_str, big_str);
    CHECK_EQ(mixed_str, small_str);
    mtl::string::to_upper(numbers);
    CHECK_EQ(numbers, std::string("1111222"));

    // create copies of the const strings so we can modify them
    std::string _one_nonascii = one_nonascii;
    std::string _only_nonascii = only_nonascii;
    std::string _mixed_nonascii = mixed_nonascii;
    mtl::string::to_upper(_one_nonascii);
    mtl::string::to_upper(_only_nonascii);
    mtl::string::to_upper(_mixed_nonascii);
    CHECK_EQ((_one_nonascii == one_nonascii_upper), true);
    CHECK_EQ((_only_nonascii == only_nonascii_upper), true);
    CHECK_EQ((_mixed_nonascii == mixed_nonascii_upper), true);
}


TEST_CASE("mtl::string::to_lower")
{
    char small_char = 'a';
    char big_char = 'A';
    mtl::string::to_lower(big_char);
    CHECK_EQ(small_char, big_char);
    CHECK_EQ(big_char, 'a');

    char num_c = '7';
    mtl::string::to_lower(num_c);
    CHECK_EQ(num_c, '7');

    std::string empty;
    std::string small_str = "aaaa";
    std::string big_str = "AAAA";
    std::string mixed_str = "aaAA";
    std::string numbers = "1111222";
    
    mtl::string::to_lower(empty);
    CHECK_EQ(empty, std::string());
    mtl::string::to_lower(big_str);
    CHECK_EQ(big_str, small_str);
    mtl::string::to_lower(mixed_str);
    CHECK_EQ(mixed_str, big_str);
    CHECK_EQ(mixed_str, small_str);
    mtl::string::to_lower(numbers);
    CHECK_EQ(numbers, std::string("1111222"));

    // create copies of the const strings so we can modify them
    std::string _one_nonascii = one_nonascii;
    std::string _only_nonascii = only_nonascii;
    std::string _mixed_nonascii = mixed_nonascii;
    mtl::string::to_lower(_one_nonascii);
    mtl::string::to_lower(_only_nonascii);
    mtl::string::to_lower(_mixed_nonascii);
    CHECK_EQ((_one_nonascii == one_nonascii_lower), true);
    CHECK_EQ((_only_nonascii == only_nonascii_lower), true);
    CHECK_EQ((_mixed_nonascii == mixed_nonascii_lower), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::string::is_ascii
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::is_ascii")
{
    for(int i = 0; i <= 127; i++)
    {
        CHECK_EQ(mtl::string::is_ascii(i), true);
    }
    for(int i = 0; i <= 127; i++)
    {
        CHECK_EQ(mtl::string::is_ascii(static_cast<char>(i)), true);
    }

    // over 127
    for(int i = 128; i <= 200; i++)
    {
        CHECK_EQ(mtl::string::is_ascii(i), false);
    }
    for(int i = 128; i <= 200; i++)
    {
        CHECK_EQ(mtl::string::is_ascii(static_cast<char>(i)), false);
    }

    // negative, all should be false
    for(int i = -1; i >= -200; i--)
    {
        CHECK_EQ(mtl::string::is_ascii(i), false);
    }
    
    std::string empty;
    std::string ascii_letters = "abcdefghijklmnoqrstABCDEFGHIJKLMNOPQRST";
    std::string ascii_numbers = "01234567890";
    std::string all_ascii = "aaabcdef##123";
    CHECK_EQ(mtl::string::is_ascii(empty), true);
    CHECK_EQ(mtl::string::is_ascii(ascii_letters), true);
    CHECK_EQ(mtl::string::is_ascii(ascii_numbers), true);
    CHECK_EQ(mtl::string::is_ascii(all_ascii), true);

    // check that is works correctly with UTF8 strings
    CHECK_EQ(mtl::string::is_ascii(one_nonascii), false);
    CHECK_EQ(mtl::string::is_ascii(only_nonascii), false);
    CHECK_EQ(mtl::string::is_ascii(mixed_nonascii), false);
    
}


// ------------------------------------------------------------------------------------------------
// mtl::string::is_alphabetic, mtl::string::is_numeric, mtl::string::is_alphanum
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::is_alphabetic")
{
    char alphabetic1 = 'd';
    char alphabetic2 = 'J';
    char non_alphabetic1 = '5';
    char non_alphabetic2 = '#';
    CHECK_EQ(mtl::string::is_alphabetic(alphabetic1), true);
    CHECK_EQ(mtl::string::is_alphabetic(alphabetic2), true);
    CHECK_EQ(mtl::string::is_alphabetic(non_alphabetic1), false);
    CHECK_EQ(mtl::string::is_alphabetic(non_alphabetic2), false);

    char first_small = static_cast<char>(97);
    char last_small  = static_cast<char>(122);
    CHECK_EQ(mtl::string::is_alphabetic(first_small), true);
    CHECK_EQ(mtl::string::is_alphabetic(last_small), true);

    char some_small1 = static_cast<char>(98);
    char some_small2  = static_cast<char>(121);
    CHECK_EQ(mtl::string::is_alphabetic(some_small1), true);
    CHECK_EQ(mtl::string::is_alphabetic(some_small2), true);

    char not_small1 = static_cast<char>(96);
    char not_small2  = static_cast<char>(123);
    CHECK_EQ(mtl::string::is_alphabetic(not_small1), false);
    CHECK_EQ(mtl::string::is_alphabetic(not_small2), false);



    std::string alphab1 = "abcdefgGHFAAHH";
    std::string alphab2 = "M";
    std::string nalpha1 = "1234567890";
    std::string nalpha2 = "abcedfh5klmn";
    std::string other = "  #303# ";
    CHECK_EQ(mtl::string::is_alphabetic(alphab1), true);
    CHECK_EQ(mtl::string::is_alphabetic(alphab2), true);
    CHECK_EQ(mtl::string::is_alphabetic(nalpha1), false);
    CHECK_EQ(mtl::string::is_alphabetic(nalpha2), false);
    CHECK_EQ(mtl::string::is_alphabetic(other), false);

    // check that is works correctly with UTF8 strings
    CHECK_EQ(mtl::string::is_alphabetic(one_nonascii), false);
    CHECK_EQ(mtl::string::is_alphabetic(only_nonascii), false);
    CHECK_EQ(mtl::string::is_alphabetic(mixed_nonascii), false);
}


TEST_CASE("mtl::string::is_numeric")
{
    char alphabetic1 = 'd';
    char alphabetic2 = 'J';
    char non_alphabetic1 = '5';
    char non_alphabetic2 = '#';
    CHECK_EQ(mtl::string::is_numeric(alphabetic1), false);
    CHECK_EQ(mtl::string::is_numeric(alphabetic2), false);
    CHECK_EQ(mtl::string::is_numeric(non_alphabetic1), true);
    CHECK_EQ(mtl::string::is_numeric(non_alphabetic2), false);

    std::string alphab1 = "abcdefgGHFAAHH";
    std::string alphab2 = "M";
    std::string nalpha1 = "1234567890";
    std::string nalpha2 = "abcedfh5klmn";
    std::string other = "  #303# ";
    CHECK_EQ(mtl::string::is_numeric(alphab1), false);
    CHECK_EQ(mtl::string::is_numeric(alphab2), false);
    CHECK_EQ(mtl::string::is_numeric(nalpha1), true);
    CHECK_EQ(mtl::string::is_numeric(nalpha2), false);
    CHECK_EQ(mtl::string::is_numeric(other), false);

    // check that is works correctly with UTF8 strings
    CHECK_EQ(mtl::string::is_numeric(one_nonascii), false);
    CHECK_EQ(mtl::string::is_numeric(only_nonascii), false);
    CHECK_EQ(mtl::string::is_numeric(mixed_nonascii), false);
}


TEST_CASE("mtl::string::is_alphanum")
{
    char alphabetic1 = 'd';
    char alphabetic2 = 'J';
    char non_alphabetic1 = '5';
    char non_alphabetic2 = '#';
    CHECK_EQ(mtl::string::is_alphanum(alphabetic1), true);
    CHECK_EQ(mtl::string::is_alphanum(alphabetic2), true);
    CHECK_EQ(mtl::string::is_alphanum(non_alphabetic1), true);
    CHECK_EQ(mtl::string::is_alphanum(non_alphabetic2), false);

    std::string alphab1 = "abcdefgGHFAAHH";
    std::string alphab2 = "M";
    std::string nalpha1 = "1234567890";
    std::string nalpha2 = "abcedfh5klmn";
    std::string other = "  #303# ";
    CHECK_EQ(mtl::string::is_alphanum(alphab1), true);
    CHECK_EQ(mtl::string::is_alphanum(alphab2), true);
    CHECK_EQ(mtl::string::is_alphanum(nalpha1), true);
    CHECK_EQ(mtl::string::is_alphanum(nalpha2), true);
    CHECK_EQ(mtl::string::is_alphanum(other), false);

    // check that is works correctly with UTF8 strings
    CHECK_EQ(mtl::string::is_alphanum(one_nonascii), false);
    CHECK_EQ(mtl::string::is_alphanum(only_nonascii), false);
    CHECK_EQ(mtl::string::is_alphanum(mixed_nonascii), false);
}

// -----------------------------------------------------------------------------------------------
// mtl::string::contains
// -----------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::contains, std::string / std::string")
{
    std::string empty1;
    std::string empty2;
    CHECK_EQ(mtl::string::contains(empty1, empty2), true);
    CHECK_EQ(mtl::string::contains(std::string(), empty2), true);
    CHECK_EQ(mtl::string::contains(empty1, std::string()), true);
    CHECK_EQ(mtl::string::contains(std::string(), std::string()), true);

    std::string s1 = "ABCDE";
    std::string s2 = "BCD";
    std::string s3 = "DCB";
    CHECK_EQ(mtl::string::contains(s1, s2), true);
    CHECK_EQ(mtl::string::contains(s1, s3), false);
    CHECK_EQ(mtl::string::contains(std::string("ABCDE"), s2), true);
    CHECK_EQ(mtl::string::contains(std::string("ABCDE"), s3), false);

    // check that is works correctly with UTF8 strings
    CHECK_EQ(mtl::string::contains(one_nonascii, smiley), true);
    CHECK_EQ(mtl::string::contains(only_nonascii, smiley), false);
    CHECK_EQ(mtl::string::contains(mixed_nonascii, smiley), false);
}

TEST_CASE("mtl::string::contains, std::string / const char*")
{
    std::string empty1;
    const char* empty2 = "";
    CHECK_EQ(mtl::string::contains(empty1, empty2), true);
    CHECK_EQ(mtl::string::contains(empty1, ""), true);
    CHECK_EQ(mtl::string::contains(std::string(), empty2), true);
    CHECK_EQ(mtl::string::contains(std::string(), ""), true);
    

    std::string s1 = "ABCDE";
    const char* s2 = "BCD";
    const char* s3 = "DCB";
    CHECK_EQ(mtl::string::contains(s1, s2), true);
    CHECK_EQ(mtl::string::contains(s1, s3), false);
}

TEST_CASE("mtl::string::contains, const char* / std::string")
{
    const char* empty1 = "";
    std::string empty2 = "";
    CHECK_EQ(mtl::string::contains(empty1, empty2), true);
    CHECK_EQ(mtl::string::contains("", empty2), true);
    CHECK_EQ(mtl::string::contains(empty1, std::string()), true);
    

    const char* s1 = "ABCDE";
    std::string s2 = "BCD";
    std::string s3 = "DCB";
    CHECK_EQ(mtl::string::contains(s1, s2), true);
    CHECK_EQ(mtl::string::contains(s1, s3), false);
}

TEST_CASE("mtl::string::contains, const char* / const char*")
{
    const char* empty1 = "";
    const char* empty2 = "";
    CHECK_EQ(mtl::string::contains(empty1, empty2), true);
    CHECK_EQ(mtl::string::contains("", empty2), true);
    CHECK_EQ(mtl::string::contains(empty1, ""), true);
    

    const char* s1 = "ABCDE";
    const char* s2 = "BCD";
    const char* s3 = "DCB";
    CHECK_EQ(mtl::string::contains(s1, s2), true);
    CHECK_EQ(mtl::string::contains(s1, s3), false);
}

// ------------------------------------------------------------------------------------------------
// mtl::string::strip_front, mtl::string::strip_back, mtl::string::strip
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::strip_front")
{
    std::string front_space = "   John";
    mtl::string::strip_front(front_space);
    CHECK_EQ(front_space, std::string("John"));

    std::string front_underscore = "_________Mary";
    mtl::string::strip_front(front_underscore, '_');
    CHECK_EQ(front_underscore, std::string("Mary"));

    std::string mill = "rmill";
    mtl::string::strip_front(mill, 'r');
    CHECK_EQ(mill, std::string("mill"));

    // call multiple times with different characters
    std::string number = " #303# ";
    mtl::string::strip_front(number, ' ');
    mtl::string::strip_front(number, '#');
    CHECK_EQ(number, std::string("303# "));

    
    // test where nothing matches
    std::string no_match = "ABCDEF";
    mtl::string::strip_front(no_match, '2');
    CHECK_EQ(no_match, std::string("ABCDEF"));

    std::string delimiter_middle = "NNNNN|NNNNN";
    mtl::string::strip_front(delimiter_middle, 'N');
    CHECK_EQ(delimiter_middle, std::string("|NNNNN"));
    
    // test where the input is a single character long and removes all characters
    std::string single_char = "A";
    mtl::string::strip_front(single_char, 'A');
    CHECK_EQ(single_char.size(), 0);
    CHECK_EQ(single_char, std::string());

    // test where the input is multiple characters long and removes all characters
    std::string all_same_chars = "AAAAA";
    mtl::string::strip_front(all_same_chars, 'A');
    CHECK_EQ(all_same_chars.size(), 0);
    CHECK_EQ(all_same_chars, std::string());

    // test where there is one character to remove and the size of the remaining string
    // is also one
    std::string same_length_single = " a";
    mtl::string::strip_front(same_length_single);
    CHECK_EQ(same_length_single.size(), 1);
    CHECK_EQ(same_length_single, std::string("a"));

    // test where the amount of characters to remove are the same as the size of the remaining
    // string
    std::string same_length = "  aa";
    mtl::string::strip_front(same_length);
    CHECK_EQ(same_length.size(), 2);
    CHECK_EQ(same_length, std::string("aa"));



    // check that is works correctly with UTF8 strings

    // create a copy of const string so we can modify it
    std::string _smiley_front_space = smiley_front_space;
    mtl::string::strip_front(_smiley_front_space);
    CHECK_EQ((_smiley_front_space == smiley), true);
    CHECK_EQ((_smiley_front_space == smiley_front_space), false);
}

TEST_CASE("mtl::string::strip_back")
{
    std::string front_space = "John  ";
    mtl::string::strip_back(front_space);
    CHECK_EQ(front_space, std::string("John"));

    std::string front_underscore = "Mary_________";
    mtl::string::strip_back(front_underscore, '_');
    CHECK_EQ(front_underscore, std::string("Mary"));

    std::string mill = "millrrr";
    mtl::string::strip_back(mill, 'r');
    CHECK_EQ(mill, std::string("mill"));

    std::string number = " #303# ";
    mtl::string::strip_back(number, ' ');
    mtl::string::strip_back(number, '#');
    CHECK_EQ(number, std::string(" #303"));


    // test where nothing matches
    std::string no_match = "ABCDEF";
    mtl::string::strip_back(no_match, '2');
    CHECK_EQ(no_match, std::string("ABCDEF"));

    std::string delimiter_middle = "NNNNN|NNNNN";
    mtl::string::strip_back(delimiter_middle, 'N');
    CHECK_EQ(delimiter_middle, std::string("NNNNN|"));
    
    // test where the input is a single character long and removes all characters
    std::string single_char = "A";
    mtl::string::strip_back(single_char, 'A');
    CHECK_EQ(single_char.size(), 0);
    CHECK_EQ(single_char, std::string());

    // test where the input is multiple characters long and removes all characters
    std::string all_same_chars = "AAAAA";
    mtl::string::strip_back(all_same_chars, 'A');
    CHECK_EQ(all_same_chars.size(), 0);
    CHECK_EQ(all_same_chars, std::string());

    // test where there is one character to remove and the size of the remaining string
    // is also one
    std::string same_length_single = "a ";
    mtl::string::strip_back(same_length_single);
    CHECK_EQ(same_length_single.size(), 1);
    CHECK_EQ(same_length_single, std::string("a"));

    // test where the amount of characters to remove are the same as the size of the remaining
    // string
    std::string same_length = "aa  ";
    mtl::string::strip_back(same_length);
    CHECK_EQ(same_length.size(), 2);
    CHECK_EQ(same_length, std::string("aa"));


    // check that is works correctly with UTF8 strings

    // create a copy of const string so we can modify it
    std::string _smiley_back_space = smiley_back_space;
    mtl::string::strip_back(_smiley_back_space);
    CHECK_EQ((_smiley_back_space == smiley), true);
    CHECK_EQ((_smiley_back_space == smiley_back_space), false);
}


TEST_CASE("mtl::string::strip")
{
    std::string front_space = "  John  ";
    mtl::string::strip(front_space);
    CHECK_EQ(front_space, std::string("John"));

    std::string front_underscore = "__Mary_________";
    mtl::string::strip(front_underscore, '_');
    CHECK_EQ(front_underscore, std::string("Mary"));

    std::string mill = "rmillrrr";
    mtl::string::strip(mill, 'r');
    CHECK_EQ(mill, std::string("mill"));

    std::string number = " #303# ";
    mtl::string::strip(number, ' ');
    mtl::string::strip(number, '#');
    CHECK_EQ(number, std::string("303"));


    // test where nothing matches
    std::string no_match = "ABCDEF";
    mtl::string::strip(no_match, '2');
    CHECK_EQ(no_match, std::string("ABCDEF"));

    std::string delimiter_middle = "NNNNN|NNNNN";
    mtl::string::strip(delimiter_middle, 'N');
    CHECK_EQ(delimiter_middle, std::string("|"));
    
    // test where the input is a single character long and removes all characters
    std::string single_char = "A";
    mtl::string::strip(single_char, 'A');
    CHECK_EQ(single_char.size(), 0);
    CHECK_EQ(single_char, std::string());

    // test where the input is multiple characters long and removes all characters
    std::string all_same_chars = "AAAAA";
    mtl::string::strip(all_same_chars, 'A');
    CHECK_EQ(all_same_chars.size(), 0);
    CHECK_EQ(all_same_chars, std::string());


    // test where there is one character to remove from the front and the size of the remaining
    // string is also one
    std::string same_length_single_front = " a";
    mtl::string::strip(same_length_single_front);
    CHECK_EQ(same_length_single_front.size(), 1);
    CHECK_EQ(same_length_single_front, std::string("a"));

    // test where the amount of characters to remove from the front are the same as the size of the
    // remaining string
    std::string same_length_front = "  aa";
    mtl::string::strip(same_length_front);
    CHECK_EQ(same_length_front.size(), 2);
    CHECK_EQ(same_length_front, std::string("aa"));


    // test where there is one character to remove from the back and the size of the remaining
    // string is also one
    std::string same_length_single_back = "a ";
    mtl::string::strip(same_length_single_back);
    CHECK_EQ(same_length_single_back.size(), 1);
    CHECK_EQ(same_length_single_back, std::string("a"));

    // test where the amount of characters to remove from the back are the same as the size of the
    // remaining string
    std::string same_length_back = "aa  ";
    mtl::string::strip(same_length_back);
    CHECK_EQ(same_length_back.size(), 2);
    CHECK_EQ(same_length_back, std::string("aa"));

    
    // test where there are two characters to remove, one in the front and one in the back and the
    // size of the remaining string is also one
    std::string same_length_two = " a ";
    mtl::string::strip(same_length_two);
    CHECK_EQ(same_length_two.size(), 1);
    CHECK_EQ(same_length_two, std::string("a"));

    // test where the amount of characters to remove are the twice the size of the remaining string
    std::string twice_length = "  aa  ";
    mtl::string::strip(twice_length);
    CHECK_EQ(twice_length.size(), 2);
    CHECK_EQ(twice_length, std::string("aa"));



    // check that is works correctly with UTF8 strings

    // create a copy of const string so we can modify it
    std::string _smiley_spaces = smiley_spaces;
    mtl::string::strip(_smiley_spaces);
    CHECK_EQ((_smiley_spaces == smiley), true);
    CHECK_EQ((_smiley_spaces == smiley_spaces), false);
}


// ------------------------------------------------------------------------------------------------
// mtl::string::pad_front, mtl::string::pad_back, mtl::string::pad
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::pad_front")
{
    std::string blank;
    mtl::string::pad_front(blank, 3);
    CHECK_EQ(blank, std::string("   "));

    std::string nothing;
    mtl::string::pad_front(nothing, 0);
    CHECK_EQ(nothing, std::string());

    std::string mike = "Mike";
    mtl::string::pad_front(mike, 0);
    CHECK_EQ(mike, std::string("Mike"));
    mtl::string::pad_front(mike, 5);
    CHECK_EQ(mike, std::string("     Mike"));
    std::string john = "John***";
    mtl::string::pad_front(john, 3, '*');
    CHECK_EQ(john, std::string("***John***"));
    std::string nick = "Nick";
    mtl::string::pad_front(nick, 3, '#');
    CHECK_EQ(nick, std::string("###Nick"));
        
    std::string long_mike = "Mike";
    std::string empty;
    mtl::string::pad_front(long_mike, empty);
    CHECK_EQ(long_mike, std::string("Mike"));
    mtl::string::pad_front(long_mike, mike);
    CHECK_EQ(long_mike, std::string("     Mike"));
    CHECK_EQ(long_mike, mike);
    std::string long_john = "John***";
    mtl::string::pad_front(long_john, john, '*');
    CHECK_EQ(long_john, std::string("***John***"));
    CHECK_EQ(long_john, john);
    std::string long_nick = "Nick";
    mtl::string::pad_front(long_nick, nick, '#');
    CHECK_EQ(long_nick, std::string("###Nick"));
    CHECK_EQ(long_nick, nick);

    // check that is works correctly with UTF8 strings

    // create a copy of const string so we can modify it
    std::string _smiley = smiley;
    mtl::string::pad_front(_smiley, 1);
    CHECK_EQ((_smiley == smiley_front_space), true);
    CHECK_EQ((_smiley == smiley), false);
}

TEST_CASE("mtl::string::pad_back")
{
    std::string mike = "Mike";
    mtl::string::pad_back(mike, 0);
    CHECK_EQ(mike, std::string("Mike"));
    mtl::string::pad_back(mike, 5);
    CHECK_EQ(mike, std::string("Mike     "));
    std::string john = "***John";
    mtl::string::pad_back(john, 3, '*');
    CHECK_EQ(john, std::string("***John***"));
    std::string nick = "Nick";
    mtl::string::pad_back(nick, 3, '#');
    CHECK_EQ(nick, std::string("Nick###"));
        
    std::string long_mike = "Mike";
    std::string empty;
    mtl::string::pad_back(long_mike, empty);
    CHECK_EQ(long_mike, std::string("Mike"));
    mtl::string::pad_back(long_mike, mike);
    CHECK_EQ(long_mike, std::string("Mike     "));
    CHECK_EQ(long_mike, mike);
    std::string long_john = "***John";
    mtl::string::pad_back(long_john, john, '*');
    CHECK_EQ(long_john, std::string("***John***"));
    CHECK_EQ(long_john, john);
    std::string long_nick = "Nick";
    mtl::string::pad_back(long_nick, nick, '#');
    CHECK_EQ(long_nick, std::string("Nick###"));
    CHECK_EQ(long_nick, nick);

    // check that is works correctly with UTF8 strings

    // create a copy of const string so we can modify it
    std::string _smiley = smiley;
    mtl::string::pad_back(_smiley, 1);
    CHECK_EQ((_smiley == smiley_back_space), true);
    CHECK_EQ((_smiley == smiley), false);
}

TEST_CASE("mtl::string::pad")
{
    std::string blank;
    mtl::string::pad(blank, 3);
    CHECK_EQ(blank, std::string("   "));

    std::string nothing;
    mtl::string::pad(nothing, 0);
    CHECK_EQ(nothing, std::string());

    std::string mike = "Mike";
    mtl::string::pad(mike, 0);
    CHECK_EQ(mike, std::string("Mike"));
    mtl::string::pad(mike, 10);
    CHECK_EQ(mike, std::string("     Mike     "));
    std::string john = "John";
    mtl::string::pad(john, 6, '*');
    CHECK_EQ(john, std::string("***John***"));
    std::string nick = "Nick";
    mtl::string::pad(nick, 6, '#');
    CHECK_EQ(nick, std::string("###Nick###"));
        
    std::string long_mike = "Mike";
    std::string empty;
    mtl::string::pad_front(long_mike, empty);
    CHECK_EQ(long_mike, std::string("Mike"));
    mtl::string::pad(long_mike, mike);
    CHECK_EQ(long_mike, std::string("     Mike     "));
    CHECK_EQ(long_mike, mike);
    std::string long_john = "John";
    mtl::string::pad(long_john, john, '*');
    CHECK_EQ(long_john, std::string("***John***"));
    CHECK_EQ(long_john, john);
    std::string long_nick = "Nick";
    mtl::string::pad(long_nick, nick, '#');
    CHECK_EQ(long_nick, std::string("###Nick###"));
    CHECK_EQ(long_nick, nick);


    std::vector<std::string> numbers 
    { "1", "22", "333", "4444", "55555", "666666", "7777777", "88888888", "999999999" };
    
    std::vector<std::string> padded_numbers 
    { "    1    ", "    22   ", "   333   ", "   4444  ", "  55555  ", "  666666 ", 
      " 7777777 ", " 88888888", "999999999" };

    REQUIRE_EQ(numbers.empty(), false);
    REQUIRE_EQ(padded_numbers.empty(), false);
    REQUIRE_EQ(numbers.size(), padded_numbers.size());

    for(size_t i = 0; i < numbers.size(); i++)
    {
        auto pnum = numbers.at(i);
        mtl::string::pad(pnum, numbers.back(), ' ', false);
        CHECK_EQ(pnum, padded_numbers.at(i));
        CHECK_EQ(pnum.size(), numbers.back().size());
    }

    // check that is works correctly with UTF8 strings
    
    // create a copy of const string so we can modify it
    std::string _smiley = smiley;
    mtl::string::pad(_smiley, 2);
    CHECK_EQ((_smiley == smiley_spaces), true);
    CHECK_EQ((_smiley == smiley), false);
}

TEST_CASE("mtl::string::pad with more_back set to true")
{
    std::string mike = "Mike";
    mtl::string::pad(mike, 0, ' ', true);
    CHECK_EQ(mike, std::string("Mike"));
    mtl::string::pad(mike, 10, ' ', true);
    CHECK_EQ(mike, std::string("     Mike     "));
    
    std::string john = "John";
    mtl::string::pad(john, 6, '*', true);
    CHECK_EQ(john, std::string("***John***"));
    std::string nick = "Nick";
    mtl::string::pad(nick, 6, '#', true);
    CHECK_EQ(nick, std::string("###Nick###"));
        
    std::string long_mike = "Mike";
    std::string empty;
    mtl::string::pad_front(long_mike, empty);
    CHECK_EQ(long_mike, std::string("Mike"));
    mtl::string::pad(long_mike, mike, ' ', true);
    CHECK_EQ(long_mike, std::string("     Mike     "));
    CHECK_EQ(long_mike, mike);
    std::string long_john = "John";
    mtl::string::pad(long_john, john, '*', true);
    CHECK_EQ(long_john, std::string("***John***"));
    CHECK_EQ(long_john, john);
    std::string long_nick = "Nick";
    mtl::string::pad(long_nick, nick, '#', true);
    CHECK_EQ(long_nick, std::string("###Nick###"));
    CHECK_EQ(long_nick, nick);

    std::vector<std::string> numbers 
    { "1", "22", "333", "4444", "55555", "666666", "7777777", "88888888", "999999999" };
    
    std::vector<std::string> padded_numbers 
    { "    1    ", "   22    ", "   333   ", "  4444   ", "  55555  ", " 666666  ", 
      " 7777777 ", "88888888 ", "999999999" };

    REQUIRE_EQ(numbers.empty(), false);
    REQUIRE_EQ(padded_numbers.empty(), false);
    REQUIRE_EQ(numbers.size(), padded_numbers.size());

    for(size_t i = 0; i < numbers.size(); i++)
    {
        auto pnum = numbers.at(i);
        mtl::string::pad(pnum, numbers.back(), ' ', true);
        CHECK_EQ(pnum, padded_numbers.at(i));
        CHECK_EQ(pnum.size(), numbers.back().size());
    }


    // check that is works correctly with UTF8 strings
    
    // create a copy of const string so we can modify it
    std::string _smiley = smiley;
    mtl::string::pad(_smiley, 2, ' ', true);
    CHECK_EQ((_smiley == smiley_spaces), true);
    CHECK_EQ((_smiley == smiley), false);
}


// ------------------------------------------------------------------------------------------------
// mtl::string::to_string
// ------------------------------------------------------------------------------------------------

// create our own class with overloaded operator<< so we can convert to string successfully
class my_custom_class
{
    std::string s = "Numbers : " ;
    int i1 = 10;
    int i2 = 20;
    int i3 = 30;
    friend std::ostream& operator<<(std::ostream& out, const my_custom_class& cc)
    {
        return out << cc.s << cc.i1 << " " << cc.i2 << " " << cc.i3;
    }
};



TEST_CASE("mtl::string::to_string with temp")
{
    std::string int_s = mtl::string::to_string(150);
    CHECK_EQ(int_s, std::string("150"));
    std::string ulint_s = mtl::string::to_string(150UL);
    CHECK_EQ(ulint_s, std::string("150"));
    std::string float_s = mtl::string::to_string(150.0f);
    CHECK_EQ(float_s, std::string("150"));
    std::string bool_s = mtl::string::to_string(true);
    CHECK_EQ(bool_s, std::string("true"));
    bool_s = mtl::string::to_string(false);
    CHECK_EQ(bool_s, std::string("false"));
    std::string pair_s = mtl::string::to_string(std::pair<int, char>(333, 'a'));
    CHECK_EQ(pair_s, std::string("333, a"));
    std::string pair_s2 = mtl::string::to_string(std::pair<int, char>(333, 'a'), " # ");
    CHECK_EQ(pair_s2, std::string("333 # a"));
    std::string char_s = mtl::string::to_string('c');
    CHECK_EQ(char_s, std::string("c"));
    std::string char_star_s = mtl::string::to_string("Hello Bill.");
    CHECK_EQ(char_star_s, std::string("Hello Bill."));
    std::string str_s = mtl::string::to_string(std::string("std::string -> std::string"));
    CHECK_EQ(str_s, std::string("std::string -> std::string"));
    std::string customc_s = mtl::string::to_string(my_custom_class());
    CHECK_EQ(customc_s, std::string("Numbers : 10 20 30"));    

}


TEST_CASE("mtl::string::to_string")
{
    int i = 150;
    std::string int_s = mtl::string::to_string(i);
    CHECK_EQ(int_s, std::string("150"));
    unsigned long ulint = 150UL;
    std::string ulint_s = mtl::string::to_string(ulint);
    CHECK_EQ(ulint_s, std::string("150"));
    float f = 150.0f;
    std::string float_s = mtl::string::to_string(f);
    CHECK_EQ(float_s, std::string("150"));
    bool b = true;
    std::string bool_s = mtl::string::to_string(b);
    CHECK_EQ(bool_s, std::string("true"));
    b = false;
    bool_s = mtl::string::to_string(b);
    CHECK_EQ(bool_s, std::string("false"));
    auto p = std::pair<int, char>(333, 'a');
    std::string pair_s = mtl::string::to_string(p);
    CHECK_EQ(pair_s, std::string("333, a"));
    std::string pair_s2 = mtl::string::to_string(p, " # ");
    CHECK_EQ(pair_s2, std::string("333 # a"));
    char c = 'c';
    std::string char_s = mtl::string::to_string(c);
    CHECK_EQ(char_s, std::string("c"));
    const char* cs = "Hello Bill.";
    std::string char_star_s = mtl::string::to_string(cs);
    CHECK_EQ(char_star_s, std::string("Hello Bill."));
    std::string str = "std::string -> std::string";
    std::string str_s = mtl::string::to_string(str);
    CHECK_EQ(str_s, std::string("std::string -> std::string"));
    my_custom_class my_class;
    std::string customc_s = mtl::string::to_string(my_class);
    CHECK_EQ(customc_s, std::string("Numbers : 10 20 30"));    

    // check that is works correctly with UTF8 strings

    std::string _one_nonascii = mtl::string::to_string(one_nonascii);
    std::string _only_nonascii = mtl::string::to_string(only_nonascii);
    std::string _mixed_nonascii = mtl::string::to_string(mixed_nonascii);
    CHECK_EQ((_one_nonascii == one_nonascii), true);
    CHECK_EQ((_only_nonascii == only_nonascii), true);
    CHECK_EQ((_mixed_nonascii == mixed_nonascii), true);
}


// ------------------------------------------------------------------------------------------------
// mtl::string::join_all
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::join_all")
{
    std::vector<int> empty_vi;
    std::string empty_i = mtl::string::join_all(empty_vi.begin(), empty_vi.end());
    CHECK_EQ(empty_i, std::string());
    
    std::vector<float> empty_vf;
    std::string empty_f = mtl::string::join_all(empty_vf.begin(), empty_vf.end());
    CHECK_EQ(empty_f, std::string());

    std::vector<std::string> empty_vs;
    std::string empty_str = mtl::string::join_all(empty_vs.begin(), empty_vs.end());
    CHECK_EQ(empty_str, std::string());


    std::vector<char> vc {'a', 'b', 'c'};
    std::string vc_s = mtl::string::join_all(vc.begin(), vc.end());
    std::string desired_chars = "abc";
    CHECK_EQ(vc_s, desired_chars);

    std::vector<int> vi {1, 2, 3, 4, 5};
    std::list<int> li {1, 2, 3, 4, 5};
    std::set<int> si {1, 2, 3, 4, 5};
    std::string vi_s = mtl::string::join_all(vi.begin(), vi.end(), ", ");
    std::string li_s = mtl::string::join_all(li.begin(), li.end(), ", ");
    std::string si_s = mtl::string::join_all(si.begin(), si.end(), ", ");
    std::string desired = "1, 2, 3, 4, 5";
    CHECK_EQ(vi_s, desired);
    CHECK_EQ(li_s, desired);
    CHECK_EQ(si_s, desired);

    std::list<bool> lb = {true, true, false, true, true};
    std::string desired_bool = "truetruefalsetruetrue";
    std::string lb_s = mtl::string::join_all(lb.begin(), lb.end());
    CHECK_EQ(lb_s, desired_bool);

    std::vector<std::string> names {"Bill", "Mary", "Nick"};
    std::string delimiter = " | ";
    std::string names_s = mtl::string::join_all(names.begin(), names.end(), delimiter);
    std::string names_desired = "Bill | Mary | Nick";
    CHECK_EQ(names_s, names_desired);

    std::vector<double> vd {10.555, 11.666, 12.777};
    char delimiter_c = '_';
    std::string vd_s = mtl::string::join_all(vd.begin(), vd.end(), delimiter_c);
    std::string vd_desired = "10.555_11.666_12.777";
    CHECK_EQ(vd_s, vd_desired);

    std::vector<const char*> vcc = { "127", "0", "0", "1"};
    std::string vcc_s = mtl::string::join_all(vcc.begin(), vcc.end(), '.');
    std::string vcc_desired = "127.0.0.1";
    CHECK_EQ(vcc_s, vcc_desired);

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smiles { smiley, smiley };
    std::string two_smiles = mtl::string::join_all(smiles.begin(), smiles.end());
    CHECK_EQ((two_smiles == smiley), false);
    CHECK_EQ((two_smiles == two_smileys), true);
}

TEST_CASE("mtl::string::join_all with output")
{
    std::vector<int> empty_vi;
    std::string empty_i;
    mtl::string::join_all(empty_vi.begin(), empty_vi.end(), empty_i, std::string());
    CHECK_EQ(empty_i, std::string());
    
    std::vector<float> empty_vf;
    std::string empty_f;
    mtl::string::join_all(empty_vf.begin(), empty_vf.end(), empty_f, std::string());
    CHECK_EQ(empty_f, std::string());

    std::vector<std::string> empty_vs;
    std::string empty_str;
    mtl::string::join_all(empty_vs.begin(), empty_vs.end(), empty_str, std::string());
    CHECK_EQ(empty_str, std::string());

    std::vector<std::string> empty_vs2;
    std::string empty_str2;
    mtl::string::join_all(empty_vs2.begin(), empty_vs2.end(), empty_str2, std::string("  "));
    CHECK_EQ(empty_str2, std::string());

    std::vector<std::string> blank { "" };
    std::string empty_str3;
    mtl::string::join_all(blank.begin(), blank.end(), empty_str3, std::string("###"));
    CHECK_EQ(empty_str3, std::string());

    std::vector<std::string> blanks { "", "" };
    std::string str_only_delim;
    mtl::string::join_all(blanks.begin(), blanks.end(), str_only_delim, std::string("###"));
    CHECK_EQ(str_only_delim, std::string("###"));

    const char* empty_cs = "";
    std::vector<const char*> blank_cs { empty_cs };
    std::string empty_str4;
    mtl::string::join_all(blank_cs.begin(), blank_cs.end(), empty_str4, std::string("###"));
    CHECK_EQ(empty_str4, std::string());

    std::vector<const char*> blanks_cs { empty_cs, empty_cs};
    std::string str_only_delim2;
    mtl::string::join_all(blanks_cs.begin(), blanks_cs.end(), str_only_delim2, std::string("###"));
    CHECK_EQ(str_only_delim2, std::string("###"));
   
    std::vector<char> vc {'a', 'b', 'c'};
    std::string vc_s;
    mtl::string::join_all(vc.begin(), vc.end(), vc_s, "");
    std::string desired_chars = "abc";
    CHECK_EQ(vc_s, desired_chars);

    std::vector<std::string> names {"Bill", "Mary", "Nick"};
    std::string names_s;
    mtl::string::join_all(names.begin(), names.end(), names_s, '|');
    std::string names_desired = "Bill|Mary|Nick";
    CHECK_EQ(names_s, names_desired);

    std::string names_s2;
    mtl::string::join_all(names.begin(), names.end(), names_s2, std::string("|"));
    CHECK_EQ(names_s2, names_desired);

    std::string names_s3;
    std::string some_delimiter = "|";
    mtl::string::join_all(names.begin(), names.end(), names_s3, some_delimiter);
    CHECK_EQ(names_s3, names_desired);

    std::string numbers_str;
    std::vector<std::string> numbers { "11", "22" };
    std::string big_delimiter = "[12345]";
    mtl::string::join_all(numbers.begin(), numbers.end(), numbers_str, big_delimiter);
    CHECK_EQ(numbers_str, std::string("11[12345]22"));

    // reserving output to avoid allocations
    std::vector<int> vi { 100, 111, 222, 333, 444, 555, 666, 777, 888, 999 };
    std::string reserved_output;
    // we know the ouput will be 30 characters long so we reserve space to avoid allocations
    reserved_output.reserve(10 * 3);
    mtl::string::join_all(vi.begin(), vi.end(), reserved_output, "");


    // check that is works correctly with UTF8 strings
    std::vector<std::string> smiles { smiley, smiley };
    std::string two_smiles;
    mtl::string::join_all(smiles.begin(), smiles.end(), two_smiles, "");
    CHECK_EQ((two_smiles == smiley), false);
    CHECK_EQ((two_smiles == two_smileys), true);
    
    std::string two_smiles_delim;
    mtl::string::join_all(smiles.begin(), smiles.end(), two_smiles_delim, "|");
    CHECK_EQ((two_smiles_delim == smiley), false);
    CHECK_EQ((two_smiles_delim == two_smileys_delimiter), true);
}

TEST_CASE("mtl::string::join_all with non-empty output")
{
    std::vector<std::string> blanks { "", "" };
    std::string str_only_delim = "^^^";
    mtl::string::join_all(blanks.begin(), blanks.end(), str_only_delim, std::string("###"));
    CHECK_EQ(str_only_delim, std::string("^^^###"));

    const char* empty_cs = "";
    std::vector<const char*> blanks_cs { empty_cs, empty_cs};
    std::string str_only_delim2 = "^^^";
    mtl::string::join_all(blanks_cs.begin(), blanks_cs.end(), str_only_delim2, std::string("###"));
    CHECK_EQ(str_only_delim2, std::string("^^^###"));
   
    std::vector<char> vc {'a', 'b', 'c'};
    std::string vc_s = "abc";
    mtl::string::join_all(vc.begin(), vc.end(), vc_s, "");
    std::string desired_chars = "abcabc";
    CHECK_EQ(vc_s, desired_chars);

    std::vector<std::string> names {"Bill", "Mary", "Nick"};
    std::string names_s = "Peter|";
    mtl::string::join_all(names.begin(), names.end(), names_s, '|');
    std::string names_desired = "Peter|Bill|Mary|Nick";
    CHECK_EQ(names_s, names_desired);

    std::string names_s2 = "Peter|";
    mtl::string::join_all(names.begin(), names.end(), names_s2, std::string("|"));
    CHECK_EQ(names_s2, names_desired);

    std::string names_s3 = "Peter|";
    std::string some_delimiter = "|";
    mtl::string::join_all(names.begin(), names.end(), names_s3, some_delimiter);
    CHECK_EQ(names_s3, names_desired);

    std::string numbers_str = "00";
    std::vector<std::string> numbers { "11", "22" };
    std::string big_delimiter = "[12345]";
    mtl::string::join_all(numbers.begin(), numbers.end(), numbers_str, big_delimiter);
    CHECK_EQ(numbers_str, std::string("0011[12345]22"));

    // reserving output to avoid allocations
    std::vector<int> vi { 100, 111, 222, 333, 444, 555, 666, 777, 888, 999 };
    std::string reserved_output = "123";
    // we know the ouput will be 33 characters long so we reserve space to avoid allocations
    reserved_output.reserve(11 * 3);
    mtl::string::join_all(vi.begin(), vi.end(), reserved_output, "");


    // check that is works correctly with UTF8 strings
    std::vector<std::string> smiles { smiley, smiley };
    std::string four_smiles = smiley + smiley;
    mtl::string::join_all(smiles.begin(), smiles.end(), four_smiles, "");
    CHECK_EQ((four_smiles == smiley), false);
    CHECK_EQ((four_smiles == two_smileys), false);
    CHECK_EQ((four_smiles == (two_smileys + two_smileys)), true);

    std::string two_smiles_delim;
    mtl::string::join_all(smiles.begin(), smiles.end(), two_smiles_delim, "|");
    CHECK_EQ((two_smiles_delim == smiley), false);
    CHECK_EQ((two_smiles_delim == two_smileys_delimiter), true);

    std::string four_smiles_delim = two_smiles_delim;
    mtl::string::join_all(smiles.begin(), smiles.end(), four_smiles_delim, "|");
    CHECK_EQ((four_smiles_delim == smiley), false);
    CHECK_EQ((four_smiles_delim == two_smileys_delimiter), false);
    CHECK_EQ((four_smiles_delim == (two_smileys_delimiter + two_smileys_delimiter)), true);
}

// ------------------------------------------------------------------------------------------------
// mtl::string::join
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::join")
{
    std::string c_s1 = mtl::string::join('a');
    CHECK_EQ(c_s1, std::string("a"));
    char c = 'a';
    std::string c_s2 = mtl::string::join(c);
    CHECK_EQ(c_s2, std::string("a"));
    CHECK_EQ(c_s1, c_s2);

    std::string i1 = mtl::string::join(130);
    int num = 130;
    std::string i2 = mtl::string::join(num);
    CHECK_EQ(i1, std::string("130"));
    CHECK_EQ(i2, std::string("130"));
    CHECK_EQ(i1, i2);


    std::string multi_char = mtl::string::join('a', ' ', 'b', ' ', 'c');
    CHECK_EQ(multi_char, std::string("a b c"));
    std::string multi_various = mtl::string::join("aaa", std::string("bbb"), 154, 1.1f, '|', true);
    CHECK_EQ(multi_various, std::string("aaabbb1541.1|true"));

    const char* cs = "Hello";
    std::string mary = " Mary ";
    double d = 2.2;
    bool b = true;
    auto p = std::pair<int, char>(33, 'd');
    std::string multi_var = mtl::string::join(cs, mary, d, b, false, b, ", ", p);
    CHECK_EQ(multi_var, std::string("Hello Mary 2.2truefalsetrue, 33, d"));



    // check that is works correctly with UTF8 strings
    std::string two_smiles = mtl::string::join(smiley, smiley);
    CHECK_EQ((two_smiles == smiley), false);
    CHECK_EQ((two_smiles == two_smileys), true);

    std::string two_smiles_delim = mtl::string::join(smiley, std::string("|"), smiley);
    CHECK_EQ((two_smiles_delim == smiley), false);
    CHECK_EQ((two_smiles_delim == two_smileys_delimiter), true);
}

// ------------------------------------------------------------------------------------------------
// mtl::string::split
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::split with empty std::string and default delimiter")
{
    std::vector<std::string> empty_result = mtl::string::split("");
    CHECK_EQ(empty_result.empty(), true);
    
    
    std::string empty;
    std::vector<std::string> empty_result2 = mtl::string::split(empty);
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with empty std::string and char delimiter")
{
    std::vector<std::string> empty_result = mtl::string::split("", ' ');
    CHECK_EQ(empty_result.empty(), true);
    
    
    std::string empty;
    std::vector<std::string> empty_result2 = mtl::string::split(empty, ' ');
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with empty std::string and const char* delimiter")
{
    std::vector<std::string> empty_result = mtl::string::split("", " ");
    CHECK_EQ(empty_result.empty(), true);
    
    
    std::string empty;
    const char* cs = " ";
    std::vector<std::string> empty_result2 = mtl::string::split(empty, cs);
    CHECK_EQ(empty_result2.empty(), true);
}




TEST_CASE("mtl::string::split with empty std::string and std::string delimiter")
{
    std::vector<std::string> empty_result = mtl::string::split("", " ");
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2 = mtl::string::split(empty, " ");
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with empty std::string and empty std::string delimiter")
{
    std::vector<std::string> empty_result = mtl::string::split("", "");
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2 = mtl::string::split(empty, "");
    CHECK_EQ(empty_result2.empty(), true);
}




TEST_CASE("mtl::string::split with std::string with default delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1 = mtl::string::split("a b c");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::vector<std::string> result2 = mtl::string::split(input);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

}

TEST_CASE("mtl::string::split with std::string with default delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1 = mtl::string::split("abc");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::vector<std::string> result2 = mtl::string::split(input);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  
}


TEST_CASE("mtl::string::split with std::string with char delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1 = mtl::string::split("a b c", ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::vector<std::string> result2 = mtl::string::split(input, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 = mtl::string::split(input2, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 = mtl::string::split(input3, '|');
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 = mtl::string::split(input4, '|');
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 
}

TEST_CASE("mtl::string::split with std::string with char delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1 = mtl::string::split("abc", ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::vector<std::string> result2 = mtl::string::split(input, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 = mtl::string::split(input2, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 
}


TEST_CASE("mtl::string::split with std::string with const char* delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1 = mtl::string::split("a b c", " ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    const char* delimiter = " ";
    std::vector<std::string> result2 = mtl::string::split(input, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 = mtl::string::split(input2, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 = mtl::string::split(input3, "|");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 = mtl::string::split(input4, "|");
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    auto split_greets = mtl::string::split(combined_greetings, "<|>");
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 4), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    const char* greet_delim = "<|>";
    std::vector<std::string> split_greets2 = mtl::string::split(combined_greetings2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 5), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3 = mtl::string::split(combined_greetings3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 6), true);
    CHECK_EQ((split_greets3 == greetings3), true);  

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { smiley, smiley };
    const char* delim = "|";
    std::vector<std::string> two_smiles = mtl::string::split(two_smileys_delimiter, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 2), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { "abcdefghijklmnopqrst", "ABCDEFGHIJKLMNOPQRST"};
    std::vector<std::string> uni_split = mtl::string::split(one_nonascii, smiley);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 2), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}

TEST_CASE("mtl::string::split with std::string with const char* delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1 = mtl::string::split("abc", " ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    const char* delimiter = " ";
    std::vector<std::string> result2 = mtl::string::split(input, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 = mtl::string::split(input2, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4 = mtl::string::split(input2, "");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 1), true);
    CHECK_EQ((result4 == desired2), true);

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { two_smileys_delimiter };
    const char* delim = "#";
    std::vector<std::string> two_smiles = mtl::string::split(two_smileys_delimiter, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 1), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { one_nonascii };
    std::vector<std::string> uni_split = mtl::string::split(one_nonascii, delim);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 1), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}



TEST_CASE("mtl::string::split with std::string with std::string delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1 = mtl::string::split("a b c", std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::string delimiter = " ";
    std::vector<std::string> result2 = mtl::string::split(input, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 = mtl::string::split(input2, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 = mtl::string::split(input3, std::string("|"));
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 = mtl::string::split(input4, std::string("|"));
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    auto split_greets = mtl::string::split(combined_greetings, std::string("<|>"));
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 4), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    std::string greet_delim = "<|>";
    std::vector<std::string> split_greets2 = mtl::string::split(combined_greetings2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 5), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3 = mtl::string::split(combined_greetings3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 6), true);
    CHECK_EQ((split_greets3 == greetings3), true);  

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { smiley, smiley };
    std::string delim = "|";
    std::vector<std::string> two_smiles = mtl::string::split(two_smileys_delimiter, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 2), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { "abcdefghijklmnopqrst", "ABCDEFGHIJKLMNOPQRST"};
    std::vector<std::string> uni_split = mtl::string::split(one_nonascii, smiley);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 2), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}

TEST_CASE("mtl::string::split with std::string with std::string delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1 = mtl::string::split("abc", std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::string delimiter = " ";
    std::vector<std::string> result2 = mtl::string::split(input, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 = mtl::string::split(input2, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4 = mtl::string::split(input2, std::string());
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 1), true);
    CHECK_EQ((result4 == desired2), true);

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { two_smileys_delimiter };
    std::string delim = "#";
    std::vector<std::string> two_smiles = mtl::string::split(two_smileys_delimiter, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 1), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { one_nonascii };
    std::vector<std::string> uni_split = mtl::string::split(one_nonascii, delim);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 1), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}








TEST_CASE("mtl::string::split with output on empty std::string and char delimiter")
{
    std::vector<std::string> empty_result; 
    mtl::string::split(std::string(), empty_result, ' ');
    CHECK_EQ(empty_result.empty(), true);
  
    std::string empty;
    std::vector<std::string> empty_result2;
    mtl::string::split(empty, empty_result2, ' ');
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with output on empty std::string and const char* delimiter")
{
    std::vector<std::string> empty_result;
    mtl::string::split(std::string(), empty_result, " ");
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2;
    mtl::string::split(empty, empty_result2, " ");
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with output on empty std::string and empty const char* delimiter")
{
    std::vector<std::string> empty_result;
    mtl::string::split(std::string(), empty_result, "");
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2;
    mtl::string::split(empty, empty_result2, "");
    CHECK_EQ(empty_result2.empty(), true);
}


TEST_CASE("mtl::string::split with output on empty std::string and std::string delimiter")
{
    std::vector<std::string> empty_result;
    mtl::string::split(std::string(), empty_result, std::string(" "));
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2;
    mtl::string::split(empty, empty_result2, std::string(" "));
    CHECK_EQ(empty_result2.empty(), true);
}

TEST_CASE("mtl::string::split with output on empty std::string and empty std::string delimiter")
{
    std::vector<std::string> empty_result;
    mtl::string::split(std::string(), empty_result, std::string());
    CHECK_EQ(empty_result.empty(), true);

    std::string empty;
    std::vector<std::string> empty_result2;
    mtl::string::split(empty, empty_result2, std::string());
    CHECK_EQ(empty_result2.empty(), true);
}


TEST_CASE("mtl::string::split with output and char delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("a b c"), result1, ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4;
    mtl::string::split(input3, result4, '|');
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5;
    mtl::string::split(input4, result5, '|');
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 
}

TEST_CASE("mtl::string::split with output and char delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc" };
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("abc"), result1, ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 
}


TEST_CASE("mtl::string::split with output and const char* delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("a b c"), result1," ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    const char* delimiter = " ";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4;
    mtl::string::split(input3, result4, "|");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5;
    mtl::string::split(input4, result5, "|");
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    std::vector<std::string> split_greets;
    mtl::string::split(combined_greetings, split_greets, "<|>");
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 4), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    const char* greet_delim = "<|>";
    std::vector<std::string> split_greets2;
    mtl::string::split(combined_greetings2, split_greets2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 5), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3;
    mtl::string::split(combined_greetings3, split_greets3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 6), true);
    CHECK_EQ((split_greets3 == greetings3), true);  

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { smiley, smiley };
    const char* delim = "|";
    std::vector<std::string> two_smiles;
    mtl::string::split(two_smileys_delimiter, two_smiles, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 2), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { "abcdefghijklmnopqrst", "ABCDEFGHIJKLMNOPQRST"};
    std::vector<std::string> uni_split;
    mtl::string::split(one_nonascii, uni_split, smiley);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 2), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}

TEST_CASE("mtl::string::split with output and const char* delim and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("abc"), result1, " ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    const char* delimiter = " ";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4;
    mtl::string::split(input2, result4, "");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 1), true);
    CHECK_EQ((result4 == desired2), true);

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { two_smileys_delimiter };
    const char* delim = "#";
    std::vector<std::string> two_smiles;
    mtl::string::split(two_smileys_delimiter, two_smiles, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 1), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { one_nonascii };
    std::vector<std::string> uni_split;
    mtl::string::split(one_nonascii, uni_split, delim);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 1), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}



TEST_CASE("mtl::string::split with output and std::string delimiter")
{
    std::vector<std::string> desired { "a", "b", "c"};
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("a b c"), result1, std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 3), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::string delimiter = " ";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 3), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 3), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4;
    mtl::string::split(input3, result4, std::string("|"));
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 3), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5;
    mtl::string::split(input4, result5, std::string("|"));
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 4), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    std::vector<std::string> split_greets;
    mtl::string::split(combined_greetings, split_greets, std::string("<|>"));
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 4), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    std::string greet_delim = "<|>";
    std::vector<std::string> split_greets2;
    mtl::string::split(combined_greetings2, split_greets2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 5), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3;
    mtl::string::split(combined_greetings3, split_greets3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 6), true);
    CHECK_EQ((split_greets3 == greetings3), true);  

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { smiley, smiley };
    std::string delim = "|";
    std::vector<std::string> two_smiles;
    mtl::string::split(two_smileys_delimiter, two_smiles, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 2), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { "abcdefghijklmnopqrst", "ABCDEFGHIJKLMNOPQRST"};
    std::vector<std::string> uni_split;
    mtl::string::split(one_nonascii, uni_split, smiley);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 2), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}

TEST_CASE("mtl::string::split with output and string delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc"};
    
    std::vector<std::string> result1;
    mtl::string::split(std::string("abc"), result1, std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 1), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::string delimiter = " ";
    std::vector<std::string> result2;
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 1), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3;
    mtl::string::split(input2, result3, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 1), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4;
    mtl::string::split(input2, result4, std::string());
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 1), true);
    CHECK_EQ((result4 == desired2), true);

    // check that is works correctly with UTF8 strings
    std::vector<std::string> smileys = { two_smileys_delimiter };
    std::string delim = "#";
    std::vector<std::string> two_smiles;
    mtl::string::split(two_smileys_delimiter, two_smiles, delim);
    CHECK_EQ(two_smiles.empty(), false);
    CHECK_EQ((two_smiles.size() == 1), true);
    CHECK_EQ((two_smiles == smileys), true);

    std::vector<std::string> uni_parts = { one_nonascii };
    std::vector<std::string> uni_split;
    mtl::string::split(one_nonascii, uni_split, delim);
    CHECK_EQ(uni_split.empty(), false);
    CHECK_EQ((uni_split.size() == 1), true);
    CHECK_EQ((uni_split == uni_parts), true);  
}



TEST_CASE("mtl::string::split with non-empty output and char delimiter")
{
    std::vector<std::string> desired { "a", "b", "c", "a", "b", "c"};
    
    std::vector<std::string> result1 {"a", "b", "c"};
    mtl::string::split(std::string("a b c"), result1, ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 6), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::vector<std::string> result2 {"a", "b", "c"};
    mtl::string::split(input, result2, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 6), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 {"a", "b", "c"};
    mtl::string::split(input2, result3, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 6), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 {"a", "b", "c"};
    mtl::string::split(input3, result4, '|');
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 6), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", "", "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 {"a", "b", "c", ""};
    mtl::string::split(input4, result5, '|');
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 8), true);
    CHECK_EQ((result5 == desired2), true); 
}

TEST_CASE("mtl::string::split with non-empty output and char delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc", "abc" };
    
    std::vector<std::string> result1 { "abc" };
    mtl::string::split(std::string("abc"), result1, ' ');

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 2), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::vector<std::string> result2 { "abc" };
    mtl::string::split(input, result2, ' ');
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 2), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c", "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 { "a b c" };
    mtl::string::split(input2, result3, '|');
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 2), true);
    CHECK_EQ((result3 == desired2), true); 
}


TEST_CASE("mtl::string::split with non-empty output and const char* delimiter")
{
    std::vector<std::string> desired { "a", "b", "c", "a", "b", "c"};
    
    std::vector<std::string> result1 { "a", "b", "c"};
    mtl::string::split(std::string("a b c"), result1, " ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 6), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    const char* delimiter = " ";
    std::vector<std::string> result2 { "a", "b", "c"};
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 6), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 { "a", "b", "c"};
    mtl::string::split(input2, result3, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 6), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 { "a", "b", "c"};
    mtl::string::split(input3, result4, "|");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 6), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", "", "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 { "a", "b", "c", "" };
    mtl::string::split(input4, result5, "|");
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 8), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", "Hello", "Hello", 
                                           "Hello", "Hello" };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    std::vector<std::string> split_greets {"Hello", "Hello", "Hello", "Hello" };
    mtl::string::split(combined_greetings, split_greets, "<|>");
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 8), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "",
                                            "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    const char* greet_delim = "<|>";
    std::vector<std::string> split_greets2 { "Hello", "Hello", "Hello", "Hello", "" };
    mtl::string::split(combined_greetings2, split_greets2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 10), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "", 
                                            "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3  { "", "Hello", "Hello", "Hello", "Hello", "" };
    mtl::string::split(combined_greetings3, split_greets3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 12), true);
    CHECK_EQ((split_greets3 == greetings3), true);  
}

TEST_CASE("mtl::string::split with non-empty output and const char* delim and nothing to split")
{
    std::vector<std::string> desired { "abc", "abc" };
    
    std::vector<std::string> result1 { "abc" };
    mtl::string::split(std::string("abc"), result1, " ");

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 2), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    const char* delimiter = " ";
    std::vector<std::string> result2 { "abc" };
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 2), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c", "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 { "a b c" };
    mtl::string::split(input2, result3, "|");
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 2), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4 { "a b c" };
    mtl::string::split(input2, result4, "");
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 2), true);
    CHECK_EQ((result4 == desired2), true);
}



TEST_CASE("mtl::string::split with non-empty output and std::string delimiter")
{
    std::vector<std::string> desired { "a", "b", "c", "a", "b", "c"};
    
    std::vector<std::string> result1 { "a", "b", "c"};
    mtl::string::split(std::string("a b c"), result1, std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 6), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "a b c";
    std::string delimiter = " ";
    std::vector<std::string> result2 { "a", "b", "c"};
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 6), true);
    CHECK_EQ((result2 == desired), true);  

    std::string input2 = "a|b|c";
    std::vector<std::string> result3 { "a", "b", "c"};
    mtl::string::split(input2, result3, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 6), true);
    CHECK_EQ((result3 == desired), true);  

    std::string input3 = "a|b|c ";
    std::vector<std::string> result4 { "a", "b", "c"};
    mtl::string::split(input3, result4, std::string("|"));
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 6), true);
    CHECK_EQ((result4 == desired), false);  

    std::vector<std::string> desired2 { "a", "b", "c", "", "a", "b", "c", ""};
    std::string input4 = "a|b|c|";
    std::vector<std::string> result5 { "a", "b", "c", "" };
    mtl::string::split(input4, result5, std::string("|"));
    CHECK_EQ(result5.empty(), false);
    CHECK_EQ((result5.size() == 8), true);
    CHECK_EQ((result5 == desired2), true); 

    std::vector<std::string> greetings = { "Hello", "Hello", "Hello", "Hello", "Hello", "Hello", 
                                           "Hello", "Hello" };
    std::string combined_greetings = "Hello<|>Hello<|>Hello<|>Hello";
    std::vector<std::string> split_greets {"Hello", "Hello", "Hello", "Hello" };
    mtl::string::split(combined_greetings, split_greets, std::string("<|>"));
    CHECK_EQ(split_greets.empty(), false);
    CHECK_EQ((split_greets.size() == 8), true);
    CHECK_EQ((split_greets == greetings), true);  

    std::vector<std::string> greetings2 = { "Hello", "Hello", "Hello", "Hello", "",
                                            "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings2 = "Hello<|>Hello<|>Hello<|>Hello<|>";
    std::string greet_delim = "<|>";
    std::vector<std::string> split_greets2 { "Hello", "Hello", "Hello", "Hello", "" };
    mtl::string::split(combined_greetings2, split_greets2, greet_delim);
    CHECK_EQ(split_greets2.empty(), false);
    CHECK_EQ((split_greets2.size() == 10), true);
    CHECK_EQ((split_greets2 == greetings2), true);  

    std::vector<std::string> greetings3 = { "", "Hello", "Hello", "Hello", "Hello", "", 
                                            "", "Hello", "Hello", "Hello", "Hello", "" };
    std::string combined_greetings3 = "<|>Hello<|>Hello<|>Hello<|>Hello<|>";
    std::vector<std::string> split_greets3  { "", "Hello", "Hello", "Hello", "Hello", "" };
    mtl::string::split(combined_greetings3, split_greets3, greet_delim);
    CHECK_EQ(split_greets3.empty(), false);
    CHECK_EQ((split_greets3.size() == 12), true);
    CHECK_EQ((split_greets3 == greetings3), true);  
}

TEST_CASE("mtl::string::split with non-empty output and string delimiter and nothing to split")
{
    std::vector<std::string> desired { "abc", "abc" };
    
    std::vector<std::string> result1 { "abc" };
    mtl::string::split(std::string("abc"), result1, std::string(" "));

    CHECK_EQ(result1.empty(), false);
    CHECK_EQ((result1.size() == 2), true);
    CHECK_EQ((result1 == desired), true);


    std::string input = "abc";
    std::string delimiter = " ";
    std::vector<std::string> result2 { "abc" };
    mtl::string::split(input, result2, delimiter);
    CHECK_EQ(result2.empty(), false);
    CHECK_EQ((result2.size() == 2), true);
    CHECK_EQ((result2 == desired), true);  

    std::vector<std::string> desired2 { "a b c", "a b c"};
    std::string input2 = "a b c";
    std::vector<std::string> result3 { "a b c" };
    mtl::string::split(input2, result3, std::string("|"));
    CHECK_EQ(result3.empty(), false);
    CHECK_EQ((result3.size() == 2), true);
    CHECK_EQ((result3 == desired2), true); 

    std::vector<std::string> result4 { "a b c" };
    mtl::string::split(input2, result4, std::string());
    CHECK_EQ(result4.empty(), false);
    CHECK_EQ((result4.size() == 2), true);
    CHECK_EQ((result4 == desired2), true);
}





// ------------------------------------------------------------------------------------------------
// mtl::string::replace
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::replace for short std::string")
{
    std::string empty;
    mtl::string::replace(empty, "Nick", "Peter");
    CHECK_EQ(empty, std::string());

    std::string no_match = "There will be nothing to replace for this one.";
    mtl::string::replace(empty, "Nick", "Peter");
    CHECK_EQ(no_match, std::string("There will be nothing to replace for this one."));

    std::string s1 = "Hello Nick. Let's Go Nick.";
    mtl::string::replace(s1, "Nick", "Peter");
    CHECK_EQ(s1, std::string("Hello Peter. Let's Go Peter."));
    std::string s2 = "Hello Nick. Let's Go Nick.";
    mtl::string::replace(s2, "Nick", "Helen");
    CHECK_EQ(s2, std::string("Hello Helen. Let's Go Helen."));
    CHECK_NE(s1, s2);

    std::string txt1 = "Something LONGLONGLONG and LONGLONGLONG and LONGLONGLONG";
    mtl::string::replace(txt1, "LONGLONGLONG", "short");
    CHECK_EQ(txt1, std::string("Something short and short and short"));

    std::string txt2 = "LONGLONGLONG";
    mtl::string::replace(txt2, "LONGLONGLONG", "short");
    CHECK_EQ(txt2, std::string("short"));

    std::string txt3 = "LONGLONGLONGLONGLONGLONG";
    mtl::string::replace(txt3, "LONGLONGLONG", "short");
    CHECK_EQ(txt3, std::string("shortshort"));

    std::string txt4 = "LONGLONGLONGLONGLONGLONG.";
    mtl::string::replace(txt4, "LONGLONGLONG", "short");
    CHECK_EQ(txt4, std::string("shortshort."));

    std::string txt5 = ".LONGLONGLONGLONGLONGLONG.";
    mtl::string::replace(txt5, "LONGLONGLONG", "short");
    CHECK_EQ(txt5, std::string(".shortshort."));

    std::string txt6 = ".LONGLONGLONG.LONGLONGLONG.";
    mtl::string::replace(txt6, "LONGLONGLONG", "short");
    CHECK_EQ(txt6, std::string(".short.short."));

    std::string fmt_str = "Here goes {}. There is {}. It is all or {}.";
    mtl::string::replace(fmt_str, "{}", "nothing");
    CHECK_EQ(fmt_str, std::string("Here goes nothing. There is nothing. It is all or nothing."));

    std::string zero_one = "01222022001010101";
    mtl::string::replace(zero_one, '2', '1');
    CHECK_EQ(zero_one, std::string("01111011001010101"));

    
    // check all possible overloads of mtl::string::replace
    std::string rep1 = "[11]-[22]-[33]";

    // std::string, std::string
    std::string eleven = "11";
    std::string nine = "9";
    mtl::string::replace(rep1, eleven, nine);
    CHECK_EQ(rep1, std::string("[9]-[22]-[33]"));
    // std::string, const char*
    mtl::string::replace(rep1, nine, "11");
    CHECK_EQ(rep1, std::string("[11]-[22]-[33]"));
    // std::string, char
    std::string thirty_three = "33";
    mtl::string::replace(rep1, thirty_three, '4');
    CHECK_EQ(rep1, std::string("[11]-[22]-[4]"));
    

    // char, std::string
    mtl::string::replace(rep1, '4', thirty_three);
    CHECK_EQ(rep1, std::string("[11]-[22]-[33]"));  
    // char, const char*
    mtl::string::replace(rep1, '2', "66");
    CHECK_EQ(rep1, std::string("[11]-[6666]-[33]"));  
    // char, char
    mtl::string::replace(rep1, '6', '5');
    CHECK_EQ(rep1, std::string("[11]-[5555]-[33]"));  


    // const char*, std::string
    mtl::string::replace(rep1, "55", nine);
    CHECK_EQ(rep1, std::string("[11]-[99]-[33]"));  
    // const char*, char
    mtl::string::replace(rep1, "99", '0');
    CHECK_EQ(rep1, std::string("[11]-[0]-[33]"));  
    // const char*, const char*
    mtl::string::replace(rep1, "11", "12345");
    CHECK_EQ(rep1, std::string("[12345]-[0]-[33]"));  


    // check that is works correctly with UTF8 strings
    
    // copy const string so we can change it
    std::string cp_one_nonascii = one_nonascii;
    mtl::string::replace(cp_one_nonascii, smiley, "");
    CHECK_EQ((cp_one_nonascii == only_ascii), true);
}

TEST_CASE("mtl::string::replace for short std::string, more tests")
{
    // long string
    const std::string long_string(20, 'z');
    REQUIRE_EQ(long_string.size(), 20);

    std::string match = "#";
    std::string replacement = "Mike";


    // create one with bigger match size than input size
    std::string smaller_input = long_string + "|";
    std::string bigger_match = long_string + "aaaaaaaa";
    std::string smaller_result = smaller_input;
    mtl::string::replace(smaller_input, bigger_match, replacement);
    CHECK_EQ(smaller_input, smaller_result);


    // create a test where there is nothing to replace
    std::string no_match = long_string;
    mtl::string::replace(no_match, match, replacement);
    CHECK_EQ(no_match, long_string);

    // create some that have stuff to replace
    // create some strings to match
    std::string s1 = match + long_string;
    std::string s2 = match + long_string + match;
    std::string s3 = match + match + long_string + match;
    std::string s4 = match + match + long_string + match + match;
    std::string s8 = s4 + s4;

    // create some strings we want to be compared with
    std::string s1_result = replacement + long_string;
    std::string s2_result = replacement + long_string + replacement;
    std::string s3_result = replacement + replacement + long_string + replacement;
    std::string s4_result = replacement + replacement + long_string + replacement + replacement;
    std::string s8_result = s4_result + s4_result;

    mtl::string::replace(s1, match, replacement);
    mtl::string::replace(s2, match, replacement);
    mtl::string::replace(s3, match, replacement);
    mtl::string::replace(s4, match, replacement);
    mtl::string::replace(s8, match, replacement);

    CHECK_EQ(s1 , s1_result);
    CHECK_EQ(s2 , s2_result);
    CHECK_EQ(s3 , s3_result);
    CHECK_EQ(s4 , s4_result);
    CHECK_EQ(s8 , s8_result);



    // create some that the match and the replacement are identical and are just one character
    const std::string single_id_match = "#";
    const std::string single_id_rep (single_id_match.begin(), single_id_match.end());
    REQUIRE_EQ(single_id_match.size(), 1);
    REQUIRE_EQ(single_id_rep.size(), 1);    
    REQUIRE_EQ(single_id_match, single_id_rep);

    // create some strings to match
    std::string single_id_s1 = single_id_match + long_string;
    std::string single_id_s2 = single_id_match + long_string + single_id_match;
    std::string single_id_s3 = single_id_match + single_id_match + long_string + single_id_match;
    std::string single_id_s4 = single_id_match + single_id_match + long_string + single_id_match;
    single_id_s4 += single_id_match;
    std::string single_id_s8 = single_id_s4 + single_id_s4;

    // create some strings we want to be compared with
    std::string single_id_s1_result = single_id_rep + long_string;
    std::string single_id_s2_result = single_id_rep + long_string + single_id_rep;
    std::string single_id_s3_result = single_id_rep + single_id_rep + long_string + single_id_rep;
    std::string single_id_s4_result = single_id_rep + single_id_rep + long_string + single_id_rep;
    single_id_s4_result +=  single_id_rep;
    std::string single_id_s8_result = single_id_s4_result + single_id_s4_result;

    mtl::string::replace(single_id_s1, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s2, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s3, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s4, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s8, single_id_match, single_id_rep);

    CHECK_EQ(single_id_s1 , single_id_s1_result);
    CHECK_EQ(single_id_s2 , single_id_s2_result);
    CHECK_EQ(single_id_s3 , single_id_s3_result);
    CHECK_EQ(single_id_s4 , single_id_s4_result);
    CHECK_EQ(single_id_s8 , single_id_s8_result);


    // create some that the match and the replacement are identical
    const std::string ident_match = "##";
    const std::string ident_rep (ident_match.begin(), ident_match.end());
    REQUIRE_EQ(ident_match, ident_rep);

    // create some strings to match
    std::string ident_s1 = ident_match + long_string;
    std::string ident_s2 = ident_match + long_string + ident_match;
    std::string ident_s3 = ident_match + ident_match + long_string + ident_match;
    std::string ident_s4 = ident_match + ident_match + long_string + ident_match + ident_match;
    std::string ident_s8 = ident_s4 + ident_s4;

    // create some strings we want to be compared with
    std::string ident_s1_result = ident_rep + long_string;
    std::string ident_s2_result = ident_rep + long_string + ident_rep;
    std::string ident_s3_result = ident_rep + ident_rep + long_string + ident_rep;
    std::string ident_s4_result = ident_rep + ident_rep + long_string + ident_rep + ident_rep;
    std::string ident_s8_result = ident_s4_result + ident_s4_result;

    mtl::string::replace(ident_s1, ident_match, ident_rep);
    mtl::string::replace(ident_s2, ident_match, ident_rep);
    mtl::string::replace(ident_s3, ident_match, ident_rep);
    mtl::string::replace(ident_s4, ident_match, ident_rep);
    mtl::string::replace(ident_s8, ident_match, ident_rep);

    CHECK_EQ(ident_s1 , ident_s1_result);
    CHECK_EQ(ident_s2 , ident_s2_result);
    CHECK_EQ(ident_s3 , ident_s3_result);
    CHECK_EQ(ident_s4 , ident_s4_result);
    CHECK_EQ(ident_s8 , ident_s8_result);



    // create some that the match and the replacement are the exact same size and it is just
    // one character
    std::string single_match = "^";
    std::string single_rep = "-";
    REQUIRE_EQ(single_match.size(), 1);
    REQUIRE_EQ(single_rep.size(), 1);
    REQUIRE_EQ(single_match.size(), single_rep.size());

    // create some strings to match
    std::string single_s1 = single_match + long_string;
    std::string single_s2 = single_match + long_string + single_match;
    std::string single_s3 = single_match + single_match + long_string + single_match;
    std::string single_s4;
    single_s4 = single_match + single_match + long_string + single_match + single_match;
    std::string single_s8 = single_s4 + single_s4;

    // create some strings we want to be compared with
    std::string single_s1_result = single_rep + long_string;
    std::string single_s2_result = single_rep + long_string + single_rep;
    std::string single_s3_result = single_rep + single_rep + long_string + single_rep;
    std::string single_s4_result = single_rep + single_rep + long_string + single_rep + single_rep;
    std::string single_s8_result = single_s4_result + single_s4_result;

    mtl::string::replace(single_s1, single_match, single_rep);
    mtl::string::replace(single_s2, single_match, single_rep);
    mtl::string::replace(single_s3, single_match, single_rep);
    mtl::string::replace(single_s4, single_match, single_rep);
    mtl::string::replace(single_s8, single_match, single_rep);

    CHECK_EQ(single_s1 , single_s1_result);
    CHECK_EQ(single_s2 , single_s2_result);
    CHECK_EQ(single_s3 , single_s3_result);
    CHECK_EQ(single_s4 , single_s4_result);
    CHECK_EQ(single_s8 , single_s8_result);



    // create some that the match and the replacement are the exact same size
    std::string same_match = "[[[Nick]]]";
    std::string same_rep = "<<|Bill|>>";
    REQUIRE_EQ(same_match.size(), same_rep.size());

    // create some strings to match
    std::string same_s1 = same_match + long_string;
    std::string same_s2 = same_match + long_string + same_match;
    std::string same_s3 = same_match + same_match + long_string + same_match;
    std::string same_s4 = same_match + same_match + long_string + same_match + same_match;
    std::string same_s8 = same_s4 + same_s4;

    // create some strings we want to be compared with
    std::string same_s1_result = same_rep + long_string;
    std::string same_s2_result = same_rep + long_string + same_rep;
    std::string same_s3_result = same_rep + same_rep + long_string + same_rep;
    std::string same_s4_result = same_rep + same_rep + long_string + same_rep + same_rep;
    std::string same_s8_result = same_s4_result + same_s4_result;

    mtl::string::replace(same_s1, same_match, same_rep);
    mtl::string::replace(same_s2, same_match, same_rep);
    mtl::string::replace(same_s3, same_match, same_rep);
    mtl::string::replace(same_s4, same_match, same_rep);
    mtl::string::replace(same_s8, same_match, same_rep);

    CHECK_EQ(same_s1 , same_s1_result);
    CHECK_EQ(same_s2 , same_s2_result);
    CHECK_EQ(same_s3 , same_s3_result);
    CHECK_EQ(same_s4 , same_s4_result);
    CHECK_EQ(same_s8 , same_s8_result);




    // create some that the match is larger than the replacement
    std::string big_match = "#AAAAAAAAAAA#";
    std::string small_rep = "@";

    // create some strings to match
    std::string other_s1 = big_match + long_string;
    std::string other_s2 = big_match + long_string + big_match;
    std::string other_s3 = big_match + big_match + long_string + big_match;
    std::string other_s4 = big_match + big_match + long_string + big_match + big_match;
    std::string other_s8 = other_s4 + other_s4;

    // create some strings we want to be compared with
    std::string other_s1_result = small_rep + long_string;
    std::string other_s2_result = small_rep + long_string + small_rep;
    std::string other_s3_result = small_rep + small_rep + long_string + small_rep;
    std::string other_s4_result = small_rep + small_rep + long_string + small_rep + small_rep;
    std::string other_s8_result = other_s4_result + other_s4_result;

    mtl::string::replace(other_s1, big_match, small_rep);
    mtl::string::replace(other_s2, big_match, small_rep);
    mtl::string::replace(other_s3, big_match, small_rep);
    mtl::string::replace(other_s4, big_match, small_rep);
    mtl::string::replace(other_s8, big_match, small_rep);

    CHECK_EQ(other_s1 , other_s1_result);
    CHECK_EQ(other_s2 , other_s2_result);
    CHECK_EQ(other_s3 , other_s3_result);
    CHECK_EQ(other_s4 , other_s4_result);
    CHECK_EQ(other_s8 , other_s8_result);



    // check that is works correctly with UTF8 strings

    // create some that the match and the replacement contains utf8 characters
	std::string utf8_match = smiley;
	std::string utf8_rep = "[" + two_smileys_delimiter + "]";

    // create some strings to match
    std::string utf8_s1 = utf8_match + long_string;
    std::string utf8_s2 = utf8_match + long_string + utf8_match;
    std::string utf8_s3 = utf8_match + utf8_match + long_string + utf8_match;
    std::string utf8_s4 = utf8_match + utf8_match + long_string + utf8_match + utf8_match;
    std::string utf8_s8 = utf8_s4 + utf8_s4;

    // create some strings we want to be compared with
    std::string utf8_s1_result = utf8_rep + long_string;
    std::string utf8_s2_result = utf8_rep + long_string + utf8_rep;
    std::string utf8_s3_result = utf8_rep + utf8_rep + long_string + utf8_rep;
    std::string utf8_s4_result = utf8_rep + utf8_rep + long_string + utf8_rep + utf8_rep;
    std::string utf8_s8_result = utf8_s4_result + utf8_s4_result;

    mtl::string::replace(utf8_s1, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s2, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s3, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s4, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s8, utf8_match, utf8_rep);

    CHECK_EQ(utf8_s1 , utf8_s1_result);
    CHECK_EQ(utf8_s2 , utf8_s2_result);
    CHECK_EQ(utf8_s3 , utf8_s3_result);
    CHECK_EQ(utf8_s4 , utf8_s4_result);
    CHECK_EQ(utf8_s8 , utf8_s8_result);
}

TEST_CASE("mtl::string::replace for long std::string")
{
    // long string
    const std::string long_string(400, 'z');
    REQUIRE_EQ(long_string.size(), 400);

    std::string match = "#";
    std::string replacement = "Mike";

    // create one with bigger match size than input size
    std::string smaller_input = long_string + "|";
    std::string bigger_match = long_string + "aaaaaaaa";
    std::string smaller_result = smaller_input;
    mtl::string::replace(smaller_input, bigger_match, replacement);
    CHECK_EQ(smaller_input, smaller_result);


    // create a test where there is nothing to replace
    std::string no_match = long_string;
    mtl::string::replace(no_match, match, replacement);
    CHECK_EQ(no_match, long_string);


    // create some that have stuff to replace
    
    // create some strings to match
    std::string s1 = match + long_string;
    std::string s2 = match + long_string + match;
    std::string s3 = match + match + long_string + match;
    std::string s4 = match + match + long_string + match + match;
    std::string s8 = s4 + s4;
    std::string s32 = s8 + s8 + s8 + s8;

    // create some strings we want to be compared with
    std::string s1_result = replacement + long_string;
    std::string s2_result = replacement + long_string + replacement;
    std::string s3_result = replacement + replacement + long_string + replacement;
    std::string s4_result = replacement + replacement + long_string + replacement + replacement;
    std::string s8_result = s4_result + s4_result;
    std::string s32_result = s8_result + s8_result + s8_result + s8_result;

    mtl::string::replace(s1, match, replacement);
    mtl::string::replace(s2, match, replacement);
    mtl::string::replace(s3, match, replacement);
    mtl::string::replace(s4, match, replacement);
    mtl::string::replace(s8, match, replacement);
    mtl::string::replace(s32, match, replacement);

    CHECK_EQ(s1 , s1_result);
    CHECK_EQ(s2 , s2_result);
    CHECK_EQ(s3 , s3_result);
    CHECK_EQ(s4 , s4_result);
    CHECK_EQ(s8 , s8_result);
    CHECK_EQ(s32 , s32_result);



    // create some that the match and the replacement are identical and are just one character
    std::string single_id_match = "#";
    std::string single_id_rep (single_id_match.begin(), single_id_match.end());
    REQUIRE_EQ(single_id_match.size(), 1);
    REQUIRE_EQ(single_id_rep.size(), 1);    
    REQUIRE_EQ(single_id_match, single_id_rep);

    // create some strings to match
    std::string single_id_s1 = single_id_match + long_string;
    std::string single_id_s2 = single_id_match + long_string + single_id_match;
    std::string single_id_s3 = single_id_match + single_id_match + long_string + single_id_match;
    std::string single_id_s4 = single_id_match + single_id_match + long_string + single_id_match;
    single_id_s4 += single_id_match;
    std::string single_id_s8 = single_id_s4 + single_id_s4;
    std::string single_id_s32 = single_id_s8 + single_id_s8 + single_id_s8 + single_id_s8;

    // create some strings we want to be compared with
    std::string single_id_s1_result = single_id_rep + long_string;
    std::string single_id_s2_result = single_id_rep + long_string + single_id_rep;
    std::string single_id_s3_result = single_id_rep + single_id_rep + long_string + single_id_rep;
    std::string single_id_s4_result = single_id_rep + single_id_rep + long_string + single_id_rep;
    single_id_s4_result +=  single_id_rep;
    std::string single_id_s8_result = single_id_s4_result + single_id_s4_result;
    std::string single_id_s32_result = single_id_s8_result + single_id_s8_result;
    single_id_s32_result = single_id_s32_result + single_id_s32_result;

    mtl::string::replace(single_id_s1, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s2, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s3, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s4, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s8, single_id_match, single_id_rep);
    mtl::string::replace(single_id_s32, single_id_match, single_id_rep);

    CHECK_EQ(single_id_s1 , single_id_s1_result);
    CHECK_EQ(single_id_s2 , single_id_s2_result);
    CHECK_EQ(single_id_s3 , single_id_s3_result);
    CHECK_EQ(single_id_s4 , single_id_s4_result);
    CHECK_EQ(single_id_s8 , single_id_s8_result);
    CHECK_EQ(single_id_s32 , single_id_s32_result);


    // create some that the match and the replacement are identical
    std::string ident_match = "##";
    std::string ident_rep (ident_match.begin(), ident_match.end());
    REQUIRE_EQ(ident_match, ident_rep);

    // create some strings to match
    std::string ident_s1 = ident_match + long_string;
    std::string ident_s2 = ident_match + long_string + ident_match;
    std::string ident_s3 = ident_match + ident_match + long_string + ident_match;
    std::string ident_s4 = ident_match + ident_match + long_string + ident_match + ident_match;
    std::string ident_s8 = ident_s4 + ident_s4;
    std::string ident_s32 = ident_s8 + ident_s8 + ident_s8 + ident_s8;

    // create some strings we want to be compared with
    std::string ident_s1_result = ident_rep + long_string;
    std::string ident_s2_result = ident_rep + long_string + ident_rep;
    std::string ident_s3_result = ident_rep + ident_rep + long_string + ident_rep;
    std::string ident_s4_result = ident_rep + ident_rep + long_string + ident_rep + ident_rep;
    std::string ident_s8_result = ident_s4_result + ident_s4_result;
    std::string ident_s32_result = ident_s8_result + ident_s8_result;
    ident_s32_result = ident_s32_result + ident_s32_result;

    mtl::string::replace(ident_s1, ident_match, ident_rep);
    mtl::string::replace(ident_s2, ident_match, ident_rep);
    mtl::string::replace(ident_s3, ident_match, ident_rep);
    mtl::string::replace(ident_s4, ident_match, ident_rep);
    mtl::string::replace(ident_s8, ident_match, ident_rep);
    mtl::string::replace(ident_s32, ident_match, ident_rep);

    CHECK_EQ(ident_s1 , ident_s1_result);
    CHECK_EQ(ident_s2 , ident_s2_result);
    CHECK_EQ(ident_s3 , ident_s3_result);
    CHECK_EQ(ident_s4 , ident_s4_result);
    CHECK_EQ(ident_s8 , ident_s8_result);
    CHECK_EQ(ident_s32 , ident_s32_result);



    // create some that the match and the replacement are the exact same size and it is just
    // one character
    std::string single_match = "^";
    std::string single_rep = "-";
    REQUIRE_EQ(single_match.size(), 1);
    REQUIRE_EQ(single_rep.size(), 1);
    REQUIRE_EQ(single_match.size(), single_rep.size());

    // create some strings to match
    std::string single_s1 = single_match + long_string;
    std::string single_s2 = single_match + long_string + single_match;
    std::string single_s3 = single_match + single_match + long_string + single_match;
    std::string single_s4;
    single_s4 = single_match + single_match + long_string + single_match + single_match;
    std::string single_s8 = single_s4 + single_s4;
    std::string single_s32 = single_s8 + single_s8 + single_s8 + single_s8;

    // create some strings we want to be compared with
    std::string single_s1_result = single_rep + long_string;
    std::string single_s2_result = single_rep + long_string + single_rep;
    std::string single_s3_result = single_rep + single_rep + long_string + single_rep;
    std::string single_s4_result = single_rep + single_rep + long_string + single_rep + single_rep;
    std::string single_s8_result = single_s4_result + single_s4_result;
    std::string single_s32_result = single_s8_result + single_s8_result;
    single_s32_result = single_s32_result + single_s32_result;

    mtl::string::replace(single_s1, single_match, single_rep);
    mtl::string::replace(single_s2, single_match, single_rep);
    mtl::string::replace(single_s3, single_match, single_rep);
    mtl::string::replace(single_s4, single_match, single_rep);
    mtl::string::replace(single_s8, single_match, single_rep);
    mtl::string::replace(single_s32, single_match, single_rep);

    CHECK_EQ(single_s1 , single_s1_result);
    CHECK_EQ(single_s2 , single_s2_result);
    CHECK_EQ(single_s3 , single_s3_result);
    CHECK_EQ(single_s4 , single_s4_result);
    CHECK_EQ(single_s8 , single_s8_result);
    CHECK_EQ(single_s32 , single_s32_result);



    // create some that the match and the replacement are the exact same size
    std::string same_match = "[[[Nick]]]";
    std::string same_rep = "<<|Bill|>>";
    REQUIRE_EQ(same_match.size(), same_rep.size());

    // create some strings to match
    std::string same_s1 = same_match + long_string;
    std::string same_s2 = same_match + long_string + same_match;
    std::string same_s3 = same_match + same_match + long_string + same_match;
    std::string same_s4 = same_match + same_match + long_string + same_match + same_match;
    std::string same_s8 = same_s4 + same_s4;
    std::string same_s32 = same_s8 + same_s8 + same_s8 + same_s8;

    // create some strings we want to be compared with
    std::string same_s1_result = same_rep + long_string;
    std::string same_s2_result = same_rep + long_string + same_rep;
    std::string same_s3_result = same_rep + same_rep + long_string + same_rep;
    std::string same_s4_result = same_rep + same_rep + long_string + same_rep + same_rep;
    std::string same_s8_result = same_s4_result + same_s4_result;
    std::string same_s32_result= same_s8_result + same_s8_result + same_s8_result + same_s8_result;

    mtl::string::replace(same_s1, same_match, same_rep);
    mtl::string::replace(same_s2, same_match, same_rep);
    mtl::string::replace(same_s3, same_match, same_rep);
    mtl::string::replace(same_s4, same_match, same_rep);
    mtl::string::replace(same_s8, same_match, same_rep);
    mtl::string::replace(same_s32, same_match, same_rep);

    CHECK_EQ(same_s1 , same_s1_result);
    CHECK_EQ(same_s2 , same_s2_result);
    CHECK_EQ(same_s3 , same_s3_result);
    CHECK_EQ(same_s4 , same_s4_result);
    CHECK_EQ(same_s8 , same_s8_result);
    CHECK_EQ(same_s32 , same_s32_result);




    // create some that the match is larger than the replacement
    std::string big_match = "#AAAAAAAAAAA#";
    std::string small_rep = "@";

    // create some strings to match
    std::string other_s1 = big_match + long_string;
    std::string other_s2 = big_match + long_string + big_match;
    std::string other_s3 = big_match + big_match + long_string + big_match;
    std::string other_s4 = big_match + big_match + long_string + big_match + big_match;
    std::string other_s8 = other_s4 + other_s4;
    std::string other_s32 = other_s8 + other_s8 + other_s8 + other_s8;

    // create some strings we want to be compared with
    std::string other_s1_result = small_rep + long_string;
    std::string other_s2_result = small_rep + long_string + small_rep;
    std::string other_s3_result = small_rep + small_rep + long_string + small_rep;
    std::string other_s4_result = small_rep + small_rep + long_string + small_rep + small_rep;
    std::string other_s8_result = other_s4_result + other_s4_result;
    std::string other_s32_result = other_s8_result + other_s8_result; 
    other_s32_result = other_s32_result + other_s32_result;

    mtl::string::replace(other_s1, big_match, small_rep);
    mtl::string::replace(other_s2, big_match, small_rep);
    mtl::string::replace(other_s3, big_match, small_rep);
    mtl::string::replace(other_s4, big_match, small_rep);
    mtl::string::replace(other_s8, big_match, small_rep);
    mtl::string::replace(other_s32, big_match, small_rep);

    CHECK_EQ(other_s1 , other_s1_result);
    CHECK_EQ(other_s2 , other_s2_result);
    CHECK_EQ(other_s3 , other_s3_result);
    CHECK_EQ(other_s4 , other_s4_result);
    CHECK_EQ(other_s8 , other_s8_result);
    CHECK_EQ(other_s32 , other_s32_result);

    // like a simpler version of C++ 20 std::format replacing all {} matches with a replacement
    std::string text_to_fmt = "I went {} and i said i have your {} with backup as fall{}.";
    std::string result_fmt  = "I went back and i said i have your back with backup as fallback.";
    std::string match_fmt   = "{}";
    std::string replacement_fmt = "back";
    mtl::string::replace(text_to_fmt, match_fmt, replacement_fmt);
    CHECK_EQ((text_to_fmt == result_fmt), true);




    // check that is works correctly with UTF8 strings

    // create some that the match and the replacement contains utf8 characters
	std::string utf8_match = smiley;
	std::string utf8_rep = "[" + two_smileys_delimiter + "]";

    // create some strings to match
    std::string utf8_s1 = utf8_match + long_string;
    std::string utf8_s2 = utf8_match + long_string + utf8_match;
    std::string utf8_s3 = utf8_match + utf8_match + long_string + utf8_match;
    std::string utf8_s4 = utf8_match + utf8_match + long_string + utf8_match + utf8_match;
    std::string utf8_s8 = utf8_s4 + utf8_s4;
    std::string utf8_s32 = utf8_s8 + utf8_s8 + utf8_s8 + utf8_s8;

    // create some strings we want to be compared with
    std::string utf8_s1_result = utf8_rep + long_string;
    std::string utf8_s2_result = utf8_rep + long_string + utf8_rep;
    std::string utf8_s3_result = utf8_rep + utf8_rep + long_string + utf8_rep;
    std::string utf8_s4_result = utf8_rep + utf8_rep + long_string + utf8_rep + utf8_rep;
    std::string utf8_s8_result = utf8_s4_result + utf8_s4_result;
    std::string utf8_s32_result= utf8_s8_result + utf8_s8_result + utf8_s8_result + utf8_s8_result;

    mtl::string::replace(utf8_s1, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s2, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s3, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s4, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s8, utf8_match, utf8_rep);
    mtl::string::replace(utf8_s32, utf8_match, utf8_rep);

    CHECK_EQ(utf8_s1 , utf8_s1_result);
    CHECK_EQ(utf8_s2 , utf8_s2_result);
    CHECK_EQ(utf8_s3 , utf8_s3_result);
    CHECK_EQ(utf8_s4 , utf8_s4_result);
    CHECK_EQ(utf8_s8 , utf8_s8_result);
    CHECK_EQ(utf8_s32 , utf8_s32_result);
}

// ------------------------------------------------------------------------------------------------
// mtl::string::replace_all
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::string::replace_all")
{
    // when both container are empty
    std::vector<std::string> empty_matches;
    std::vector<std::string> empty_replacements;
    std::string text = "Hello world";
    mtl::string::replace_all(text, empty_matches, empty_replacements);
    CHECK_EQ(empty_matches.empty(), true);
    CHECK_EQ(empty_replacements.empty(), true);
    CHECK_EQ((text == std::string("Hello world")), true);

    // with matches container empty and replacements container not empty, when the containers are
    // different size it should throw std::invalid_argument
    std::vector<std::string> replacements{ "One", "Two"};
    REQUIRE_THROWS_AS((mtl::string::replace_all(text, empty_matches, replacements)), 
                       std::invalid_argument);
    CHECK_EQ((text == std::string("Hello world")), true);

    // with matches container not empty and replacements container empty, when the containers are
    // different size it should throw std::invalid_argument
    std::vector<std::string> matches {"Joe", "Jill", "Jack"}; 
    REQUIRE_THROWS_AS((mtl::string::replace_all(text, matches, empty_replacements)), 
                       std::invalid_argument);     
    CHECK_EQ((text == std::string("Hello world")), true);

    // with containers of different size, when the containers are different size it should throw
    // std::invalid_argument           
    REQUIRE_THROWS_AS((mtl::string::replace_all(text, matches, replacements)), 
                       std::invalid_argument);  
    CHECK_EQ((text == std::string("Hello world")), true);

    // with empty input string and empty containers
    std::string empty;
    mtl::string::replace_all(empty, empty_matches, empty_replacements);
    CHECK_EQ(empty.empty(), true);

    // with empty input string
    std::vector<std::string> num_matches {"1", "2", "3"};
    std::vector<std::string> num_replacements {"one", "two", "three"};
    mtl::string::replace_all(empty, empty_matches, empty_replacements);
    CHECK_EQ(empty.empty(), true);

    // with nothing matching to replace
    mtl::string::replace_all(text, num_matches, num_replacements);
    CHECK_EQ((text == std::string("Hello world")), true);

    // with something to replace
    std::string text_with_matches = "This car is maybe 1 to 2 times faster but not 3.";
    std::string result_with_matches = "This car is maybe one to two times faster but not three.";
    mtl::string::replace_all(text_with_matches, num_matches, num_replacements);
    CHECK_EQ((text_with_matches == result_with_matches), true);

    // with multiple items to replace in various positions
    std::string multi_matches = "123,123,123,123";
    std::string multi_result = "onetwothree";
    multi_result = multi_result + "," + multi_result + "," + multi_result + "," + multi_result;
    mtl::string::replace_all(multi_matches, num_matches, num_replacements);
    CHECK_EQ((multi_matches == multi_result), true);

    // with multiple items to replace in various positions with a long std::string
    const std::string long_string(400, 'z');
    REQUIRE_EQ(long_string.size(), 400);

    std::string multi_m_long = "[123][123][123][123]";
    multi_m_long = multi_m_long + long_string + multi_m_long;
    std::string multi_res_long = "[onetwothree]";
    multi_res_long = multi_res_long + multi_res_long + multi_res_long + multi_res_long;
    multi_res_long = multi_res_long + long_string + multi_res_long;
    mtl::string::replace_all(multi_m_long, num_matches, num_replacements);
    REQUIRE_EQ((multi_m_long.size() > 400), true);
    REQUIRE_EQ((multi_res_long.size() > 400), true);
    CHECK_EQ((multi_m_long == multi_res_long), true);
    


    // with multiple items to replace in various positions with a long std::string with a big
    // number of matches
    std::string mmb_long = "[123][123][123][123]";
    mmb_long = mmb_long + mmb_long + mmb_long + mmb_long + mmb_long;
    mmb_long = mmb_long + mmb_long + mmb_long + mmb_long;
    mmb_long = mmb_long + long_string + mmb_long;

    std::string mrb_long = "[onetwothree][onetwothree][onetwothree][onetwothree]";
    mrb_long = mrb_long + mrb_long + mrb_long + mrb_long + mrb_long;
    mrb_long = mrb_long + mrb_long + mrb_long + mrb_long;
    mrb_long = mrb_long + long_string + mrb_long;
    mtl::string::replace_all(mmb_long, num_matches, num_replacements);

    REQUIRE_EQ((mmb_long.size() > 400), true);
    REQUIRE_EQ((mrb_long.size() > 400), true);
    CHECK_EQ((mmb_long == mrb_long), true);

    // like a simpler version of C++ 20 std::format replacing all {0}{1}{2} holes with replacement
    // elements
    std::string text_to_fmt = "Hello {0}, {1} and {2}";
    std::string result_fmt = "Hello Jill, Jack and Joe";
    std::vector<std::string> num_holes = { "{0}", "{1}", "{2}" };
    std::vector<std::string> names = { "Jill", "Jack", "Joe" };
    
    mtl::string::replace_all(text_to_fmt, num_holes, names);
    CHECK_EQ(text_to_fmt, result_fmt);
}