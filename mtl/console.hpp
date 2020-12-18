#pragma once
// console by Michael Trikergiotis
// 09/09/2018
// 
// Header for mtl::console.
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information. 
// See ThirdPartyNotices.txt in the project root for third party licenses information.

#include "definitions.hpp" // various definitions
#include <string>          // std::string
#include <cstring>         // std::strlen
#include <vector>          // std::vector
#include <iterator>        // std::distance
#include <algorithm>       // std::max_element, std::find
#include <utility>         // std::forward
#include <cstdio>          // std::fflush, stdout
#include "type_traits.hpp" // mtl::is_std_string_v, mtl::is_c_string_v
#include "utility.hpp"     // MTL_ASSERT_MSG
#include "fmt_include.hpp" // fmt::print, fmt::memory_buffer, fmt::format_to, fmt::to_string
#include "string.hpp"      // mtl::string::to_string, mtl::string::pad, mtl::string::pad_front,
						   // mtl::string::pad_back


// Windows only headers
#if defined(_WIN32)

// this define makes the huge Windows.h header compile faster
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#include <io.h>      // _isatty
#include <stdio.h>   // _fileno
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
// Some general functions and constants that are used throughout mtl::console.
// ------------------------------------------------------------------------------------------------

#if defined(_WIN32)

// Determines if we are running in the terminal or not. For Windows.
[[nodiscard]]
inline bool is_terminal()
{
	// returns whether a file descriptor refers to a terminal
	return (_isatty(_fileno(stdout)));
}


// Set the Windows console to accept ASCII escape sequences. If we succeed return true. If we can't
// set it then it means we are in a version of Windows before Windows 10 v.1607. Retrun false
// indicating we couldn't set Windows console to use ASCII escape sequences.
[[nodiscard]]
inline bool enable_win_ascii()
{
	// if we are not on a terminal do not try to do anything just return true
	if (is_terminal() == false)
	{
		return true;
	}


// there seems to be some Windows enviroments where ENABLE_VIRTUAL_TERMINAL_PROCESSING is not
// defined so we have to define it
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console_handle == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Error. Can't get console window handle.");
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
// console and allows them to be thread safe.
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

/// Print a single parameter the console.
/// @param[in] arg An argument of any type that can be printed.
template <typename Arg>
inline void print(const Arg& arg)
{
	fmt::print("{}", arg);
}

/// Print all parameters to the console.
/// @param[in] arg An argument of any type that can be printed.
/// @param[in] args Any number of argument of any type that can be printed.
template <typename Arg, typename... Args>
inline void print(const Arg& arg, Args&&... args)
{
	// print the first argument
	print(arg);
	// call print recursively using pack expansion syntax for the rest of the arguments
	print(std::forward<Args>(args)...);
}



// ================================================================================================
// PRINTLN - Prints each parameter to the console in a new line.
// ================================================================================================

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
/// @param[in] args Any number of argument of any type that can be printed.
template <typename Arg, typename... Args>
inline void println(const Arg& arg, Args&&... args)
{
	// println the first argument
	println(arg);
	// call println recursively using pack expansion syntax for the rest of the arguments
	println(std::forward<Args>(args)...);
}



// ================================================================================================
// PRINT_PAD  - Enumeration that allows print_all to select which side you want the printed 
//              element to be padded to.
// PRINT_ALL  - Print all items in a range with multitude of fromatting options.
// ================================================================================================




/// Enumeraction that allows to set the padding for mtl::console::print_all.
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

// Adds padding to a string based on how big is the largest item with a given padding style.
inline void print_padding_impl(std::string& item, const size_t largest, 
							   const print_pad padding_style)
{
	const size_t item_size = item.size();
	// check that the item can be padded based on size
	if (item_size < largest)
	{
		// pad based on the selected padding style
		if (padding_style == print_pad::front)
		{
			mtl::string::pad_front(item, largest - item_size, ' ');
		}
		else if (padding_style == print_pad::both_front)
		{
			mtl::string::pad(item, largest - item_size, ' ', false);
		}
		else if (padding_style == print_pad::both_back)
		{
			mtl::string::pad(item, largest - item_size, ' ', true);
		}
		else if (padding_style == print_pad::back)
		{
			mtl::string::pad_back(item, largest - item_size, ' ');
		}
	}
}

} // namespace detail end



