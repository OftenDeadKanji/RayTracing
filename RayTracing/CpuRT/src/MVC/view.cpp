#include "view.h"
#include "controller.h"
#include <iostream>

namespace MVC
{
	View::View(Controller& controller, const WindowProperties& windowProperties)
		: controller(&controller), window(windowProperties)
	{
		window.attachEventManager(eventManager);

		initRendering();
	}

	View::~View()
	{
		glDeleteTextures(1, &m_texture);
		glDeleteProgram(m_shader);
		glDeleteBuffers(1, &m_textureQuadVBO);
		glDeleteVertexArrays(1, &m_textureQuadVAO);
	}

	void View::checkInput()
	{
		eventManager.checkForEvents();

		while(!eventManager.isEventQueueEmpty())
		{
			switch (eventManager.getEventTypeFromQueue())
			{
			default:
				break;
			case EventType::WindowResized:
				break;
			case EventType::WindowClosed:
				if (m_windowCloseCallback != nullptr)
				{
					m_windowCloseCallback();
				}
				break;
			case EventType::KeyboardKeyPressed:
				break;
			case EventType::KeyboardKeyReleased:
				break;
			case EventType::MouseButtonPressed:
				break;
			case EventType::MouseButtonReleased:
				break;
			case EventType::MouseCursorMoved:
				break;
			}
		}
	}

	void View::render(float deltaTime, const std::vector<float>& texture, int width, int height)
	{
		window.fillWithColorRGB({ 0, 100, 0 });

		glUseProgram(m_shader);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(glGetUniformLocation(m_shader, "renderedImage"), 0); // manually
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, texture.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindVertexArray(m_textureQuadVAO);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.swapBuffers();
	}

	void View::setWindowCloseCallback(std::function<void()> callback)
	{
		m_windowCloseCallback = std::move(callback);
	}

	void View::generateTexture(const std::vector<float>& texture, int width, int height)
	{
		glGenTextures(1, &m_texture);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		int w, h, chan;
		unsigned char* data = stbi_load("test.png", &w, &h, &chan, 0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, texture.data());
		glGenerateMipmap(GL_TEXTURE_2D);

		updateQuadTextureCoords(vec2(width, height));
	}

	void View::initRendering()
	{
		glGenVertexArrays(1, &m_textureQuadVAO);
		glGenBuffers(1, &m_textureQuadVBO);

		glBindVertexArray(m_textureQuadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_textureQuadVBO);

		float textureQuad[] = {
			-1.0f,  1.0f,  0.0f,    0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f,    0.0f, 0.0f,
			 1.0f,  1.0f,  0.0f,    1.0f, 1.0f,

			 1.0f,  1.0f,  0.0f,    1.0f, 1.0f,
			-1.0f, -1.0f,  0.0f,    0.0f, 0.0f,
			 1.0f, -1.0f,  0.0f,    1.0f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(textureQuad), textureQuad, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		const char* const vertexShaderCode = R"(
			#version 430
			
			layout (location = 0) in vec3 in_Position;
			layout (location = 1) in vec2 in_TexCoord;

			out vec2 v2f_TexCoord;			

			void main()
			{
				v2f_TexCoord = in_TexCoord;				

				gl_Position = vec4(in_Position, 1.0);
			}
			)";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
		glCompileShader(vertexShader);

		int successVertex;
		char infoLogVertex[512];

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

		if (!successVertex)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLogVertex);
			std::cout << infoLogVertex << std::endl;
		}

		auto fragmentShaderCode = R"(
			#version 430

			in vec2 v2f_TexCoord;			
			out vec4 out_Color;
			
			uniform sampler2D renderedImage;

			void main()
			{
				out_Color = texture(renderedImage, v2f_TexCoord);
			}
			)";

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
		glCompileShader(fragmentShader);

		int successFragment;
		char infoLogFragment[512];

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

		if (!successFragment)
		{
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLogFragment);
			std::cout << infoLogFragment << std::endl;
		}

		m_shader = glCreateProgram();
		glAttachShader(m_shader, vertexShader);
		glAttachShader(m_shader, fragmentShader);
		glLinkProgram(m_shader);

		int successProgram;
		char infoLogProgram[512];

		glGetProgramiv(m_shader, GL_LINK_STATUS, &successProgram);

		if (!successProgram)
		{
			glGetProgramInfoLog(m_shader, 512, nullptr, infoLogProgram);
			std::cout << infoLogProgram << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void View::updateQuadTextureCoords(vec2 textureResolution)
	{
		vec2 windowSize = window.getSize();
		bool isWindowWidthBigger = windowSize.x >= windowSize.y;

		if (isWindowWidthBigger)
		{
			float aspectRatio = static_cast<float>(windowSize.x) / windowSize.y;

			float upperBoundary[] = { 1.0 - 0.5f * (1.0f - 1.0f / aspectRatio) };
			float lowerBoundary[] = { 0.5f * (1.0f - 1.0f / aspectRatio) };

			glBindBuffer(GL_ARRAY_BUFFER, m_textureQuadVBO);
			
			glBufferSubData(GL_ARRAY_BUFFER, 4 * sizeof(float), 1 * sizeof(float), upperBoundary);
			glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float), 1 * sizeof(float), lowerBoundary);
			glBufferSubData(GL_ARRAY_BUFFER, 14 * sizeof(float), 1 * sizeof(float), upperBoundary);

			glBufferSubData(GL_ARRAY_BUFFER, 19 * sizeof(float), 1 * sizeof(float), upperBoundary);
			glBufferSubData(GL_ARRAY_BUFFER, 24 * sizeof(float), 1 * sizeof(float), lowerBoundary);
			glBufferSubData(GL_ARRAY_BUFFER, 29 * sizeof(float), 1 * sizeof(float), lowerBoundary);
		}
	}
}
