#include "window.hpp"
#include "../../Application/EventSystem/eventManager.hpp"
#include <iostream>

#pragma region GLFW Callbacks
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);

	std::cout << width << '\t' << height << '\n';
}

void window_close_callback(GLFWwindow* window)
{
	EventManager::getInstance()->onWindowClose();
}

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	std::cout << width << '\t' << height << '\n';
}

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
//	if (userWindow)
//	{
//		keyCallback(userWindow, key, scancode, action, mods);
//	}
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
//	if (userWindow)
//	{
//		mouseButtonCallback(userWindow, button, action, mods);
//	}
//}
//
//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	auto* userWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
//	if (userWindow)
//	{
//		cursorPositionCallback(userWindow, xpos, ypos);
//	}
//}
#pragma endregion

Window::~Window()
{
	glfwDestroyWindow(m_glfwWindow);
}

void Window::init(WindowProperties properties)
{
	m_properties = std::move(properties);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, m_properties.resizable);

	switch (m_properties.mode)
	{
	default: [[fallthrough]];
	case WindowMode::Windowed:
		createWindowedWindow();
		centerWindow();
		break;
	case WindowMode::Fullscreen:
		createFullsreenWindow();
		break;
	}

	glfwMakeContextCurrent(m_glfwWindow);

	glfwSetWindowCloseCallback(m_glfwWindow, window_close_callback);
	glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);
	glfwSetWindowSizeCallback(m_glfwWindow, window_resize_callback);

	if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glViewport(0, 0, m_properties.size.x(), m_properties.size.y());
	}
}

void Window::createWindowedWindow()
{
	m_glfwWindow = glfwCreateWindow(m_properties.size.x(), m_properties.size.y(), m_properties.title.c_str(), nullptr, nullptr);
}

void Window::createFullsreenWindow()
{
	auto* monitor = glfwGetPrimaryMonitor();
	m_glfwWindow = glfwCreateWindow(m_properties.size.x(), m_properties.size.y(), m_properties.title.c_str(), monitor, nullptr);
}

void Window::centerWindow()
{
	auto* monitor = glfwGetPrimaryMonitor();
	auto mode = glfwGetVideoMode(monitor);

	math::Vec2i monitorPos;
	glfwGetMonitorPos(monitor, &monitorPos[0], &monitorPos[1]);

	math::Vec2i windowSize;
	glfwGetWindowSize(m_glfwWindow, &windowSize[0], &windowSize[1]);

	glfwSetWindowPos(m_glfwWindow, monitorPos.x() + (mode->width - windowSize.x()) / 2, monitorPos.y() + (mode->height - windowSize.y()) / 2);
}

