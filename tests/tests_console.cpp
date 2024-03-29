// tests by Michael Trikergiotis
// 31/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <ostream> // std::ostream
#include <vector>  // std::vector
#include <array>   // std::array
#include <list>    // std::list
#include <set>     // std::set
#include <map>     // std::map
#include <numeric> // std::iota


// Disable some asserts so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS


#include "../mtl/console.hpp" 
// mtl::console::print, mtl::console::println, 
// mtl::console::print_all, mtl::console::print_color, mtl::console::println_color,
// mtl::console::overtype, mtl::console::clear


// Create our own class with an overloaded operator<< so we can print it successfully.
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

// Create our own class with an overloaded operator<< that is not a friend function, so we can
// print it successfully.
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

TEST_CASE("mtl::console::print with conversion specifiers, single item")
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

TEST_CASE("mtl::console::print with conversion specifiers, multiple items")
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

TEST_CASE("mtl::console::println with conversion specifiers, single item")
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

TEST_CASE("mtl::console::println with conversion specifiers, multiple items")
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
    for (size_t i = 0; i < size; i++)
    {
        if ((i > 0) && (i % 5 == 0))
        {
            counter = 0;
        }
        counter++;
        vi.at(i) = counter;
    }

    size_t multiplier = 1;
    for (size_t i = 0; i < size; i++)
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
    mtl::console::println("\n------------\n");
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
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all")
{
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end()));
    mtl::console::println("\n------------\n");
}


