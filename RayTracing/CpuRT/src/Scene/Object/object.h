#pragma once
#include "../../Utilities/types.h"
#include "transform.h"
#include "../../Intersection/intersectionPoint.h"

class Ray;

class Object
{
public:
	Object(const vec3& color = sc_defaultColor);
	Object(const Transform& transform, const vec3& color = sc_defaultColor);
	virtual ~Object() = default;

	virtual bool isIntersecting(const Ray* ray, IntersectionPoint& intersectionPoint) const = 0;

	void setPosition(const vec3& position);

	vec3& getColor();
	const vec3& getColor() const;
	void setColor(const vec3& color);

protected:
	static constexpr vec3 sc_defaultColor{ 1.0f, 1.0f, 1.0f };

	Transform m_transform;
	vec3 m_color;
};

