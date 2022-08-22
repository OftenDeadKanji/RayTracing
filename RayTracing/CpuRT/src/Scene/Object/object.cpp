#include "object.h"

Object::Object(const vec3& color)
	: m_transform{}, m_color{color}
{
}

Object::Object(const Transform& transform, const vec3& color)
	: m_transform{ transform }, m_color{ color }
{
}

void Object::setPosition(const vec3& position)
{
	m_transform.position = position;
}

vec3& Object::getColor()
{
	return m_color;
}

const vec3& Object::getColor() const
{
	return m_color;
}

void Object::setColor(const vec3& color)
{
	m_color = color;
}
