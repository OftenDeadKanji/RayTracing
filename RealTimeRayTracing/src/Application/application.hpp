#pragma once
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

	math::Vec2i m_mousePosition{};
	math::Vec2i m_mousePreviousPosition{};
	math::Vec2i m_mousePositionDelta{}; // mouse position difference since last frame

	bool m_leftMouseButtonState{}, m_rightMouseButtonState{};
	math::Vec2i m_mousePositionOnLeftClick{}, m_mousePositionOnRightClick{};
	math::Vec2i m_leftMouseButtonHoldPositionDelta{}, m_rightMouseButtonHoldPositionDelta{}; // mouse position difference since LMB/RMB was clicked

	Camera camera;
	float m_cameraMovementSpeed = 10.0f;
	float m_cameraMovementSpeedup = 10.0f;
	float m_cameraRotationSpeed = 0.001f;

	void processInput();
	void processCameraControl();
};
