#include "intersection.h"

const IntersectionInfo IntersectionInfo::NoIntersection = IntersectionInfo(false, std::vector<vec3>(), nullptr, std::vector<vec3>());

IntersectionInfo::IntersectionInfo()
	: IntersectionInfo(false, std::vector<vec3>(), nullptr, std::vector<vec3>())
{
}

IntersectionInfo::IntersectionInfo(bool intersected, std::vector<vec3> intersectionPoints, const Object* intersectedObject, std::vector<vec3> intersectionPointsNormals)
	: intersected(intersected), intersectionPoints(std::move(intersectionPoints)), intersectedObject(intersectedObject), intersectionPointsNormals(std::move(intersectionPointsNormals))
{
}
