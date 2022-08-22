#pragma once
#include "eventType.h"
#include "../Keyboard/keyboardKey.h"
#include "../Keyboard/keyboardKeyAction.h"
#include "../Mouse/mouseButton.h"
#include "../Mouse/mouseButtonAction.h"
#include <queue>
#include "../../Utilities/types.h"

class EventManager
{
public:
	void windowResizeCallback(const vec2& size);
	void windowCloseCallback(bool shouldWindowClose);

	void keyboardKeyCallback(KeyboardKey key, KeyboardKeyAction action);

	void mouseButtonCallback(MouseButton button, MouseButtonAction action);
	void cursorPositionCallback(const vec2& position);

	void checkForEvents();

	bool isEventQueueEmpty() const;
	void clearEventQueue();
	EventType getEventTypeFromQueue();
protected:
	std::queue<EventType> m_eventQueue;
};
