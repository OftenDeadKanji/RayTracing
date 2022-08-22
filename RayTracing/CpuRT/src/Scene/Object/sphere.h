#pragma once
#include "object.h"

class Sphere
	: public Object
{
public:
	Sphere(const vec3 & = sc_defaultColor);
	Sphere(float radius, const Transform& position, const vec3& color = sc_defaultColor);

	bool isIntersecting(const Ray* ray, IntersectionPoint& intersectionPoint) const override;

	void setRadius(float radius);
private:
	float m_radius;
};

