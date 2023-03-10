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

	void onWindowClose()
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onWindowClose();
		}
	}

	void onWindowResize(const math::Vec2i& newSize)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onWindowResize(newSize);
		}
	}

	void onKeyPressed(int key)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onKeyPressed(key);
		}
	}

	void onKeyReleased(int key)
	{
		for (auto* listeners : m_windowListeners)
		{
			listeners->onKeyReleased(key);
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