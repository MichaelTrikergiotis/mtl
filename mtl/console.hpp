#pragma once
// console header by Michael Trikergiotis
// 09/09/2018
// 
// 
// This header contains algorithms that interact with the console.
// 
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.


#include "definitions.hpp" // various definitions
#include <string>          // std::string
#include <string_view>     // std::string_view
#include <cstring>         // std::strlen
#include <vector>          // std::vector
#include <iterator>        // std::distance
#include <algorithm>       // std::max_element, std::find
#include <utility>         // std::forward
#include <cstdio>          // std::fflush, stdout
#include "type_traits.hpp" // mtl::is_std_string_v, mtl::is_c_string_v
#include "fmt_include.hpp" // fmt::print, fmt::runtime
#include "string.hpp"      // mtl::string::to_string, mtl::string::pad, mtl::string::pad_front,
						   // mtl::string::pad_back, mtl::string::join


// Windows only headers
#if defined(_WIN32)

// this define makes the huge Windows.h header compile faster
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#include <io.h>      // _isatty
#include <cstdio>    // _fileno
#include <stdexcept> // std::runtime_error
#include <mutex>     // std::mutex, std::lock_guard

#if defined(__MINGW32__) || defined(__MINGW64__)
// we need to include the lowercase windows.h header because it fixes a cross-compilation issue
// when compiling with mingw on Linux targeting Windows
#include <windows.h>
#else
// use the Windows.h header like normal
#include <Windows.h> // HANDLE, WORD, DWORD, COORD, TCHAR, CONSOLE_SCREEN_BUFFER_INFO, 
					 // STD_OUTPUT_HANDLE, GetStdHandle, SetConsoleTextAttribute,
					 // SetConsoleCursorPosition, GetConsoleScreenBufferInfo,
					 // FillConsoleOutputCharacter, FillConsoleOutputAttribute
#endif // __MINGW32__ and __MINGW64__ end


// Linux / Unix only headers
#else

#include <unistd.h> // isatty

#endif // WIN32 end




namespace mtl
{
namespace console
{


namespace detail
{

// ------------------------------------------------------------------------------------------------
// Some helper functions and constants.
// ------------------------------------------------------------------------------------------------

#if defined(_WIN32)

// Determines if we are running in the terminal or not. For Windows.
[[nodiscard]]
inline bool is_terminal()
{
	// returns whether a file descriptor refers to a terminal
	return (_isatty(_fileno(stdout)));
}


// Set the Windows console to accept ASCII escape sequences. If we succeed, return true. If we
// can't set it then it means we are in a version of Windows before Windows 10 v.1607. Return
// false indicating we couldn't set Windows console to use ASCII escape sequences.
[[nodiscard]]
inline bool enable_win_ascii()
{
	// if we are not on a terminal do not try to do anything just return true
	if (is_terminal() == false)
	{
		return true;
	}


// there seems to be some Windows environments where ENABLE_VIRTUAL_TERMINAL_PROCESSING is not
// defined so we have to define it
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console_handle == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Error. Can't get the console's window handle.");
	}

	DWORD console_mode = 0;
	if (!GetConsoleMode(console_handle, &console_mode))
	{
		throw std::runtime_error("Error. Can't get console mode.");
	}

	// add virtual terminal processing to the console mode
	console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// try to set the new console mode if we can't we are in Windows before Windows 10 v.1607
	if (!SetConsoleMode(console_handle, console_mode))
	{
		return false;
	}

	// if we reached this point it means we could set the console mode so we are in 
	// Windows 10 v.1607 or later and so the Windows console supports ASCII escape sequences
	return true;
}


// If this is false we are in Windows 10 v.1607 or later. If this is set to true then we are in
// older versions of Windows and have to use WIN32 API for some of the console functionality.
static const bool legacy_windows = !(enable_win_ascii());


// Mutex used to lock legacy Windows console functions that use WIN32 API to interact with the
// console and allows them to be thread-safe.
static std::mutex console_mutex_legacy_win;


#else

// Determines if we are running in the terminal or not. For Linux / Unix.
[[nodiscard]]
inline bool is_terminal()
{
	// returns whether a file descriptor refers to a terminal
	return (isatty(STDOUT_FILENO) == 1);
}

#endif


// Reports if we are running in the terminal or not.
static const bool inside_terminal = is_terminal();


} // namespace detail end



// ================================================================================================
// PRINT - Prints all parameters to the console.
// ================================================================================================


/// Print nothing to the console.
inline void print() {}

/// Print a single parameter to the console.
/// @param[in] arg An argument of any type that can be printed.
template <typename Arg>
inline void print(const Arg& arg)
{
	fmt::print("{}", arg);
}

/// Print all parameters to the console.
/// @param[in] arg An argument of any type that can be printed.
/// @param[in] args Any number of arguments of any type that can be printed.
template <typename Arg, typename... Args>
inline void print(const Arg& arg, Args&&... args)
{
	// the number of variadic arguments
	constexpr size_t number_args = sizeof...(args);

	// if there are any variadic arguments
	if constexpr(number_args > 0)
	{
		// concatenate all arguments to a single string, so we only need a single call to print
		fmt::print("{}", mtl::string::join(arg, std::forward<Args>(args)...));
	}
	// if there are no variadic arguments
	else
	{
		fmt::print("{}", arg);
	}
}



// ================================================================================================
// PRINTLN - Prints each parameter to the console in a new line.
// ================================================================================================

namespace detail
{
	// Concatenates an argument and a newline at the end of a buffer.
	inline void concat_to_buffer_newline(std::string& buffer, const std::string& arg)	
	{
		buffer += arg;
		buffer.push_back('\n');
	}

