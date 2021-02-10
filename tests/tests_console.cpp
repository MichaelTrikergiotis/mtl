// tests by Michael Trikergiotis
// 31/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <string>
#include <sstream> // std::stringstream
#include <ostream> // std::ostream
#include <vector>
#include <numeric>


// Disable some of the asserts in mtl so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/console.hpp" 
// mtl::console::print, mtl::console::println, 
// mtl::console::print_all, mtl::console::print_color, mtl::console::println_color,
// mtl::console::overtype, mtl::console::clear


// Create our own class with overloaded operator<< so we can print it successfully.
class custom_class
{
    std::string s = "Numbers : " ;
    int i = 10;
    float f = 10.1f;
    double d = 10.1;   
    friend std::ostream& operator<<(std::ostream& out, const custom_class& cc)
    {
        return out << cc.s << " " << cc.i << " " << cc.f << " " << cc.d;
    }
};

// Create our own class with overloaded operator<< that is not a friend function, so we can print
// it successfully.
class unfriendly_class
{
public:
    std::string s = "Numbers : ";
    int i = 10;
    float f = 10.1f;
    double d = 10.1;
};

std::ostream& operator<<(std::ostream& out, const unfriendly_class& cc)
{
    return out << cc.s << " " << cc.i << " " << cc.f << " " << cc.d;
}

TEST_CASE("Make sure custom_class and unfriendly class produce the same results")
{
    // compare the result of operator<< for both classes to be equal
    std::stringstream ss_cs;
    std::stringstream ss_uc;
    custom_class cc;
    ss_cs << cc;
    unfriendly_class uc;
    ss_uc << uc;
    std::string cc_result = ss_cs.str();
    std::string uc_result = ss_uc.str();
    REQUIRE_EQ(cc_result, uc_result);
}

// ------------------------------------------------------------------------------------------------
// mtl::console::print and mtl::console::println
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::console::print, simple tests")
{
    REQUIRE_NOTHROW(mtl::console::print("\n\n\n"));

    mtl::console::print("======================================================================");
    mtl::console::print("=========\n");

    REQUIRE_NOTHROW(mtl::console::print("[mtl] Starting mtl::console tests.\n"));
  
    mtl::console::print("======================================================================");
    mtl::console::print("=========\n\n");
}

TEST_CASE("empty mtl::console::print")
{
    REQUIRE_NOTHROW((mtl::console::print()));
}

TEST_CASE("mtl::console::print print conversion specifiers without formatting, single item")
{
    // mtl::console::print does not format the passed arguments so strings like {}, {0} and %i etc
    // should not cause formatting changes
    const std::vector<std::string> conversion_specifiers
    { "{}", "{0}", "{1}", "{2}", "%", "%c", "%s", "%d", "%i", "%o", "%x", "%X","%u","%f", "%F",
      "%e", "%E", "%a", "%A", "%g", "%G", "%n", "%p", "#", "2.33#.2", "{#}", "{2.33#.2}" };

    REQUIRE_NOTHROW(mtl::console::print("mtl::console::print does not format the passed "));
    REQUIRE_NOTHROW(mtl::console::print("arguments, there should be no formatted text.\n"));
    REQUIRE_NOTHROW(mtl::console::print("This should print the conversion specifiers and not "));
    REQUIRE_NOTHROW(mtl::console::print("formatted text.\n"));
    for (const auto& specifier : conversion_specifiers)
    {
        // print a single item
        REQUIRE_NOTHROW(mtl::console::print(specifier));
        REQUIRE_NOTHROW(mtl::console::print('\n'));
    }
    REQUIRE_NOTHROW(mtl::console::print("\n\n\n"));
}

TEST_CASE("mtl::console::print print conversion specifiers without formatting, multiple items")
{
    // mtl::console::print does not format the passed arguments so strings like {}, {0} and %i etc
    // should not cause formatting changes
    const std::vector<std::string> conversion_specifiers
    { "{}", "{0}", "{1}", "{2}", "%", "%c", "%s", "%d", "%i", "%o", "%x", "%X","%u","%f", "%F",
      "%e", "%E", "%a", "%A", "%g", "%G", "%n", "%p", "#", "2.33#.2", "{#}", "{2.33#.2}" };

    std::string s = "world.";
    REQUIRE_NOTHROW(mtl::console::print("mtl::console::print does not format the passed "));
    REQUIRE_NOTHROW(mtl::console::print("arguments, there should be no formatted text.\n"));
    REQUIRE_NOTHROW(mtl::console::print("This should print the conversion specifiers and not "));
    REQUIRE_NOTHROW(mtl::console::print("formatted text.\n"));
    for (const auto& specifier : conversion_specifiers)
    {
        // print multiple items per call
        REQUIRE_NOTHROW(mtl::console::print('a', 'b', 'c', 13, "  ", specifier, " Hi ", s, '\n'));
    }
    REQUIRE_NOTHROW(mtl::console::print("\n\n\n"));
}

