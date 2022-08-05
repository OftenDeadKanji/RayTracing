#pragma once
#include "object.h"

class Sphere
	: public Object
{
public:
	Sphere(vec3 position);
	Sphere(Transform transform);

	bool isColliding(const Sphere* other) const override;
private:
	float radius;
};

