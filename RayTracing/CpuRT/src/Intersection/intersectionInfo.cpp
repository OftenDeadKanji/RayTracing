#include "intersectionInfo.h"

const IntersectionInfo IntersectionInfo::NoIntersection{};

IntersectionInfo::IntersectionInfo()
	: intersectedObject{ nullptr }, intersectionPoint{}
{
}

IntersectionInfo::IntersectionInfo(const Object* intersectedObject, IntersectionPoint intersectionPoint)
	: intersectedObject{ intersectedObject }, intersectionPoint{ std::move(intersectionPoint) }
{
}
