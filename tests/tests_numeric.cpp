// tests by Michael Trikergiotis
// 02/06/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <string>     // std::string
#include <vector>     // std::vector
#include <list>       // std::list
#include <numeric>    // std::iota
#include <algorithm>  // std::sort
#include <functional> // std::hash, std::equal_to

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/numeric.hpp" 
// mtl::iota, mtl::frequency, mtl::mean, mtl::median 



// -----------------------------------------------------------------------------
// mtl::iota
// -----------------------------------------------------------------------------

TEST_CASE("mtl::iota with std::vector<int>")
{
    // mtl::iota with no parameters
    std::vector<int> zero_four{ 0, 1, 2, 3, 4 };
    std::vector<int> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::vector<int> five_nine {5, 6, 7, 8, 9};
    std::vector<int> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::vector<int> nfive_nnine{ -5, -4, -3, -2, -1 };
    std::vector<int> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::vector<int> five_fortyfive{ 5, 15, 25, 35, 45 };
    std::vector<int> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5, 10);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::vector<int> five_nthirtyfive{ 5, -5, -15, -25, -35 };
    std::vector<int> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5, -10);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::vector<int> n_one_fortythree{ -1, 10, 21, 32, 43 };
    std::vector<int> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1, 11);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::vector<int> ntwo_nfortytwo{ -2, -12, -22, -32, -42 };
    std::vector<int> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2, -10);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::vector<int> std_iota_nums(100);
    std::vector<int> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::vector<unsigned int>")
{
    // no tests for negative values for unsigned int because it unsigned integers do not support
    // negatie values

    // mtl::iota with no parameters
    std::vector<unsigned int> zero_four{ 0, 1, 2, 3, 4 };
    std::vector<unsigned int> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::vector<unsigned int> five_nine{ 5, 6, 7, 8, 9 };
    std::vector<unsigned int> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with two parameters, positive start and positive step value
    std::vector<unsigned int> five_fortyfive{ 5, 15, 25, 35, 45 };
    std::vector<unsigned int> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5, 10);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::vector<unsigned int> std_iota_nums(100);
    std::vector<unsigned int> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::vector<float>")
{
    // mtl::iota with no parameters
    std::vector<float> zero_four{ 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };
    std::vector<float> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::vector<float> five_nine{ 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    std::vector<float> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0f);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::vector<float> nfive_nnine{ -5.0f, -4.0f, -3.0f, -2.0f, -1.0f };
    std::vector<float> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0f);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::vector<float> five_fortyfive{ 5.0f, 15.0f, 25.0f, 35.0f, 45.0f };
    std::vector<float> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0f, 10.0f);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::vector<float> five_nthirtyfive{ 5.0f, -5.0f, -15.0f, -25.0f, -35.0f };
    std::vector<float> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0f, -10.0f);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::vector<float> n_one_fortythree{ -1.0f, 10.0f, 21.0f, 32.0f, 43.0f };
    std::vector<float> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0f, 11.0f);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::vector<float> ntwo_nfortytwo{ -2.0f, -12.0f, -22.0f, -32.0f, -42.0f };
    std::vector<float> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0f, -10.0f);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::vector<float> std_iota_nums(100);
    std::vector<float> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0f);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0f);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::vector<double>")
{
    // mtl::iota with no parameters
    std::vector<double> zero_four{ 0.0, 1.0, 2.0, 3.0, 4.0 };
    std::vector<double> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::vector<double> five_nine{ 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::vector<double> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::vector<double> nfive_nnine{ -5.0, -4.0, -3.0, -2.0, -1.0 };
    std::vector<double> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::vector<double> five_fortyfive{ 5.0, 15.0, 25.0, 35.0, 45.0 };
    std::vector<double> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0, 10.0);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::vector<double> five_nthirtyfive{ 5.0, -5.0, -15.0, -25.0, -35.0 };
    std::vector<double> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0, -10.0);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::vector<double> n_one_fortythree{ -1.0, 10.0, 21.0, 32.0, 43.0 };
    std::vector<double> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0, 11.0);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::vector<double> ntwo_nfortytwo{ -2.0, -12.0, -22.0, -32.0, -42.0 };
    std::vector<double> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0, -10.0);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::vector<double> std_iota_nums(100);
    std::vector<double> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::vector<long double>")
{
    // mtl::iota with no parameters
    std::vector<long double> zero_four{ 0.0l, 1.0l, 2.0l, 3.0l, 4.0l };
    std::vector<long double> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::vector<long double> five_nine{ 5.0l, 6.0l, 7.0l, 8.0l, 9.0l };
    std::vector<long double> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0l);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::vector<long double> nfive_nnine{ -5.0l, -4.0l, -3.0l, -2.0l, -1.0l };
    std::vector<long double> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0l);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::vector<long double> five_fortyfive{ 5.0l, 15.0l, 25.0l, 35.0l, 45.0l };
    std::vector<long double> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0l, 10.0l);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::vector<long double> five_nthirtyfive{ 5.0l, -5.0l, -15.0l, -25.0l, -35.0l };
    std::vector<long double> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0l, -10.0l);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::vector<long double> n_one_fortythree{ -1.0l, 10.0l, 21.0l, 32.0l, 43.0l };
    std::vector<long double> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0l, 11.0l);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::vector<long double> ntwo_nfortytwo{ -2.0l, -12.0l, -22.0l, -32.0l, -42.0l };
    std::vector<long double> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0l, -10.0l);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::vector<long double> std_iota_nums(100);
    std::vector<long double> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0l);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0l);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::list<int>")
{
    // mtl::iota with no parameters
    std::list<int> zero_four{ 0, 1, 2, 3, 4 };
    std::list<int> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::list<int> five_nine{ 5, 6, 7, 8, 9 };
    std::list<int> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::list<int> nfive_nnine{ -5, -4, -3, -2, -1 };
    std::list<int> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::list<int> five_fortyfive{ 5, 15, 25, 35, 45 };
    std::list<int> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5, 10);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::list<int> five_nthirtyfive{ 5, -5, -15, -25, -35 };
    std::list<int> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5, -10);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::list<int> n_one_fortythree{ -1, 10, 21, 32, 43 };
    std::list<int> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1, 11);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::list<int> ntwo_nfortytwo{ -2, -12, -22, -32, -42 };
    std::list<int> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2, -10);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::list<int> std_iota_nums(100);
    std::list<int> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::list<unsigned int>")
{
    // no tests for negative values for unsigned int because it unsigned integers do not support
    // negatie values

    // mtl::iota with no parameters
    std::list<unsigned int> zero_four{ 0, 1, 2, 3, 4 };
    std::list<unsigned int> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::list<unsigned int> five_nine{ 5, 6, 7, 8, 9 };
    std::list<unsigned int> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with two parameters, positive start and positive step value
    std::list<unsigned int> five_fortyfive{ 5, 15, 25, 35, 45 };
    std::list<unsigned int> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5, 10);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::list<unsigned int> std_iota_nums(100);
    std::list<unsigned int> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::list<float>")
{
    // mtl::iota with no parameters
    std::list<float> zero_four{ 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };
    std::list<float> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::list<float> five_nine{ 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    std::list<float> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0f);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::list<float> nfive_nnine{ -5.0f, -4.0f, -3.0f, -2.0f, -1.0f };
    std::list<float> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0f);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::list<float> five_fortyfive{ 5.0f, 15.0f, 25.0f, 35.0f, 45.0f };
    std::list<float> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0f, 10.0f);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::list<float> five_nthirtyfive{ 5.0f, -5.0f, -15.0f, -25.0f, -35.0f };
    std::list<float> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0f, -10.0f);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::list<float> n_one_fortythree{ -1.0f, 10.0f, 21.0f, 32.0f, 43.0f };
    std::list<float> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0f, 11.0f);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::list<float> ntwo_nfortytwo{ -2.0f, -12.0f, -22.0f, -32.0f, -42.0f };
    std::list<float> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0f, -10.0f);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::list<float> std_iota_nums(100);
    std::list<float> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0f);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0f);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::list<double>")
{
    // mtl::iota with no parameters
    std::list<double> zero_four{ 0.0, 1.0, 2.0, 3.0, 4.0 };
    std::list<double> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::list<double> five_nine{ 5.0, 6.0, 7.0, 8.0, 9.0 };
    std::list<double> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::list<double> nfive_nnine{ -5.0, -4.0, -3.0, -2.0, -1.0 };
    std::list<double> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::list<double> five_fortyfive{ 5.0, 15.0, 25.0, 35.0, 45.0 };
    std::list<double> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0, 10.0);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::list<double> five_nthirtyfive{ 5.0, -5.0, -15.0, -25.0, -35.0 };
    std::list<double> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0, -10.0);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::list<double> n_one_fortythree{ -1.0, 10.0, 21.0, 32.0, 43.0 };
    std::list<double> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0, 11.0);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::list<double> ntwo_nfortytwo{ -2.0, -12.0, -22.0, -32.0, -42.0 };
    std::list<double> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0, -10.0);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::list<double> std_iota_nums(100);
    std::list<double> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

