#pragma once
#include <chrono>

namespace Time {
	//Timer in milliseconds.
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> end;
		std::chrono::duration<double, std::milli> duration;
	public:
		void Start() {
			start = std::chrono::high_resolution_clock::now();
		}
		void Stop() {
			//Stop the clock.
			end = std::chrono::high_resolution_clock::now();
			//Calculate time difference.
			duration = std::chrono::duration<double, std::milli>(end - start);
		}
		double Duration() { return duration.count(); }

	};
}