	// Concatenates an argument and a newline at the end of a buffer.
	template<typename Arg>
	inline void concat_to_buffer_newline(std::string& buffer, const Arg& arg)	
	{
		buffer += mtl::string::to_string(arg);
		buffer.push_back('\n');
	}

	// Concatenates all given arguments with a newline at the end of each and stores them in a
	// buffer.
	template<typename Arg, typename... Args>
	inline void concat_to_buffer_newline(std::string& buffer, const Arg& arg, Args&&... args)	
	{
		concat_to_buffer_newline(buffer, arg);
		concat_to_buffer_newline(buffer, args...);
	}

	// Concatenates all given arguments with a newline at the end of each and returns a string.
	template<typename Arg, typename... Args>
	inline std::string concat_args_newline(const Arg& arg, Args&&... args)	
	{
		std::string buffer;
		concat_to_buffer_newline(buffer, arg, std::forward<Args>(args)...);
		return buffer;
	}	
} // namespace detail end


/// Print a new line to the console.
inline void println()
{
	fmt::print("\n");
}

/// Print a parameter to the console followed by a new line.
/// @param[in] arg An argument of any type that can be printed.
template <typename Arg>
inline void println(const Arg& arg)
{
	fmt::print("{}\n", arg);
}

/// Print each parameter followed by a new line.
/// @param[in] arg An argument of any type that can be printed.
/// @param[in] args Any number of arguments of any type that can be printed.
template <typename Arg, typename... Args>
inline void println(const Arg& arg, Args&&... args)
{
	// the number of variadic arguments
	constexpr size_t number_args = sizeof...(args);

	// if there are any variadic arguments
	if constexpr(number_args > 0)
	{
		// concatenate all arguments to a single string, so we only need a single call to print
		fmt::print("{}", mtl::console::detail::concat_args_newline(arg, 
																   std::forward<Args>(args)...));
	}
	// if there are no variadic arguments
	else
	{
		fmt::print("{}\n", arg);
	}
}



// ================================================================================================
// PRINT_PAD  - Enumeration that allows print_all to select which side you want the printed 
//              element to be padded to.
// PRINT_ALL  - Print all elements in a range with a multitude of formatting options.
// ================================================================================================




/// Enumeration that allows you to set the padding for mtl::console::print_all.
enum class print_pad
{
	/// No padding.
	none,

	/// Padding to the front side.
	front,

	/// Padding to the back side.
	back,

	/// Padding to both the front and back sides of the element so it is aligned to the middle but 
	/// prefer to pad the front side more if the times that padding needs to be applied is an odd
	/// number.
	both_front,

