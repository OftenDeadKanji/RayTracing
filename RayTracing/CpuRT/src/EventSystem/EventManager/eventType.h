#pragma once

enum class EventType
{
	None,

	WindowResized,
	WindowClosed,

	KeyboardKeyPressed,
	KeyboardKeyReleased,

	MouseButtonPressed,
	MouseButtonReleased,

	MouseCursorMoved
};
