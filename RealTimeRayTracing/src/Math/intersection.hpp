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

		void reset();
		bool intersected() const;
	};

#pragma region Inline methods definitions
	inline void IntersectionInfo::reset()
	{
		t = std::numeric_limits<float>::infinity();
	}

	inline bool IntersectionInfo::intersected() const
	{
		return t != std::numeric_limits<float>::infinity();
	}
#pragma endregion
}

#endif
