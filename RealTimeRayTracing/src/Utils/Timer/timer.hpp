#ifndef __TIMER_HPP__
#define __TIMER_HPP__
#include <chrono>

class Timer
{
public:
	void start();
	void stop();

	float getTimeInSec() const;
private:
	using clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<float>;
	clock::time_point m_start, m_end;
};

#pragma region Inline methods definitions
inline void Timer::start()
{
	m_start = clock::now();
}
inline void Timer::stop()
{
	m_end = clock::now();
}

inline float Timer::getTimeInSec() const
{
	return duration(m_end - m_start).count();
}
#pragma endregion

#endif