/// Prints to console all items in a range. The newline_count affects after how many items the
/// newline character will be used. Delimiter is a string used between all elements.
/// The line_start affects what gets printed when a new line starts and line_end affects what is
/// printed when a line ends. Padding style allows you to pass an enumeration to select which side
/// you want all elements to be padded. Padding only works with items that are ASCII characters.
/// @param[in] first An iterator to the start of the range.
/// @param[in] last An iterator to the end of the range.
/// @param[in] delimiter An optional delimiter to use between each element.
/// @param[in] newline_count The optional number of items after we print a new line.
/// @param[in] line_start An optional text to print on the start of a new line.
/// @param[in] line_end An optional text to print on the end of a new line.
/// @param[in] padding_style The optional mtl::console::print_pad style used to pad elements.
template<typename Iter>
inline void print_all(Iter first, Iter last, const std::string& delimiter = "", 
					  size_t newline_count = 0, const std::string& line_start = "", 
					  const std::string& line_end = "",  
					  mtl::console::print_pad padding_style = mtl::console::print_pad::none)
{
	if (first == last) { return; }

	// convert all items to strings and keep them in a container to facilitate further processing
	std::vector<std::string> items;

	// find the number of elements
	auto size_temp = std::distance(first, last);

#ifndef MTL_DISABLE_SOME_ASSERTS 
	// if the number of elements are less than 0 the iterators passed are incorrect
	MTL_ASSERT_MSG(!(size_temp < 0), "Incorrect iterators passed.");
#endif

	// if iterators passed are 0 or negative do nothing
	if (size_temp <= 0) { return; }

	// convert the std::ptrdiff type to size_t this is safe as we checked it is not negative
	const size_t size = static_cast<size_t>(size_temp);

	// GCOVR_EXCL_START
	// reserve vector size to avoid unnecessary allocations
	items.reserve(size);

	// convert all elements to strings and place them in the vector
	for (auto it = first; it != last; ++it)
	{
		items.emplace_back(mtl::string::to_string(*it));
	}

	
	// find the size of the string with the largest length so we can add padding
	size_t largest = (std::max_element(items.begin(), items.end(),
									   [](const auto& lhs, const auto& rhs)
									   { return lhs.size() < rhs.size(); }))->size();

	// create a memory buffer
	fmt::memory_buffer memory;
	// reserve some memory to avoid allocations, memory reserved is how many characters we want,
	// we are somewhat convervative to avoid allocating way more memory than we need
	memory.reserve(items.size() * 5);

	// print the items in the console with newline characters
	if (newline_count > 0)
	{
		// counter to keep track when to change line
		size_t newline_counter = 0;

		// countdown counter to keep track if it is the last element
		size_t last_counter = size;

		for (auto& item : items)
		{
			
			// if counter is 0 it means a new line is just starting
			if (newline_counter == 0)
			{
				fmt::format_to(memory, "{}", line_start); 
			}

			// pad the item with the given padding style
			mtl::console::detail::print_padding_impl(item, largest, padding_style); 

			// print the item, in our case just hold it in the memory buffer
			fmt::format_to(memory, "{}", item); 

			// adjust the counters
			++newline_counter;
			--last_counter;
			
			
			// check if we should print a delimiter or a line end character based on the counters
			if ((newline_counter < newline_count) && (last_counter > 0)) 
			{
				fmt::format_to(memory, "{}", delimiter); 
			}
			else
			{
				fmt::format_to(memory, "{}\n", line_end); 
				newline_counter = 0;
			}
			
		}
	}
	// print the items to the console without newline characters
	else
	{

		fmt::format_to(memory, "{}", line_start); 
		for (size_t i = 0; i < items.size(); ++i)
		{
			// pad the item with the given padding style
			mtl::console::detail::print_padding_impl(items[i], largest, padding_style); 
			

			// print the item, in our case just hold it in the memory buffer
			fmt::format_to(memory, "{}", items[i]); 

			// print the delimiter if it is not the last item
			if (i < items.size() - 1) 
			{ 
				fmt::format_to(memory, "{}", delimiter); 
			}
		}
		fmt::format_to(memory, "{}", line_end); 
		
	}
	// write the entire memory buffer to console, benchmarks show we gained 4x or more speed
	// compared to the old code where we writing each individual item to console one at a time
	fmt::print("{}", fmt::to_string(memory));
	// GCOVR_EXCL_STOP
}








