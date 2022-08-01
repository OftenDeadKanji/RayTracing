#pragma once
#include "GLFW/glfw3.h"

enum class MouseButton
{
	None = -1,

	Left = 0,
	Middle,
	Right,

	Count
};

inline MouseButton convertToMouseButton(int button)
{
	switch (button)
	{
	default:
		return MouseButton::None;
	case GLFW_MOUSE_BUTTON_LEFT:
		return MouseButton::Left;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		return MouseButton::Middle;
	case GLFW_MOUSE_BUTTON_RIGHT:
		return MouseButton::Right;
	}
}
