#pragma once
#include "../../Utilities/types.h"
#include "glm/gtc/quaternion.hpp"

struct Transform
{
	Transform();
	Transform(const vec3& position);
	Transform(const vec3& position, const vec3& rotation, const vec3& scale);

	vec3 position;
	glm::quat rotation;
	vec3 scale;
};