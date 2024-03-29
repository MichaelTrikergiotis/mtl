﻿// tests by Michael Trikergiotis
// 02/06/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "doctest_include.hpp" 
#include <vector>     // std::vector
#include <list>       // std::list
#include <string>     // std::string, std::to_string
#include <filesystem> // std::filesystem::is_regular_file, std::filesystem::remove
                      // std::filesystem::file_size, std::filesystem::path


// Disable some asserts so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS


#include "../mtl/filesystem.hpp" 
// mtl::filesystem::read_file, mtl::filesystem::read_all_lines, 
// mtl::filesystem::write_file, mtl::filesystem::write_all_lines



// ------------------------------------------------------------------------------------------------
// Create some UTF8 strings to check if the mtl functions can handle UTF8 without errors.
// ------------------------------------------------------------------------------------------------


// We have to use reinterpret_cast<const char*>(u8"utf8_str") so the tests can be compiled for
// both C++ 17 and C++ 20 or later when the gcc and clang flag -fno-char8_t or the
// MSVC /Zc:char8_t- flag is not used. This is because C++ 20 introduced a breaking change,
// u8 string literals are now char8_t type instead of char_t type.
// For more information check :
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1423r3.html#reinterpret_cast
// https://docs.microsoft.com/en-us/cpp/overview/cpp-conformance-improvements?view=vs-2019#char8_t
// https://stackoverflow.com/a/57453713

// String containing UTF8 text from various languages.
const std::string text1 
(reinterpret_cast<const char*>
(u8"Greek : Χαίρετε, Japanese : こんにちは, Chinese : 你好,           |"));

// String containing UTF8 text from various languages.
const std::string text2 
(reinterpret_cast<const char*>
(u8"Russian : Привет, French : Bonjour, Bulgarian : Здравеите  |"));

// Strings that will be used as a filename containing UTF8 text from various languages.
const std::string filename_base (reinterpret_cast<const char*>
(u8"_test_file_αρχείο_ファイル_文件_файл"));



// Generates unique filenames and keeps track of them.
class filename_generator
{
    // Stores the filenames generated for each test case.
    std::vector<std::string>* filenames = nullptr;

    // Set the storage for filenames.
    void set_filenames_storage()
    { 
        static std::vector<std::string> _filenames;
        filenames = &_filenames;
    }

public :
    
    // Generate a different filename for each test case. 
    std::string generate_filename()
    {
        // set the storage for filenames
        set_filenames_storage();

        // create a unique id for each file
        static int filename_id = 0;
        ++filename_id;

        // generate a new name and store it
        std::string filename = std::to_string(filename_id) + filename_base;
        filenames->emplace_back(filename);
        return filename;
    }

    // Retrieve a list of all the filenames.
    std::vector<std::string>* get_filenames()
    {
        set_filenames_storage();
        return filenames;
    }
};




// -----------------------------------------------------------------------------
// mtl::filesystem::write_file
// -----------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_file with empty file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    // empty string
    const std::string empty;

    // create an empty file
    bool written_correctly = mtl::filesystem::write_file(filename, empty);

    // check that the file exists and is exactly 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize == 0), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}



// -----------------------------------------------------------------------------
// mtl::filesystem::read_file
// -----------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::read_file with non-existent file")
{
    filename_generator fname_generator;
    const std::string non_existent = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(non_existent);

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

    // make sure the file still doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(non_existent)), false);

    // delete the file used for this test case
    std::filesystem::remove(non_existent);
}


// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_file and mtl::filesystem::read_file
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_file and mtl::filesystem::read_file with empty file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    // empty string
    const std::string empty;

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
    REQUIRE_EQ(read_data.empty(), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file write / append and mtl::filesystem::read_file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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
    REQUIRE_EQ((read_data == correct_data), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file write / append and mtl::filesystem::read_file with LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file write / append and mtl::filesystem::read_file with CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newlines = "Hi \r\nHi\r\n Hi \r\n Hi\r\n\r\n";
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

    // delete the file used for this test case
    std::filesystem::remove(filename);
}


TEST_CASE("mtl::filesystem::write_file and mtl::filesystem::read_file with mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newlines = "Hi \r\nHi\n Hi \r\n Hi\n\r\n";
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

    // delete the file used for this test case
    std::filesystem::remove(filename);
}


// ------------------------------------------------------------------------------------------------
// mtl::filesystem::read_all_lines
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::filesystem::read_all_lines with non-existent file")
{
    filename_generator fname_generator;
    const std::string non_existent = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(non_existent);

    // make sure the file doesn't exist
    REQUIRE_EQ((std::filesystem::is_regular_file(non_existent)), false);

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

    // delete the file used for this test case
    std::filesystem::remove(non_existent);
}

TEST_CASE("mtl::filesystem::read_all_lines with a single line file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_line("abcd01234567890");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_line);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // there should only be a single line
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 1);
    REQUIRE_EQ((read_data.at(0) == single_line), true);
    

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with non-empty output and a single line file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_line("abcd01234567890");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_line);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    
    std::vector<std::string> desired_result { "abcd01234567890", "abcd01234567890" };
    // there should only be a single line
    std::vector<std::string> read_data { "abcd01234567890" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 2);
    REQUIRE_EQ((read_data.at(0) == single_line), true);
    REQUIRE_EQ((read_data.at(1) == single_line), true);
    REQUIRE_EQ((read_data == desired_result), true);
    

    // delete the file used for this test case
    std::filesystem::remove(filename);
}



TEST_CASE("mtl::filesystem::read_all_lines with a single character file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_char("h");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_char);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // there should only be a single line
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 1);
    REQUIRE_EQ((read_data.at(0) == single_char), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with non-empty output and a single character file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_char("h");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_char);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    std::vector<std::string> desired_data { "h", "h" };
    std::vector<std::string> read_data    { "h" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 2);
    REQUIRE_EQ((read_data.at(0) == single_char), true);
    REQUIRE_EQ((read_data.at(1) == single_char), true);
    REQUIRE_EQ((read_data == desired_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with a single LF character file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_newline("\n");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_newline);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // read all lines from the file there should only be a single line
    std::vector<std::string> read_data;
    const std::string empty;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 1);
    REQUIRE_EQ((read_data.at(0) == empty), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with two characters CRLF file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string single_newline("\r\n");

    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, single_newline);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // read all lines from the file there should only be a single line
    std::vector<std::string> read_data;
    const std::string empty;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 1);
    REQUIRE_EQ(read_data.at(0), empty);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines a file containing only LF characters")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string newlines("\n\n\n\n");

    // create a file
    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, newlines);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // read all lines from the file
    const std::string empty;
    std::vector<std::string> desired_result {empty, empty, empty, empty};
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), desired_result.size());
    REQUIRE_EQ(read_data, desired_result);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines a file containing only CRLF characters")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string newlines("\r\n\r\n\r\n\r\n");

    // create a file
    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, newlines);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // read all lines from the file
    const std::string empty;
    std::vector<std::string> desired_result {empty, empty, empty, empty};
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), desired_result.size());
    REQUIRE_EQ(read_data, desired_result);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines a file containing only mixed LF and CRLF characters")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string newlines("\r\n\n\r\n\n");

    // create a file
    bool written_correctly = false;
    written_correctly = mtl::filesystem::write_file(filename, newlines);

    // check that the file exists
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    

    // read all lines from the file
    const std::string empty;
    std::vector<std::string> desired_result {empty, empty, empty, empty};
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), desired_result.size());
    REQUIRE_EQ(read_data, desired_result);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}



