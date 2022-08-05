#pragma once
#include "../../Utilities/types.h"
#include "glm/gtc/quaternion.hpp"

struct Transform
{
	Transform();
	Transform(vec3 position);
	Transform(vec3 position, vec3 rotation, vec3 scale);

	vec3 position;
	glm::quat rotation;
	vec3 scale;
};