TEST_CASE("mtl::iota with std::list<long double>")
{
    // mtl::iota with no parameters
    std::list<long double> zero_four{ 0.0l, 1.0l, 2.0l, 3.0l, 4.0l };
    std::list<long double> no_param(5);
    mtl::iota(no_param.begin(), no_param.end());
    REQUIRE_EQ((zero_four == no_param), true);


    // mtl::iota with one parameter, positive start
    std::list<long double> five_nine{ 5.0l, 6.0l, 7.0l, 8.0l, 9.0l };
    std::list<long double> iota_nums(5);
    mtl::iota(iota_nums.begin(), iota_nums.end(), 5.0l);
    REQUIRE_EQ((five_nine == iota_nums), true);

    // mtl::iota with one parameter, negative start
    std::list<long double> nfive_nnine{ -5.0l, -4.0l, -3.0l, -2.0l, -1.0l };
    std::list<long double> iota_neg_nums(5);
    mtl::iota(iota_neg_nums.begin(), iota_neg_nums.end(), -5.0l);
    REQUIRE_EQ((nfive_nnine == iota_neg_nums), true);


    // mtl::iota with two parameters, positive start and positive step value
    std::list<long double> five_fortyfive{ 5.0l, 15.0l, 25.0l, 35.0l, 45.0l };
    std::list<long double> iota_positive_nums(5);
    mtl::iota(iota_positive_nums.begin(), iota_positive_nums.end(), 5.0l, 10.0l);
    REQUIRE_EQ((five_fortyfive == iota_positive_nums), true);

    // mtl::iota with two parameters, positive start and negative step value
    std::list<long double> five_nthirtyfive{ 5.0l, -5.0l, -15.0l, -25.0l, -35.0l };
    std::list<long double> iota_posneg_nums(5);
    mtl::iota(iota_posneg_nums.begin(), iota_posneg_nums.end(), 5.0l, -10.0l);
    REQUIRE_EQ((five_nthirtyfive == iota_posneg_nums), true);

    // mtl::iota with two parameters, negative start and positive step value
    std::list<long double> n_one_fortythree{ -1.0l, 10.0l, 21.0l, 32.0l, 43.0l };
    std::list<long double> iota_negpos_nums(5);
    mtl::iota(iota_negpos_nums.begin(), iota_negpos_nums.end(), -1.0l, 11.0l);
    REQUIRE_EQ((n_one_fortythree == iota_negpos_nums), true);

    // mtl::iota with two parameters, negative start and negative step value
    std::list<long double> ntwo_nfortytwo{ -2.0l, -12.0l, -22.0l, -32.0l, -42.0l };
    std::list<long double> iota_negneg_nums(5);
    mtl::iota(iota_negneg_nums.begin(), iota_negneg_nums.end(), -2.0l, -10.0l);
    REQUIRE_EQ((ntwo_nfortytwo == iota_negneg_nums), true);


    // check that std::iota and mtl::iota produce the same results
    std::list<long double> std_iota_nums(100);
    std::list<long double> mtl_iota_nums(100);
    std::iota(std_iota_nums.begin(), std_iota_nums.end(), 10.0l);
    mtl::iota(mtl_iota_nums.begin(), mtl_iota_nums.end(), 10.0l);
    REQUIRE_EQ((std_iota_nums == mtl_iota_nums), true);
}

