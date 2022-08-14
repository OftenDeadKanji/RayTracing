#pragma once
#include "../../Utilities/types.h"
#include "transform.h"
#include <vector>

class Ray;

class Object
{
public:
	Object();
	Object(vec3 position);
	Object(Transform transform);
	virtual ~Object() = default;

	virtual bool isIntersecting(const Ray* ray, std::vector<vec3>& intersectionPoints) const = 0;

	void setPosition(vec3 position);

	vec3 getColor() const;
protected:
	Transform m_transform;
	vec3 m_color;
};

