#pragma once
#include "../Utilities/types.h"

class Object;

class IntersectionPoint
{
public:
	enum class FaceSide
	{
		front,
		back
	};

public:
	IntersectionPoint();
	IntersectionPoint(const vec3& position, const vec3& normal, FaceSide side);

	bool isOnTheFrontSide() const;

	vec3 position;
	vec3 normal;
	FaceSide side;
};

