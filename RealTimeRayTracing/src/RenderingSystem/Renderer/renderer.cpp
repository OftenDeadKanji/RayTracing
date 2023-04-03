#include "renderer.hpp"
#include "glad/glad.h"
#include <iostream>
#include "../Window/window.hpp"
#include "../Camera/camera.hpp"
#include "../Scene/scene.hpp"
#include "ImGui/imgui.h"

std::unique_ptr<Renderer> Renderer::s_instance = nullptr;

Renderer::Renderer()
{
	glCreateVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_screenTexture);
	glBindTexture(GL_TEXTURE_2D, m_screenTexture);
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	const char* vertexCode = R"(
#version 450

out vec2 texCoord;

const vec2 POSITION[3] = vec2[3](
	vec2(-1.0, -1.0),
	vec2(3.0, -1.0),
	vec2(-1.0, 3.0)
	);

const vec2 TEX_COORD[3] = vec2[3](
	vec2(0.0, 0.0),
	vec2(2.0, 0.0),
	vec2(0.0, 2.0)
	);

void main()
{
	gl_Position = vec4(POSITION[gl_VertexID], 0.0, 1.0);
	texCoord = TEX_COORD[gl_VertexID];
}

)";

	const char* fragmentCode = R"(
#version 450

in vec2 texCoord;
out vec4 color;

uniform sampler2D renderedImage;

void main()
{
	color = texture(renderedImage, texCoord);
}

)";

	auto vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, nullptr);
	glCompileShader(vertex);

	int result;
	char log[512] = {};

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, log);
		std::cout << log << std::endl;
		std::fill_n(log, 512, 0);
	}

	auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, log);
		std::cout << log << std::endl;
		std::fill_n(log, 512, 0);
	}

	m_shader = glCreateProgram();

	glAttachShader(m_shader, vertex);
	glAttachShader(m_shader, fragment);
	glLinkProgram(m_shader);

	glGetProgramiv(m_shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shader, 512, nullptr, log);
		std::cout << log << std::endl;
		std::fill_n(log, 512, 0);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	glUseProgram(m_shader);

	glUniform1i(glGetUniformLocation(m_shader, "renderedImage"), 0);
}

Renderer::~Renderer()
{
	glDeleteTextures(1, &m_screenTexture);
	glDeleteProgram(m_shader);
	glDeleteVertexArrays(1, &m_vao);
}

void Renderer::initScreenTexture(const math::Vec2i& size)
{
	m_textureSize = size;
	m_texels.resize(size.x() * size.y()); 
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureSize.x(), m_textureSize.y(), 0, GL_RGB, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, m_screenTexture);

	for (auto& vec : m_texels)
	{
		vec = { 1.0f, 0.8f, 0.9f };
	}
}

void Renderer::render(const Window& window, const Camera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (m_sceneToRender)
	{
		m_sceneToRender->render(camera, m_texels, window.getSize(), m_textureSize);
	}

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_textureSize.x(), m_textureSize.y(), GL_RGB, GL_FLOAT, m_texels.data());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	ImGui::Render();
}
