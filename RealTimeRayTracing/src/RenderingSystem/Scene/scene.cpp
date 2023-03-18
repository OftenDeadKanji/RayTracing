#include "scene.hpp"
#include "../../Math/ray.hpp"
#include "../../Math/intersection.hpp"
#include "../Camera/camera.hpp"
#include "IntersectionInfo/intersectionInfo.hpp"
#include "../Lighting/blinnPhong.hpp"

std::unique_ptr<Scene> Scene::s_instance = nullptr;

Scene::Scene()
{
	Material mat;
	mat.color = { 1.0f, 0.0f, 0.0f };
	mat.shininess = 32.0f;

	SphereObject sphere;
	sphere.m_sphere.position = { 0.0f, 0.0f, 100.0f };
	sphere.m_sphere.radius = 10.0f;
	sphere.m_material = mat;

	m_spheres.push_back(sphere);

	DirectionalLight dirLight;
	dirLight.color = { 1.0f, 1.0f, 1.0f };
	dirLight.direction = { 1.0f, -1.0f, 1.0f };

	m_directionalLights.push_back(dirLight);
}

void Scene::render(const Camera& camera, std::vector<math::Vec3f>& outPixels, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution)
{
	for (int i = 0; i < textureResolution.x(); i++)
	{
		for (int j = 0; j < textureResolution.y(); j++)
		{
			float x = (static_cast<float>(i) / textureResolution.x()) * windowResolution.x();
			float y = (static_cast<float>(j) / textureResolution.y()) * windowResolution.y();

			outPixels[i + j * textureResolution.x()] = calculatePixelColor(camera, { i, j }, windowResolution, textureResolution);
		}
	}
}

math::Vec3f Scene::calculatePixelColor(const Camera& camera, const math::Vec2i& pixelCoordinate, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution)
{
	math::Ray ray = camera.generateRay(pixelCoordinate, textureResolution);

	IntersectionInfo intersection;
	intersection.reset();
	math::Vec3f color;

	findIntersection(ray, intersection, color);
	if (intersection.occured())
	{
		math::Vec3f resultColor = { 0.0f, 0.0f, 0.0f };
		BlinnPhong blinnPhong;

		for (auto& dirLight : m_directionalLights)
		{
			resultColor += blinnPhong.calculateLighting(dirLight, intersection, ray);
		}

		return resultColor;
	}

	return m_backgroundColor;
}

void Scene::findIntersection(const math::Ray& ray, IntersectionInfo& outIntersection, math::Vec3f& outColor)
{
	for (auto& sphere : m_spheres)
	{
		if (sphere.isIntersecting(ray, outIntersection))
		{
			outColor = sphere.m_material.color;
		}
	}
}
