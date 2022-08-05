#include "object.h"

Object::Object(vec3 position)
	: m_transform(position)
{
}

Object::Object(Transform transform)
	: m_transform(transform)
{
}