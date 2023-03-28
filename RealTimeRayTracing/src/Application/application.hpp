#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "../RenderingSystem/Window/window.hpp"
#include "EventSystem/IWindowListener.hpp"
#include "../Utils/Timer/timer.hpp"
#include "../RenderingSystem/Camera/camera.hpp"

class Application
	: public IWindowListener
{
public:
	Application();
	~Application();

	void run();

	void onWindowClose() override;
	void onWindowResize(const math::Vec2i& newSize) override;
	void onKeyPressed(int key) override;
	void onKeyReleased(int key) override;
	void onMouseMove(const math::Vec2i& newPos)override;
	void onLeftMouseButtonPressed(const math::Vec2i& position) override;
	void onLeftMouseButtonReleased(const math::Vec2i& position) override;
	void onRightMouseButtonPressed(const math::Vec2i& position) override;
	void onRightMouseButtonReleased(const math::Vec2i& position) override;
private:
	bool m_mainLoopCondition = true;
	
	Window m_window;

	Timer timer;
	float m_deltaTime{};

	bool m_keyStates[GLFW_KEY_LAST + 1]{};

	math::Vec2i m_mousePosition = { 0, 0 };
	math::Vec2i m_mousePreviousPosition = { 0, 0 };
	math::Vec2i m_mousePositionDelta = { 0, 0 }; // mouse position difference since last frame

	bool m_leftMouseButtonState{}, m_rightMouseButtonState{};
	math::Vec2i m_mousePositionOnLeftClick = { 0, 0 }, m_mousePositionOnRightClick = { 0, 0 };
	math::Vec2i m_leftMouseButtonHoldPositionDelta = { 0, 0 }, m_rightMouseButtonHoldPositionDelta = { 0, 0 }; // mouse position difference since LMB/RMB was clicked

	Camera camera;
	float m_cameraMovementSpeed = 20.0f;
	float m_cameraMovementSpeedup = 10.0f;
	float m_cameraRotationSpeed = 0.0025f;

	void processInput();
	void processCameraControl();
};

#pragma region Inline methods definitions
inline void Application::onWindowClose()
{
	m_mainLoopCondition = false;
}

inline void Application::onKeyPressed(int key)
{
	m_keyStates[key] = true;
}

inline void Application::onKeyReleased(int key)
{
	m_keyStates[key] = false;
}

inline void Application::onLeftMouseButtonPressed(const math::Vec2i& position)
{
	m_leftMouseButtonState = true;
	m_mousePositionOnLeftClick = position;;
}

inline void Application::onLeftMouseButtonReleased(const math::Vec2i& position)
{
	m_leftMouseButtonState = false;
	m_leftMouseButtonHoldPositionDelta = { 0, 0 };
}

inline void Application::onRightMouseButtonPressed(const math::Vec2i& position)
{
	m_rightMouseButtonState = true;
	m_mousePositionOnRightClick = position;
}

inline void Application::onRightMouseButtonReleased(const math::Vec2i& position)
{
	m_rightMouseButtonState = false;
	m_rightMouseButtonHoldPositionDelta = { 0, 0 };
}

inline void Application::processInput()
{
	processCameraControl();
}

#pragma endregion

#endif
