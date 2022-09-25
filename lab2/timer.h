// Workshop 2
// Sunny Qi - 2022/09/25

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_finish;
		std::chrono::duration<double> m_duration;
	public:
		Timer();
		void start();
		long long stop();
	};
}
#endif // !SDDS_TIMER_H