TEST_CASE("mtl::console::print single item, temp")
{
    REQUIRE_NOTHROW(mtl::console::print("aaa"));
    REQUIRE_NOTHROW(mtl::console::print(", "));
    REQUIRE_NOTHROW(mtl::console::print(std::string("aaa")));
    REQUIRE_NOTHROW(mtl::console::print(", "));
    REQUIRE_NOTHROW(mtl::console::print(1));
    REQUIRE_NOTHROW(mtl::console::print(", "));
    REQUIRE_NOTHROW(mtl::console::print(1.1111f));
    REQUIRE_NOTHROW(mtl::console::print(", "));
    REQUIRE_NOTHROW(mtl::console::print(1.11111));
    REQUIRE_NOTHROW(mtl::console::print(", "));
    REQUIRE_NOTHROW(mtl::console::print('a'));
    REQUIRE_NOTHROW(mtl::console::print('\n'));
    REQUIRE_NOTHROW(mtl::console::print(custom_class()));
    REQUIRE_NOTHROW(mtl::console::print(unfriendly_class()));
    REQUIRE_NOTHROW(mtl::console::print('\n'));
}

TEST_CASE("mtl::console::print single item")
{
    const char* cs = "aaa";
    std::string comma = ", ";
    REQUIRE_NOTHROW(mtl::console::print(cs));
    REQUIRE_NOTHROW(mtl::console::print(comma));
    std::string s = "aaa";
    REQUIRE_NOTHROW(mtl::console::print(s));
    REQUIRE_NOTHROW(mtl::console::print(comma));
    int i = 1;
    REQUIRE_NOTHROW(mtl::console::print(i));
    REQUIRE_NOTHROW(mtl::console::print(comma));
    float f = 1.1111f;
    REQUIRE_NOTHROW(mtl::console::print(f));
    REQUIRE_NOTHROW(mtl::console::print(comma));
    double d = 1.11111;
    REQUIRE_NOTHROW(mtl::console::print(d));
    REQUIRE_NOTHROW(mtl::console::print(comma));
    const char c = 'a';
    REQUIRE_NOTHROW(mtl::console::print(c));
    const char nl = '\n';
    REQUIRE_NOTHROW(mtl::console::print(nl));
    custom_class cc;
    REQUIRE_NOTHROW(mtl::console::print(cc));
    REQUIRE_NOTHROW(mtl::console::print(nl));
    unfriendly_class uc;
    REQUIRE_NOTHROW(mtl::console::print(uc));
    REQUIRE_NOTHROW(mtl::console::print(nl));
}

TEST_CASE("mtl::console::print multiple items")
{
    REQUIRE_NOTHROW( 
    mtl::console::print("aa", std::string("aaa"), 1, 1.1111f, 1.11111, 'a', '\n', 
                        custom_class(), unfriendly_class() , '\n') );
}


TEST_CASE("mtl::console::print multiple items")
{
        const char* cs = "aaa";
        std::string comma = ", ";
        std::string s = "aaa";
        int i = 1;
        float f = 1.1111f;
        double d = 1.11111;
        const char c = 'a';
        const char nl = '\n';
        custom_class cc;
        unfriendly_class uc;

        REQUIRE_NOTHROW(
        mtl::console::print(cs, comma, s, comma, i, comma, f, comma, d,
                            comma, c, nl, cc, nl, uc, nl));
}


// ---------------------
// mtl::console::println
// ---------------------

TEST_CASE("empty mtl::console::println")
{
    REQUIRE_NOTHROW((mtl::console::println()));
}

