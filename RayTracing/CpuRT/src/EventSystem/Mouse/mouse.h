#pragma once
#include <array>
#include "mouseButton.h"
#include "../../Utilities/types.h"

struct Mouse
{
	static std::array<bool, static_cast<size_t>(MouseButton::Count)> buttons;
	static vec2 position;
};
