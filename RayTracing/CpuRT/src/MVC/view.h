#pragma once
#include "../Window/window.h"
#include <functional>

namespace MVC
{
	class Controller;

	class View
	{
	public:
		View(Controller& controller, const WindowProperties& windowProperties);

		void checkInput();
		void render(float deltaTime);

		void setWindowCloseCallback(std::function<void(void)> callback);
	private:
		Controller* controller;
		Window window;
		EventManager eventManager;

#pragma region Callbacks
		std::function<void(void)> m_windowCloseCallback;
#pragma endregion
	};
}
