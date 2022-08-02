#include "application.h"

Application::Application()
{
}

void Application::run()
{
	m_lastFrameStart = std::chrono::high_resolution_clock::now();
	while(m_controller.MainLoopCondition)
	{
		const float deltaTime = calculateDeltaTime();

		m_controller.processInput(deltaTime);
		m_controller.update(deltaTime);
		m_controller.render(deltaTime);
	}
}

float Application::calculateDeltaTime()
{
	const auto currentTimePoint = std::chrono::high_resolution_clock::now();
	const std::chrono::high_resolution_clock::duration duration = m_lastFrameStart - currentTimePoint;

	m_lastFrameStart = std::chrono::high_resolution_clock::now();

	const auto deltaTime_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

	return static_cast<float>(deltaTime_ns) / 1'000'000'000.0f;
}
