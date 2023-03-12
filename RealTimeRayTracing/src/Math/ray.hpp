#ifndef __RAY_HPP__
#define __RAY_HPP__
#include "mathUtils.hpp"

namespace math
{
	struct Ray
	{
		math::Vec3f origin;
		math::Vec3f direction;
	};
}
#endif
