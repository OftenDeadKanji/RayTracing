#include "scene.hpp"
#include "../../Math/ray.hpp"
#include "../../Math/intersection.hpp"
#include "../Camera/camera.hpp"
#include "IntersectionInfo/intersectionInfo.hpp"
#include "../Lighting/blinnPhong.hpp"
#include "../../ResourceManagers/meshManager.hpp"
#include <iostream>

std::unique_ptr<Scene> Scene::s_instance = nullptr;

Scene::Scene()
{
	Material mat;
	mat.color = { 1.0f, 0.0f, 0.0f };
	mat.shininess = 32.0f;
	mat.isEmmisive = false;

	SphereObject sphere;
	sphere.m_sphere.position = { 0.0f, 0.0f, 100.0f };
	sphere.m_sphere.radius = 10.0f;
	sphere.m_material = mat;

	m_spheres.push_back(sphere);

	MeshObject mesh;
	mesh.setMesh(MeshManager::getInstance()->getUnitCube());
	mesh.m_material.color = { 0.0f, 1.0f, 0.0f };
	mesh.m_material.shininess = 64.0f;
	mesh.m_material.isEmmisive = false;
	mesh.m_transform = math::Transform({ 0.0f, -10.0f, 50.0f }, math::Quat::Identity(), { 10.0f, 10.0f, 10.0f });

	m_meshes.push_back(mesh);

	DirectionalLight dirLight;
	dirLight.color = { 0.2f, 0.2f, 0.2f };
	dirLight.direction = { 1.0f, -1.0f, 1.0f };

	m_directionalLights.push_back(dirLight);

	PointLight pointLight;
	pointLight.color = { 10.0f, 10.0f, 100.0f };
	pointLight.position = { 0.0f, 15.0f, 100.0f };

	m_pointLights.push_back(pointLight);

	pointLight.position = { 0.0f, 11.0f, 50.0f };
	m_pointLights.push_back(pointLight);

	SphereObject spherePL;
	spherePL.m_material.isEmmisive = true;
	spherePL.m_material.color = { 10.0f, 10.0f, 100.0f };
	spherePL.m_sphere.position = { 0.0f, 15.0f, 100.0f };
	spherePL.m_sphere.radius = 1.0f;
	m_spheres.push_back(spherePL);

	spherePL.m_sphere.position = { 0.0f, 11.0f, 50.0f };
	m_spheres.push_back(spherePL);

	m_threadPool.start();
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