	/// Padding to both the front and back sides of the element so it is aligned to the middle but 
	/// prefer to pad the back side more if the times that padding needs to be applied is an odd
	/// number.
	both_back
};


namespace detail
{

// Adds padding to a string to match the target length with the given padding style.
inline void print_padding_impl(std::string& value, const size_t length, 
							   const mtl::console::print_pad padding_style)
{
	
	const size_t size = value.size();
	// check if the string needs padding based on requested length
	if (size < length)
	{
		// pad the given string with the selected padding style

		// when padding to the front
		if (padding_style == mtl::console::print_pad::front)
		{
			mtl::string::pad_front(value, length - size, ' ');
		}
		// when padding to the back side
		else if (padding_style == mtl::console::print_pad::back)
		{
			mtl::string::pad_back(value, length - size, ' ');
		}
		// when padding to the front and back side but mostly to the front
		else if (padding_style == mtl::console::print_pad::both_front)
		{
			mtl::string::pad(value, length - size, ' ', false);
		}
		// when padding to the front and back side but mostly to the back
		else
		{
			mtl::string::pad(value, length - size, ' ', true);
		}
	
	}

}

} // namespace detail end



/// Prints to console all elements in a range. The newline_threshold affects after how many
/// elements the newline character will be used. Delimiter is a string used between all elements.
/// The line_start affects what gets printed when a new line starts and line_end affects what is
/// printed when a line ends. Padding style allows you to pass an enumeration to select which side
/// you want all elements to be padded. Padding only works correctly with ASCII characters.
/// @param[in] first An iterator to the start of the range.
/// @param[in] last An iterator to the end of the range.
/// @param[in] delimiter An optional delimiter to use between each element.
/// @param[in] newline_threshold The optional number of elements after a new line will be printed.
/// @param[in] line_start An optional text to print at the start of a new line.
/// @param[in] line_end An optional text to print at the end of a new line.
/// @param[in] padding_style The optional padding style used to pad elements.
template<typename Iter>
inline void print_all(Iter first, Iter last, const std::string& delimiter = "", 
					  size_t newline_threshold = 0, const std::string& line_start = "", 
					  const std::string& line_end = "",  
					  mtl::console::print_pad padding_style = mtl::console::print_pad::none)
{
	
	
	if (first == last) // GCOVR_EXCL_LINE
	{ 
		return; 
	}

	// find the number of elements
	auto iter_distance = std::distance(first, last);
	// check that the iterator distance is not zero or lower
	if (iter_distance <= 0) { return; }
	// convert to size_t as we checked it is not a negative number
	const size_t num_elements = static_cast<size_t>(iter_distance);

	// GCOVR_EXCL_START
	
	std::vector<std::string> elements;
	// reserve space to avoid unnecessary allocations
	elements.reserve(num_elements);
	// convert all elements to strings so we can manipulate them
	for (auto it = first; it != last; ++it)
	{
		elements.emplace_back(mtl::string::to_string(*it));
	}


	size_t longest = 0;
	// if padding is requested find the longest string so we can add the correct amount of padding
	if(padding_style != mtl::console::print_pad::none)
	{
		longest = 	(std::max_element(elements.begin(), elements.end(), 
									  [](const auto& lhs, const auto& rhs)
									  {
										  return lhs.size() < rhs.size();
									  }))->size();
	}
	

	// create a buffer to store everything so we only have to print once
	std::string buffer;

	// if printing a newline after a certain number of elements is requested
	if (newline_threshold > 0)
	{
		// counter to keep track when we need to print the newline character
		size_t newline_counter = 0;

		// counter to keep track if it is the last element
		size_t last_element_counter = 0;

		for (auto& element : elements)
		{		
			// if the counter is 0 it means a new line is just starting
			if (newline_counter == 0)
			{
				buffer += line_start;
			}

			// pad the element with the given padding style
			mtl::console::detail::print_padding_impl(element, longest, padding_style); 

			// store the element in the buffer
			buffer += element; 

			++newline_counter;
			++last_element_counter;
			
			// check if we should add a delimiter or if it the end of a line based on the counters
			if ((newline_counter < newline_threshold) && (last_element_counter < num_elements)) 
			{
				buffer += delimiter; 
			}
			else
			{
				buffer = mtl::string::join(buffer, line_end, "\n");
				newline_counter = 0;
			}
		}
	}
	// if printing a newline after a certain number of elements is not requested
	else
	{
		buffer += line_start; 
		
		// counter to keep track if it is the last element
		size_t last_element_counter = 0;

		for (auto& element : elements)
		{
			// pad the element with the given padding style
			mtl::console::detail::print_padding_impl(element, longest, padding_style); 
			
			// store the element in the buffer
			buffer += element; 

			++last_element_counter;
			
			// add the delimiter if it is not the last element
			if (last_element_counter < num_elements)
			{ 
				buffer += delimiter; 
			}		
		}
		buffer += line_end; 
	}

	// write the entire buffer to the console, benchmarks show great performance gains 
	// compared to printing each individual element to the console one at a time
	fmt::print("{}", buffer);
	
	// GCOVR_EXCL_STOP
}








// ================================================================================================
// COLOR - Enumeration for all the colors that can be used with the console.
// ================================================================================================


/// Enumeration of the standard terminal colors that can be used to output color to the
/// console plus one extra for the default color.
enum class color : uint8_t
{
	// color sort order and codes from taken from :
	// en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