// -----------------------------------------------------------------------------
// mtl::frequency
// -----------------------------------------------------------------------------

TEST_CASE("mtl::frequency with empty std::vector<int>")
{
    std::vector<int> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}


TEST_CASE("mtl::frequency with std::vector<int>")
{
    std::vector<int> numbers{ 1, 3, 3, 3, 5, 5, 5, 5, 5, 4, 4, 4, 4, 2, 2 };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq[1] == 1), true);
    REQUIRE_EQ((freq[2] == 2), true);
    REQUIRE_EQ((freq[3] == 3), true);
    REQUIRE_EQ((freq[4] == 4), true);
    REQUIRE_EQ((freq[5] == 5), true);
}

TEST_CASE("mtl::frequency with std::vector<int> with parameters")
{
    std::vector<int> n{ 1, 3, 3, 3, 5, 5, 5, 5, 5, 4, 4, 4, 4, 2, 2 };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<int>{}, std::equal_to<int>{});
    REQUIRE_EQ((freq[1] == 1), true);
    REQUIRE_EQ((freq[2] == 2), true);
    REQUIRE_EQ((freq[3] == 3), true);
    REQUIRE_EQ((freq[4] == 4), true);
    REQUIRE_EQ((freq[5] == 5), true);
}

TEST_CASE("mtl::frequency with empty std::vector<double>")
{
    std::vector<double> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}

