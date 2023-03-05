#include "application.hpp"
#include "EventSystem/eventManager.hpp"
#include "../RenderingSystem/Renderer/renderer.hpp"

Application::Application()
{
	m_window.init(WindowProperties(
		math::Vec2i(1600, 900), WindowMode::Windowed, "Real-time ray tracing", false
	));

	auto* renderer = Renderer::createInstance();
	renderer->initScreenTexture(m_window.getSize() / 2);
	
	auto* scene = Scene::createInstance();
	scene->setBackgroundColor({ 1.0f, 0.9f, 0.15f });

	auto* eventManager = EventManager::createInstance();
	eventManager->addWindowListener(this);
}

Application::~Application()
{
	EventManager::deleteInstance();
	Scene::deleteInstance();
	Renderer::deleteInstance();
}

void Application::run()
{
	auto* eventManager = EventManager::getInstance();
	auto* renderer = Renderer::getInstance();

	while (m_mainLoopCondition)
	{
		timer.stop();
		float deltaTime = timer.getTimeInSec();
		if (deltaTime >= (1.0f / 60.0f))
		{
			m_window.setTitle("Real-time ray tracing    " + std::to_string(deltaTime) + "    " + std::to_string(static_cast<int>(1.0f / deltaTime)) + " FPS");

			timer.start();
			eventManager->checkForEvents();
			processInput();

			renderer->render(m_window);
			m_window.flush();
		}
	}
}

void Application::onWindowClose()
{
	m_mainLoopCondition = false;
}

void Application::processInput()
{
}
