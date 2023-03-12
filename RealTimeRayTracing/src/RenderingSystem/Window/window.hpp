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

	void flush();

	math::Vec2i getSize() const;
	void setSize(const math::Vec2i& size);

	void setTitle(std::string title);

private:
	WindowProperties m_properties;
	GLFWwindow* m_glfwWindow;

	void createWindowedWindow();
	void createFullsreenWindow();

	void centerWindow();
};

#pragma region Inline methods definitions
inline void Window::flush()
{
	glfwSwapBuffers(m_glfwWindow);
}

inline math::Vec2i Window::getSize() const
{
	return m_properties.size;
}

inline void Window::setSize(const math::Vec2i& size)
{
	m_properties.size = size;
	glViewport(0, 0, m_properties.size.x(), m_properties.size.y());
}

inline void Window::setTitle(std::string title)
{
	m_properties.title = std::move(title);
	glfwSetWindowTitle(m_glfwWindow, m_properties.title.c_str());
}
#pragma endregion

#endif