TEST_CASE("mtl::frequency with std::vector<double>")
{
    std::vector<double> numbers{ 1.0, 3.0, 3.0, 3.0, 5.0, 5.0, 5.0, 5.0, 5.0, 4.0, 4.0, 4.0, 4.0,
                                 2.0, 2.0 };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq[1.0] == 1), true);
    REQUIRE_EQ((freq[2.0] == 2), true);
    REQUIRE_EQ((freq[3.0] == 3), true);
    REQUIRE_EQ((freq[4.0] == 4), true);
    REQUIRE_EQ((freq[5.0] == 5), true);
}

TEST_CASE("mtl::frequency with std::vector<double> with parameters")
{
    std::vector<double> n{ 1.0, 3.0, 3.0, 3.0, 5.0, 5.0, 5.0, 5.0, 5.0, 4.0, 4.0, 4.0, 4.0, 2.0,
                           2.0 };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<double>{}, std::equal_to<double>{});
    REQUIRE_EQ((freq[1.0] == 1), true);
    REQUIRE_EQ((freq[2.0] == 2), true);
    REQUIRE_EQ((freq[3.0] == 3), true);
    REQUIRE_EQ((freq[4.0] == 4), true);
    REQUIRE_EQ((freq[5.0] == 5), true);
}

TEST_CASE("mtl::frequency with empty std::vector<std::string>")
{
    std::vector<std::string> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}

TEST_CASE("mtl::frequency with std::vector<std::string>")
{
    std::vector<std::string> numbers{ "1", "3", "3", "3", "5", "5", "5", "5", "5", "4", "4", "4",
                                      "4", "2", "2" };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq["1"] == 1), true);
    REQUIRE_EQ((freq["2"] == 2), true);
    REQUIRE_EQ((freq["3"] == 3), true);
    REQUIRE_EQ((freq["4"] == 4), true);
    REQUIRE_EQ((freq["5"] == 5), true);
}

TEST_CASE("mtl::frequency with std::vector<std::string> with parameters")
{
    std::vector<std::string> n{ "1", "3", "3", "3", "5", "5", "5", "5", "5", "4", "4", "4", "4",
                                "2", "2" };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<std::string>{},
                               std::equal_to<std::string>{});
    REQUIRE_EQ((freq["1"] == 1), true);
    REQUIRE_EQ((freq["2"] == 2), true);
    REQUIRE_EQ((freq["3"] == 3), true);
    REQUIRE_EQ((freq["4"] == 4), true);
    REQUIRE_EQ((freq["5"] == 5), true);
}

TEST_CASE("mtl::frequency with std::vector<std::string>, names")
{
    std::vector<std::string> numbers{ "Bill", "Bill", "Jill", "Jill", "Jack", "John", "Jill",
                                      "Jill", "Bill", "Jack", "Nick", "Nick", "Nick", "Nick", 
                                      "Nick"};
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq["John"] == 1), true);
    REQUIRE_EQ((freq["Jack"] == 2), true);
    REQUIRE_EQ((freq["Bill"] == 3), true);
    REQUIRE_EQ((freq["Jill"] == 4), true);
    REQUIRE_EQ((freq["Nick"] == 5), true);
}

TEST_CASE("mtl::frequency with empty std::list<int>")
{
    std::list<int> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}

TEST_CASE("mtl::frequency with std::list<int>")
{
    std::list<int> numbers{ 1, 3, 3, 3, 5, 5, 5, 5, 5, 4, 4, 4, 4, 2, 2 };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq[1] == 1), true);
    REQUIRE_EQ((freq[2] == 2), true);
    REQUIRE_EQ((freq[3] == 3), true);
    REQUIRE_EQ((freq[4] == 4), true);
    REQUIRE_EQ((freq[5] == 5), true);
}

