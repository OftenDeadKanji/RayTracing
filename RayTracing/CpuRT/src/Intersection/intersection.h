#pragma once
#include <vector>
#include "../Utilities/types.h"

class Object;

struct IntersectionInfo
{
public:
	IntersectionInfo();
	IntersectionInfo(bool intersected, std::vector<vec3> intersectionPoints, const Object* intersectedObject);
	
	static const IntersectionInfo NoIntersection;

	bool intersected;
	std::vector<vec3> intersectionPoints;
	const Object* intersectedObject;
	//const Ray* intersectingRay; ?
};

