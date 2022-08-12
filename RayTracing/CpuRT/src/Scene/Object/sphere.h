#pragma once
#include "object.h"

class Sphere
	: public Object
{
public:
	Sphere();
	Sphere(float radius, vec3 position);
	Sphere(float radius, Transform transform);

	bool isColliding(const Sphere* other) const override;

	void setRadius(float radius);
private:
	float m_radius;
};

