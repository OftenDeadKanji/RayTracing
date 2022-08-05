#include "sphere.h"

Sphere::Sphere(vec3 position)
	: Object(position)
{
}

Sphere::Sphere(Transform transform)
	: Object(transform)
{
}

bool Sphere::isColliding(const Sphere* other) const
{
	return this->radius + other->radius >= glm::distance(this->m_transform.position, other->m_transform.position);
}

