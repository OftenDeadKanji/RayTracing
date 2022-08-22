#include "transform.h"

Transform::Transform()
	: Transform{ vec3{ 0.0f,0.0f,0.0f }, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 0.0f, 0.0f } }
{

}
Transform::Transform(const vec3& position)
	: Transform{position, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 0.0f, 0.0f }}
{

}

Transform::Transform(const vec3& position, const vec3& rotation, const vec3& scale)
	: position{ position }, rotation{ rotation }, scale{ scale }
{}
