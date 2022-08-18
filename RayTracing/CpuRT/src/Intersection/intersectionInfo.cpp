#include "intersectionInfo.h"

const IntersectionInfo IntersectionInfo::NoIntersection = IntersectionInfo(false, IntersectionPoint(), vec3(0.0f), nullptr);

IntersectionInfo::IntersectionInfo()
	: IntersectionInfo(false, IntersectionPoint(), vec3(0.0f), nullptr)
{
}

IntersectionInfo::IntersectionInfo(bool intersected, IntersectionPoint intersectionPoint, vec3 color, const Object* intersectedObject)
	: intersected(intersected), intersectionPoint(std::move(intersectionPoint)), color(color), intersectedObject(intersectedObject)
{
}
