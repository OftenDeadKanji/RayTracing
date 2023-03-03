#include "application.hpp"
#include "EventSystem/eventManager.hpp"
#include "../RenderingSystem/Renderer/renderer.hpp"

Application::Application()
{
	m_window.init(WindowProperties(
		math::Vec2i(1600, 900), WindowMode::Windowed, "Real-time ray tracing", false
	));

	auto* renderer = Renderer::createInstance();
	renderer->initScreenTexture(math::Vec2i(1600, 900));
	
	auto* scene = Scene::createInstance();
	scene->setBackgroundColor({ 1.0f, 0.9f, 0.15f });

	auto* eventManager = EventManager::createInstance();
	eventManager->addWindowListener(this);
}

void Application::run()
{
	auto* eventManager = EventManager::getInstance();
	auto* renderer = Renderer::getInstance();

	while (m_mainLoopCondition)
	{
		eventManager->checkForEvents();
		processInput();

		renderer->render();
		m_window.flush();
	}
}

void Application::onWindowClose()
{
	m_mainLoopCondition = false;
}

void Application::processInput()
{
}