	/// Default Color.
	default_color = 29,
	/// Black Color.
	black = 30,
	/// Red Color.
	red = 31,
	/// Green Color.
	green = 32,
	/// Yellow Color.
	yellow = 33,
	/// Blue Color.
	blue = 34,
	/// Magenta Color.
	magenta = 35,
	/// Cyan Color.
	cyan = 36,
	/// White Color.
	white = 37,

	/// Bright Black Color.
	bright_black = 90,
	/// Bright Red Color.
	bright_red = 91,
	/// Bright Green Color.
	bright_green = 92,
	/// Bright Yellow Color.
	bright_yellow = 93,
	/// Bright Blue Color.
	bright_blue = 94,
	/// Bright Magenta Color.
	bright_magenta = 95,
	/// Bright Cyan Color.
	bright_cyan = 96,
	/// Bright White Color.
	bright_white = 97
};


// ================================================================================================
// PRINT_COLOR   - Prints to console with foreground and background color.
// PRINTLN_COLOR - Prints to console with a newline with foreground and background color.
// ================================================================================================


namespace detail
{

#if defined(_WIN32)
// Implementation for both print_color and println_color for using the WIN32 API to be used on 
// Windows for the console (cmd.exe).
template<typename Type>
inline void print_color_win_legacy(const Type& arg, mtl::console::color foreground_color,
								   mtl::console::color background_color, bool newline = false)
{
	// we use an std::lock_guard because we want this function to be thread-safe
	std::lock_guard<std::mutex> lockg(mtl::console::detail::console_mutex_legacy_win);

	// handle to the current console
	HANDLE console_handle = nullptr;
	// original foreground colors
	WORD original_fg = 0;
	// original background colors
	WORD original_bg = 0;
	// screen buffer information for the current console
	CONSOLE_SCREEN_BUFFER_INFO console_screen_buff_info;
	// get the handle for the current console output
	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console_handle == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Error. Can't get the console's window handle.");
	}

	// get the screen buffer information for the current console
	if (!GetConsoleScreenBufferInfo(console_handle, &console_screen_buff_info))
	{
		throw std::runtime_error("Error. Can't get the console's screen buffer information.");
	}


	// store the original foreground color information
	original_fg = console_screen_buff_info.wAttributes & ~(BACKGROUND_RED  | BACKGROUND_GREEN |
														   BACKGROUND_BLUE | BACKGROUND_INTENSITY);

	// store the original background color information
	original_bg = console_screen_buff_info.wAttributes & ~(FOREGROUND_RED  | FOREGROUND_GREEN |
														   FOREGROUND_BLUE | FOREGROUND_INTENSITY);


	// by initializing foreground and background color with the original foreground and background
	// color we don't have to check for mtl::console::color::default_color as it is essentially
	// the same thing
	WORD fg_color = original_fg;
	WORD bg_color = original_bg;


	// color sort order and codes from taken from :
	// en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

	// --------------------
	// SET FOREGROUND COLOR
	// --------------------

	// set normal foreground color
	if (foreground_color == mtl::console::color::black)
	{
		fg_color = 0;
	}
	else if (foreground_color == mtl::console::color::red)
	{
		fg_color = FOREGROUND_RED;
	}
	else if (foreground_color == mtl::console::color::green)
	{
		fg_color = FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::yellow)
	{
		fg_color = FOREGROUND_RED | FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::blue)
	{
		fg_color = FOREGROUND_BLUE;
	}
	else if (foreground_color == mtl::console::color::magenta)
	{
		fg_color = FOREGROUND_RED | FOREGROUND_BLUE;
	}
	else if (foreground_color == mtl::console::color::cyan)
	{
		fg_color = FOREGROUND_BLUE | FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::white)
	{
		fg_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}