TEST_CASE("mtl::console::println print conversion specifiers without formatting, single item")
{
    // mtl::console::println does not format the passed arguments so strings like {}, {0} and %i 
    // etc should not cause formatting changes
    const std::vector<std::string> conversion_specifiers
    { "{}", "{0}", "{1}", "{2}", "%", "%c", "%s", "%d", "%i", "%o", "%x", "%X","%u","%f", "%F",
      "%e", "%E", "%a", "%A", "%g", "%G", "%n", "%p", "#", "2.33#.2", "{#}", "{2.33#.2}" };

    REQUIRE_NOTHROW(mtl::console::print("mtl::console::println does not format the passed "));
    REQUIRE_NOTHROW(mtl::console::println("arguments, there should be no formatted text."));
    REQUIRE_NOTHROW(mtl::console::print("This should print the conversion specifiers and not "));
    REQUIRE_NOTHROW(mtl::console::println("formatted text."));
    for (const auto& specifier : conversion_specifiers)
    {
        // print a single item
        REQUIRE_NOTHROW(mtl::console::println(specifier));
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::println print conversion specifiers without formatting, multiple items")
{
    // mtl::console::println does not format the passed arguments so strings like {}, {0} and %i
    // etc should not cause formatting changes
    const std::vector<std::string> conversion_specifiers
    { "{}", "{0}", "{1}", "{2}", "%", "%c", "%s", "%d", "%i", "%o", "%x", "%X","%u","%f", "%F",
      "%e", "%E", "%a", "%A", "%g", "%G", "%n", "%p", "#", "2.33#.2", "{#}", "{2.33#.2}" };

    std::string s = "world.";
    REQUIRE_NOTHROW(mtl::console::print("mtl::console::println does not format the passed "));
    REQUIRE_NOTHROW(mtl::console::println("arguments, there should be no formatted text."));
    REQUIRE_NOTHROW(mtl::console::print("This should print the conversion specifiers and not "));
    REQUIRE_NOTHROW(mtl::console::println("formatted text."));
    for (const auto& specifier : conversion_specifiers)
    {
        // print multiple items per call
        REQUIRE_NOTHROW(mtl::console::println('a', 'b', 'c', 7, "  ", specifier, " Hi ", s, '\n'));
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::println single item, temp")
{
    REQUIRE_NOTHROW(mtl::console::println("aaa"));
    REQUIRE_NOTHROW(mtl::console::println(", "));
    REQUIRE_NOTHROW(mtl::console::println(std::string("aaa")));
    REQUIRE_NOTHROW(mtl::console::println(", "));
    REQUIRE_NOTHROW(mtl::console::println(1));
    REQUIRE_NOTHROW(mtl::console::println(", "));
    REQUIRE_NOTHROW(mtl::console::println(1.1111f));
    REQUIRE_NOTHROW(mtl::console::println(", "));
    REQUIRE_NOTHROW(mtl::console::println(1.11111));
    REQUIRE_NOTHROW(mtl::console::println(", "));
    REQUIRE_NOTHROW(mtl::console::println('a'));
    REQUIRE_NOTHROW(mtl::console::println('\n'));
    REQUIRE_NOTHROW(mtl::console::println(custom_class()));
    REQUIRE_NOTHROW(mtl::console::println(unfriendly_class()));
    REQUIRE_NOTHROW(mtl::console::println('\n'));
}

TEST_CASE("mtl::console::println single item")
{
    const char* cs = "aaa";
    std::string comma = ", ";
    REQUIRE_NOTHROW(mtl::console::println(cs));
    REQUIRE_NOTHROW(mtl::console::println(comma));
    std::string s = "aaa";
    REQUIRE_NOTHROW(mtl::console::println(s));
    REQUIRE_NOTHROW(mtl::console::println(comma));
    int i = 1;
    REQUIRE_NOTHROW(mtl::console::println(i));
    REQUIRE_NOTHROW(mtl::console::println(comma));
    float f = 1.1111f;
    REQUIRE_NOTHROW(mtl::console::println(f));
    REQUIRE_NOTHROW(mtl::console::println(comma));
    double d = 1.11111;
    REQUIRE_NOTHROW(mtl::console::println(d));
    REQUIRE_NOTHROW(mtl::console::println(comma));
    const char c = 'a';
    REQUIRE_NOTHROW(mtl::console::println(c));
    const char nl = '\n';
    REQUIRE_NOTHROW(mtl::console::println(nl));
    custom_class cc;
    REQUIRE_NOTHROW(mtl::console::println(cc));
    REQUIRE_NOTHROW(mtl::console::println(nl));
    unfriendly_class uc;
    REQUIRE_NOTHROW(mtl::console::println(uc));
    REQUIRE_NOTHROW(mtl::console::println(nl));
}

TEST_CASE("mtl::console::println multiple items")
{
    REQUIRE_NOTHROW(
        mtl::console::println("aa", std::string("aaa"), 1, 1.1111f, 1.11111, 'a', '\n',
                            custom_class(), unfriendly_class(), '\n'));
}


TEST_CASE("mtl::console::println multiple items")
{
    const char* cs = "aaa";
    std::string comma = ", ";
    std::string s = "aaa";
    int i = 1;
    float f = 1.1111f;
    double d = 1.11111;
    const char c = 'a';
    const char nl = '\n';
    custom_class cc;
    unfriendly_class uc;

    REQUIRE_NOTHROW(
        mtl::console::println(cs, comma, s, comma, i, comma, f, comma, d,
                              comma, c, nl, cc, nl, uc, nl));
}



// ------------------------------------------------------------------------------------------------
// mtl::console::print_all
// ------------------------------------------------------------------------------------------------

// Generates some numbers that are nice to print.
std::vector<size_t> generate_numbers()
{
    constexpr size_t size = 90;
    // numbers doubling every 10 numbers to check padding
    // 1, 2, 3, 4,  5,  6,  7,  8,  9, 10, 
    // 2, 4, 6, 8, 10, 12, 14, 16, 18, 20
    std::vector<size_t> vi(size);
    size_t counter = 0;
    for(size_t i = 0; i < size; i++)
    {
        if ((i > 0) && (i % 5 == 0))
        {
            counter = 0;
        }
        counter++;
        vi.at(i) = counter;
    }

    size_t multiplier = 1;
    for(size_t i = 0; i < size; i++)
    {
        if ((i > 0) && (i % 5 == 0))
        {
            multiplier = multiplier * 2;
        }
        vi.at(i) = vi.at(i) * multiplier;
    }

    return vi;
}


TEST_CASE("mtl::console::print_all with empty std::vector")
{
    std::vector<int> vi;
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end()));
    mtl::console::println("\n----");
}

TEST_CASE("mtl::console::print_all with incorrect iterators")
{
    std::vector<int> vi {1, 2, 3, 4, 5};
    // create to iterators pointing to the beginning of the vector
    auto bad_it = vi.begin();
    auto end_iter = vi.begin();
    // move one of the iterators 3 positions forward
    bad_it = std::next(bad_it, 3);

    // pass the iterator that is further along the vector as the first iterator to check what 
    // happens when you pass incorrect iterators
    REQUIRE_NOTHROW(mtl::console::print_all(bad_it, end_iter));
    mtl::console::println("\n----");
}

TEST_CASE("mtl::console::print_all")
{
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end()));
    mtl::console::println("\n----");
}