TEST_CASE("mtl::frequency with std::list<int> with parameters")
{
    std::list<int> n{ 1, 3, 3, 3, 5, 5, 5, 5, 5, 4, 4, 4, 4, 2, 2 };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<int>{}, std::equal_to<int>{});
    REQUIRE_EQ((freq[1] == 1), true);
    REQUIRE_EQ((freq[2] == 2), true);
    REQUIRE_EQ((freq[3] == 3), true);
    REQUIRE_EQ((freq[4] == 4), true);
    REQUIRE_EQ((freq[5] == 5), true);
}

TEST_CASE("mtl::frequency with empty std::list<double>")
{
    std::list<double> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}

TEST_CASE("mtl::frequency with std::list<double>")
{
    std::list<double> numbers{ 1.0, 3.0, 3.0, 3.0, 5.0, 5.0, 5.0, 5.0, 5.0, 4.0, 4.0, 4.0, 4.0,
                                 2.0, 2.0 };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq[1.0] == 1), true);
    REQUIRE_EQ((freq[2.0] == 2), true);
    REQUIRE_EQ((freq[3.0] == 3), true);
    REQUIRE_EQ((freq[4.0] == 4), true);
    REQUIRE_EQ((freq[5.0] == 5), true);
}

TEST_CASE("mtl::frequency with std::list<double> with parameters")
{
    std::list<double> n{ 1.0, 3.0, 3.0, 3.0, 5.0, 5.0, 5.0, 5.0, 5.0, 4.0, 4.0, 4.0, 4.0, 2.0,
                           2.0 };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<double>{}, std::equal_to<double>{});
    REQUIRE_EQ((freq[1.0] == 1), true);
    REQUIRE_EQ((freq[2.0] == 2), true);
    REQUIRE_EQ((freq[3.0] == 3), true);
    REQUIRE_EQ((freq[4.0] == 4), true);
    REQUIRE_EQ((freq[5.0] == 5), true);
}

TEST_CASE("mtl::frequency with empty std::list<std::string>")
{
    std::list<std::string> numbers;
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ(numbers.empty(), true);
    REQUIRE_EQ(freq.empty(), true);
}

TEST_CASE("mtl::frequency with std::list<std::string>")
{
    std::list<std::string> numbers{ "1", "3", "3", "3", "5", "5", "5", "5", "5", "4", "4", "4",
                                      "4", "2", "2" };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq["1"] == 1), true);
    REQUIRE_EQ((freq["2"] == 2), true);
    REQUIRE_EQ((freq["3"] == 3), true);
    REQUIRE_EQ((freq["4"] == 4), true);
    REQUIRE_EQ((freq["5"] == 5), true);
}

TEST_CASE("mtl::frequency with std::list<std::string> with parameters")
{
    std::list<std::string> n{ "1", "3", "3", "3", "5", "5", "5", "5", "5", "4", "4", "4", "4",
                                "2", "2" };
    auto freq = mtl::frequency(n.begin(), n.end(), std::hash<std::string>{},
                               std::equal_to<std::string>{});
    REQUIRE_EQ((freq["1"] == 1), true);
    REQUIRE_EQ((freq["2"] == 2), true);
    REQUIRE_EQ((freq["3"] == 3), true);
    REQUIRE_EQ((freq["4"] == 4), true);
    REQUIRE_EQ((freq["5"] == 5), true);
}

TEST_CASE("mtl::frequency with std::list<std::string>, names")
{
    std::list<std::string> numbers{ "Bill", "Bill", "Jill", "Jill", "Jack", "John", "Jill",
                                      "Jill", "Bill", "Jack", "Nick", "Nick", "Nick", "Nick",
                                      "Nick" };
    auto freq = mtl::frequency(numbers.begin(), numbers.end());
    REQUIRE_EQ((freq["John"] == 1), true);
    REQUIRE_EQ((freq["Jack"] == 2), true);
    REQUIRE_EQ((freq["Bill"] == 3), true);
    REQUIRE_EQ((freq["Jill"] == 4), true);
    REQUIRE_EQ((freq["Nick"] == 5), true);
}

// -----------------------------------------------------------------------------
// mtl::mean
// -----------------------------------------------------------------------------

TEST_CASE("mtl::mean with empty std::vector<int>")
{
    std::vector<int> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with std::vector<int>, positive values")
{
    std::vector<int> vi {10, 20, 30, 40, 50};
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 30);
}

