// tests by Michael Trikergiotis
// 02/06/2020
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include "doctest_include.hpp" 
#include <string>
#include <vector>
#include <list>
#include <filesystem> // std::filesystem::is_regular_file, std::filesystem::remove
                      // std::filesystem::file_size


// Disable some of the asserts in mtl so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS

// THE TESTED HEADER SHOULD BE THE LAST HEADER INCLUDED, EVERYTHING TO BE TESTED SHOULD BE LISTED
// IN THE LINES BELOW THE HEADER
#include "../mtl/filesystem.hpp" 
// mtl::filesystem::read_file, mtl::filesystem::read_all_lines, 
// mtl::filesystem::write_file, mtl::filesystem::write_all_lines


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

// String containing UTF8 text from various languages.
const std::string text1 
(reinterpret_cast<const char*>
(u8"Greek : Χαίρετε, Japanese : こんにちは, Chinese : 你好,           |"));

// String containing UTF8 text from various languages.
const std::string text2 
(reinterpret_cast<const char*>
(u8"Russian : Привет, French : Bonjour, Bulgarian : Здравеите  |"));

// Strings that will be used as a filename conaining UTF8 text from various languages.
const std::string filename_base (reinterpret_cast<const char*>
(u8"_test_file_αρχείο_ファイル_文件_файл"));

const std::string filename1 (std::string("1") + filename_base);

const std::string filename2 (std::string("2") + filename_base);

const std::string filename3 (std::string("3") + filename_base);

const std::string filename4 (std::string("4") + filename_base);

const std::string filename5 (std::string("5") + filename_base);

const std::string filename6 (std::string("6") + filename_base);

const std::string filename7(std::string("7") + filename_base);

const std::string filename8(std::string("8") + filename_base);

// -----------------------------------------------------------------------------
// mtl::filesystem::write_file and mtl::filesystem::read_file
// -----------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_file and mtl::filesystem::read_file with empty file")
{
    std::string filename ("empty_file");

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // empty string
    std::string empty;

    // create an empty file
    bool written_correctly = mtl::filesystem::write_file(filename, empty);

    // check that the file exists and is exactly 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize == 0), true);

    // read the file and check that the read data is 0
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == 0 ), true);



    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}

TEST_CASE("mtl::filesystem::write_file write / append and mtl::filesystem::read_file")
{
    std::string filename = filename1;

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // create the file
    bool written_correctly = mtl::filesystem::write_file(filename, text1);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read file and check contents are what we want
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    std::string correct_data = text1;
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data == correct_data ), true);

    // append the file
    bool appened_correctly = mtl::filesystem::write_file(filename, text2, true);

    // check that the file exists and is more bytes than before
    REQUIRE_EQ(appened_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > filesize), true);

    // read file and check contents are what we want
    read_correctly = mtl::filesystem::read_file(filename, read_data);
    correct_data = text1 + text2;
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data == correct_data ), true);

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}

TEST_CASE("mtl::filesystem::write_file write/append and mtl::filesystem::read_file with newlines")
{
    std::string filename = filename2;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    const std::string text_with_newlines = "Hi \nHi\n Hi \n Hi\n\n Hi \n\n Hi\n\n Hi \n \nHi";
    const std::string text_newlines_two_times = text_with_newlines + text_with_newlines;

    // create the file
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newlines);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read file and check contents are what we want
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    std::string correct_data = text_with_newlines;
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data == correct_data), true);

    // append the file
    bool appened_correctly = mtl::filesystem::write_file(filename, text_with_newlines, true);

    // check that the file exists and is more bytes than before
    REQUIRE_EQ(appened_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > filesize), true);

    // read file and check contents are what we want
    read_correctly = mtl::filesystem::read_file(filename, read_data);
    correct_data = text_newlines_two_times;

    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data == correct_data), true);

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_all_lines and mtl::filesystem::read_all_lines
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::filesystem::write_all_lines and mtl::filesystem::read_all_lines with empty file")
{
    std::string filename ("empty_file_lines");

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // empty std::vector<std::string>
    std::vector<std::string> empty;

    // create an empty file
    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_all_lines(filename, empty.begin(), empty.end());

    // check that the file exists and is exactly 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize == 0), true);

    // read all lines from the file and check that the lines read are 0
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == 0 ), true);



    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}