TEST_CASE("mtl::filesystem::read_all_lines with LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\nHi\nHi\nHi\nHi\nHi\nHi\nHi";

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

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with non-empty output and LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\nHi\nHi\nHi\nHi\nHi\nHi\nHi";

    // write the file
    bool written_correctly = mtl::filesystem::write_file(filename, crlf_text);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> desired_result = { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi",
                                                "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    std::vector<std::string> read_data        { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}


TEST_CASE("mtl::filesystem::read_all_lines with CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with non-empty output and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi\r\nHi";

    // write the file
    bool written_correctly = mtl::filesystem::write_file(filename, crlf_text);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> desired_result = { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi",
                                                "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    std::vector<std::string> read_data        { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\r\nHi\nHi\r\nHi\nHi\r\nHi\nHi\r\nHi";

    // write the file
    bool written_correctly = mtl::filesystem::write_file(filename, crlf_text);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> desired_result = { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::read_all_lines with non-empty output and mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\r\nHi\nHi\r\nHi\nHi\r\nHi\nHi\r\nHi";

    // write the file
    bool written_correctly = mtl::filesystem::write_file(filename, crlf_text);

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read all lines of the file and check contents are what we want
    std::vector<std::string> desired_result = { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi",
                                                "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    std::vector<std::string> read_data        { "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi", "Hi" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_all_lines
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_all_lines with LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\nHi\nHi\n";
    std::vector<std::string> crlf_lines {crlf_text, crlf_text, crlf_text};

    // write all lines to a file
    bool written_correctly = mtl::filesystem::write_all_lines(filename, crlf_lines.begin(), 
                                                              crlf_lines.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read file and check contents are what we want, we have to account for the newlines that
    // mtl::write_all_lines outputs to the file between elements
    const std::string desired_result = crlf_text + "\n" + crlf_text + "\n" + crlf_text + "\n"; 
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);
    
    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_all_lines with CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\r\nHi\r\nHi\r\n";
    std::vector<std::string> crlf_lines {crlf_text, crlf_text, crlf_text};

    // write all lines to a file
    bool written_correctly = mtl::filesystem::write_all_lines(filename, crlf_lines.begin(), 
                                                              crlf_lines.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read file and check contents are what we want, we have to account for the newlines that
    // mtl::write_all_lines outputs to the file between elements
    const std::string desired_result = crlf_text + "\n" + crlf_text + "\n" + crlf_text + "\n"; 
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);
    
    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_all_lines with mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string crlf_text = "Hi\r\nHi\nHi\r\n";
    std::vector<std::string> crlf_lines {crlf_text, crlf_text, crlf_text};

    // write all lines to a file
    bool written_correctly = mtl::filesystem::write_all_lines(filename, crlf_lines.begin(), 
                                                              crlf_lines.end());

    // check that the file exists and is more than 0 bytes
    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    auto filesize = std::filesystem::file_size(filename);
    REQUIRE_EQ((filesize > 0), true);

    // read file and check contents are what we want, we have to account for the newlines that
    // mtl::write_all_lines outputs to the file between elements
    const std::string desired_result = crlf_text + "\n" + crlf_text + "\n" + crlf_text + "\n"; 
    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data.size() == desired_result.size()), true);
    REQUIRE_EQ((read_data == desired_result), true);
    
    // delete the file used for this test case
    std::filesystem::remove(filename);
}



TEST_CASE("mtl::filesystem::write_all_lines with integers")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    // create the file by writing all number from the container, mtl::filesystem::write_all_lines
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


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_all_lines with floats")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    // create the file by writing all numbers from the container, 
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


    // delete the file used for this test case
    std::filesystem::remove(filename);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_all_lines and mtl::filesystem::read_all_lines
// ------------------------------------------------------------------------------------------------


TEST_CASE("mtl::filesystem::write_all_lines and mtl::filesystem::read_all_lines with empty file")
{

    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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
    REQUIRE_EQ(read_data.empty(), true);



    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_all_lines and read_all_lines non-empty output but empty file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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

    std::vector<std::string> desired_result { "a" };
    std::vector<std::string> read_data      { "a" };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_data.empty(), false);
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ(read_data.size(), 1);
    REQUIRE_EQ((read_data == desired_result), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}


TEST_CASE("mtl::filesystem::write_all_lines write / append and mtl::filesystem::read_all_lines")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    // create the file by writing all lines from the container
    std::vector<std::string> text_data1 { text1, text1, text1, text1, text1 };
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
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data2.size() == correct_data.size()), true);
    REQUIRE_EQ((read_data2 == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}



TEST_CASE("mtl::filesystem::write_all_lines write/append and read_all_lines with LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "R\nG\nB";
    // create the file by writing all lines from the container
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
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data2.size() == correct_data_twice.size()), true);
    REQUIRE_EQ((read_data2 == correct_data_twice), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}


TEST_CASE("mtl::filesystem::write_all_lines write/append and read_all_lines with CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "R\r\nG\r\nB";
    // create the file by writing all lines from the container
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
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data2.size() == correct_data_twice.size()), true);
    REQUIRE_EQ((read_data2 == correct_data_twice), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_all_lines write/append and read_all_lines mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "R\nG\r\nB";
    // create the file by writing all lines from the container
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
    REQUIRE_EQ(read_correctly, true);
    REQUIRE_EQ((read_data2.size() == correct_data_twice.size()), true);
    REQUIRE_EQ((read_data2 == correct_data_twice), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_file with mtl::filesystem::read_all_lines
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_file with mtl::filesystem::read_all_lines with LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file with read_all_lines with non-empty output and LF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "\nR\nG\nB\nCMYK\n\nR\nG\nB\n\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_lines.empty(), false);

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "",
      "", "R", "G", "B", "CMYK", "", "R", "G", "B", "" };

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file with mtl::filesystem::read_all_lines with CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "\r\nR\r\nG\r\nB\r\nCMYK\r\n\r\nR\r\nG\r\nB\r\n\r\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines;

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file with read_all_lines with non-empty output and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "\r\nR\r\nG\r\nB\r\nCMYK\r\n\r\nR\r\nG\r\nB\r\n\r\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_lines.empty(), false);
    

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "",
      "", "R", "G", "B", "CMYK", "", "R", "G", "B", "" };

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file with mtl::filesystem::read_all_lines mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "\nR\r\nG\nB\nCMYK\r\n\r\nR\nG\r\nB\n\r\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines;

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}

