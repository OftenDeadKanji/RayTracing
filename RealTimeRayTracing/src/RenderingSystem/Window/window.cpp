#include "window.hpp"
#include "../../Application/EventSystem/eventManager.hpp"
#include <iostream>

#pragma region GLFW Callbacks

void window_close_callback(GLFWwindow* window)
{
	EventManager::getInstance()->onWindowClose(window);
}

void window_resize_callback(GLFWwindow* window, int width, int height)
{
	EventManager::getInstance()->onWindowResize(window, math::Vec2i(width, height));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		EventManager::getInstance()->onKeyPressed(window, key);
	}
	else if (action == GLFW_RELEASE)
	{
		EventManager::getInstance()->onKeyReleased(window, key);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			EventManager::getInstance()->onLeftMouseButtonPressed(window);
		}
		else if (action == GLFW_RELEASE)
		{
			EventManager::getInstance()->onLeftMouseButtonReleased(window);
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			EventManager::getInstance()->onRightMouseButtonPressed(window);
		}
		else if (action == GLFW_RELEASE)
		{
			EventManager::getInstance()->onRightMouseButtonReleased(window);
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	EventManager::getInstance()->onMouseMove(window, math::Vec2i(xpos, ypos));
}
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

	//glfwSwapInterval(1);

	glfwSetWindowCloseCallback(m_glfwWindow, window_close_callback);
	glfwSetWindowSizeCallback(m_glfwWindow, window_resize_callback);
	glfwSetKeyCallback(m_glfwWindow, key_callback);
	glfwSetMouseButtonCallback(m_glfwWindow, mouse_button_callback);
	glfwSetCursorPosCallback(m_glfwWindow, cursor_position_callback);

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
