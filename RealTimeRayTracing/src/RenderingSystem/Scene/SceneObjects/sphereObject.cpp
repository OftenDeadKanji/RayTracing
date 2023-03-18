#include "sphereObject.hpp"
#include "../IntersectionInfo/intersectionInfo.hpp"

bool SphereObject::isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo)
{
	if (m_sphere.isIntersecting(ray, outIntersectionInfo.intersection))
	{
		outIntersectionInfo.type = IntersectionType::Sphere;
		outIntersectionInfo.intersectedObject = this;

		return true;
	}

	return false;
}