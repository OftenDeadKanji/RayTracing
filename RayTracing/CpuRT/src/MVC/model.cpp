#include "model.h"

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene()
{
	for (int i = 0; i < m_camera.Resolution.x; ++i)
	{
		m_screenTexture.push_back(std::vector<std::array<float, 3>>());
		for (int j = 0; j < m_camera.Resolution.y; ++j)
		{
			m_screenTexture[i].push_back(std::array<float, 3>());
		}
	}
}

void MVC::Model::update()
{
}
