#pragma once
#include "MVC/controller.h"
#include <chrono>

class Application
{
public:
	Application();
	~Application() = default;

	void run();
	float calculateDeltaTime();
private:
	MVC::Controller m_controller;
	std::chrono::high_resolution_clock::time_point m_lastFrameStart;
};

