#pragma once
// filesystem by Michael Trikergiotis
// 26/04/2020
// 
// Header for mtl::filesystem.
// 
// For information about third party licenses check ThirdPartyNotices.txt.

#include <filesystem>      // std::filesystem::file_size, std::filesystem::path, 
						   // std::filesystem::exists, std::filesystem::is_regular_file
#include <string>          // std::string
#include <cstring>         // std::strlen
#include <cstdint>         // std::uintmax_t
#include <fstream>		   // std::ofstream, std::ifstream
#include <system_error>    // std::error_code
#include <type_traits>     // std::enable_if_t
#include <limits>          // std::numeric_limits
#include <ios>			   // std::ios_base::openmode, std::ios::in, std::ios::out, 
						   // std::ios::binary, std::streamsize
#include "type_traits.hpp" // mtl::is_c_string
#include "string.hpp"      // mtl::string::join_all, mtl::string::split
#include "utility.hpp"     // MTL_ASSERT_MSG


#include <iostream>


namespace mtl
{

namespace filesystem
{

// ================================================================================================
// READ_FILE        - Reads an entire file to a string.
// READ_ALL_LINES   - Reads all lines from to a container of strings.
// ================================================================================================



/// Read an entire file to a std::string. The filename is what file to read from. The output is
/// where the file will be read to. Returns if the file was read successfully.
/// @param[in] filename The relative or absolute path to a file.
/// @param[out] output An std::string where the file will be stored.
/// @return Returns if the file was read successfully.
inline bool read_file(const std::filesystem::path& filename, std::string& output)
{

#ifndef MTL_DISABLE_SOME_ASSERTS
	// when in debug mode check the file we want to open exists and assert if it doens't
	MTL_ASSERT_MSG(std::filesystem::is_regular_file(filename),
				   "File doesn't exist or incorrect path given.");
#endif

	// what mode to open the file
	std::ios_base::openmode open_mode = std::ios::out;
	// set the mask to binary mode so it works better in Windows when reading newlines
	open_mode = (open_mode | std::ios::binary);

	// std::ifstream is RAII wrapper and will close correctly if an exception is thrown
	std::ifstream in_file(filename, open_mode);

	// if we can't open the file it is an error
	if (in_file.is_open() == false) { return false; }

	// enable exceptions for std::ifstream, do not use std::ifstream::failbit as it is set when
	// EOF is reached and it throws an exception even when there is no actual error
	in_file.exceptions(std::ifstream::badbit);

	// create an std::error_code object so we can call the noexcept version
	std::error_code error_code;
	// get exact file size in bytes
	std::uintmax_t size = std::filesystem::file_size(filename, error_code);
	// if filesize is 0 then just leave and report success as there is nothing to be read
	if (size == 0) { return true; }
	// if the std::error_code indicates an error or the size from std::filesystem::file_size 
	// is equal static_cast<std::uintmax_t>(-1) then we have an error
	auto too_big = static_cast<std::uintmax_t>(-1);
	if ((error_code) || (size == too_big)) { return false; } // GCOVR_EXCL_LINE

	// check if we are compiling in 64 bit mode, for gcc and clang we detect 64 bit compilation
	// with the macro __LP64__ and for MSVC with the macro _WIN64
#if defined(__LP64__) || defined(_WIN64)
	// resize the output to be exactly the same size as the file
	output.resize(size);
#else
	// when compiling in 32 bit mode size_t it is way smaller than std::uintmax_t so we have to
	// check and not allow file to be read if is beyond what size_t can hold as we can't resize
	// the output beyond size_t for a std::string, this usually will not happen as 32 bit OS can't
	// use files beyond 4GB but better be safe than sorry

	// thow an assert in debug mode to alert the user
	MTL_ASSERT_MSG((size <= std::numeric_limits<size_t>::max()),
	"Error in mtl::filesystem::read_file. File too large for 32 bit operating system.");

	// return false to indicate that the file was not read because of size
	if (size > std::numeric_limits<size_t>::max()) { return false; }

	// resize the output to be exactly the same size as the file
	output.resize(static_cast<size_t>(size));
#endif

	// read the file and place it in the output
	in_file.read(output.data(), static_cast<std::streamsize>(size));

	// if we reached this point it means success
	return true;
}



/// Read an entire file in lines. The filename is what file to read from. The output is where
/// the file will be read to. Allows you to reserve memory for the container. The container element
/// type has to be std::string. Returns if the file was read successfully. 
/// @param[in] filename The relative or absolute path to a file.
/// @param[out] output A container with element type std::string where all lines will be stored.
/// @return Returns if all the lines where read successfully.
template<typename Container>
inline bool read_all_lines(const std::filesystem::path& filename, Container& output)
{
	std::string internal_buffer;
	// try to read the file into the buffer
	if (mtl::filesystem::read_file(filename, internal_buffer))
	{
		// check that the buffer is not empty before we try to split it
		if (internal_buffer.size() > 0)
		{
			mtl::string::split(internal_buffer, output, '\n');
			// if the last element is empty remove it, we are sure that the output is not empty
			// become we know that the internal buffer is bigger than 0 if we reached this point
			if (output.back() == "")
			{
				output.pop_back();
			}
		}
	}
	// means we couldn't read the file for some reason
	else
	{
		return false;
	}
	// if we are here means everything went fine
	return true;
}


// ================================================================================================
// WRITE_FILE       - Writes a string to a file.
// WRITE_ALL_LINES  - Writes all elements of a container to a file.
// ================================================================================================


/// Write a std::string to a file. The filename is what is the file to write to. The input is where
/// to place the read file. Appends allow to append to the end of the file or overwrite it. Returns
/// if the file was written successfully.
/// @param[in] filename The relative or absolute path to a file.
/// @param[in] input An std::string where the data will be read.
/// @param[in] append An optional boolean to and append to the end of the file or overwrite it.
/// @return Returns if the file was written successfully.
inline bool write_file(const std::filesystem::path& filename, const std::string& input,
					   const bool append = false)
{
	// what mode to open the file
	std::ios_base::openmode open_mode = std::ios::out;
	// set the mask to binary mode so it works better in Windows when reading newlines
	open_mode = (open_mode | std::ios::binary);
	// should we overwrite or append to the file
	if (append) { open_mode = (open_mode | std::ios::app); }

	// std::ofstream is RAII wrapper and will close correctly if an exception is thrown
	std::ofstream out_file(filename, open_mode);
	// if we can't open the file it is an error
	if (out_file.is_open() == false) { return false; }

	// enable exceptions for std::ofstream
	out_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);

	// write the data to file
	out_file.write(input.data(), static_cast<std::streamsize>(input.size()));

	// if we reached this point it means we succeded
	return true;
}


/// Write a range to new lines in a file. The filename is what is the file to write to. The
/// range from first to last is what to write to the file. Returns if the file was written
/// successfully.
/// @param[in] filename The relative or absolute path to a file.
/// @param[in] first An iterator to the start of a range. Element type can be any type convertible
///                  to std::string by mtl::string::to_string.
/// @param[in] last An iterator to the end of a range.
/// @param[in] append An optional boolean to and append to the end of the file or overwrite it.
/// @return Returns if the all lines where written successfully.
template<typename Iter>
inline bool write_all_lines(const std::filesystem::path& filename, Iter first, Iter last,
					 		const bool append = false)
{
	std::string internal_buffer;
	
	// join all the elements with \n as a delimiter to an internal_buffer
	mtl::string::join_all(first, last, internal_buffer, '\n');

	if (internal_buffer.size() > 0)
	{
		internal_buffer.push_back('\n');
	}

	// write to file
	return mtl::filesystem::write_file(filename, internal_buffer, append);
}





} // namespace filesystem end
} // namespace mtl end
