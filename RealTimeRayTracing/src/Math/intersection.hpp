#ifndef __INTERSECTION_HPP__
#define __INTERSECTION_HPP__
#include "mathUtils.hpp"
#include <limits>

namespace math
{
	struct IntersectionInfo
	{
		math::Vec3f point;
		float t;

		void reset()
		{
			t = std::numeric_limits<float>::infinity();
		}

		bool intersected() const
		{
			return t != std::numeric_limits<float>::infinity();
		}
	};
}
#endif