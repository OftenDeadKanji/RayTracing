#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "../../Math/mathUtils.hpp"
#include "../../Utils/nonCopyable.hpp"
#include "SceneObjects/sphereObject.hpp"
#include "SceneObjects/meshObject.hpp"
#include "../Lighting/directionalLight.hpp"
#include "../Lighting/pointLight.hpp"
#include "../../Utils/ThreadPool/threadPool.hpp"

class Window;
class Camera;

struct IntersectionInfo;

class Scene
	: public NonCopyable
{
public:
	Scene();
	~Scene();

	void render(const Camera& camera, std::vector<math::Vec3f>& outPixels, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);

	void setBackgroundColor(const math::Vec3f& color);
	void setAmbientLight(const math::Vec3f& ambientLight);
	void addDirectionalLight(const math::Vec3f& color, const math::Vec3f& direction);
	void addPointLight(const math::Vec3f& color, const math::Vec3f& position);
	void addSphereObject(const math::Vec3f& position, float radius, const Material& material);
	void addMeshObject(std::shared_ptr<Mesh> mesh, const math::Transform& transform, const Material& material);

	void clear();
private:
	ThreadPool m_threadPool;

	math::Vec3f m_backgroundColor;
	
	//objects
	std::vector<SphereObject> m_spheres;
	std::vector<MeshObject> m_meshes;

	//lights
	math::Vec3f m_ambientLight { 0.01f, 0.01f, 0.01f };
	std::vector<DirectionalLight> m_directionalLights;
	std::vector<PointLight> m_pointLights;

	void task(std::vector<math::Vec3f>& outPixels, const Camera& camera, int startRow, int endRow, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);
	void calculatePixelColor(math::Vec3f& outColor, const Camera& camera, const math::Vec2i& pixelCoordinate, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);
	void findIntersection(const math::Ray& ray, IntersectionInfo& outIntersection);
};

#pragma region Inline methods definitions

inline void Scene::setBackgroundColor(const math::Vec3f& color)
{
	m_backgroundColor = color;
}

inline void Scene::setAmbientLight(const math::Vec3f& ambientLight)
{
	m_ambientLight = ambientLight;
}

inline void Scene::addDirectionalLight(const math::Vec3f& color, const math::Vec3f& direction)
{
	m_directionalLights.emplace_back(color, direction);
}
inline void Scene::addPointLight(const math::Vec3f& color, const math::Vec3f& position)
{
	m_pointLights.emplace_back(color, position);
	addSphereObject(position, 1.0f, Material{ .color = color, .isEmmisive = true });
}
inline void Scene::addSphereObject(const math::Vec3f& position, float radius, const Material& material)
{
	SphereObject sphere;
	sphere.m_sphere = math::Sphere{ .position = position, .radius = radius };
	sphere.m_material = material;

	m_spheres.push_back(sphere);
}
inline void Scene::addMeshObject(std::shared_ptr<Mesh> mesh, const math::Transform& transform, const Material& material)
{
	MeshObject meshObject;
	meshObject.m_mesh = mesh;
	meshObject.m_transform = transform;
	meshObject.m_material = material;
	m_meshes.push_back(meshObject);
}
inline void Scene::clear()
{
	m_spheres.clear();
	m_meshes.clear();
	m_directionalLights.clear();
	m_pointLights.clear();
}
#pragma endregion

#endif
