#ifndef __RAY_HPP__
#define __RAY_HPP__
#include "mathUtils.hpp"

namespace math
{
	struct Ray
	{
		math::Vec3f origin;
		math::Vec3f direction;

		Ray reflected(const math::Vec3f& normal) const
		{
			Ray out = *this;
			out.direction = direction - 2.0f * direction.dot(normal) * normal;

			return out;
		}
	};
}
#endif
