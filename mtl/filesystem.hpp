#pragma once
// filesystem header by Michael Trikergiotis
// 26/04/2020
// 
//
// This header contains algorithms that interact with the filesystem.
//
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp" // various definitions
#include <filesystem>      // std::filesystem::file_size, std::filesystem::path, 
						   // std::filesystem::is_regular_file
#include <string>          // std::string
#include <string_view>     // std::string_view
#include <cstdint>         // std::uintmax_t
#include <fstream>		   // std::ofstream, std::ifstream
#include <system_error>    // std::error_code
#include <limits>          // std::numeric_limits
#include <ios>			   // std::ios_base::openmode, std::ios::out, 
						   // std::ios::binary, std::streamsize
#include "string.hpp"      // mtl::string::join_all
#include "utility.hpp"     // MTL_ASSERT_MSG




namespace mtl
{

namespace filesystem
{

// ================================================================================================
// READ_FILE        - Reads an entire file to a string.
// ================================================================================================


/// Read an entire file to an std::string. The filename is used to specify which file to read.
/// The read_data is where the read file will be stored. Returns if the file was read successfully.
/// @param[in] filename The relative or absolute path to a file.
/// @param[out] read_data An std::string where the read file will be stored.
/// @return Returns if the file was read successfully.
inline bool read_file(const std::filesystem::path& filename, std::string& read_data)
{

#ifndef MTL_DISABLE_SOME_ASSERTS
	// when in debug mode check the file we want to open exists and assert if it doens't
	MTL_ASSERT_MSG(std::filesystem::is_regular_file(filename),
				   "File doesn't exist or incorrect path given.");
#endif // MTL_DISABLE_SOME_ASSERTS end

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
	read_data.resize(size);
#else
	// when compiling in 32 bit mode size_t it is way smaller than std::uintmax_t so we have to
	// check and not allow file to be read if is beyond what size_t can hold as we can't resize
	// the output beyond size_t for an std::string, this usually will not happen as 32 bit OS
	// can't use files beyond 4GB but better be safe than sorry

	// thow an assert in debug mode to alert the user
	MTL_ASSERT_MSG((size <= std::numeric_limits<size_t>::max()),
	"Error in mtl::filesystem::read_file. File too large for 32 bit operating system.");

	// return false to indicate that the file was not read because of size
	if (size > std::numeric_limits<size_t>::max()) { return false; }

	// resize the output to be exactly the same size as the file
	read_data.resize(static_cast<size_t>(size));
#endif // __LP64__ end

	// read the file and place it in the output
	in_file.read(read_data.data(), static_cast<std::streamsize>(size));

	// if we reached this point it means success
	return true;
}



// ================================================================================================
// READ_ALL_LINES   - Reads all lines from to a container of strings.
// ================================================================================================


namespace detail
{
	// Splits the given string at newlines and stores them to the given container. Specialized
	// string splitting algorithm that takes into account both LF and CRLF characters when
	// splitting at newlines.
	template<typename Container>
	inline void specialized_split_crlf(const std::string& read_data, Container& split_lines)
	{	
		// handle the case where there is only one character and it is a newline
		if((read_data.size() == 1) && (read_data[0] == '\n'))
		{
			mtl::emplace_back(split_lines, std::string("")); 
			mtl::emplace_back(split_lines, std::string("")); 
			return;
		}

		// handle the case where there is only one character and it is not a newline
		if((read_data.size() == 1) && (read_data[0] != '\n'))
		{
			mtl::emplace_back(split_lines, read_data); 
			return;
		}

		// the size of the container before we start modifying it
		const auto original_size = split_lines.size();

		const std::string delimiter ("\n");

		// remember the starting position
		size_t start = 0;
		// position of the first match
		size_t match_pos = read_data.find(delimiter);

		// keep the position for the last item
		size_t last_pos = 0;

		// add all tokens to the container except the last one
		while (match_pos != std::string::npos)
		{
			last_pos = match_pos;	
			// make sure match position is larger than 0
			if(match_pos > 0)
			{
				// lf case
				if(read_data[match_pos - 1] != '\r')
				{
					const std::string_view token(read_data.data() + start, match_pos - start);
					mtl::emplace_back(split_lines, token);
				}
				// crlf case
				else
				{
					const auto crlf_position = match_pos - (start + 1);
					const std::string_view token(read_data.data() + start, crlf_position);
					mtl::emplace_back(split_lines, token);
				}
			}
			else
			{
				const std::string_view token(read_data.data() + start, match_pos - start);
				mtl::emplace_back(split_lines, token);
			}	
			
			// set the new starting position
			start = match_pos + 1;
			// find a new position in the input string if there are any matches left
			match_pos = read_data.find(delimiter, start);
		}

		// how much we added to the container
		const auto size_difference = split_lines.size() - original_size;

		// if container changed size it means there are tokens in the output
		if(size_difference > 0)
		{
			// add the last item using the last position
			const std::string_view token(read_data.data() + (last_pos + 1));
			mtl::emplace_back(split_lines, token);
		}


		// if the container's size didn't change at all then add the entire input string because
		// it means there are no places that it needs to be split
		if (size_difference == 0)
		{ 
			mtl::emplace_back(split_lines, read_data); 
		}
	}

} // namespace detail end


/// Read an entire file in lines. The filename is used to specify which file to read. The 
/// read_lines is where the file will be placed. Allows you to reserve memory for the container. 
/// The container element type has to be std::string. Returns if the file was read successfully. 
/// @param[in] filename The relative or absolute path to a file.
/// @param[out] read_lines A container with element type std::string to store the read lines.
/// @return Returns if all the lines where read successfully.
template<typename Container>
inline bool read_all_lines(const std::filesystem::path& filename, Container& read_lines)
{
	std::string internal_buffer;
	// try to read the file into the buffer
	if (mtl::filesystem::read_file(filename, internal_buffer))
	{
		// check that the buffer is not empty before we try to split it
		if (internal_buffer.empty() == false)
		{
			// split each line to an output container at each newline
			mtl::filesystem::detail::specialized_split_crlf(internal_buffer, read_lines);
			// if the last element is empty remove it, we are sure that the output is not empty
			// become we know that the internal buffer is bigger than 0 if we reached this point
			if (read_lines.back().empty())
			{
				read_lines.pop_back();
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
// ================================================================================================


/// Write an std::string to a file. The filename is used to specify which file to write. The
/// write_data is what to write to the file. Append if set to true adds to the end of the
/// file instead of overwriting it. Returns if the file was written successfully.
/// @param[in] filename The relative or absolute path to a file.
/// @param[in] write_data An std::string to write to the file.
/// @param[in] append An optional boolean to and append to the end of the file or overwrite it.
/// @return Returns if the file was written successfully.
inline bool write_file(const std::filesystem::path& filename, const std::string& write_data,
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
	out_file.write(write_data.data(), static_cast<std::streamsize>(write_data.size()));

	// if we reached this point it means we succeded
	return true;
}



// ================================================================================================
// WRITE_ALL_LINES  - Writes all elements of a container to a file.
// ================================================================================================


/// Write a range to new lines in a file. The filename is used to specify which file to write. The
/// elements in the range from first to last will be written to the file. Append if set to true
/// adds to the end of the file instead of overwriting it. Returns if the file was written
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

	if (internal_buffer.empty() == false)
	{
		internal_buffer.push_back('\n');
	}

	// write to file
	return mtl::filesystem::write_file(filename, internal_buffer, append);
}





} // namespace filesystem end
} // namespace mtl end
