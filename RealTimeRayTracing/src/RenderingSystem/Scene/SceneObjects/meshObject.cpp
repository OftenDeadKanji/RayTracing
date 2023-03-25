#include "meshObject.hpp"
#include "../IntersectionInfo/intersectionInfo.hpp"

bool MeshObject::isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo)
{
	if (m_mesh->isIntersecting(ray, outIntersectionInfo.intersection))
	{
		outIntersectionInfo.type = IntersectionType::Mesh;
		outIntersectionInfo.intersectedObject = this;

		return true;
	}

	return false;
}