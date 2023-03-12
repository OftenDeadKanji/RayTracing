#ifndef __EVENT_MANAGER_HPP
#define __EVENT_MANAGER_HPP
#include "IWindowListener.hpp"
#include "../../Utils/nonCopyable.hpp"
#include <memory>
#include <vector>

#include "GLFW/glfw3.h"

class EventManager
	: public NonCopyable
{
public:
	static EventManager* createInstance()
	{
		s_instance = std::unique_ptr<EventManager>(new EventManager());
		return s_instance.get();
	}

	static void deleteInstance()
	{
		s_instance.release();
	}

	static EventManager* getInstance()
	{
		return s_instance.get();
	}

	void addWindowListener(IWindowListener* listener)
	{
		m_windowListeners.push_back(listener);
	}

	void onWindowClose(GLFWwindow* window)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onWindowClose();
		}
	}

	void onWindowResize(GLFWwindow* window, const math::Vec2i& newSize)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onWindowResize(newSize);
		}
	}

	void onKeyPressed(GLFWwindow* window, int key)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onKeyPressed(key);
		}
	}

	void onKeyReleased(GLFWwindow* window, int key)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onKeyReleased(key);
		}
	}

	void onMouseMove(GLFWwindow* window, const math::Vec2i& newPos)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onMouseMove(newPos);
		}
	}

	void onLeftMouseButtonPressed(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		for (auto* listeners : m_windowListeners)
		{
			listeners->onLeftMouseButtonPressed(math::Vec2i(x, y));
		}
	}

	void onLeftMouseButtonReleased(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		for (auto* listeners : m_windowListeners)
		{
			listeners->onLeftMouseButtonReleased(math::Vec2i(x, y));
		}
	}

	void onRightMouseButtonPressed(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		for (auto* listeners : m_windowListeners)
		{
			listeners->onRightMouseButtonPressed(math::Vec2i(x, y));
		}
	}

	void onRightMouseButtonReleased(GLFWwindow* window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		for (auto* listeners : m_windowListeners)
		{
			listeners->onRightMouseButtonReleased(math::Vec2i(x, y));
		}
	}

	void checkForEvents()
	{
		glfwPollEvents();
	}

private:
	static std::unique_ptr<EventManager> s_instance;
	std::vector<IWindowListener*> m_windowListeners;
};

#endif