TEST_CASE("mtl::console::print_all, integers with delimiter")
{ 
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all, doubles with delimiter")
{ 
    std::vector<double> vd { 1.1, 2.2, 3.3, 4.4, 5.5 };
    REQUIRE_NOTHROW(mtl::console::print_all(vd.begin(), vd.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all, std::strings with delimiter")
{ 
    std::vector<std::string> vs { "AA", "BB", "CC" , "DD", "FF" };
    REQUIRE_NOTHROW(mtl::console::print_all(vs.begin(), vs.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all, booleans with delimiter")
{ 
    std::array<bool, 6> ab { true, true, false, false, false, true };
    REQUIRE_NOTHROW(mtl::console::print_all(ab.begin(), ab.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with delimiter using std::array")
{ 
    std::array<int, 5> ai { 11, 22, 33, 44, 55 };
    REQUIRE_NOTHROW(mtl::console::print_all(ai.begin(), ai.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with delimiter using std::list")
{ 
    std::list<int> li { 111, 222, 333, 444, 555 };
    REQUIRE_NOTHROW(mtl::console::print_all(li.begin(), li.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with delimiter using std::set")
{ 
    std::set<int> si { 11, 22, 33, 44, 55, 11, 22, 33, 44, 55, 11, 22, 33, 44, 55 };
    REQUIRE_NOTHROW(mtl::console::print_all(si.begin(), si.end(), ", "));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with delimiter using std::map")
{ 
    std::map<std::string, int> msi { {"AA", 11}, {"BB", 22}, {"CC", 33}, {"DD", 44}, {"EE", 55} };
    REQUIRE_NOTHROW(mtl::console::print_all(msi.begin(), msi.end(), ", "));
    mtl::console::println("\n------------\n");
}



TEST_CASE("mtl::console::print_all with delimiter and newline threshold")
{
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", ", 10));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all without delimiter but with newline threshold")
{
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 10));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with delimiter, newline threshold and line start and finish")
{
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), ", ", 10, "[", "]"));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all without delimiter but with newline threshold and start/finish")
{
    auto vi = generate_numbers();
    // number in increasing order 10, 11, 12, 13, etc...
    std::iota(vi.begin(), vi.end(), 10);
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 10, "[", "]"));
    mtl::console::println("\n------------\n");
}



TEST_CASE("mtl::console::print_all with every option except delimiter, padding none")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::none));

    mtl::console::println("\n------------\n");   
}

TEST_CASE("mtl::console::print_all with every option except delimiter, padding front")
{
    auto vi = generate_numbers();
               
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option except delimiter, padding back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                    mtl::console::print_pad::back));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option except delimiter, padding both_front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                            mtl::console::print_pad::both_front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option except delimiter, padding both_back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "", 5, "[", "]", 
                            mtl::console::print_pad::both_back));
    mtl::console::println("\n------------\n");
}

// --

TEST_CASE("mtl::console::print_all with every option, padding none")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::none));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding back")
{
    auto vi = generate_numbers();

    REQUIRE_NOTHROW(mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                    mtl::console::print_pad::back));

    mtl::console::println("\n------------\n");

}

TEST_CASE("mtl::console::print_all with every option, padding both_front")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                            mtl::console::print_pad::both_front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding both_back")
{
    auto vi = generate_numbers();
                
    REQUIRE_NOTHROW(
    mtl::console::print_all(vi.begin(), vi.end(), "][", 5, "[", "]", 
                            mtl::console::print_pad::both_back));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding both_front with char")
{
    std::vector<char> vc { 'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E',  
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E' };
    REQUIRE_NOTHROW(mtl::console::print_all(vc.begin(), vc.end(), ")><(", 5, "<(", ")>", 
                    mtl::console::print_pad::both_front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding both_back with char")
{
    std::vector<char> vc { 'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E', 
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E',  
                           'a', 'b', 'c', 'd', 'e', 'A', 'B', 'C', 'D', 'E' };
    REQUIRE_NOTHROW(mtl::console::print_all(vc.begin(), vc.end(), ")><(", 5, "<(", ")>", 
                    mtl::console::print_pad::both_back));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding both_front with string")
{
    std::vector<std::string> vs { 
    "a", "b", "c", "d", "e", "A", "B", "C", "D", "E", 
    "aaa", "bbb", "ccc", "ddd", "eee", "AAA", "BBB", "CCC", "DDD", "EEE", 
    "aaaaa", "bbbbb", "ccccc", "ddddd", "eeeee", "AAAAA", "BBBBB", "CCCCC", "DDDDD", "EEEEE", 
    };
    REQUIRE_NOTHROW(mtl::console::print_all(vs.begin(), vs.end(), ")>|<(", 10, "<(", ")>", 
                    mtl::console::print_pad::both_front));
    mtl::console::println("\n------------\n");
}

TEST_CASE("mtl::console::print_all with every option, padding both_back with string")
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

TEST_CASE("mtl::console::print_all with conversion specifiers")
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


TEST_CASE("mtl::console::print_color with no arguments passed")
{
    REQUIRE_NOTHROW(mtl::console::println("No arguments :"));

    int i = 111;
    REQUIRE_NOTHROW(mtl::console::print_color(i));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::print_color(d));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    const char c = 'c';
    REQUIRE_NOTHROW(mtl::console::print_color(c));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    const char* cs_empty = "";
    REQUIRE_NOTHROW(mtl::console::print_color(cs_empty));
    const char* cs = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(cs));
    REQUIRE_NOTHROW(mtl::console::print_color(", "));
    std::string s = "Hello world";
    REQUIRE_NOTHROW(mtl::console::print_color(s));
    REQUIRE_NOTHROW(mtl::console::println());
    std::string str_newlines = "Some text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::print_color(str_newlines));
    const char* cs_newlines = "Some more text\nwith\nnewlines\nin it.\n";
    REQUIRE_NOTHROW(mtl::console::print_color(cs_newlines));
    std::string text_nocolor = "Some noncolored text on this line.";
    REQUIRE_NOTHROW(mtl::console::println(text_nocolor));

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::print_color with one argument, all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
        REQUIRE_NOTHROW(mtl::console::print("One argument, foreground :"));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
        REQUIRE_NOTHROW(mtl::console::println(" : "));
        auto current_color = all_colors.at(x);

        int i = 111;
        REQUIRE_NOTHROW(mtl::console::print_color(i, current_color));
        REQUIRE_NOTHROW(mtl::console::print_color(", ", current_color));
        double d = 333.333;
        REQUIRE_NOTHROW(mtl::console::print_color(d, current_color));
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
        
        REQUIRE_NOTHROW(mtl::console::println("\n\n"));
    }
}

TEST_CASE("mtl::console::print_color with two arguments, all colors with all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
    for (size_t y = 0; y < all_colors.size(); y++)
    {    
    REQUIRE_NOTHROW(mtl::console::print("Two arguments, foreground :"));
    REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
    REQUIRE_NOTHROW(mtl::console::print(", background :"));
    REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(y)));
    REQUIRE_NOTHROW(mtl::console::println(" : "));
    auto foreground_color = all_colors.at(x);
    auto background_color = all_colors.at(y);

    int i = 111;
    REQUIRE_NOTHROW(mtl::console::print_color(i, foreground_color, background_color));
    REQUIRE_NOTHROW(mtl::console::print_color(", ", foreground_color, background_color));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::print_color(d, foreground_color, background_color));
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

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    }
    }
}



