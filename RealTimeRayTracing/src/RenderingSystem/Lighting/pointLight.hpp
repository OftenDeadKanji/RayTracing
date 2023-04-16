#ifndef __POINT_LIGHT_HPP__
#define __POINT_LIGHT_HPP__
#include "../../Math/mathUtils.hpp"
#include "../TransformSystem/transformManager.hpp"

struct PointLight
{
	math::Vec3f color;
	TransformManager::TransformID transformID;
};

#endif
