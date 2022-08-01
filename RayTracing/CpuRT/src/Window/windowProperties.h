#pragma once
#include <string>

struct WindowProperties
{
	WindowProperties(int width, int height, std::string title);
	WindowProperties(const WindowProperties& other);
	WindowProperties(WindowProperties&& other) noexcept;

	WindowProperties& operator=(const WindowProperties& other);
	WindowProperties& operator=(WindowProperties&& other) noexcept;

	int width;
	int height;
	std::string title;
};