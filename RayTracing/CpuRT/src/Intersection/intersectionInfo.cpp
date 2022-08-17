#include "intersectionInfo.h"

const IntersectionInfo IntersectionInfo::NoIntersection = IntersectionInfo(false, std::vector<IntersectionPoint>(), nullptr);

IntersectionInfo::IntersectionInfo()
	: IntersectionInfo(false, std::vector<IntersectionPoint>(), nullptr)
{
}

IntersectionInfo::IntersectionInfo(bool intersected, std::vector<IntersectionPoint> intersectionPoints, const Object* intersectedObject)
	: intersected(intersected), intersectionPoints(std::move(intersectionPoints)), intersectedObject(intersectedObject)
{
}
