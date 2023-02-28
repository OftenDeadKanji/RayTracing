#include "application.hpp"
#include "EventSystem/eventManager.hpp"

Application::Application()
{
	EventManager::createInstance()->addWindowListener(this);
	
	m_window.init(WindowProperties(
		math::Vec2i(1600, 900), WindowMode::Windowed, "Real-time ray tracing", false
	));

}

void Application::run()
{
	auto* eventManager = EventManager::getInstance();
	while (m_mainLoopCondition)
	{
		eventManager->checkForEvents();
		processInput();
	}
}

void Application::onWindowClose()
{
	m_mainLoopCondition = false;
}

void Application::processInput()
{
}
