#pragma once
#include "windowProperties.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../EventSystem/EventManager/eventManager.h"

class Window
{
public:
	explicit Window(WindowProperties properties);
	Window(const Window&) = delete;
	Window(Window&&) noexcept;
	~Window();

	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) noexcept;

	void setSize(const Size& size);
	Size getSize();

	void setTitle(const std::string& title);
	const std::string& getTitle();

	void setIcon(const std::string& iconFilePath);

	void fillWithColorRGB(const vec3& color = { 0, 0, 0 });
	void fillWithColorRGBf(const vec3& color = { 0.0f, 0.0f, 0.0f });

	void swapBuffers();

	void attachEventManager(EventManager& manager);

	void windowCloseCallback(bool shouldWindowClose) const;
	void windowResizeCallback(vec2 size) const;
	void keyboardKeyCallback(KeyboardKey key, KeyboardKeyAction action) const;
	void mouseButtonCallback(MouseButton button, MouseButtonAction action) const;
	void cursorPositionCallback(vec2 position) const;

	void resetCursorPos();

	GLFWwindow* getGLFWWindow() const;
private:
	void createGLFWWindow();

	void centerWindow() const;

	void initializeOpenGL();
	void initImGUI();

	WindowProperties properties;
	GLFWwindow* glfwWindow{};
	EventManager* eventManager{};
};

