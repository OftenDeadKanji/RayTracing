#include "windowProperties.h"

WindowProperties::WindowProperties(int width, int height, std::string title)
	: width(width), height(height), title(std::move(title))
{
}

WindowProperties::WindowProperties(const WindowProperties& other)
	: width(other.width), height(other.height), title(other.title)
{}

WindowProperties::WindowProperties(WindowProperties&& other) noexcept
	: width(other.width), height(other.height), title(std::move(other.title))
{}

WindowProperties& WindowProperties::operator=(const WindowProperties& other)
{
	if(this != &other)
	{
		width = other.width;
		height = other.height;
		title = other.title;
	}

	return *this;
}

WindowProperties& WindowProperties::operator=(WindowProperties&& other) noexcept
{
	if (this != &other)
	{
		width = other.width;
		height = other.height;
		title = std::move(other.title);
	}

	return *this;
}