TEST_CASE("mtl::filesystem::write_file with read_all_lines non-empty output and mixed LF and CRLF")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string text_with_newline = "\nR\r\nG\nB\nCMYK\r\n\r\nR\nG\r\nB\n\r\n";
    
    bool written_correctly = mtl::filesystem::write_file(filename, text_with_newline);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);
    
    std::vector<std::string> read_lines { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "", };
    // for this specific test make sure the output container is not empty
    REQUIRE_EQ(read_lines.empty(), false);

    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_lines);

    REQUIRE_EQ(read_correctly, true);

    const std::vector<std::string> correct_data
    { "", "R", "G", "B", "CMYK", "", "R", "G", "B", "",
      "", "R", "G", "B", "CMYK", "", "R", "G", "B", "" };

    REQUIRE_EQ(read_lines.empty(), false);
    REQUIRE_EQ((read_lines.size() == correct_data.size()), true);
    REQUIRE_EQ((read_lines == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}



// ------------------------------------------------------------------------------------------------
// mtl::filesystem::write_all_lines with mtl::filesystem::read_file
// ------------------------------------------------------------------------------------------------

TEST_CASE("mtl::filesystem::write_all_lines with mtl::filesystem::read_file")
{
    filename_generator fname_generator;
    const std::string filename = fname_generator.generate_filename();

    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

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
    REQUIRE_EQ(read_line.empty(), false);
    REQUIRE_EQ((read_line.size() == correct_data.size()), true);
    REQUIRE_EQ((read_line == correct_data), true);


    // delete the file used for this test case
    std::filesystem::remove(filename);
}






TEST_CASE("Tests with different encoding depending on OS, write_file and read_file")
{

#if defined(_WIN32)
    // The filename for Windows should be UTF-16 encoded.
    const std::filesystem::path filename (L"_UTF16_test_file_αρχείο_ファイル_文件_файл_1.txt");
#else
    // The filename for all operating systems excluding Windows should be UTF-8 encoded. Do not
    // use UTF-16 encoding for any operating system except Windows.
    // 
    // We need to use reinterpret_cast to make u8 work for both C++ 17 and C++ 20. For a more
    // detailed explanation on why that is, read the comments at the start of this file.
    const std::filesystem::path filename
    (reinterpret_cast<const char*>(u8"_UTF8_test_file_αρχείο_ファイル_文件_файл_1.txt"));
#endif



    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::string data = "aaaaaaa bbbbbbbb 1111122222 ####### $$$$$$$$$$$$$";

    bool written_correctly = mtl::filesystem::write_file(filename, data);

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);

    std::string read_data;
    bool read_correctly = mtl::filesystem::read_file(filename, read_data);

    REQUIRE_EQ(read_correctly, true);

    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ((read_data.size() == data.size()), true);
    REQUIRE_EQ((read_data == data), true);

    // append to the existing file
    bool appended_correctly = mtl::filesystem::write_file(filename, data, true);
    REQUIRE_EQ(appended_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);


    std::string new_read_data;
    bool new_read_correctly = mtl::filesystem::read_file(filename, new_read_data);

    REQUIRE_EQ(new_read_correctly, true);

    const std::string correct_data = data + data;
    REQUIRE_EQ(new_read_data.empty(), false);
    REQUIRE_EQ((new_read_data.size() == correct_data.size()), true);
    REQUIRE_EQ((new_read_data == correct_data), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}


TEST_CASE("Tests with different encoding depending on OS, write_all_lines and read_all_lines")
{

#if defined(_WIN32)
    // The filename for Windows should be UTF-16 encoded.
    const std::filesystem::path filename (L"_UTF16_test_file_αρχείο_ファイル_文件_файл_2.txt");
#else
    // The filename for all operating systems excluding Windows should be UTF-8 encoded. Do not
    // use UTF-16 encoding for any operating system except Windows.
    // 
    // We need to use reinterpret_cast to make u8 work for both C++ 17 and C++ 20. For a more
    // detailed explanation on why that is, read the comments at the start of this file.
    const std::filesystem::path filename
    (reinterpret_cast<const char*>(u8"_UTF8_test_file_αρχείο_ファイル_文件_файл_2.txt"));
#endif



    // delete the file used for this test case if it exists from a previous failed run
    std::filesystem::remove(filename);

    const std::vector<std::string> data =
    { "aaaaaaa", "bbbbbbbb", "1111122222", "#######", "$$$$$$$$$$$$$" };

    bool written_correctly = mtl::filesystem::write_all_lines(filename, data.begin(), data.end());

    REQUIRE_EQ(written_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);

    std::vector<std::string> read_data;
    bool read_correctly = mtl::filesystem::read_all_lines(filename, read_data);

    REQUIRE_EQ(read_correctly, true);

    REQUIRE_EQ(read_data.empty(), false);
    REQUIRE_EQ((read_data.size() == data.size()), true);
    REQUIRE_EQ((read_data == data), true);

    // append to the existing file
    bool appended_correctly = mtl::filesystem::write_all_lines(filename, data.begin(), data.end(),
                                                               true);
    REQUIRE_EQ(appended_correctly, true);
    REQUIRE_EQ((std::filesystem::is_regular_file(filename)), true);
    REQUIRE_EQ((std::filesystem::file_size(filename) > 0), true);


    std::vector<std::string> new_read_data;
    bool new_read_correctly = mtl::filesystem::read_all_lines(filename, new_read_data);

    REQUIRE_EQ(new_read_correctly, true);

    const std::vector<std::string> correct_data =
    { "aaaaaaa", "bbbbbbbb", "1111122222", "#######", "$$$$$$$$$$$$$",
      "aaaaaaa", "bbbbbbbb", "1111122222", "#######", "$$$$$$$$$$$$$" };
    REQUIRE_EQ(new_read_data.empty(), false);
    REQUIRE_EQ((new_read_data.size() == correct_data.size()), true);
    REQUIRE_EQ((new_read_data == correct_data), true);

    // delete the file used for this test case
    std::filesystem::remove(filename);
}






TEST_CASE("Delete remaining files due to failed test cases")
{
    // we check again for existing files because if a test fails it will not delete it's 
    // associated temporary file
    filename_generator fname_generator;
    for(const auto& filename : *(fname_generator.get_filenames()))
    {
        // if the file still exists delete it
        std::filesystem::remove(filename);

        // check that the file was deleted properly, incase it existed
        CHECK_EQ(std::filesystem::is_regular_file(filename), false);
    }



    // delete temporary files from tests with different encoding depending on OS

#if defined(_WIN32)
    // The filename for Windows should be UTF-16 encoded.
    const std::filesystem::path filename1 (L"_UTF16_test_file_αρχείο_ファイル_文件_файл_1.txt");
    const std::filesystem::path filename2 (L"_UTF16_test_file_αρχείο_ファイル_文件_файл_2.txt");
#else
    // The filename for all operating systems excluding Windows should be UTF-8 encoded. Do not
    // use UTF-16 encoding for any operating system except Windows.
    // 
    // We need to use reinterpret_cast to make u8 work for both C++ 17 and C++ 20. For a more
    // detailed explanation on why that is, read the comments at the start of this file.
    const std::filesystem::path filename1
    (reinterpret_cast<const char*>(u8"_UTF8_test_file_αρχείο_ファイル_文件_файл_1.txt"));
    const std::filesystem::path filename2
    (reinterpret_cast<const char*>(u8"_UTF8_test_file_αρχείο_ファイル_文件_файл_2.txt"));
#endif

    // delete the files
    std::filesystem::remove(filename1);
    std::filesystem::remove(filename2);

    // check that the files were deleted properly, incase they existed
    CHECK_EQ(std::filesystem::is_regular_file(filename1), false);
    CHECK_EQ(std::filesystem::is_regular_file(filename2), false);
}