// ================================================================================================
// COLOR - Enumeration for all the colors that can be used with console.
// ================================================================================================


/// Enumartion of the standard terminal colors that can be used to output color to the
/// console plus one extra for the default color.
enum class color : uint8_t
{
	// color sort order and codes from taken from https:// i.stack.imgur.com/9UVnC.png

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
	// we use an std::lock_guard because we want this function to be thread safe
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
		throw std::runtime_error("Error. Can't get console window handle.");
	}

	// get the screen buffer information for the current console
	if (!GetConsoleScreenBufferInfo(console_handle, &console_screen_buff_info))
	{
		throw std::runtime_error("Error. Could not get console's screen buffer information.");
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


	// color sort order and codes from taken from https:// i.stack.imgur.com/9UVnC.png

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

	bool contains_newline = false;

	// if the argument is of type string check if it contains a newline character
	if constexpr (mtl::is_std_string_v<decltype(arg)>)
	{
		contains_newline = (arg.find('\n') != std::string::npos);
	}

	// if the argument is of type const char* check if it contains a newline character
	if constexpr (mtl::is_c_string_v<decltype(arg)>)
	{
		auto size = std::strlen(arg);
		if (size > 0)
		{
			auto found = std::find(arg, arg + size, '\n');
			if (found != (arg + size))
			{
				contains_newline = true;
			}
		}
	}

	// if the string / const char* contains a new line inside it loop over and print each part
	// seperately and print the newline with the old color attributes to prevent color spilling
	// to the other lines
	if (contains_newline)
	{
		// convert to a std::string from either std::string or const char* to make it easier to
		// work with
		std::string argument_newline = mtl::string::to_string(arg);

		// remember the start position
		size_t start = 0;
		// position of the first match
		size_t match_pos = argument_newline.find('\n');

		// keep the position for the last item
		size_t last_pos = 0;

		// print all parts except the last one
		while (match_pos != std::string::npos)
		{
			last_pos = match_pos;

			// set foreground and background colors to the selected color
			if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
			{
				throw std::runtime_error(
					  "Error. Could not set console's attributes successfully.");
			}

			// get the part
			std::string part = argument_newline.substr(start, match_pos - start);

			// print the part
			fmt::print("{}", part);

			// set foreground and background colors back to default colors
			if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
			{
				throw std::runtime_error(
					  "Error. Could not set console's attributes successfully.");
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
			auto part = argument_newline.substr(last_pos + 1);
			// set foreground and background colors to the selected color
			if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
			{
				throw std::runtime_error(
					  "Error. Could not set console's attributes successfully.");
			}

			fmt::print("{}", part);

			// set foreground and background colors back to default colors
			if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
			{
				throw std::runtime_error(
					  "Error. Could not set console's attributes successfully.");
			}
		}
	}

	// if the string / const char* doesn't contain the newline character
	else
	{
		// set foreground and background colors to the selected color
		if (!SetConsoleTextAttribute(console_handle, fg_color | bg_color))
		{
			throw std::runtime_error("Error. Could not set console's attributes successfully.");
		}

		// print the argument passed to the function
		fmt::print("{}", arg);

		// set foreground and background colors back to normal
		if (!SetConsoleTextAttribute(console_handle, original_fg | original_bg))
		{
			throw std::runtime_error("Error. Could not set console's attributes successfully.");
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
	// color sort order and codes from taken from https:// i.stack.imgur.com/9UVnC.png

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


	bool contains_newline = false;

	// if the argument is of type string check if it contains a newline character
	if constexpr (mtl::is_std_string_v<decltype(arg)>)
	{
		contains_newline = (arg.find('\n') != std::string::npos);
	}

	// if the argument is of type const char* check if it contains a newline character
	if constexpr (mtl::is_c_string_v<decltype(arg)>)
	{
		auto size = std::strlen(arg);
		if (size > 0)
		{
			auto found = std::find(arg, arg + size, '\n'); // GCOVR_EXCL_LINE
			if (found != (arg + size))
			{
				contains_newline = true;
			}
		}
	}

	// if the string / const char* contains a new line inside it loop over and print each part
	// seperately and print the newline with the old color attributes to prevent color spilling
	// to the other lines
	if (contains_newline)
	{
		// convert to a std::string from either std::string or const char* to make it easier to
		// work with
		std::string argument_newline = mtl::string::to_string(arg); // GCOVR_EXCL_LINE

		// remember the start position
		size_t start = 0;
		// position of the first match
		size_t match_pos = argument_newline.find('\n');

		// keep the position for the last item
		size_t last_pos = 0;

		// print all parts except the last one
		while (match_pos != std::string::npos)
		{
			last_pos = match_pos;

			// GCOVR_EXCL_START
			
			// get the part
			std::string part = argument_newline.substr(start, match_pos - start);
			

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
			auto part = argument_newline.substr(last_pos + 1);

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



// The actual implementaion of print_color that select if it will print color usinng ASCII.
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
		fmt::print(argument);
		return;
	}
	// GCOVR_EXCL_STOP

    // create a string consisting of \b that will move the cursor back, this allows us to avoid
    // printing \b multiple times and we instead need to print only once, this is a significant
    // performance gain in the range of 2x to 8x times faster
    std::string multiple_backspaces(argument.size(), '\b');
    fmt::print(multiple_backspaces);
	
	fmt::print(argument);
	// flush the buffer so the console is updated, it is threadsafe both in Windows and Linux
	std::fflush(stdout);
}

/// Allows you to print over already printed characters to the console. Flushes the stdout buffer 
/// on every call. Can only overtype characters that are not on a previous line. Can only overtype 
/// characters when the output is a console and not when redirecting to a file or a pipe.
/// @param[in] argument An argument to overtype.
inline void overtype(const char* argument)
{
	// GCOVR_EXCL_START
	// if we are not inside a terminal just print the characters and return
	if (mtl::console::detail::inside_terminal == false) 
	{
		fmt::print(argument); 
		return;
	}
	// GCOVR_EXCL_STOP

	size_t size = std::strlen(argument);
	// create a string consisting of \b that will move the cursor back, this allows us to avoid
    // printing \b multiple times and we instead need to print only once, this is a significant
    // performance gain in the range of 2x to 8x times faster
	std::string multiple_backspaces(size, '\b');
	fmt::print(multiple_backspaces);
	
	fmt::print(argument);
	// flush the buffer so the console is updated, it is threadsafe both in Windows and Linux
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

		// we use an std::lock_guard because we want this function to be thread safe
		std::lock_guard<std::mutex> lockg(mtl::console::detail::console_mutex_legacy_win);

		// get the handle for the current console
		HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (console_handle == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("Error. Can't get console window handle.");
		}
		// intiialize screen coordinates to 0, 0 for the cursor
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
			throw std::runtime_error("Error. Can't get console screen buffer information.");
		}

		// after getting console screen buffer information we can find the console size
		console_size = static_cast<DWORD>(console_screen_buff_info.dwSize.X *
										  console_screen_buff_info.dwSize.Y);

		// fill the screen with blank characters
		if (!FillConsoleOutputCharacter(console_handle,          // handle for which console to use
										static_cast<TCHAR>(' '), // use the blank character
										console_size,            // number of times to write 
										screen_coordinates,      // the starting coordinates
										&number_chars_written))  // number of characters written
		{
			throw std::runtime_error("Error. Can't fill console with given character.");
		}

		// retrieve the screen attributes for the console and store them to the
		// console screen buffer info
		if (!GetConsoleScreenBufferInfo(console_handle, &console_screen_buff_info))
		{
			throw std::runtime_error("Error. Can't get console screen buffer information.");
		}

		// set console attributes appropriately
		if (!FillConsoleOutputAttribute(console_handle,          // handle for which console to use
										console_screen_buff_info.wAttributes, // char attributes
										console_size,            // number of times to write 
										screen_coordinates,      // the starting coordinates
										&number_chars_written))  // number of characters written
		{
			throw std::runtime_error("Error. Can't set console attributes.");
		}

		// set the cursor at the starting position
		if (!SetConsoleCursorPosition(console_handle, screen_coordinates))
		{
			throw std::runtime_error("Error. Can't the cursor position.");
		}

	}
#endif
    
}





} // namespace console end
} // namespace mtl end