#pragma once
#include "intersectionPoint.h"
#include "../Utilities/types.h"
#include <optional>

class Object;

struct IntersectionInfo
{
public:
	IntersectionInfo();
	IntersectionInfo(const Object* intersectedObject, IntersectionPoint intersectionPoints);
	
	static const IntersectionInfo NoIntersection;

	const Object* intersectedObject;
	std::optional<IntersectionPoint> intersectionPoint;
};

