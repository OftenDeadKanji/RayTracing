#ifndef __SPHERE_OBJECT_HPP__
#define __SPHERE_OBJECT_HPP__
#include "../../../Math/sphere.hpp"
#include "../../Material/material.hpp"
#include "../../TransformSystem/transformManager.hpp"

struct IntersectionInfo;

class SphereObject
{
	friend class Scene;
	friend class FileWriter;
public:
	bool isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo);

	std::shared_ptr<Material> getMaterial() const;
private:
	std::shared_ptr<Material> m_material;
	TransformManager::TransformID m_transformID;
};

#pragma region Inline methods definitions
inline std::shared_ptr<Material> SphereObject::getMaterial() const
{
	return m_material;
}
#pragma endregion

#endif