	// set bright foreground color
	else if (foreground_color == mtl::console::color::bright_black)
	{
		fg_color = FOREGROUND_INTENSITY | 0;
	}
	else if (foreground_color == mtl::console::color::bright_red)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_RED;
	}
	else if (foreground_color == mtl::console::color::bright_green)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::bright_yellow)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::bright_blue)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
	}
	else if (foreground_color == mtl::console::color::bright_magenta)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
	}
	else if (foreground_color == mtl::console::color::bright_cyan)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;
	}
	else if (foreground_color == mtl::console::color::bright_white)
	{
		fg_color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}


	// --------------------
	// SET BACKGROUND COLOR
	// --------------------

	// set normal background color
	if (background_color == mtl::console::color::black)
	{
		bg_color = 0;
	}
	else if (background_color == mtl::console::color::red)
	{
		bg_color = BACKGROUND_RED;
	}
	else if (background_color == mtl::console::color::green)
	{
		bg_color = BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::yellow)
	{
		bg_color = BACKGROUND_RED | BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::blue)
	{
		bg_color = BACKGROUND_BLUE;
	}
	else if (background_color == mtl::console::color::magenta)
	{
		bg_color = BACKGROUND_RED | BACKGROUND_BLUE;
	}
	else if (background_color == mtl::console::color::cyan)
	{
		bg_color = BACKGROUND_BLUE | BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::white)
	{
		bg_color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}

	// set bright background color
	else if (background_color == mtl::console::color::bright_black)
	{
		bg_color = BACKGROUND_INTENSITY | 0;
	}
	else if (background_color == mtl::console::color::bright_red)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_RED;
	}
	else if (background_color == mtl::console::color::bright_green)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::bright_yellow)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::bright_blue)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_BLUE;
	}
	else if (background_color == mtl::console::color::bright_magenta)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
	}
	else if (background_color == mtl::console::color::bright_cyan)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN;
	}
	else if (background_color == mtl::console::color::bright_white)
	{
		bg_color = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}




	// keep track if the argument contains the newline character
	bool contains_newline = false;

	// if the argument is of type std::string check if it contains a newline character
	if constexpr (mtl::is_std_string_v<decltype(arg)>)
	{
		contains_newline = mtl::string::contains(arg, '\n');
	}

	// if the argument is of type const char* check if it contains a newline character
	if constexpr (mtl::is_c_string_v<decltype(arg)>)
	{
		contains_newline = mtl::string::contains(arg, '\n');
	}


	// if the argument contains a newline character, print the argument with the color attributes
	// but without the newline character and then print the newline character with the old color
	// attributes to prevent color spilling to the next line
	if (contains_newline)
	{
		// convert to a std::string from either std::string or const char* to make it easier to
		// work with
		std::string argument_newline = mtl::string::to_string(arg);

		// remember the start position
		size_t start = 0;
		// position of the first match
		size_t match_pos = argument_newline.find('\n');

		// keep the position for the last element
		size_t last_pos = 0;

		// print all parts except the last one
		while (match_pos != std::string::npos)
		{
			last_pos = match_pos;

			// set foreground and background colors to the selected color
			if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
			{
				throw std::runtime_error("Error. Can't set the console's attributes.");
			}

			// get the part
			const std::string_view part(argument_newline.data() + start, match_pos - start);

			// print the part
			fmt::print("{}", part);

			// set foreground and background colors back to default colors
			if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
			{
				throw std::runtime_error("Error. Can't set the console's attributes.");
			}

			// print the newline character with the default colors
			fmt::print("\n");

			// set the a new starting position
			start = match_pos + 1;
			// find a new position in the input string if there are any matches left
			match_pos = argument_newline.find('\n', start);
		}

		// if we are still within bounds print the last part
		if ((last_pos + 1) < argument_newline.size())
		{
			// print the last part
			const std::string_view part(argument_newline.data() + (last_pos + 1));
			// set foreground and background colors to the selected color
			if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
			{
				throw std::runtime_error("Error. Can't set the console's attributes.");
			}

			fmt::print("{}", part);

			// set foreground and background colors back to default colors
			if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
			{
				throw std::runtime_error("Error. Can't set the console's attributes.");
			}
		}
	}

	// if the string / const char* doesn't contain the newline character
	else
	{
		// set foreground and background colors to the selected color
		if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
		{
			throw std::runtime_error("Error. Can't set the console's attributes.");
		}

		// print the argument passed to the function
		fmt::print("{}", arg);

		// set foreground and background colors back to normal
		if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
		{
			throw std::runtime_error("Error. Can't set the console's attributes.");
		}
	}

	// if newline parameter is true we have to print a newline character at the end
	if (newline)
	{
		fmt::print("{}", "\n");
	}
}

#endif // WIN32


