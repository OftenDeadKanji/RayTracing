#include "eventManager.h"
#include "../Keyboard/keyboard.h"
#include "../Mouse/mouse.h"

void EventManager::windowResizeCallback(const vec2& size)
{
	this->eventQueue.push(EventType::WindowResized);
}

void EventManager::windowCloseCallback(bool shouldWindowClose)
{
	if (shouldWindowClose)
	{
		this->eventQueue.push(EventType::WindowClosed);
	}
}

void EventManager::keyboardKeyCallback(KeyboardKey key, KeyboardKeyAction action)
{
	if (key != KeyboardKey::KeyNone)
	{
		if (action == KeyboardKeyAction::Pressed)
		{
			Keyboard::keys[static_cast<size_t>(key)] = true;
			this->eventQueue.push(EventType::KeyboardKeyPressed);
		}
		else if (action == KeyboardKeyAction::Released)
		{
			Keyboard::keys[static_cast<size_t>(key)] = false;
			this->eventQueue.push(EventType::KeyboardKeyReleased);
		}
	}
}

void EventManager::mouseButtonCallback(MouseButton button, MouseButtonAction action)
{
	if (action == MouseButtonAction::Pressed)
	{
		Mouse::buttons[static_cast<size_t>(button)] = true;
		this->eventQueue.push(EventType::MouseButtonPressed);
	}
	else if (action == MouseButtonAction::Released)
	{
		Mouse::buttons[static_cast<size_t>(button)] = false;
		this->eventQueue.push(EventType::MouseButtonReleased);
	}
}

void EventManager::cursorPositionCallback(const vec2& position)
{
	Mouse::position = position;
	this->eventQueue.push(EventType::MouseCursorMoved);
}

void EventManager::checkForEvents()
{
	glfwPollEvents();
}

bool EventManager::isEventQueueEmpty() const
{
	return this->eventQueue.empty();
}

void EventManager::clearEventQueue()
{
	while (!this->eventQueue.empty())
	{
		this->eventQueue.pop();
	}
}

EventType EventManager::getEventTypeFromQueue()
{
	const auto tmp = this->eventQueue.front();
	this->eventQueue.pop();

	return tmp;
}
