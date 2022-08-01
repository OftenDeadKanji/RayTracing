#pragma once
#include "GLFW/glfw3.h"

enum class MouseButtonAction
{
	None,

	Pressed,
	Released
};

inline MouseButtonAction convertToMouseButtonAction(int glfw_action)
{
	switch (glfw_action)
	{
	default:
		return MouseButtonAction::None;
	case GLFW_PRESS:
		return MouseButtonAction::Pressed;
	case GLFW_RELEASE:
		return MouseButtonAction::Released;
	}
}
