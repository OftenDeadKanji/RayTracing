#include "application.hpp"
#include "EventSystem/eventManager.hpp"
#include "../RenderingSystem/Renderer/renderer.hpp"

Application::Application()
{
	m_window.init(WindowProperties(
		math::Vec2i(1600, 900), WindowMode::Windowed, "Real-time ray tracing", true
	));

	auto* renderer = Renderer::createInstance();
	renderer->initScreenTexture(m_window.getSize() / 2);
	
	auto* scene = Scene::createInstance();
	scene->setBackgroundColor({ 1.0f, 0.9f, 0.15f });

	auto* eventManager = EventManager::createInstance();
	eventManager->addWindowListener(this);

	camera.setPerspective(45.0f, static_cast<float>(m_window.getSize().x()) / m_window.getSize().y(), 0.1f, 1000.0f);
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
		m_deltaTime = timer.getTimeInSec();
		if (m_deltaTime >= (1.0f / 60.0f))
		{
			m_window.setTitle("Real-time ray tracing    " + std::to_string(m_deltaTime) + "    " + std::to_string(static_cast<int>(1.0f / m_deltaTime)) + " FPS");

			timer.start();
			eventManager->checkForEvents();
			processInput();

			renderer->render(m_window, camera);
			m_window.flush();
		}
	}
}

void Application::onWindowClose()
{
	m_mainLoopCondition = false;
}

void Application::onWindowResize(const math::Vec2i& newSize)
{
	m_window.setSize(newSize);
	camera.setPerspective(45.0f, static_cast<float>(m_window.getSize().x()) / m_window.getSize().y(), 0.1f, 1000.0f);
	Renderer::getInstance()->initScreenTexture(m_window.getSize() / 2);
}

void Application::onKeyPressed(int key)
{
	m_keyStates[key] = true;
}

void Application::onKeyReleased(int key)
{
	m_keyStates[key] = false;
}

void Application::processInput()
{
	processCameraControl();
}

void Application::processCameraControl()
{
	math::Vec3f movement = { 0.0f, 0.0f, 0.0f };
	
	if (m_keyStates[GLFW_KEY_W])
	{
		movement.z() += m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_S])
	{
		movement.z() -= m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_D])
	{
		movement.x() += m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_A])
	{
		movement.x() -= m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_LEFT_CONTROL])
	{
		movement.y() += m_cameraMovementSpeed;
	}
	if (m_keyStates[GLFW_KEY_SPACE])
	{
		movement.y() -= m_cameraMovementSpeed;
	}

	if (m_keyStates[GLFW_KEY_LEFT_SHIFT])
	{
		movement *= m_cameraMovementSpeedup;
	}

	movement *= m_deltaTime;

	camera.addLocalPosition(movement);
	camera.update();
}
