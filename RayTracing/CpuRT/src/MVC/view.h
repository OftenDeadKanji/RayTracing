#pragma once
#include "../Window/window.h"
#include <functional>
#include "glad/glad.h"

namespace MVC
{
	class Controller;

	class View
	{
	public:
		View(Controller& controller, const WindowProperties& windowProperties);
		~View();

		void checkInput();
		void render(float deltaTime, const std::vector<float>& texture, int width, int height);

		void setWindowCloseCallback(std::function<void(void)> callback);

		void generateTexture(const std::vector<float>& texture, int width, int height);
	private:
		void initRendering();

		Window m_window;
		EventManager m_eventManager;

#pragma region Callbacks
		std::function<void(void)> m_windowCloseCallback;
#pragma endregion

		GLuint m_textureQuadVAO;
		GLuint m_textureQuadVBO;
		GLuint m_texture;

		GLuint m_shader;
	};
}
