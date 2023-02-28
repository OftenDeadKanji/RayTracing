#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__
#include "windowProperties.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window() = default;

	void init(WindowProperties m_properties);
private:
	WindowProperties m_properties;
	GLFWwindow* m_glfwWindow;

	void createWindowedWindow();
	void createFullsreenWindow();

	void centerWindow();
};

#endif
