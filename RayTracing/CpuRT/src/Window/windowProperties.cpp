#include "windowProperties.h"

WindowProperties::WindowProperties(const vec2i& size, std::string title)
	: size(size), title(std::move(title))
{
}

WindowProperties::WindowProperties(const WindowProperties& other)
	: size(other.size), title(other.title)
{}

WindowProperties::WindowProperties(WindowProperties&& other) noexcept
	: size(other.size), title(std::move(other.title))
{}

WindowProperties& WindowProperties::operator=(const WindowProperties& other)
{
	if(this != &other)
	{
		size = other.size;
		title = other.title;
	}

	return *this;
}

WindowProperties& WindowProperties::operator=(WindowProperties&& other) noexcept
{
	if (this != &other)
	{
		size = other.size;
		title = std::move(other.title);
	}

	return *this;
}
