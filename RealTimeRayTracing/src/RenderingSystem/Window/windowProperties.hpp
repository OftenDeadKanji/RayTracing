#ifndef __WINDOW_PROPERTIES_HPP__
#define __WINDOW_PROPERTIES_HPP__
#include "windowMode.hpp"
#include "../../Math/mathUtils.hpp"
#include <string>

struct WindowProperties
{
	math::Vec2i size;
	WindowMode mode;
	std::string title;
	bool resizable;

	WindowProperties() = default;
	WindowProperties(const math::Vec2i& size, WindowMode mode, std::string title, bool resizable)
		: size(size), mode(mode), title(std::move(title)), resizable(resizable)
	{}
};

#endif