#ifndef __DIRECTIONAL_LIGHT_HPP__
#define __DIRECTIONAL_LIGHT_HPP__
#include "../../Math/mathUtils.hpp"

struct DirectionalLight
{
	math::Vec3f color;
	math::Vec3f direction;
};

#endif