TEST_CASE("mtl::mean with std::vector<int>, negative values")
{
    std::vector<int> vi{ -10, -20, -30, -40, -50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, -30);
}

TEST_CASE("mtl::mean with std::vector<int>, mixed positive and negative values")
{
    std::vector<int> vi{ -10, -110, 30, 40, 50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with empty std::vector<unsigned int>")
{
    std::vector<unsigned int> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with std::vector<unsigned int>")
{
    std::vector<unsigned int> vi{ 10, 20, 30, 40, 50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 30);
}

TEST_CASE("mtl::mean with empty std::vector<float>")
{
    std::vector<float> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01F));
    REQUIRE_GT(result, (-0.01F)); 
}

TEST_CASE("mtl::mean with std::vector<float>, positive values")
{
    std::vector<float> vi {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = 30.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));  
}

TEST_CASE("mtl::mean with std::vector<float>, negative values")
{
    std::vector<float> vi{ -10.0f, -20.0f, -30.0f, -40.0f, -50.0f };
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = -30.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));
}

TEST_CASE("mtl::mean with std::vector<float>, mixed positive and negative values")
{
    std::vector<float> vi{ -10.0f, -110.0f, 30.0f, 40.0f, 50.0f };
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = 0.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));
}

TEST_CASE("mtl::mean with empty std::vector<double>")
{
    std::vector<double> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01));
    REQUIRE_GT(result, (-0.01)); 
}

TEST_CASE("mtl::mean with std::vector<double>, positive values")
{
    std::vector<double> vi {10.0, 20.0, 30.0, 40.0, 50.0};
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = 30.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));  
}

TEST_CASE("mtl::mean with std::vector<double>, negative values")
{
    std::vector<double> vi{ -10.0, -20.0, -30.0, -40.0, -50.0 };
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = -30.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::mean with std::vector<double>, mixed positive and negative values")
{
    std::vector<double> vi{ -10.0, -110.0, 30.0, 40.0, 50.0 };
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = 0.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::mean with empty std::vector<long double>")
{
    std::vector<long double> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01l));
    REQUIRE_GT(result, (-0.01l)); 
}

TEST_CASE("mtl::mean with std::vector<long double>, positive values")
{
    std::vector<long double> vi{ 10.0l, 20.0l, 30.0l, 40.0l, 50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = 30.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::mean with std::vector<long double>, negative values")
{
    std::vector<long double> vi{ -10.0l, -20.0l, -30.0l, -40.0l, -50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = -30.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::mean with std::vector<long double>, mixed positive and negative values")
{
    std::vector<long double> vi{ -10.0l, -110.0l, 30.0l, 40.0l, 50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = 0.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}



TEST_CASE("mtl::mean with empty std::list<int>")
{
    std::list<int> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with std::list<int>, positive values")
{
    std::list<int> vi{ 10, 20, 30, 40, 50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 30);
}

TEST_CASE("mtl::mean with std::list<int>, negative values")
{
    std::list<int> vi{ -10, -20, -30, -40, -50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, -30);
}

TEST_CASE("mtl::mean with std::list<int>, mixed positive and negative values")
{
    std::list<int> vi{ -10, -110, 30, 40, 50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with empty std::list<unsigned int>")
{
    std::list<unsigned int> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::mean with std::list<unsigned int>")
{
    std::list<unsigned int> vi{ 10, 20, 30, 40, 50 };
    auto result = mtl::mean(vi.begin(), vi.end());
    REQUIRE_EQ(result, 30);
}

TEST_CASE("mtl::mean with empty std::list<float>")
{
    std::list<float> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01F));
    REQUIRE_GT(result, (-0.01F)); 
}

TEST_CASE("mtl::mean with std::list<float>, positive values")
{
    std::list<float> vi{ 10.0f, 20.0f, 30.0f, 40.0f, 50.0f };
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = 30.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));
}

TEST_CASE("mtl::mean with std::list<float>, negative values")
{
    std::list<float> vi{ -10.0f, -20.0f, -30.0f, -40.0f, -50.0f };
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = -30.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));
}

TEST_CASE("mtl::mean with std::list<float>, mixed positive and negative values")
{
    std::list<float> vi{ -10.0f, -110.0f, 30.0f, 40.0f, 50.0f };
    auto result = mtl::mean(vi.begin(), vi.end());
    float value = 0.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01F));
    REQUIRE_GT(result, (value - 0.01F));
}

TEST_CASE("mtl::mean with empty std::list<double>")
{
    std::list<double> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01));
    REQUIRE_GT(result, (-0.01)); 
}

