#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "../../Math/mathUtils.hpp"
#include "../../Utils/nonCopyable.hpp"
#include <memory>
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
private:
	Scene();
public:
	static Scene* createInstance();
	static void deleteInstance();

	static Scene* getInstance();

	void render(const Camera& camera, std::vector<math::Vec3f>& outPixels, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);

	void setBackgroundColor(const math::Vec3f& color);
	void setAmbientLight(const math::Vec3f& ambientLight);
private:
	static std::unique_ptr<Scene> s_instance;
	ThreadPool m_threadPool;

	math::Vec3f m_backgroundColor;
	
	//objects
	std::vector<SphereObject> m_spheres;
	std::vector<MeshObject> m_meshes;

	//lights
	math::Vec3f m_ambientLight;
	std::vector<DirectionalLight> m_directionalLights;
	std::vector<PointLight> m_pointLights;

	void task(std::vector<math::Vec3f>& outPixels, const Camera& camera, int startRow, int endRow, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);
	void calculatePixelColor(math::Vec3f& outColor, const Camera& camera, const math::Vec2i& pixelCoordinate, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution);
	void findIntersection(const math::Ray& ray, IntersectionInfo& outIntersection);
};

#pragma region Inline methods definitions
inline Scene* Scene::createInstance()
{
	s_instance = std::unique_ptr<Scene>(new Scene());
	return s_instance.get();
}
inline void Scene::deleteInstance()
{
	s_instance.release();
}

inline Scene* Scene::getInstance()
{
	return s_instance.get();
}

inline void Scene::setBackgroundColor(const math::Vec3f& color)
{
	m_backgroundColor = color;
}

inline void Scene::setAmbientLight(const math::Vec3f& ambientLight)
{
	m_ambientLight = ambientLight;
}
#pragma endregion

#endif
