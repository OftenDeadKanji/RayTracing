#ifndef __SPHERE_OBJECT_HPP__
#define __SPHERE_OBJECT_HPP__
#include "../../../Math/sphere.hpp"
#include "../../Material/material.hpp"

struct IntersectionInfo;
class Scene;

class SphereObject
{
	friend class Scene;
public:
	bool isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo);

	const Material& getMaterial() const;
private:
	math::Sphere m_sphere;
	Material m_material;
};

#pragma region Inline methods definitions
inline const Material& SphereObject::getMaterial() const
{
	return m_material;
}
#pragma endregion

#endif