TEST_CASE("mtl::console::print_all with delimiter")
{
   
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", "));
    mtl::console::println("\n----");

}

TEST_CASE("mtl::console::print_all with delimiter and per line items")
{
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", ", 10));
    mtl::console::println("\n----");
}

TEST_CASE("mtl::console::print_all without delimiter but with and per line items")
{
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 10));
    mtl::console::println("\n----");
}

TEST_CASE("mtl::console::print_all with delimiter, per line items and start/finish for lines")
{
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", ", 10, "[", "]"));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all without delimiter but with per line and start/finish for lines")
{
    auto vi = generate_numbers();
    // number in incresing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 10, "[", "]"));
    mtl::console::println("----");
}



TEST_CASE("mtl::console::print_all with every option except delimiter and padding none")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::none));

    mtl::console::println("----");   
}

TEST_CASE("mtl::console::print_all with every option except delimiter and padding front")
{
    auto vi = generate_numbers();
               
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option except delimiter and padding back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::back));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option except delimiter and padding both_front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                            mtl::console::print_pad::both_front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option except delimiter and padding both_back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                            mtl::console::print_pad::both_back));
    mtl::console::println("----");
}

// --

TEST_CASE("mtl::console::print_all with every option including padding to none")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::none));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to back")
{
    auto vi = generate_numbers();

    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::back));

    mtl::console::println("----");

}

