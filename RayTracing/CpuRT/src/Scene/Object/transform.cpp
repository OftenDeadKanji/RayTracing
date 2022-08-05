#include "transform.h"

Transform::Transform()
	: Transform({ 0.0f,0.0f,0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f })
{

}
Transform::Transform(vec3 position)
	: Transform(position, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f })
{

}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale)
	: position(position), rotation(rotation), scale(scale)
{}
