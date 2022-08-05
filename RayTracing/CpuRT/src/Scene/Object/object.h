#pragma once
#include "../../Utilities/types.h"
#include "transform.h"

class Sphere;

class Object
{
public:
	Object(vec3 position);
	Object(Transform transform);
	virtual ~Object() = default;

	virtual bool isColliding(const Sphere* other) const = 0;
protected:
	Transform m_transform;
};