TEST_CASE("mtl::mean with std::list<double>, positive values")
{
    std::list<double> vi{ 10.0, 20.0, 30.0, 40.0, 50.0 };
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = 30.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::mean with std::list<double>, negative values")
{
    std::list<double> vi{ -10.0, -20.0, -30.0, -40.0, -50.0 };
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = -30.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::mean with std::list<double>, mixed positive and negative values")
{
    std::list<double> vi{ -10.0, -110.0, 30.0, 40.0, 50.0 };
    auto result = mtl::mean(vi.begin(), vi.end());
    double value = 0.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::mean with empty std::list<long double>")
{
    std::list<long double> vi;
    auto result = mtl::mean(vi.begin(), vi.end());
    
    // approximate equality
    REQUIRE_LT(result, (0.01l));
    REQUIRE_GT(result, (-0.01l)); 
}

TEST_CASE("mtl::mean with std::list<long double>, positive values")
{
    std::list<long double> vi{ 10.0l, 20.0l, 30.0l, 40.0l, 50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = 30.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::mean with std::list<long double>, negative values")
{
    std::list<long double> vi{ -10.0l, -20.0l, -30.0l, -40.0l, -50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = -30.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::mean with std::list<long double>, mixed positive and negative values")
{
    std::list<long double> vi{ -10.0l, -110.0l, 30.0l, 40.0l, 50.0l };
    auto result = mtl::mean(vi.begin(), vi.end());
    long double value = 0.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}


// -----------------------------------------------------------------------------
// mtl::median
// -----------------------------------------------------------------------------

TEST_CASE("mtl::median with empty std::vector<int>")
{
    std::vector<int> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::median with std::vector<int> with single value")
{
    std::vector<int> numbers{ 1984 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 1984);
}

TEST_CASE("mtl::median with std::vector<int> that has odd number of elements")
{
    std::vector<int> numbers{ 5, 3, 2, 4, 1 };
    // the std::vector has to be sorted to work with mtl::median
    std::sort(numbers.begin(), numbers.end());
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with std::vector<int> that has even number of elements")
{
    std::vector<int> numbers{ 1, 2, 3, 3, 4, 5 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with empty std::vector<unsigned int>")
{
    std::vector<unsigned int> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::median with std::vector<unsigned int> with single value")
{
    std::vector<unsigned int> numbers{ 1984 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 1984);
}

TEST_CASE("mtl::median with std::vector<unsigned int> that has odd number of elements")
{
    std::vector<unsigned int> numbers{ 5, 3, 2, 4, 1 };
    // the std::vector has to be sorted to work with mtl::median
    std::sort(numbers.begin(), numbers.end());
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with std::vector<unsigned int> that has even number of elements")
{
    std::vector<unsigned int> numbers{ 1, 2, 3, 3, 4, 5 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with empty std::vector<float>")
{
    std::vector<float> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 0.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::vector<float> with single value")
{
    float value = 1984.0f;
    std::vector<float> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::vector<float> that has odd number of elements")
{
    std::vector<float> numbers{ 5.0f, 3.0f, 2.0f, 4.0f, 1.0f };
    // the std::vector has to be sorted to work with mtl::median
    std::sort(numbers.begin(), numbers.end());
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 3.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::vector<float> that has even number of elements")
{
    std::vector<float> numbers{ 1.0f, 2.0f, 3.0f, 3.0f, 4.0f, 5.0f };
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 3.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with empty std::vector<double>")
{
    std::vector<double> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    double value = 0.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::vector<double> with single value")
{
    double value = 1984.0;
    std::vector<double> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::vector<double> that has odd number of elements")
{
    std::vector<double> numbers{ 5.0, 3.0, 2.0, 4.0, 1.0 };
    // the std::vector has to be sorted to work with mtl::median
    std::sort(numbers.begin(), numbers.end());
    double result = mtl::median(numbers.begin(), numbers.end());
    double value = 3.0;
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::vector<double> that has even number of elements")
{
    std::vector<double> numbers{ 1.0, 2.0, 3.0, 3.0, 4.0, 5.0 };
    double result = mtl::median(numbers.begin(), numbers.end());
    double value = 3.0;
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with empty std::vector<long double>")
{
    std::vector<long double> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 0.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::vector<long double> with single value")
{
    long double value = 1984.0l;
    std::vector<long double> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::vector<long double> that has odd number of elements")
{
    std::vector<long double> numbers{ 5.0l, 3.0l, 2.0l, 4.0l, 1.0l };
    // the std::vector has to be sorted to work with mtl::median
    std::sort(numbers.begin(), numbers.end());
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 3.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::vector<long double> that has even number of elements")
{
    std::vector<long double> numbers{ 1.0l, 2.0l, 3.0l, 3.0l, 4.0l, 5.0l };
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 3.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}



TEST_CASE("mtl::median with empty std::list<int>")
{
    std::list<int> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::median with std::list<int> with single value")
{
    std::list<int> numbers{ 1984 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 1984);
}

TEST_CASE("mtl::median with std::list<int> that has odd number of elements")
{
    std::list<int> numbers{ 5, 3, 2, 4, 1 };
    // the std::list has to be sorted to work with mtl::median
    numbers.sort();
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with std::list<int> that has even number of elements")
{
    std::list<int> numbers{ 1, 2, 3, 3, 4, 5 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with empty std::list<unsigned int>")
{
    std::list<unsigned int> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 0);
}

TEST_CASE("mtl::median with std::list<unsigned int> with single value")
{
    std::list<unsigned int> numbers{ 1984 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 1984);
}

TEST_CASE("mtl::median with std::list<unsigned int> that has odd number of elements")
{
    std::list<unsigned int> numbers{ 5, 3, 2, 4, 1 };
    // the std::list has to be sorted to work with mtl::median
    numbers.sort();
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with std::list<unsigned int> that has even number of elements")
{
    std::list<unsigned int> numbers{ 1, 2, 3, 3, 4, 5 };
    auto result = mtl::median(numbers.begin(), numbers.end());
    REQUIRE_EQ(result, 3);
}

TEST_CASE("mtl::median with empty std::list<float>")
{
    std::list<float> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 0.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::list<float> with single value")
{
    float value = 1984.0f;
    std::list<float> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::list<float> that has odd number of elements")
{
    std::list<float> numbers{ 5.0f, 3.0f, 2.0f, 4.0f, 1.0f };
    // the std::list has to be sorted to work with mtl::median
    numbers.sort();
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 3.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with std::list<float> that has even number of elements")
{
    std::list<float> numbers{ 1.0f, 2.0f, 3.0f, 3.0f, 4.0f, 5.0f };
    auto result = mtl::median(numbers.begin(), numbers.end());
    float value = 3.0f;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01f));
    REQUIRE_GT(result, (value - 0.01f));
}

TEST_CASE("mtl::median with empty std::list<double>")
{
    std::list<double> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    double value = 0.0;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::list<double> with single value")
{
    double value = 1984.0;
    std::list<double> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::list<double> that has odd number of elements")
{
    std::list<double> numbers{ 5.0, 3.0, 2.0, 4.0, 1.0 };
    // the std::list has to be sorted to work with mtl::median
    numbers.sort();
    double result = mtl::median(numbers.begin(), numbers.end());
    double value = 3.0;
     
    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with std::list<double> that has even number of elements")
{
    std::list<double> numbers{ 1.0, 2.0, 3.0, 3.0, 4.0, 5.0 };
    double result = mtl::median(numbers.begin(), numbers.end());
    double value = 3.0;

    // approximate equality
    REQUIRE_LT(result, (value + 0.01));
    REQUIRE_GT(result, (value - 0.01));
}

TEST_CASE("mtl::median with empty std::list<long double>")
{
    std::list<long double> numbers;
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 0.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::list<long double> with single value")
{
    long double value = 1984.0l;
    std::list<long double> numbers{ value };
    auto result = mtl::median(numbers.begin(), numbers.end());
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::list<long double> that has odd number of elements")
{
    std::list<long double> numbers{ 5.0l, 3.0l, 2.0l, 4.0l, 1.0l };
    // the std::list has to be sorted to work with mtl::median
    numbers.sort();
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 3.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}

TEST_CASE("mtl::median with std::list<long double> that has even number of elements")
{
    std::list<long double> numbers{ 1.0l, 2.0l, 3.0l, 3.0l, 4.0l, 5.0l };
    auto result = mtl::median(numbers.begin(), numbers.end());
    long double value = 3.0l;
    
    // approximate equality
    REQUIRE_LT(result, (value + 0.01l));
    REQUIRE_GT(result, (value - 0.01l));
}
