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
	mesh.m_transform = math::Transform({ 0.0f, 0.0f, 50.0f }, math::Quat::Identity(), { 10.0f, 10.0f, 10.0f });

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
			return material.color.normalized();
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

		return resultColor;
	}

	return m_ambientLight;
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
