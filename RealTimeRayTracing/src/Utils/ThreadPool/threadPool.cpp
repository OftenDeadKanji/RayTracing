#include "threadPool.hpp"

void ThreadPool::start()
{
	m_idleThreads = 0;

	auto threadsCount = std::thread::hardware_concurrency();
	m_threads.resize(threadsCount);
	for (auto i = 0; i < threadsCount; i++)
	{
		m_threads[i] = std::thread(&ThreadPool::threadLoop, this);
	}

}

void ThreadPool::queueTask(const std::function<void()>& task)
{
	{
		std::unique_lock<std::mutex> lock(m_mutexQueue);
		m_tasks.push(task);
	}
	m_conditionalForMutex.notify_one();
}

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock(m_mutexQueue);
		m_shouldTerminate = true;
	}

	m_conditionalForMutex.notify_all();

	for (auto& thread : m_threads)
	{
		thread.join();
	}

	m_threads.clear();
}

void ThreadPool::waitToFinish()
{
	std::unique_lock<std::mutex> lock(m_mutexIdleThread);
	m_conditionalIdleThread.wait(lock, [this] { return m_idleThreads == m_threads.size() && m_tasks.empty(); });
}

void ThreadPool::threadLoop()
{
	while (true)
	{
		std::function<void()> task;
		{
			std::unique_lock<std::mutex> lock(m_mutexQueue);
			
			{
				std::unique_lock<std::mutex> lockIdle(m_mutexIdleThread);
				m_idleThreads++;

				m_conditionalIdleThread.notify_one();
			}

			m_conditionalForMutex.wait(lock, [this] {
				return !m_tasks.empty() || m_shouldTerminate;
				});

			if (m_shouldTerminate)
			{
				return;
			}

			{
				std::unique_lock<std::mutex> lockIdle(m_mutexIdleThread);
				m_idleThreads--;
			}

			task = m_tasks.front();
			m_tasks.pop();
		}

		task();
	}
}
