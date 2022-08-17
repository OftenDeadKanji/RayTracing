#pragma once
#include <vector>
#include "intersectionPoint.h"
#include "../Utilities/types.h"

class Object;

struct IntersectionInfo
{
public:
	IntersectionInfo();
	IntersectionInfo(bool intersected, std::vector<IntersectionPoint> intersectionPoints, const Object* intersectedObject);
	
	static const IntersectionInfo NoIntersection;

	bool intersected;
	std::vector<IntersectionPoint> intersectionPoints;
	const Object* intersectedObject;
	//const Ray* intersectingRay; ?
};