TEST_CASE("mtl::filesystem::write_all_lines write / append and mtl::filesystem::read_all_lines")
{
    std::string filename = filename3;

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // create the file by writting all lines from the container
    std::vector<std::string> text_data1 {text1, text1, text1, text1, text1};
    bool written_correctly = mtl::filesystem::write_all_lines(filename, text_data1.begin(), 
                                                             text_data1.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == text_data1.size()), true);
    REQUIRE_EQ((read_data == text_data1), true);

        
    // append lines to the file
    bool appened_correctly = mtl::filesystem::write_all_lines(filename, text_data1.begin(), 
                                                              text_data1.end(), true);

    // check that the file exists and is more bytes than before
    REQUIRE_EQ(appened_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > filesize), true);

    // read file and check contents are what we want
    std::vector<std::string> read_data2;
    read_correctly = mtl::filesystem::read_all_lines(filename, read_data2);
    std::vector<std::string> correct_data(text_data1.begin(), text_data1.end());
    correct_data.insert(correct_data.end(), text_data1.begin(), text_data1.end());
    CHECK_EQ(read_correctly, true);
    CHECK_EQ((read_data2.size() == correct_data.size()), true);
    CHECK_EQ((read_data2 == correct_data), true);


    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    CHECK_EQ((std::filesystem::is_regular_file(filename)), false);
}

TEST_CASE("mtl::filesystem::read_all_lines with CRLF input file")
{
    const std::string filename = "file_containing_crlf";

    // if the file exists delete it
    if(std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // create some text that contains CRLF
    const std::string crlf_text = "Hi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi";

    // write the file
    bool written_correctly = mtl::filesystem::write_file(filename, crlf_text);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> desired_result = { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi"};
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    CHECK_EQ((std::filesystem::is_regular_file(filename)), false);
}



TEST_CASE("mtl::filesystem::write_all_lines with integers and mtl::filesystem::read_all_lines")
{
    std::string filename = filename4;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // create the file by writting all number from the container, mtl::filesystem::write_all_lines
    // can accept any type of element that can be converted to std::string by mtl::to_string
    std::vector<int> text_data1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    bool written_correctly = mtl::filesystem::write_all_lines(filename, text_data1.begin(), 
                                                              text_data1.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);


    // read all lines of the file and check contents are what we want
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);

    std::vector<std::string> correct_data{ "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == correct_data.size()), true);
    REQUIRE_EQ((read_data == correct_data), true);


    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    CHECK_EQ((std::filesystem::is_regular_file(filename)), false);
}

TEST_CASE("mtl::filesystem::write_all_lines with floats and mtl::filesystem::read_all_lines")
{
    std::string filename = filename5;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    // create the file by writting all numbers from the container, 
    // mtl::filesystem::write_all_lines can accept any type of element that can be converted to 
    // std::string by mtl::to_string 
    std::vector<float> text_data1 { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f };
    bool written_correctly = mtl::filesystem::write_all_lines(filename, text_data1.begin(), 
                                                              text_data1.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);


    // read all lines of the file and check contents are what we want
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);

    std::vector<std::string> correct_data{ "1.1", "2.2", "3.3", "4.4", "5.5", "6.6", "7.7", "8.8",
                                           "9.9" };

    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == correct_data.size()), true);
    REQUIRE_EQ((read_data == correct_data), true);


    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    CHECK_EQ((std::filesystem::is_regular_file(filename)), false);
}



TEST_CASE("mtl::filesystem::write_all_lines write/append and read_all_lines with newlines")
{
    std::string filename = filename6;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    std::string text_with_newline = "R\nG\nB";
    // create the file by writting all lines from the container
    std::vector<std::string> text_data1{ text_with_newline, text_with_newline };
    bool written_correctly = mtl::filesystem::write_all_lines(filename, text_data1.begin(), 
                                                              text_data1.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    std::vector<std::string> correct_data{ "R", "G", "B", "R", "G", "B", };

    // read all lines of the file and check contents are what we want
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == correct_data.size()), true);
    REQUIRE_EQ((read_data == correct_data), true);

    

    // append lines to the file
    mtl::filesystem::write_all_lines(filename, text_data1.begin(), text_data1.end(), true);

    // check that the file exists and is more bytes than before
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > filesize), true);

    // read file and check contents are what we want
    std::vector<std::string> read_data2;
    read_correctly = mtl::filesystem::read_all_lines(filename, read_data2);
    std::vector<std::string> correct_data_twice(correct_data.begin(), correct_data.end());
    correct_data_twice.insert(correct_data_twice.end(), correct_data.begin(), correct_data.end());
    CHECK_EQ(read_correctly, true);
    CHECK_EQ((read_data2.size() == correct_data_twice.size()), true);
    CHECK_EQ((read_data2 == correct_data_twice), true);


    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    CHECK_EQ((std::filesystem::is_regular_file(filename)), false);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_file with mtl::filesystem::read_all_lines
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_file with mtl::filesystem::read_all_lines")
{
    std::string filename = filename7;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    const std::string text_with_newline = "\nR\nG\nB\nCMYK\n\nR\nG\nB\n\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines;

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };

    REQUIRE_EQ((read_lines.size() > 0), true);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}


// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_all_lines with mtl::filesystem::read_file
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_all_lines with mtl::filesystem::read_file")
{
    std::string filename = filename8;

    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }

    const std::vector<std::string> data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };

    bool written_correctly = mtl::filesystem::write_all_lines(filename, data.begin(), data.end());

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);

    std::string read_line;

    bool read_correctly = mtl::filesystem::read_file(filename, read_line);

    REQUIRE_EQ(read_correctly, true);

    const std::string correct_data = "\nR\nG\nB\nCMYK\n\nR\nG\nB\n\n";

    REQUIRE_EQ((read_line.size() > 0), true);
    REQUIRE_EQ((read_line.size() == correct_data.size()), true);
    REQUIRE_EQ((read_line == correct_data), true);


    // if the file exists delete it
    if (std::filesystem::is_regular_file(filename))
    {
        std::filesystem::remove(filename);
    }
    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), false);
}


TEST_CASE("Try read non-existent file mtl::filesystem::read_file, mtl::filesystem::read_all_lines")
{
    const std::string non_existent = "non-existent-file.txt";

    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(non_existent)), false);

    std::string file_data;
    // trying to read a non-existent file in debug mode with mtl::filesystem::read_file will 
    // result in an assertion, we have disabled the assertion to test it better with the use of 
    // the macro MTL_DISABLE_SOME_ASSERTS, so if the file doesn't exist it will just return false,
    // in your code it is recommended that before you use mtl::filesystem::read_file you check
    // that the file actually exists
    bool read_file = mtl::filesystem::read_file(non_existent, file_data);

    REQUIRE_EQ(file_data.empty(), true);
    REQUIRE_EQ(read_file, false);

    std::vector<std::string> lines;
    // trying to read a non-existent file in debug mode with mtl::filesystem::read_all_lines will 
    // result in an assertion, we have disabled the assertion to test it better with the use of 
    // the macro MTL_DISABLE_SOME_ASSERTS, so if the file doesn't exist it will just return false,
    // in your code it is recommended that before you use mtl::filesystem::read_all_lines you check
    // that the file actually exists
    bool read_lines = mtl::filesystem::read_all_lines(non_existent, lines);

    REQUIRE_EQ(lines.empty(), true);
    REQUIRE_EQ(read_lines, false);

    // make sure the file still doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(non_existent)), false);
}

TEST_CASE("mtl::filesystem::read_all_lines with a single line")
{
    std::string sl_filename = "single-line";
    std::string sl_data = "No newlines can be found in this text.";
    bool write_file = mtl::filesystem::write_file(sl_filename, sl_data);
    REQUIRE_EQ(write_file, true);

    // make sure the file exists
    REQUIRE_EQ((std::filesystem::is_regular_file(sl_filename)), true);

    std::list<std::string> data;
    bool read_lines = mtl::filesystem::read_all_lines(sl_filename, data);
    REQUIRE_EQ(read_lines, true);
    REQUIRE_EQ(data.size(), 1);
    REQUIRE_EQ(data.front(), sl_data);

    // if the file exists delete it
    if (std::filesystem::is_regular_file(sl_filename))
    {
        std::filesystem::remove(sl_filename);
    }
    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(sl_filename)), false);
}


TEST_CASE("Check again to make sure that all files created do not exist")
{
    // we check again for files existing because if a test fails it will not delete it's 
    // associated file
    REQUIRE_EQ((std::filesystem::is_regular_file(filename1)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename2)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename3)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename4)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename5)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename6)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename7)), false);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename8)), false);
    const std::string crlf_file = "file_containing_crlf";
    REQUIRE_EQ((std::filesystem::is_regular_file(crlf_file)), false);
    const std::string empty_file = "empty_file";
    REQUIRE_EQ((std::filesystem::is_regular_file(empty_file)), false);
    const std::string empty_file_lines = "empty_file_lines";
    REQUIRE_EQ((std::filesystem::is_regular_file(empty_file_lines)), false);
    const std::string sl_filename = "single-line";
    REQUIRE_EQ((std::filesystem::is_regular_file(sl_filename)), false);
}