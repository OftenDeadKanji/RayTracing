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
	math::Transform& getTransform() const;
	TransformManager::TransformID getTransformID() const;
	void setTransformID(TransformManager::TransformID id);
private:
	std::shared_ptr<Material> m_material;
	TransformManager::TransformID m_transformID;
};

#pragma region Inline methods definitions
inline std::shared_ptr<Material> SphereObject::getMaterial() const
{
	return m_material;
}

inline math::Transform& SphereObject::getTransform() const
{
	return TransformManager::getInstance()->getTransform(m_transformID);
}
inline TransformManager::TransformID SphereObject::getTransformID() const
{
	return m_transformID;
}
inline void SphereObject::setTransformID(TransformManager::TransformID id)
{
	m_transformID = id;
}
#pragma endregion

#endif
