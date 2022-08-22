#pragma once
#include "../Utilities/types.h"
#include <string>

struct WindowProperties
{
	WindowProperties(const vec2i& size, std::string title);
	WindowProperties(const WindowProperties& other);
	WindowProperties(WindowProperties&& other) noexcept;

	WindowProperties& operator=(const WindowProperties& other);
	WindowProperties& operator=(WindowProperties&& other) noexcept;

	vec2i size;
	std::string title;
};