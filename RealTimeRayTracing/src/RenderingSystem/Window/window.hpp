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

	void setSize(const math::Vec2i& size)
	{
		m_properties.size = size;
		glViewport(0, 0, m_properties.size.x(), m_properties.size.y());
	}

	void setTitle(std::string title)
	{
		m_properties.title = std::move(title);
		glfwSetWindowTitle(m_glfwWindow, m_properties.title.c_str());
	}

private:
	WindowProperties m_properties;
	GLFWwindow* m_glfwWindow;

	void createWindowedWindow();
	void createFullsreenWindow();

	void centerWindow();
};

#endif
