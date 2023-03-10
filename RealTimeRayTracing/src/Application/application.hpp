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
private:
	bool m_mainLoopCondition = true;
	
	Window m_window;

	Timer timer;
	float m_deltaTime{};

	bool m_keyStates[GLFW_KEY_LAST + 1]{};

	Camera camera;
	float m_cameraMovementSpeed = 10.0f;
	float m_cameraMovementSpeedup = 10.0f;

	void processInput();
	void processCameraControl();
};
