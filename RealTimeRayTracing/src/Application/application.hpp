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
private:
	bool m_mainLoopCondition = true;
	
	Window m_window;
	Timer timer;

	Camera camera;

	void processInput();
};
