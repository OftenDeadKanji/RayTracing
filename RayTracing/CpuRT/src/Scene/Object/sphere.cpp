#include "sphere.h"

Sphere::Sphere()
	: Object()
{
}

Sphere::Sphere(float radius, vec3 position)
	: Object(position), m_radius(radius)
{
}

Sphere::Sphere(float radius, Transform transform)
	: Object(transform), m_radius(radius)
{
}

bool Sphere::isColliding(const Sphere* other) const
{
	return this->m_radius + other->m_radius >= glm::distance(this->m_transform.position, other->m_transform.position);
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}

