#pragma once
#include "../RenderingSystem/Window/window.hpp"
#include "EventSystem/IWindowListener.hpp"
#include "../Utils/Timer/timer.hpp"

class Application
	: public IWindowListener
{
public:
	Application();

	void run();

	void onWindowClose() override;
private:
	bool m_mainLoopCondition = true;
	
	Window m_window;
	Timer timer;
	void processInput();
};
