#include "scene.hpp"

std::unique_ptr<Scene> Scene::s_instance = nullptr;

void Scene::render(std::vector<math::Vec3f>& outPixels, const math::Vec2i& resolution)
{
	for (int i = 0; i < resolution.x(); i++)
	{
		for (int j = 0; j < resolution.y(); j++)
		{
			outPixels[j + i * resolution.y()] = calculatePixelColor({ i, j });
		}
	}
}

math::Vec3f Scene::calculatePixelColor(const math::Vec2i& pixelCoordinate)
{
	return m_backgroundColor;
}