TEST_CASE("mtl::console::print_all with every option including padding to both_front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                            mtl::console::print_pad::both_front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to both_back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                            mtl::console::print_pad::both_back));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to both_front with char")
{
    std::vector<char> vc { 'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E',  
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E' };
    REQUIRE_NOTHROW(mtl::console::print_all(vc.begin(), vc.end(), ")><(", 5, "<(", ")>", 
                    mtl::console::print_pad::both_front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to both_back with char")
{
    std::vector<char> vc { 'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E',  
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E' };
    REQUIRE_NOTHROW(mtl::console::print_all(vc.begin(), vc.end(), ")><(", 5, "<(", ")>", 
                    mtl::console::print_pad::both_back));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to both_front with string")
{
    std::vector<std::string> vs { 
    "a", "b", "c", "d", "e", "A", "B", "C", "D", "E", 
    "aaa", "bbb", "ccc", "ddd", "eee", "AAA", "BBB", "CCC", "DDD", "EEE", 
    "aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee", "AAAAA", "BBBBB", "CCCCC", "DDDDD", "EEEEE", 
    };
    REQUIRE_NOTHROW(mtl::console::print_all(vs.begin(), vs.end(), ")>|<(", 10, "<(", ")>", 
                    mtl::console::print_pad::both_front));
    mtl::console::println("----");
}

TEST_CASE("mtl::console::print_all with every option including padding to both_back with string")
{
    std::vector<std::string> vs { 
    "a", "b", "c", "d", "e", "A", "B", "C", "D", "E", 
    "aaa", "bbb", "ccc", "ddd", "eee", "AAA", "BBB", "CCC", "DDD", "EEE", 
    "aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee", "AAAAA", "BBBBB", "CCCCC", "DDDDD", "EEEEE", 
    };
    REQUIRE_NOTHROW(mtl::console::print_all(vs.begin(), vs.end(), ")>|<(", 10, "<(", ")>", 
                    mtl::console::print_pad::both_back));
    mtl::console::println("\n--------------\n\n\n");
}

TEST_CASE("mtl::console::print_all with conversion specifiers without formatting")
{
    // mtl::console::print_all does not format the passed arguments so strings like {}, {0}, {1}
    // and %i etc should not cause formatting changes
    const std::vector<std::string> conversion_specifiers
    { "{}", "{0}", "{1}", "{2}", "%", "%c", "%s", "%d", "%i", "%o", "%x", "%X","%u","%f", "%F",
      "%e", "%E", "%a", "%A", "%g", "%G", "%n", "%p", "#", "2.33#.2", "{#}", "{2.33#.2}" };

    REQUIRE_NOTHROW(mtl::console::print("mtl::console::print_all does not format the passed "));
    REQUIRE_NOTHROW(mtl::console::print("arguments, there should be no formatted text.\n"));
    REQUIRE_NOTHROW(mtl::console::print("This should print the conversion specifiers and not "));
    REQUIRE_NOTHROW(mtl::console::print("formatted text.\n"));
    REQUIRE_NOTHROW(mtl::console::print_all(conversion_specifiers.begin(), 
                                            conversion_specifiers.end(), "][", 10, "[", "]", 
                                            mtl::console::print_pad::both_back));
    mtl::console::println("\n--------------\n\n\n");
}


// ------------------------------------------------------------------------------------------------
// mtl::console::print_color
// ------------------------------------------------------------------------------------------------


const std::vector<mtl::console::color> all_colors =
{
    mtl::console::color::default_color,
    mtl::console::color::black,
    mtl::console::color::red,
    mtl::console::color::green,
    mtl::console::color::yellow,
    mtl::console::color::blue,
    mtl::console::color::magenta,
    mtl::console::color::cyan,
    mtl::console::color::white,

    mtl::console::color::bright_black,
    mtl::console::color::bright_red,
    mtl::console::color::bright_green,
    mtl::console::color::bright_yellow,
    mtl::console::color::bright_blue,
    mtl::console::color::bright_magenta,
    mtl::console::color::bright_cyan,
    mtl::console::color::bright_white
};

const std::vector<std::string> all_colors_names =
{
    "default_color",
    "black",
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan",
    "white",

    "bright_black",
    "bright_red",
    "bright_green",
    "bright_yellow",
    "bright_blue",
    "bright_magenta",
    "bright_cyan",
    "bright_white",
};


TEST_CASE("mtl::console::print_color with no parameters passed")
{
    REQUIRE_NOTHROW(mtl::console::println("No parameters : "));
    REQUIRE_NOTHROW(mtl::console::print_color(111));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color(222.22f));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color(333.333));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color(4444.444l));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color('c'));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color(""));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color("Hello world"));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    REQUIRE_NOTHROW(mtl::console::print_color(std::string("Hello world")));
    REQUIRE_NOTHROW(mtl::console::println());
    REQUIRE_NOTHROW(mtl::console::print_color("Some text\nwith\nnewlines\nin it.\n"));
    REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


    int i = 111;
    REQUIRE_NOTHROW(mtl::console::print_color(i));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    float f = 222.22f;
    REQUIRE_NOTHROW(mtl::console::print_color(f));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::print_color(d));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    long double ld = 4444.444l;
    REQUIRE_NOTHROW(mtl::console::print_color(ld));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    const char c = 'c';
    REQUIRE_NOTHROW(mtl::console::print_color(c));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    const char* cs = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(cs));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    std::string s = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(s));
    REQUIRE_NOTHROW(mtl::console::println());
    std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::print_color(str_newlines));
    std::string text_nocolor = "Some noncolored text on this line.";
    REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

    for (int x = 0; x < 10; x++)
    {
        REQUIRE_NOTHROW(mtl::console::print_color("["));
        REQUIRE_NOTHROW(mtl::console::print_color(x + 1));
        REQUIRE_NOTHROW(mtl::console::print_color("]"));
    }

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::print_color with one parameter, all colors")
{
    for(size_t x = 0; x < all_colors.size(); x++)
    {
    REQUIRE_NOTHROW(mtl::console::print("One parameter, foreground "));
    REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
    REQUIRE_NOTHROW(mtl::console::println(" : "));
    auto current_color = all_colors.at(x);
    REQUIRE_NOTHROW(mtl::console::print_color(111, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(222.22f, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(333.333, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(4444.444l, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color('c', current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color("Hello world", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(std::string("Hello world"), 
                                              current_color));
    REQUIRE_NOTHROW(mtl::console::println());
    REQUIRE_NOTHROW(mtl::console::print_color("Some text\nwith\nnewlines\nin it.\n", 
                                              current_color));
    REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


    int i = 111;
    REQUIRE_NOTHROW(mtl::console::print_color(i, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    float f = 222.22f;
    REQUIRE_NOTHROW(mtl::console::print_color(f, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::print_color(d, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    long double ld = 4444.444l;
    REQUIRE_NOTHROW(mtl::console::print_color(ld, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    const char c = 'c';
    REQUIRE_NOTHROW(mtl::console::print_color(c, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    const char* cs = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(cs, current_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
    std::string s = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(s, current_color));
    REQUIRE_NOTHROW(mtl::console::println());
    std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::print_color(str_newlines, current_color));
    std::string text_nocolor = "Some noncolored text on this line.";
    REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

    for (int z = 0; z < 10; z++)
    {
        REQUIRE_NOTHROW(mtl::console::print_color("[", current_color));
        REQUIRE_NOTHROW(mtl::console::print_color(z + 1, current_color));
        REQUIRE_NOTHROW(mtl::console::print_color("]", current_color));
    }

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    }
}

TEST_CASE("mtl::console::print_color with two parameters, all colors with all colors")
{
    for(size_t x = 0; x < all_colors.size(); x++)
    {
    for(size_t y = 0; y < all_colors.size(); y++)
    {    
    REQUIRE_NOTHROW(mtl::console::print("Two parameters, foreground "));
    REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
    REQUIRE_NOTHROW(mtl::console::print(", background "));
    REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(y)));
    REQUIRE_NOTHROW(mtl::console::println(" : "));
    auto foreground_color = all_colors.at(x);
    auto background_color = all_colors.at(y);
    
    REQUIRE_NOTHROW(mtl::console::print_color(111, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(222.22f, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(333.333, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(4444.444l, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color('c', foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color("Hello world", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(std::string("Hello world"),
                                              foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::println());
    REQUIRE_NOTHROW(mtl::console::print_color("Some text\nwith\nnewlines\nin it.\n",
                                              foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


    int i = 111;
    REQUIRE_NOTHROW(mtl::console::print_color(i, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    float f = 222.22f;
    REQUIRE_NOTHROW(mtl::console::print_color(f, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::print_color(d, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    long double ld = 4444.444l;
    REQUIRE_NOTHROW(mtl::console::print_color(ld, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    const char c = 'c';
    REQUIRE_NOTHROW(mtl::console::print_color(c, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    const char* cs = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(cs, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    std::string s = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(s, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::println());
    std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::print_color(str_newlines, foreground_color, background_color));
    std::string text_nocolor = "Some noncolored text on this line.";
    REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

    for (int z = 0; z < 10; z++)
    {
        REQUIRE_NOTHROW(mtl::console::print_color("[", foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::print_color(z + 1, foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::print_color("]", foreground_color, background_color));
    }

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    }
    }
}

// ------------------------------------------------------------------------------------------------
// mtl::console::println_color
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::console::println_color with no parameters passed")
{
    REQUIRE_NOTHROW(mtl::console::println("No parameters : "));
    REQUIRE_NOTHROW(mtl::console::println_color(111));
    REQUIRE_NOTHROW(mtl::console::println_color(222.22f));
    REQUIRE_NOTHROW(mtl::console::println_color(333.333));
    REQUIRE_NOTHROW(mtl::console::println_color(4444.444l));
    REQUIRE_NOTHROW(mtl::console::println_color('c'));
    REQUIRE_NOTHROW(mtl::console::println_color("Hello world"));
    REQUIRE_NOTHROW(mtl::console::println_color(std::string("Hello world")));
    REQUIRE_NOTHROW(mtl::console::println_color("Some text\nwith\nnewlines\nin it.\n"));
    REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


    int i = 111;
    REQUIRE_NOTHROW(mtl::console::println_color(i));
    float f = 222.22f;
    REQUIRE_NOTHROW(mtl::console::println_color(f));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::println_color(d));
    long double ld = 4444.444l;
    REQUIRE_NOTHROW(mtl::console::println_color(ld));
    const char c = 'c';
    REQUIRE_NOTHROW(mtl::console::println_color(c));
    const char* cs = "Hello world";
    REQUIRE_NOTHROW(mtl::console::println_color(cs));
    std::string s = "Hello world";
    REQUIRE_NOTHROW(mtl::console::println_color(s));
    std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::println_color(str_newlines));
    std::string text_nocolor = "Some noncolored text on this line.";
    REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

    for (int x = 0; x < 10; x++)
    {
        REQUIRE_NOTHROW(mtl::console::print_color("["));
        REQUIRE_NOTHROW(mtl::console::print_color(x + 1));
        REQUIRE_NOTHROW(mtl::console::println_color("]"));
    }

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::println_color with one parameter, all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
        REQUIRE_NOTHROW(mtl::console::print("One parameter, foreground "));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
        REQUIRE_NOTHROW(mtl::console::println(" : "));
        auto current_color = all_colors.at(x);
        REQUIRE_NOTHROW(mtl::console::println_color(111, current_color));
        REQUIRE_NOTHROW(mtl::console::println_color(222.22f, current_color));
        REQUIRE_NOTHROW(mtl::console::println_color(333.333, current_color));
        REQUIRE_NOTHROW(mtl::console::println_color(4444.444l, current_color));
        REQUIRE_NOTHROW(mtl::console::println_color('c', current_color));
        REQUIRE_NOTHROW(mtl::console::println_color("Hello world", current_color));
        REQUIRE_NOTHROW(mtl::console::println_color(std::string("Hello world"),
                                                    current_color));
        REQUIRE_NOTHROW(mtl::console::println_color("Some text\nwith\nnewlines\nin it.\n", 
                                                    current_color));
        REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


        int i = 111;
        REQUIRE_NOTHROW(mtl::console::println_color(i, current_color));
        float f = 222.22f;
        REQUIRE_NOTHROW(mtl::console::println_color(f, current_color));
        double d = 333.333;
        REQUIRE_NOTHROW(mtl::console::println_color(d, current_color));
        long double ld = 4444.444l;
        REQUIRE_NOTHROW(mtl::console::println_color(ld, current_color));
        const char c = 'c';
        REQUIRE_NOTHROW(mtl::console::println_color(c, current_color));
        const char* cs = "Hello world";
        REQUIRE_NOTHROW(mtl::console::println_color(cs, current_color));
        std::string s = "Hello world";
        REQUIRE_NOTHROW(mtl::console::println_color(s, current_color));
        std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
        REQUIRE_NOTHROW(mtl::console::println_color(str_newlines, current_color));
        std::string text_nocolor = "Some noncolored text on this line.";
        REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

        for (int z = 0; z < 10; z++)
        {
            REQUIRE_NOTHROW(mtl::console::print_color("[", current_color));
            REQUIRE_NOTHROW(mtl::console::print_color(z + 1, current_color));
            REQUIRE_NOTHROW(mtl::console::println_color("]", current_color));
        }

        REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    }
}

TEST_CASE("mtl::console::println_color with two parameters, all colors with all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
        for (size_t y = 0; y < all_colors.size(); y++)
        {
        REQUIRE_NOTHROW(mtl::console::print("Two parameters, foreground "));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
        REQUIRE_NOTHROW(mtl::console::print(", background "));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(y)));
        REQUIRE_NOTHROW(mtl::console::println(" : "));
        auto foreground_color = all_colors.at(x);
        auto background_color = all_colors.at(y);
        REQUIRE_NOTHROW(mtl::console::println_color(111, foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println_color(222.22f, foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println_color(333.333, foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println_color(4444.444l, foreground_color, 
                                                    background_color));
        REQUIRE_NOTHROW(mtl::console::println_color('c', foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println_color("Hello world", foreground_color, 
                                                    background_color));
        REQUIRE_NOTHROW(mtl::console::println_color(std::string("Hello world"),
                                                    foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println_color("Some text\nwith\nnewlines\nin it.\n",
                                                    foreground_color, background_color));
        REQUIRE_NOTHROW(mtl::console::println("Some noncolored text on this line."));


        int i = 111;
        REQUIRE_NOTHROW(mtl::console::println_color(i, foreground_color, background_color));
        float f = 222.22f;
        REQUIRE_NOTHROW(mtl::console::println_color(f, foreground_color, background_color));
        double d = 333.333;
        REQUIRE_NOTHROW(mtl::console::println_color(d, foreground_color, background_color));
        long double ld = 4444.444l;
        REQUIRE_NOTHROW(mtl::console::println_color(ld, foreground_color, background_color));
        const char c = 'c';
        REQUIRE_NOTHROW(mtl::console::println_color(c, foreground_color, background_color));
        const char* cs = "Hello world";
        REQUIRE_NOTHROW(mtl::console::println_color(cs, foreground_color, background_color));
        std::string s = "Hello world";
        REQUIRE_NOTHROW(mtl::console::println_color(s, foreground_color, background_color));
        std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
        REQUIRE_NOTHROW(mtl::console::println_color(str_newlines, foreground_color, 
                                                    background_color));
        std::string text_nocolor = "Some noncolored text on this line.";
        REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

        for (int z = 0; z < 10; z++)
        {
            REQUIRE_NOTHROW(mtl::console::print_color("[", foreground_color, background_color));
            REQUIRE_NOTHROW(mtl::console::print_color(z + 1, foreground_color, 
                                                      background_color));
            REQUIRE_NOTHROW(mtl::console::println_color("]", foreground_color, background_color));
        }
        REQUIRE_NOTHROW(mtl::console::println("\n\n"));
        }
    }
}


// ------------------------------------------------------------------------------------------------
// mtl::console::overtype
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::console::overtype with empty original and empty replacement, std::string")
{
    std::string original = "";
    std::string replacement = "";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty original, std::string")
{
    std::string original = "";
    std::string replacement = "DDEE";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty replacment, std::string")
{
    std::string original = "AABBCC";
    std::string replacement = "";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original and replacement being one char long, std::string")
{
    std::string original = "z";
    std::string replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original being one char long, std::string")
{
    std::string original = "z";
    std::string replacement = "xxx";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with replacement being one char long, std::string")
{
    std::string original = "zzz";
    std::string replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with equal length original and replacement, std::string")
{
    std::string original = "AABBCC";
    std::string replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with smaller original than replacement, std::string")
{
    std::string original = "ABC";
    std::string replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with bigger original than replacement, std::string")
{
    std::string original = "AABBCC";
    std::string replacement = "EE"; 
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype multiple times, std::string")
{
    std::string original = "ABC";
    std::string replacement = "Multiple numbers from 0 to 9, one at a time"; 
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    for(int i = 0; i < 10; i++)
    {
        std::string counter = std::to_string(i);
        REQUIRE_NOTHROW(mtl::console::overtype(counter));
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype showcase how updating a counter would look like, std::string")
{
    std::string original    = "[            0%]";
    std::string replacement = "[==========100%]"; 
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    for(int x = 0; x <= 10; x++)
    {       
        std::string counter = "[";              
        for(int y = 0; y < x; y++)
        {
            counter += "=";
        }

        for(int y = 0; y < (10 - x); y++)
        {
            counter += " ";
        }

        // add extra spaces for the "100%" to fit nicely
        counter += "   ";

        std::string number = std::to_string((x * 10));
        for(int z = 0; z < static_cast<int>(number.size()); z++)
        {
            counter.pop_back();
        }
        counter += number + "%]";
        // here you add some long running operation or simulate something taking a long time like:
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        mtl::console::overtype(counter);
        
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}





TEST_CASE("mtl::console::overtype with empty original and empty replacement, const char*")
{
    std::string original = "";
    const char* replacement = "";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty original, const char*")
{
    std::string original = "";
    const char* replacement = "DDEE";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty replacment, const char*")
{
    std::string original = "AABBCC";
    const char* replacement = "";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original and replacement being one char long, const char*")
{
    std::string original = "z";
    const char* replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original being one char long, const char*")
{
    std::string original = "z";
    const char* replacement = "xxx";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with replacement being one char long, const char*")
{
    std::string original = "zzz";
    const char* replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with equal length original and replacement, const char*")
{
    std::string original = "AABBCC";
    const char* replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with smaller original than replacement, const char*")
{
    std::string original = "ABC";
    const char* replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with bigger original than replacement, const char*")
{
    std::string original = "AABBCC";
    const char* replacement = "EE";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype multiple times, const char*")
{
    std::string original = "ABC";
    std::string replacement = "Multiple numbers from 0 to 9, one at a time";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    for (int i = 0; i < 10; i++)
    {
        std::string counter = std::to_string(i);
        const char* counter_cs = counter.c_str();
        REQUIRE_NOTHROW(mtl::console::overtype(counter_cs));
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype showcase how updating a counter would look like, const char*")
{
    std::string original = "[            0%]";
    std::string replacement = "[==========100%]";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    for (int x = 0; x <= 10; x++)
    {
        std::string counter = "[";
        for (int y = 0; y < x; y++)
        {
            counter += "=";
        }

        for (int y = 0; y < (10 - x); y++)
        {
            counter += " ";
        }

        // add extra spaces for the "100%" to fit nicely
        counter += "   ";

        std::string number = std::to_string((x * 10));
        for (int z = 0; z < static_cast<int>(number.size()); z++)
        {
            counter.pop_back();
        }
        counter += number + "%]";
        const char* counter_cs = counter.c_str();
        // here you add some long running operation or simulate something taking a long time like:
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        mtl::console::overtype(counter_cs);

    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n\n\n"));
}





// ------------------------------------------------------------------------------------------------
// Print some info
// ------------------------------------------------------------------------------------------------

TEST_CASE("Print that we finished the mtl::console tests.")
{
    mtl::console::print("======================================================================");
    mtl::console::println("=========");

    REQUIRE_NOTHROW(mtl::console::println("[mtl] End of mtl::console tests."));

    mtl::console::print("======================================================================");
    mtl::console::println("=========");


}

TEST_CASE("print the newline character with various ways")
{
    REQUIRE_NOTHROW(mtl::console::println());
    REQUIRE_NOTHROW(mtl::console::println('\n'));
    REQUIRE_NOTHROW(mtl::console::print("\n\n"));
    REQUIRE_NOTHROW(mtl::console::print('\n'));
    REQUIRE_NOTHROW(mtl::console::print("\n\n"));

    char newline_char = '\n';
    REQUIRE_NOTHROW(mtl::console::print(newline_char));

    const char* newline_cs = "\n";
    REQUIRE_NOTHROW(mtl::console::print(newline_cs));

    const char* multi_newline_cs = "\n\n";
    REQUIRE_NOTHROW(mtl::console::print(multi_newline_cs));

    std::string newline("\n");
    REQUIRE_NOTHROW(mtl::console::print(newline));

    std::string multi_newline("\n\n\n\n\n\n\n\n\n\n\n");
    REQUIRE_NOTHROW(mtl::console::print(multi_newline));
}

// ------------------------------------------------------------------------------------------------
// mtl::console::clear
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::console::clear")
{
    // this clears the console
    REQUIRE_NOTHROW(mtl::console::clear());
}


// ------------------------------------------------------------------------------------------------
// Print some doctest info
// ------------------------------------------------------------------------------------------------

TEST_CASE("print doctest text")
{
    // print the exact same message that doctest would have printed if we didn't clear the screen

    // use blue color from doctest to print blue colored letters
    REQUIRE_NOTHROW(mtl::console::print(doctest::Color::Cyan));
    REQUIRE_NOTHROW(mtl::console::print("[doctest]"));
    // stop using blue colored letters
    REQUIRE_NOTHROW(mtl::console::print(doctest::Color::None)); 

    REQUIRE_NOTHROW(mtl::console::print(" doctest version is "));
    // grab the version of the current doctest from the doctest version macro
    const auto doctest_version = DOCTEST_VERSION_STR;
    REQUIRE_NOTHROW(mtl::console::println(doctest_version));

    // use blue color from doctest to print blue colored letters
    REQUIRE_NOTHROW(mtl::console::print(doctest::Color::Cyan));
    REQUIRE_NOTHROW(mtl::console::print("[doctest]"));
    // stop using blue colored letters
    REQUIRE_NOTHROW(mtl::console::print(doctest::Color::None)); 
    REQUIRE_NOTHROW(mtl::console::println(" run with \"--help\" for options"));
}
