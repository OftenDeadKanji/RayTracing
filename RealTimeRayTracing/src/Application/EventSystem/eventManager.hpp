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
	static EventManager* createInstance();

	static void deleteInstance();
	static EventManager* getInstance();

	void addWindowListener(IWindowListener* listener);
	
	void onWindowClose(GLFWwindow* window);
	void onWindowResize(GLFWwindow* window, const math::Vec2i& newSize);
	void onKeyPressed(GLFWwindow* window, int key);
	void onKeyReleased(GLFWwindow* window, int key);
	void onMouseMove(GLFWwindow* window, const math::Vec2i& newPos);
	void onLeftMouseButtonPressed(GLFWwindow* window);
	void onLeftMouseButtonReleased(GLFWwindow* window);
	void onRightMouseButtonPressed(GLFWwindow* window);
	void onRightMouseButtonReleased(GLFWwindow* window);
	
	void checkForEvents();
private:
	static std::unique_ptr<EventManager> s_instance;
	std::vector<IWindowListener*> m_windowListeners;
};

#pragma region Inline methods definitions
inline EventManager* EventManager::createInstance()
{
	s_instance = std::unique_ptr<EventManager>(new EventManager());
	return s_instance.get();
}

inline void EventManager::deleteInstance()
{
	s_instance.release();
}

inline EventManager* EventManager::getInstance()
{
	return s_instance.get();
}

inline void EventManager::addWindowListener(IWindowListener* listener)
{
	m_windowListeners.push_back(listener);
}

inline void EventManager::onWindowClose(GLFWwindow* window)
{
	for (auto* listeners : m_windowListeners)
	{
		listeners->onWindowClose();
	}
}

inline void EventManager::onWindowResize(GLFWwindow* window, const math::Vec2i& newSize)
{
	for (auto* listeners : m_windowListeners)
	{
		listeners->onWindowResize(newSize);
	}
}

inline void EventManager::onKeyPressed(GLFWwindow* window, int key)
{
	for (auto* listeners : m_windowListeners)
	{
		listeners->onKeyPressed(key);
	}
}

inline void EventManager::onKeyReleased(GLFWwindow* window, int key)
{
	for (auto* listeners : m_windowListeners)
	{
		listeners->onKeyReleased(key);
	}
}

inline void EventManager::onMouseMove(GLFWwindow* window, const math::Vec2i& newPos)
{
	for (auto* listeners : m_windowListeners)
	{
		listeners->onMouseMove(newPos);
	}
}

inline void EventManager::onLeftMouseButtonPressed(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	for (auto* listeners : m_windowListeners)
	{
		listeners->onLeftMouseButtonPressed(math::Vec2i(x, y));
	}
}

inline void EventManager::onLeftMouseButtonReleased(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	for (auto* listeners : m_windowListeners)
	{
		listeners->onLeftMouseButtonReleased(math::Vec2i(x, y));
	}
}

inline void EventManager::onRightMouseButtonPressed(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	for (auto* listeners : m_windowListeners)
	{
		listeners->onRightMouseButtonPressed(math::Vec2i(x, y));
	}
}

inline void EventManager::onRightMouseButtonReleased(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	for (auto* listeners : m_windowListeners)
	{
		listeners->onRightMouseButtonReleased(math::Vec2i(x, y));
	}
}

inline void EventManager::checkForEvents()
{
	glfwPollEvents();
}
#pragma endregion

inline std::unique_ptr<EventManager> EventManager::s_instance = nullptr;

#endif
