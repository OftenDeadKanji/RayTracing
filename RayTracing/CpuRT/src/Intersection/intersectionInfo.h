#pragma once
#include "intersectionPoint.h"
#include "../Utilities/types.h"

class Object;

struct IntersectionInfo
{
public:
	IntersectionInfo();
	IntersectionInfo(bool intersected, IntersectionPoint intersectionPoints, vec3 color, const Object* intersectedObject);
	
	static const IntersectionInfo NoIntersection;

	bool intersected;
	vec3 color;
	IntersectionPoint intersectionPoint;
	const Object* intersectedObject;
	//const Ray* intersectingRay; ?
};