// Implementation for both print_color and println_color with ASCII escape sequences. 
template<typename Type>
inline void print_color_ascii(const Type& arg, mtl::console::color foreground_color,
							  mtl::console::color background_color, bool newline = false)
{
	// color sort order and codes from taken from :
	// en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

	// set the starting ANSI escape code for foreground color
	std::string fg_color = "\033[";
	// set the starting ANSI escape code for background color
	std::string bg_color = "\033[";

	// --------------------
	// SET FOREGROUND COLOR
	// --------------------

	// GCOVR_EXCL_START

	// set normal foreground color
	if (foreground_color == mtl::console::color::default_color)
	{
		fg_color += "39;";
	}
	else if (foreground_color == mtl::console::color::black)
	{
		fg_color += "30;";
	}
	else if (foreground_color == mtl::console::color::red)
	{
		fg_color += "31;";
	}
	else if (foreground_color == mtl::console::color::green)
	{
		fg_color += "32;";
	}
	else if (foreground_color == mtl::console::color::yellow)
	{
		fg_color += "33;";
	}
	else if (foreground_color == mtl::console::color::blue)
	{
		fg_color += "34;";
	}
	else if (foreground_color == mtl::console::color::magenta)
	{
		fg_color += "35;";
	}
	else if (foreground_color == mtl::console::color::cyan)
	{
		fg_color += "36;";
	}
	else if (foreground_color == mtl::console::color::white)
	{
		fg_color += "37;";
	}

	// set bright foreground color
	else if (foreground_color == mtl::console::color::bright_black)
	{
		fg_color += "90;";
	}
	else if (foreground_color == mtl::console::color::bright_red)
	{
		fg_color += "91;";
	}
	else if (foreground_color == mtl::console::color::bright_green)
	{
		fg_color += "92;";
	}
	else if (foreground_color == mtl::console::color::bright_yellow)
	{
		fg_color += "93;";
	}
	else if (foreground_color == mtl::console::color::bright_blue)
	{
		fg_color += "94;";
	}
	else if (foreground_color == mtl::console::color::bright_magenta)
	{
		fg_color += "95;";
	}
	else if (foreground_color == mtl::console::color::bright_cyan)
	{
		fg_color += "96;";
	}
	else if (foreground_color == mtl::console::color::bright_white)
	{
		fg_color += "97;";
	}


	// --------------------
	// SET BACKGROUND COLOR
	// --------------------

	// set normal background color
	if (background_color == mtl::console::color::default_color)
	{
		bg_color += "49;";
	}
	else if (background_color == mtl::console::color::black)
	{
		bg_color += "40;";
	}
	else if (background_color == mtl::console::color::red)
	{
		bg_color += "41;";
	}
	else if (background_color == mtl::console::color::green)
	{
		bg_color += "42;";
	}
	else if (background_color == mtl::console::color::yellow)
	{
		bg_color += "43;";
	}
	else if (background_color == mtl::console::color::blue)
	{
		bg_color += "44;";
	}
	else if (background_color == mtl::console::color::magenta)
	{
		bg_color += "45;";
	}
	else if (background_color == mtl::console::color::cyan)
	{
		bg_color += "46;";
	}
	else if (background_color == mtl::console::color::white)
	{
		bg_color += "47;";
	}

	// set bright background color
	else if (background_color == mtl::console::color::bright_black)
	{
		bg_color += "100;";
	}
	else if (background_color == mtl::console::color::bright_red)
	{
		bg_color += "101;";
	}
	else if (background_color == mtl::console::color::bright_green)
	{
		bg_color += "102;";
	}
	else if (background_color == mtl::console::color::bright_yellow)
	{
		bg_color += "103;";
	}
	else if (background_color == mtl::console::color::bright_blue)
	{
		bg_color += "104;";
	}
	else if (background_color == mtl::console::color::bright_magenta)
	{
		bg_color += "105;";
	}
	else if (background_color == mtl::console::color::bright_cyan)
	{
		bg_color += "106;";
	}
	else if (background_color == mtl::console::color::bright_white)
	{
		bg_color += "107;";
	}
	
	// GCOVR_EXCL_STOP

	// add 22m character to set normal level of intensity for foreground and background
	fg_color += "22m";
	bg_color += "22m";




	// keep track if the argument contains the newline character
	bool contains_newline = false;
	
	// if the argument is of type std::string check if it contains a newline character
	if constexpr (mtl::is_std_string_v<decltype(arg)>)
	{
		contains_newline = mtl::string::contains(arg, '\n');
	}

	// if the argument is of type const char* check if it contains a newline character
	if constexpr (mtl::is_c_string_v<decltype(arg)>)
	{
		contains_newline = mtl::string::contains(arg, '\n');
	}


	// if the argument contains a newline character, print the argument with the color attributes
	// but without the newline character and then print the newline character with the old color
	// attributes to prevent color spilling to the next line
	if (contains_newline)
	{
		// convert to a std::string from either std::string or const char* to make it easier to
		// work with
		std::string argument_newline = mtl::string::to_string(arg); // GCOVR_EXCL_LINE

		// remember the start position
		size_t start = 0;
		// position of the first match
		size_t match_pos = argument_newline.find('\n');

		// keep the position for the last element
		size_t last_pos = 0;

		// print all parts except the last one
		while (match_pos != std::string::npos)
		{
			last_pos = match_pos;

			// GCOVR_EXCL_START
			
			// get the part
			const std::string_view part(argument_newline.data() + start, match_pos - start);
			

			// print the part and then newline character with default colors
			fmt::print("{}{}{}\033[0m\x1B[K\n", fg_color, bg_color, part);

			// GCOVR_EXCL_STOP

			// set the a new starting position
			start = match_pos + 1;
			// find a new position in the input string if there are any matches left
			match_pos = argument_newline.find('\n', start);
		}

		// GCOVR_EXCL_START

		// if we are still within bounds print the last part
		if ((last_pos + 1) < argument_newline.size())
		{
			// get the last part
			const std::string_view part(argument_newline.data() + (last_pos + 1));

			// print the last part
			fmt::print("{}{}{}\033[0m\x1B[K", fg_color, bg_color, part);
		}
		
		// GCOVR_EXCL_STOP
		
		// if the parameter newline is true print with newline at the end, this is not the same
		// as the argument containing newline characters
		if (newline)
		{
			fmt::print("\n"); // GCOVR_EXCL_LINE
		}
	}
	// if the argument doesn't contain newline characters
	else
	{
		// if the parameter newline is true print with newline at the end, this is not the same
		// as the argument containing newline characters
		if (newline)
		{
			fmt::print("{}{}{}\033[0m\n", fg_color, bg_color, arg); // GCOVR_EXCL_LINE
		}
		else
		{
			// we have to use x1B[K ASCII escape sequence to clear to the end of line after we 
			// print because if we don't there is a bug that affects only some terminals that
			// sporadically makes background colors spill to the next line or the line after that
			// if we don't
			fmt::print("{}{}{}\033[0m\x1B[K", fg_color, bg_color, arg); // GCOVR_EXCL_LINE
		}
	}
}



