#include "model.h"
#include <numbers>

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene(), iteratorX(0), iteratorY(0)
{
	m_screenTexture.resize(static_cast<size_t>(textureResolution.x * textureResolution.y * 3));
}

void MVC::Model::update()
{
	if (iteratorX < m_camera.Resolution.x)
	{
		if (iteratorY < m_camera.Resolution.y)
		{
			Ray ray = generateRay(iteratorX, iteratorY);
			IntersectionInfo info = m_scene.intersect(ray);

			if (info.intersected)
			{
				vec3 color = { info.intersectedObject->getColor().r,info.intersectedObject->getColor().g, info.intersectedObject->getColor().b };
				setTexturePixelColor(iteratorX, iteratorY, color);
			}
			else
			{
				vec3 color = { m_scene.getBackgroundColor().r,m_scene.getBackgroundColor().g,m_scene.getBackgroundColor().b };
				setTexturePixelColor(iteratorX, iteratorY, color);
			}

			iteratorY++;
		}
		else
		{
			iteratorY = 0;
			iteratorX++;
		}
	}
}

const std::vector<float>& MVC::Model::getScreenTexture() const
{
	return m_screenTexture;
}

vec2i MVC::Model::getTextureResolution() const
{
	return m_camera.Resolution;
}

Ray MVC::Model::generateRay(int x, int y)
{
	float imageAspectRatio = m_camera.Resolution.x / (float)m_camera.Resolution.y; // assuming width > height
	
	float Px = (2.0f * ((x + 0.5f) / m_camera.Resolution.x) - 1.0f) * std::tanf(m_camera.Fov / 2.0f * std::numbers::pi / 180.0f) * imageAspectRatio;
	float Py = (1.0f - 2.0f * ((y + 0.5f) / m_camera.Resolution.y)) * std::tanf(m_camera.Fov / 2.0f * std::numbers::pi / 180.0f);
	
	vec3 rayOrigin(0.0f);
	vec3 rayDirection = vec3(Px, Py, -1.0f) - rayOrigin;
	rayDirection = normalize(rayDirection);

	return Ray(rayOrigin, rayDirection);
}

void MVC::Model::setTexturePixelColor(int x, int y, vec3 color)
{
	int flippedX = m_camera.Resolution.x - x - 1;
	
	int coord = flippedX * m_camera.Resolution.y + y;


	m_screenTexture[coord * 3] = color.r;
	m_screenTexture[coord * 3 + 1] = color.g;
	m_screenTexture[coord * 3 + 2] = color.b;
}
