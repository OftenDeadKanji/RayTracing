#pragma once
#include "../../Utilities/types.h"
#include "transform.h"

class Sphere;

class Object
{
public:
	Object();
	Object(vec3 position);
	Object(Transform transform);
	virtual ~Object() = default;

	virtual bool isColliding(const Sphere* other) const = 0;

	void setPosition(vec3 position);
protected:
	Transform m_transform;
};

