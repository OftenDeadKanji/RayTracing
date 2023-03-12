#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "../../Math/mathUtils.hpp"
#include "../../Utils/nonCopyable.hpp"
#include <memory>
#include "../../Math/sphere.hpp"

namespace math
{
	struct Ray;
	struct Plane;
	struct IntersectionInfo;
}

class Window;
class Camera;

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
private:
	static std::unique_ptr<Scene> s_instance;

	math::Vec3f m_backgroundColor;
	
	std::vector<math::Sphere> m_spheres;

	int maxBouncesCount = 50;

	math::Vec3f calculatePixelColor(const Camera& camera, const math::Vec2i& pixelCoordinate, const math::Vec2i& windowResolution, const math::Vec2i& textureResolution /*Camera& camera*/);
	void findIntersection(const math::Ray& ray, math::IntersectionInfo& outIntersection, math::Vec3f& outColor, int bounce);
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
#pragma endregion

#endif