TEST_CASE("mtl::console::print_color with an argument that contains LF")
{
    const char* cs_newline = "\n";
    const std::string string_newline (cs_newline);
    
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(cs_newline, mtl::console::color::blue, 
                                                          mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_newline, mtl::console::color::blue, 
                                                              mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("text\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_1, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\ntext");   
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_2, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_3 ("text\ntext");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_3, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_4 ("\ntext\ntext\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_4, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\n1\n2\n3\n4\n5\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(multiple, mtl::console::color::green, 
                                                        mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::print_color with an argument that contains CRLF")
{
    const char* cs_newline = "\r\n";
    const std::string string_newline (cs_newline);
    
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(cs_newline, mtl::console::color::blue, 
                                                          mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_newline, mtl::console::color::blue, 
                                                              mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("text\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_1, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\r\ntext");   
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_2, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_3 ("text\r\ntext");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_3, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_4 ("\r\ntext\r\ntext\r\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_4, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\r\n1\r\n2\r\n3\r\n4\r\n5\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(multiple, mtl::console::color::green, 
                                                        mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::print_color with an argument that contains mixed LF and CRLF")
{
    const char* cs_newline = "\n\r\n\n";
    const std::string string_newline (cs_newline);

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(cs_newline, mtl::console::color::blue, 
                                                          mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_newline, mtl::console::color::blue, 
                                                              mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("\ntext\r\ntext\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_1, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\r\ntext\ntext\r\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(string_text_2, mtl::console::color::blue, 
                                                             mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\n1\r\n2\n3\n4\n5\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(multiple, mtl::console::color::green, 
                                                        mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}



TEST_CASE("mtl::console::print_color with char")
{
    char c = 'a';
    const char cc = 'b';
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(c, mtl::console::color::green,
                                                 mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(cc, mtl::console::color::green,
                                                  mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color('c', mtl::console::color::green,
                                                   mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::println("\n"));
}


TEST_CASE("mtl::console::print_color with char that is a newline")
{
    char c_newline = '\n';
    const char cc_newline = '\n';
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(c_newline, mtl::console::color::green,
                                                         mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color(cc_newline, mtl::console::color::green,
                                                          mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::print_color('\n', mtl::console::color::green,
                                                    mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    REQUIRE_NOTHROW(mtl::console::println("-------------------------\n\n"));
}


// ------------------------------------------------------------------------------------------------
// mtl::console::println_color
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::console::println_color with no arguments passed")
{
    REQUIRE_NOTHROW(mtl::console::println("No arguments :"));

    int i = 111;
    REQUIRE_NOTHROW(mtl::console::println_color(i));
    double d = 333.333;
    REQUIRE_NOTHROW(mtl::console::println_color(d));
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

    
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::println_color with one argument, all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
        REQUIRE_NOTHROW(mtl::console::print("One argument, foreground :"));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
        REQUIRE_NOTHROW(mtl::console::println(" : "));
        auto current_color = all_colors.at(x);
        

        int i = 111;
        REQUIRE_NOTHROW(mtl::console::println_color(i, current_color));
        double d = 333.333;
        REQUIRE_NOTHROW(mtl::console::println_color(d, current_color));
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

        REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    }
}

TEST_CASE("mtl::console::println_color with two arguments, all colors with all colors")
{
    for (size_t x = 0; x < all_colors.size(); x++)
    {
        for (size_t y = 0; y < all_colors.size(); y++)
        {
        REQUIRE_NOTHROW(mtl::console::print("Two arguments, foreground :"));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(x)));
        REQUIRE_NOTHROW(mtl::console::print(", background :"));
        REQUIRE_NOTHROW(mtl::console::print(all_colors_names.at(y)));
        REQUIRE_NOTHROW(mtl::console::println(" : "));
        auto foreground_color = all_colors.at(x);
        auto background_color = all_colors.at(y);

        int i = 111;
        REQUIRE_NOTHROW(mtl::console::println_color(i, foreground_color, background_color));
        double d = 333.333;
        REQUIRE_NOTHROW(mtl::console::println_color(d, foreground_color, background_color));
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

        REQUIRE_NOTHROW(mtl::console::println("\n\n"));
        }
    }
}



TEST_CASE("mtl::console::println_color with an argument that contains LF")
{
    const char* cs_newline = "\n";
    const std::string string_newline (cs_newline);
    
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(cs_newline, mtl::console::color::blue, 
                                                            mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_newline, mtl::console::color::blue, 
                                                                mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("text\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_1, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\ntext");   
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_2, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_3 ("text\ntext");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_3, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_4 ("\ntext\ntext\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_4, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\n1\n2\n3\n4\n5\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(multiple, mtl::console::color::green, 
                                                          mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::println_color with an argument that contains CRLF")
{
    const char* cs_newline = "\r\n";
    const std::string string_newline (cs_newline);
    
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(cs_newline, mtl::console::color::blue, 
                                                            mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_newline, mtl::console::color::blue, 
                                                                mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("text\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_1, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\r\ntext");   
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_2, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_3 ("text\r\ntext");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_3, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_4 ("\r\ntext\r\ntext\r\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_4, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\r\n1\r\n2\r\n3\r\n4\r\n5\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(multiple, mtl::console::color::green, 
                                                          mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::println_color with an argument that contains mixed LF and CRLF")
{
    const char* cs_newline = "\n\r\n\n";
    const std::string string_newline (cs_newline);

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(cs_newline, mtl::console::color::blue, 
                                                            mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_newline, mtl::console::color::blue, 
                                                                mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    const std::string string_text_1 ("\ntext\r\ntext\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_1, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    const std::string string_text_2 ("\r\ntext\ntext\r\n"); 
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(string_text_2, mtl::console::color::blue, 
                                                               mtl::console::color::yellow));
    REQUIRE_NOTHROW(mtl::console::println("]"));
    REQUIRE_NOTHROW(mtl::console::println());

    const std::string multiple("\n1\r\n2\n3\n4\n5\r\n");
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(multiple, mtl::console::color::green, 
                                                          mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));


    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::println_color with char")
{
    char c = 'a';
    const char cc = 'b';
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(c, mtl::console::color::green,
                                                   mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(cc, mtl::console::color::green,
                                                    mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color('c', mtl::console::color::green,
                                                     mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::print("]"));

    REQUIRE_NOTHROW(mtl::console::println("\n"));
}


TEST_CASE("mtl::console::println_color with char that is a newline")
{
    char c_newline = '\n';
    const char cc_newline = '\n';
    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(c_newline, mtl::console::color::green,
                                                           mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color(cc_newline, mtl::console::color::green,
                                                            mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::print("["));
    REQUIRE_NOTHROW(mtl::console::println_color('\n', mtl::console::color::green,
                                                      mtl::console::color::red));
    REQUIRE_NOTHROW(mtl::console::println("]"));

    REQUIRE_NOTHROW(mtl::console::println("\n\n"));

    REQUIRE_NOTHROW(mtl::console::println("-------------------------\n\n"));
}




// ------------------------------------------------------------------------------------------------
// mtl::console::overtype
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::console::overtype with empty original and empty replacement, std::string")
{
    const std::string original = "";
    const std::string replacement = "";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty original, std::string")
{
    const std::string original = "";
    const std::string replacement = "DDEE";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with empty replacment, std::string")
{
    const std::string original = "AABBCC";
    const std::string replacement = "";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original and replacement being one char long, std::string")
{
    const std::string original = "z";
    const std::string replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with original being one char long, std::string")
{
    const std::string original = "z";
    const std::string replacement = "xxx";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with replacement being one char long, std::string")
{
    const std::string original = "zzz";
    const std::string replacement = "x";
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with equal length original and replacement, std::string")
{
    const std::string original = "AABBCC";
    const std::string replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with smaller original than replacement, std::string")
{
    const std::string original = "ABC";
    const std::string replacement = "DDEEFF";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype with bigger original than replacement, std::string")
{
    const std::string original = "AABBCC";
    const std::string replacement = "EE";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print (original));
    REQUIRE_NOTHROW(mtl::console::overtype(replacement));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype multiple times, std::string")
{
    const std::string original = "ABC";
    const std::string replacement = "Multiple numbers from 0 to 9, one at a time";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    for (int i = 0; i < 10; i++)
    {
        std::string counter = std::to_string(i);
        REQUIRE_NOTHROW(mtl::console::overtype(counter));
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}

TEST_CASE("mtl::console::overtype, how updating a progress bar would look like, std::string")
{
    const std::string original    = "[            0%]";
    const std::string replacement = "[==========100%]";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The string to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
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

        // at this point, there would be some long-running operation and overtype would
        // simulate the effect of a progress bar filling by overtyping spaces

        mtl::console::overtype(counter);
        
    }
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}




TEST_CASE("mtl::console::overtype with nullptr, const char*")
{
    // this test shouldn't overtype anything because the argument passed is a nullptr
    const std::string original = "Nothing should be changed from this message.";
    const char* cs_nullptr = nullptr;
    REQUIRE_NOTHROW(mtl::console::print("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The const char* to overtype : \n[]\n"));
    REQUIRE_NOTHROW(mtl::console::print("The result             : \n"));
    REQUIRE_NOTHROW(mtl::console::print(original));
    REQUIRE_NOTHROW(mtl::console::overtype(cs_nullptr));
    REQUIRE_NOTHROW(mtl::console::println("\n\n"));
}


TEST_CASE("mtl::console::overtype with empty original and empty replacement, const char*")
{
    const std::string original = "";
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
    const std::string original = "";
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
    const std::string original = "AABBCC";
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
    const std::string original = "z";
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
    const std::string original = "z";
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
    const std::string original = "zzz";
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
    const std::string original = "AABBCC";
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
    const std::string original = "ABC";
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
    const std::string original = "AABBCC";
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
    const std::string original = "ABC";
    const std::string replacement = "Multiple numbers from 0 to 9, one at a time";
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

TEST_CASE("mtl::console::overtype, how updating a progress bar would look like, const char*")
{
    const std::string original    = "[            0%]";
    const std::string replacement = "[==========100%]";
    REQUIRE_NOTHROW(mtl::console::print ("The original string    : \n[", original, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The const char* to overtype : \n[", replacement, "]\n"));
    REQUIRE_NOTHROW(mtl::console::print ("The result             : \n"));
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

        // at this point, there would be some long-running operation and overtype would
        // simulate the effect of a progress bar filling by overtyping spaces

        mtl::console::overtype(counter.c_str());
    }


    REQUIRE_NOTHROW(mtl::console::println("\n\n\n\n"));
}





// ------------------------------------------------------------------------------------------------
// print some info
// ------------------------------------------------------------------------------------------------

TEST_CASE("Print that we finished the mtl::console tests.")
{
    mtl::console::print("======================================================================");
    mtl::console::println("=========");

    REQUIRE_NOTHROW(mtl::console::println("[mtl] End of mtl::console tests."));

    mtl::console::print("======================================================================");
    mtl::console::println("=========");


}

TEST_CASE("print the newline character in various ways")
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
// print the doctest info
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
