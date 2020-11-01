#pragma once
// stopwatch by Michael Trikergiotis
// 02/07/2017
//  
// Header for mtl::chrono::stopwatch.
// 
// For information about third party licenses check ThirdPartyNotices.txt.



#include <chrono> // std::chrono::time_point, std::chrono::high_resolution_clock,
				  // std::chrono::duration, std::milli, std::micro, std::nano


namespace mtl
{

namespace chrono
{


// ================================================================================================
// STOPWATCH - Stopwatch that counts time between two time points and returns the difference.
// ================================================================================================


/// Stopwatch that counts time between two time points and returns the difference. Full compiler
/// optimizations should be turned on to get more accurate timings.
class stopwatch
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
public:

	/// Starts the stopwatch.
	void start()
	{
		start_time = std::chrono::high_resolution_clock::now();
	}

	/// Stops the stopwatch.
	void stop()
	{
		end_time = std::chrono::high_resolution_clock::now();
	}

	/// Stops measuring and resets everything to 0.
	void reset()
	{
		start();
		end_time = start_time;
	}

	/// Stops previous measurment and start measuring time from the current time point.
	void restart()
	{
		start();
	}

	/// Returns the time elapsed in minutes.
	/// @return The number of elapsed minutes.
	double elapsed_minutes()
	{
		std::chrono::duration<double> elapsed = end_time - start_time;
		double result = elapsed.count();
		// we have to divide seconds by 60.0 to find minutes, but instead we perform division by
		// an invaritant number using multication as it is much faster than a costly division
		result = result * 0.016666666666666667406815349750104360282421112060546875;
		return result;
	}

	/// Returns the time elapsed in seconds.
	/// @return The number of elapsed seconds.
	double elapsed_seconds()
	{
		std::chrono::duration<double> elapsed = end_time - start_time;
		double result = elapsed.count();
		return result;
	}

	/// Returns the time elapsed in milliseconds.
	/// @return The number of elapsed milliseconds.
	double elapsed_milli()
	{
		std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
		double result = elapsed.count();
		return result;
	}

	/// Returns the time elapsed in microseconds.
	/// @return The number of elapsed microseconds.
	double elapsed_micro()
	{
		std::chrono::duration<double, std::micro> elapsed = end_time - start_time;
		double result = elapsed.count();
		return result;
	}

	/// Returns the time elapsed in nanoseconds.
	/// @return The number of elapsed nanoseconds.
	double elapsed_nano()
	{
		std::chrono::duration<double, std::nano> elapsed = end_time - start_time;
		double result = elapsed.count();
		return result;
	}
};


} // namespace chrono end
} // namespace mtl end