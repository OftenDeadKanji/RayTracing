#include "intersection.h"

const IntersectionInfo IntersectionInfo::NoIntersection = IntersectionInfo(false, std::vector<vec3>(), nullptr);

IntersectionInfo::IntersectionInfo()
	: IntersectionInfo(false, std::vector<vec3>(), nullptr)
{
}

IntersectionInfo::IntersectionInfo(bool intersected, std::vector<vec3> intersectionPoints, const Object* intersectedObject)
	: intersected(intersected), intersectionPoints(std::move(intersectionPoints)), intersectedObject(intersectedObject)
{
}
