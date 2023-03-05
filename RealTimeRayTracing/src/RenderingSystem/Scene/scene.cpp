#include "scene.hpp"
#include "../../Math/ray.hpp"
#include "../../Math/intersection.hpp"

std::unique_ptr<Scene> Scene::s_instance = nullptr;

Scene::Scene()
{
	math::Sphere sphere;
	sphere.position = { 800.0f, 450.0f, 100.0f };
	sphere.radius = 50.0f;
	m_spheres.push_back(sphere);


}

void Scene::render(std::vector<math::Vec3f>& outPixels, const math::Vec2i& resolution)
{
	for (int i = 0; i < resolution.x(); i++)
	{
		for (int j = 0; j < resolution.y(); j++)
		{
			outPixels[i + j * resolution.x()] = calculatePixelColor({ i, j });
		}
	}
}

math::Vec3f Scene::calculatePixelColor(const math::Vec2i& pixelCoordinate)
{
	math::Ray ray;
	ray.origin = { static_cast<float>(pixelCoordinate.x()), static_cast<float>(pixelCoordinate.y()), -0.0f };
	ray.direction = { 0.0f, 0.0f, 1.0f };

	math::IntersectionInfo intersection;
	intersection.reset();
	math::Vec3f color;

	findIntersection(ray, intersection, color);

	return intersection.intersected() ? color : m_backgroundColor;
}

void Scene::findIntersection(const math::Ray& ray, math::IntersectionInfo& outIntersection, math::Vec3f& outColor)
{
	for (const auto& sphere : m_spheres)
	{
		if (sphere.isIntersecting(ray, outIntersection))
		{
			outColor = math::Vec3f(0.5f, 0.5f, 0.5f);
		}
	}
}
