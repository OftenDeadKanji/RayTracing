#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>

class ThreadPool
{
public:
	void start();
	void queueTask(const std::function<void()>& task);
	void stop();
	void waitToFinish();
private:
	bool m_shouldTerminate = false;
	
	std::mutex m_mutexQueue;
	std::condition_variable m_conditionalForMutex;

	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;

	int m_idleThreads;
	std::mutex m_mutexIdleThread;
	std::condition_variable m_conditionalIdleThread;

	void threadLoop();
};

#endif
