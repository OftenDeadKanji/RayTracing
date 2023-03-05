#ifndef __TIMER_HPP__
#define __TIMER_HPP__
#include <chrono>

class Timer
{
public:
	void start()
	{
		m_start = clock::now();
	}
	void stop()
	{
		m_end = clock::now();
	}

	float getTimeInSec() const
	{
		return duration(m_end - m_start).count();
	}
private:
	using clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<float>;
	clock::time_point m_start, m_end;
};

#endif
