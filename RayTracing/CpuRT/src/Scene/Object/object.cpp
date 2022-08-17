#include "object.h"

Object::Object()
	: m_transform(), m_color(vec3(0.3f, 1.0f, 0.0f))
{
}

Object::Object(vec3 position)
	: m_transform(position), m_color(vec3(0.3f, 1.0f, 0.0f))
{
}

Object::Object(Transform transform)
	: m_transform(transform), m_color(vec3(0.3f, 1.0f, 0.0f))
{
}

void Object::setPosition(vec3 position)
{
	m_transform.position = position;
}

vec3 Object::getColor() const
{
	return m_color;
}

void Object::setColor(vec3 color)
{
	m_color = color;
}
