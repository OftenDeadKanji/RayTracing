#include "ray.h"

Ray::Ray()
	: Ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f))
{
}

Ray::Ray(vec3 origin, vec3 direction, Object* startingObject, float maxT)
	: m_origin(origin), m_direction(direction), m_startingObject(startingObject), m_maxT(maxT)
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

float Ray::getMaxT() const
{
	return m_maxT;
}

void Ray::setMaxT(float maxT)
{
	m_maxT = maxT;
}

Object* Ray::getStartingObject()
{
	return m_startingObject;
}

Object* const Ray::getStartingObject() const
{
	return m_startingObject;
}

void Ray::setStartingObject(Object* object)
{
	m_startingObject = object;
}
