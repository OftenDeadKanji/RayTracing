#include "ray.h"

Ray::Ray()
	: Ray{ vec3{0.0f, 0.0f, 0.0f}, vec3{0.0f, 0.0f, -1.0f} }
{
}

Ray::Ray(vec3 origin, vec3 direction, float minT, float maxT, Object* startingObject)
	: m_origin{ origin }, m_direction{ direction }, m_minT{ minT }, m_maxT{ maxT }, m_startingObject{ startingObject }
{
}

const vec3& Ray::getOrigin() const
{
	return m_origin;
}

void Ray::setOrigin(vec3 origin)
{
	m_origin = origin;
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

float Ray::getMinT() const
{
	return m_minT;
}

void Ray::setMinT(float minT)
{
	m_minT = minT;
}

Object* Ray::getStartingObject() const
{
	return m_startingObject;
}

void Ray::setStartingObject(Object* object)
{
	m_startingObject = object;
}
