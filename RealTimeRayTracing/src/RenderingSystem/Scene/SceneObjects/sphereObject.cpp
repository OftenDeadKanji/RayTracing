#include "sphereObject.hpp"
#include "../IntersectionInfo/intersectionInfo.hpp"

bool SphereObject::isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo)
{
	auto* transformManager = TransformManager::getInstance();
	const math::Transform& transform = transformManager->getTransform(m_transformID);

	math::Sphere sphere;
	sphere.position = transform.getTranslation();
	sphere.radius = transform.getScale().x();

	if (sphere.isIntersecting(ray, outIntersectionInfo.intersection))
	{
		outIntersectionInfo.type = IntersectionType::Sphere;
		outIntersectionInfo.intersectedObject = this;

		return true;
	}

	return false;
}