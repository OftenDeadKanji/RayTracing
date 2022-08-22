#include "eventManager.h"
#include "../Keyboard/keyboard.h"
#include "../Mouse/mouse.h"

void EventManager::windowResizeCallback(const vec2& size)
{
	this->m_eventQueue.push(EventType::WindowResized);
}

void EventManager::windowCloseCallback(bool shouldWindowClose)
{
	if (shouldWindowClose)
	{
		this->m_eventQueue.push(EventType::WindowClosed);
	}
}

void EventManager::keyboardKeyCallback(KeyboardKey key, KeyboardKeyAction action)
{
	if (key != KeyboardKey::KeyNone)
	{
		if (action == KeyboardKeyAction::Pressed)
		{
			Keyboard::keys[static_cast<size_t>(key)] = true;
			this->m_eventQueue.push(EventType::KeyboardKeyPressed);
		}
		else if (action == KeyboardKeyAction::Released)
		{
			Keyboard::keys[static_cast<size_t>(key)] = false;
			this->m_eventQueue.push(EventType::KeyboardKeyReleased);
		}
	}
}

void EventManager::mouseButtonCallback(MouseButton button, MouseButtonAction action)
{
	if (action == MouseButtonAction::Pressed)
	{
		Mouse::buttons[static_cast<size_t>(button)] = true;
		this->m_eventQueue.push(EventType::MouseButtonPressed);
	}
	else if (action == MouseButtonAction::Released)
	{
		Mouse::buttons[static_cast<size_t>(button)] = false;
		this->m_eventQueue.push(EventType::MouseButtonReleased);
	}
}

void EventManager::cursorPositionCallback(const vec2& position)
{
	Mouse::position = position;
	this->m_eventQueue.push(EventType::MouseCursorMoved);
}

void EventManager::checkForEvents()
{
	glfwPollEvents();
}

bool EventManager::isEventQueueEmpty() const
{
	return this->m_eventQueue.empty();
}

void EventManager::clearEventQueue()
{
	while (!this->m_eventQueue.empty())
	{
		this->m_eventQueue.pop();
	}
}

EventType EventManager::getEventTypeFromQueue()
{
	const auto tmp = this->m_eventQueue.front();
	this->m_eventQueue.pop();

	return tmp;
}