// The actual implementation of print_color that selects if it will print color using ASCII or
// the legacy method.
template<typename Type>
inline void 
print_color_impl(const Type& arg,
				 mtl::console::color foreground_color = mtl::console::color::default_color,
				 mtl::console::color background_color = mtl::console::color::default_color,
				 bool newline = false)
{
	// if we are in a terminal print with colors
	if (inside_terminal)  // GCOVR_EXCL_LINE
	{
		
#if defined(_WIN32)
		// if we are not in legacy Windows use ASCII escape sequences
		if (legacy_windows == false)
		{
			print_color_ascii(arg, foreground_color, background_color, newline);
		}
		// if we are in legacy Windows use WIN32 API
		else
		{
			print_color_win_legacy(arg, foreground_color, background_color, newline);
		}
#else
		// if we are not in Windows use ASCII escape sequences
		print_color_ascii(arg, foreground_color, background_color, newline);

#endif // _WIN32 end

	}

	// if we are not in a terminal print without colors
	else
	{
		if (newline) // GCOVR_EXCL_LINE
		{
			fmt::print("{}\n", arg); // GCOVR_EXCL_LINE
		}
		else
		{
			fmt::print("{}", arg); // GCOVR_EXCL_LINE
		}
	}
}

} // namespace detail end


/// Prints an argument with foreground and background colors. Colors can vary greatly on different
/// terminals. Terminals with colored themes can deviate from the expected colors.
/// @param[in] arg An argument of any type that can be printed.
/// @param[in] foreground_color A color for the text.
/// @param[in] background_color A color for the background.
template<typename Type>
inline void print_color(const Type& arg,
						mtl::console::color foreground_color = mtl::console::color::default_color,
						mtl::console::color background_color = mtl::console::color::default_color)
{
	mtl::console::detail::print_color_impl(arg, foreground_color, background_color, false);
}

/// Prints an argument with a newline at the end with foreground and background colors. Colors can
/// vary greatly on different terminals. Terminals with colored themes can deviate from the 
/// expected colors.
/// @param[in] arg An argument of any type that can be printed.
/// @param[in] foreground_color A color for the text.
/// @param[in] background_color A color for the background.
template<typename Type>
inline void println_color(const Type& arg,
						 mtl::console::color foreground_color = mtl::console::color::default_color,
						 mtl::console::color background_color = mtl::console::color::default_color)
{
	mtl::console::detail::print_color_impl(arg, foreground_color, background_color, true);
}






// ================================================================================================
// OVERTYPE - Allows you to print over already printed characters to the console.
// ================================================================================================

