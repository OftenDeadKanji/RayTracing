#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__
#include "windowProperties.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

class Window
{
public:
	Window() = default;
	~Window();

	void init(WindowProperties m_properties);

	void flush()
	{
		glfwSwapBuffers(m_glfwWindow);
	}

	math::Vec2i getSize() const
	{
		return m_properties.size;
	}

private:
	WindowProperties m_properties;
	GLFWwindow* m_glfwWindow;

	void createWindowedWindow();
	void createFullsreenWindow();

	void centerWindow();
};

#endif
