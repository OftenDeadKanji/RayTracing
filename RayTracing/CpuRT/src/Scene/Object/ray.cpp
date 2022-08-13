#include "ray.h"

Ray::Ray()
	: Ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f))
{
}

Ray::Ray(vec3 origin, vec3 direction, float maxT)
	: m_origin(origin), m_direction(direction), m_maxT(maxT)
{
}

vec3& Ray::getOrigin()
{
	return m_origin;
}

const vec3& Ray::getOrigin() const
{
	return m_origin;
}

void Ray::setOrigin(vec3 origin)
{
	m_origin = origin;
}

vec3& Ray::getDirection()
{
	return m_direction;
}

const vec3& Ray::getDirection() const
{
	return m_direction;
}

void Ray::setDirection(vec3 direction)
{
	m_direction = direction;
}

float Ray::getMaxT()
{
	return m_maxT;
}

void Ray::setMaxT(float maxT)
{
	m_maxT = maxT;
}
