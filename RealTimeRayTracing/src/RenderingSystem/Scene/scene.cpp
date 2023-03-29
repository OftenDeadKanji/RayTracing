#include "scene.hpp"
#include "../../Math/ray.hpp"
#include "../../Math/intersection.hpp"
#include "../Camera/camera.hpp"
#include "IntersectionInfo/intersectionInfo.hpp"
#include "../Lighting/blinnPhong.hpp"
#include "../../ResourceManagers/meshManager.hpp"
#include <iostream>

Scene::Scene()
{
	m_threadPool.start();
}

Scene::~Scene()
{
	m_threadPool.stop();
}

void Scene::render(const Camera& camera, std::vector<math::Vec3f>& outPixels, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution)
{
	const int rowsPerTask = 50;

	for (int startRow = 0; startRow < textureResolution.x(); startRow += rowsPerTask)
	{
		int endRow = std::min(startRow + rowsPerTask, windowResolution.x());

		m_threadPool.queueTask([&outPixels, &textureResolution, &camera, &windowResolution, startRow, endRow, this]()
			{
				task(outPixels, camera, startRow, endRow, windowResolution, textureResolution);
			});
	}

	m_threadPool.waitToFinish();
}

void Scene::task(std::vector<math::Vec3f>& outPixels, const Camera& camera, int startRow, int endRow, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution)
{
	for (int i = startRow; i < endRow; i++)
	{
		for (int j = 0; j < textureResolution.y(); j++)
		{
			calculatePixelColor(outPixels[i + j * textureResolution.x()], camera, { i, j }, windowResolution, textureResolution);
		}
	}
}

void Scene::calculatePixelColor(math::Vec3f& outColor, const Camera& camera, const math::Vec2i& pixelCoordinate, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution)
{
	math::Ray ray = camera.generateRay(pixelCoordinate, textureResolution);

	IntersectionInfo intersection;
	intersection.reset();
	math::Vec3f color;

	findIntersection(ray, intersection);
	if (intersection.occured())
	{
		Material material;
		switch (intersection.type)
		{
		case IntersectionType::Sphere:
		{
			SphereObject* sphere = static_cast<SphereObject*>(intersection.intersectedObject);
			material = sphere->getMaterial();
		}
		break;
		case IntersectionType::Mesh:
		{
			MeshObject* mesh = static_cast<MeshObject*>(intersection.intersectedObject);
			material = mesh->getMaterial();
		}
		break;
		case IntersectionType::None:
			[[fallthrough]];
		default:
			assert(0);
		}

		if (material.isEmmisive)
		{
			outColor = material.color.normalized();

			return;
		}

		math::Vec3f resultColor = m_ambientLight.cwiseProduct(material.color);
		BlinnPhong blinnPhong;

		for (auto& dirLight : m_directionalLights)
		{
			resultColor += blinnPhong.calculateLighting(dirLight, intersection.intersection.point, intersection.intersection.normal, -ray.direction, material);
		}

		for (auto& pointLight : m_pointLights)
		{
			resultColor += blinnPhong.calculateLighting(pointLight, intersection.intersection.point, intersection.intersection.normal, -ray.direction, material);
		}

		outColor = resultColor;
		return;
	}

	outColor = m_backgroundColor;
}

void Scene::findIntersection(const math::Ray& ray, IntersectionInfo& outIntersection)
{
	for (auto& sphere : m_spheres)
	{
		sphere.isIntersecting(ray, outIntersection);
	}
	for (auto& mesh : m_meshes)
	{
		math::Ray rayInMS (ray);

		mesh.m_transform.globalToLocal(rayInMS.origin, 1.0f);
		mesh.m_transform.globalToLocal(rayInMS.direction, 0.0f);

		if (mesh.isIntersecting(rayInMS, outIntersection))
		{
			mesh.m_transform.localToGlobal(outIntersection.intersection.point, 1.0f);
			mesh.m_transform.localToGlobal(outIntersection.intersection.normal, 0.0f);

			outIntersection.intersection.normal.normalize();
		}
	}
}