/// Allows you to print over already printed characters to the console. Flushes the stdout buffer 
/// on every call. Can only overtype characters that are not on a previous line. Can only overtype 
/// characters when the output is a console and not when redirecting to a file or a pipe.
/// @param[in] argument An argument to overtype.
inline void overtype(const std::string& argument)
{
	// GCOVR_EXCL_START
	// if we are not inside a terminal just print the characters and return
	if (mtl::console::detail::inside_terminal == false)
	{
		fmt::print(fmt::runtime(argument));
		return;
	}
	// GCOVR_EXCL_STOP


	// create a string consisting of the backspace character that will move the cursor back, this
	// allows us to avoid printing the backspace character multiple times, and we instead need to
	// print only once, this is a very significant performance gain
	const std::string multiple_backspaces(argument.size(), '\b');
	fmt::print(fmt::runtime(multiple_backspaces));
	
	fmt::print(fmt::runtime(argument));
	// flush the buffer, so the console is updated, it is thread-safe both in Windows and Linux
	std::fflush(stdout);
}

/// Allows you to print over already printed characters to the console. Flushes the stdout buffer 
/// on every call. Can only overtype characters that are not on a previous line. Can only overtype 
/// characters when the output is a console and not when redirecting to a file or a pipe.
/// @param[in] argument An argument to overtype.
inline void overtype(const char* argument)
{
	// if the const char* is nullptr do nothing
	if(argument == nullptr)
	{
		return;
	}

	// GCOVR_EXCL_START
	// if we are not inside a terminal just print the characters and return
	if (mtl::console::detail::inside_terminal == false) 
	{
		fmt::print(fmt::runtime(argument));
		return;
	}
	// GCOVR_EXCL_STOP
	

	size_t size = std::strlen(argument);
	// create a string consisting of the backspace character that will move the cursor back, this
	// allows us to avoid printing the backspace character multiple times, and we instead need to
	// print only once, this is a very significant performance gain
	const std::string multiple_backspaces(size, '\b');
	fmt::print(fmt::runtime(multiple_backspaces));
	
	fmt::print(fmt::runtime(argument));
	// flush the buffer, so the console is updated, it is thread-safe both in Windows and Linux
	std::fflush(stdout);
}


// ================================================================================================
// CLEAR - Clears the console.
// ================================================================================================

/// Clears the console. Only works when the output is a console and not when redirecting to a file
/// or a pipe.
inline void clear()
{
	// if we are not inside terminal do nothing
	if (mtl::console::detail::inside_terminal == false)	{ return; }

    // we try to clear the screen using ASCII escape codes
    fmt::print("\033c");

    
#if defined(_WIN32)

	// if we are in legacy Windows use WIN32 API to clear console
	if (mtl::console::detail::legacy_windows)
	{

		// we use an std::lock_guard because we want this function to be thread-safe
		std::lock_guard<std::mutex> lockg(mtl::console::detail::console_mutex_legacy_win);

		// get the handle for the current console
		HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (console_handle == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("Error. Can't get the console's window handle.");
		}
		// initialize screen coordinates to 0, 0 for the cursor
		COORD screen_coordinates = { 0, 0 }; 
		// keep track the number of characters written to the console
		DWORD number_chars_written = 0;
		// information for the console screen buffer
		CONSOLE_SCREEN_BUFFER_INFO console_screen_buff_info;
		// console size
		DWORD console_size = 0;

		// get the console's screen buffer information
		if (!GetConsoleScreenBufferInfo(console_handle, &console_screen_buff_info))
		{       
			throw std::runtime_error("Error. Can't get the console's screen buffer information.");
		}

		// after getting console screen buffer information we can find the console size
		console_size = static_cast<DWORD>(console_screen_buff_info.dwSize.X *
										  console_screen_buff_info.dwSize.Y);

		// fill the screen with the space character
		if (!FillConsoleOutputCharacter(console_handle,          // handle for which console to use
										static_cast<TCHAR>(' '), // use the space character
										console_size,            // number of times to write 
										screen_coordinates,      // the starting coordinates
										&number_chars_written))  // number of characters written
		{
			throw std::runtime_error("Error. Can't fill the console with the space character.");
		}

		// retrieve the screen attributes for the console and store them to the
		// console screen buffer info
		if (!GetConsoleScreenBufferInfo(console_handle, &console_screen_buff_info))
		{
			throw std::runtime_error("Error. Can't get the console's screen buffer information.");
		}

		// set console attributes appropriately
		if (!FillConsoleOutputAttribute(console_handle,          // handle for which console to use
										console_screen_buff_info.wAttributes, // char attributes
										console_size,            // number of times to write 
										screen_coordinates,      // the starting coordinates
										&number_chars_written))  // number of characters written
		{
			throw std::runtime_error("Error. Can't set the console's attributes.");
		}

		// set the cursor at the starting position
		if (!SetConsoleCursorPosition(console_handle, screen_coordinates))
		{
			throw std::runtime_error("Error. Can't set the cursor position.");
		}

	}
#endif
    
}





} // namespace console end
} // namespace mtl end
