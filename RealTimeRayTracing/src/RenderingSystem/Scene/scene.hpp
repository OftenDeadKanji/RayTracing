#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "../../Math/mathUtils.hpp"
#include "../../Utils/nonCopyable.hpp"
#include <memory>
#include "../../Math/sphere.hpp"

namespace math
{
	struct Ray;
	//struct Sphere;
	struct Plane;
	struct IntersectionInfo;
}

class Window;

class Scene
	: public NonCopyable
{
private:
	Scene();
public:
	static Scene* createInstance()
	{
		s_instance = std::unique_ptr<Scene>(new Scene());
		return s_instance.get();
	}
	static void deleteInstance()
	{
		s_instance.release();
	}

	static Scene* getInstance()
	{
		return s_instance.get();
	}

	void render(/*Camera& camera, */ std::vector<math::Vec3f>& outPixels, const math::Vec2i& resolution);

	void setBackgroundColor(const math::Vec3f& color)
	{
		m_backgroundColor = color;
	}
private:
	static std::unique_ptr<Scene> s_instance;

	math::Vec3f m_backgroundColor;
	
	std::vector<math::Sphere> m_spheres;

	math::Vec3f calculatePixelColor(const math::Vec2i& pixelCoordinate /*Camera& camera*/);
	void findIntersection(const math::Ray& ray, math::IntersectionInfo& outIntersection, math::Vec3f& outColor);
};

#endif