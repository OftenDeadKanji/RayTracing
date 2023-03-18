#ifndef __INTERSECTION_HPP__
#define __INTERSECTION_HPP__
#include "mathUtils.hpp"
#include <limits>

namespace math
{
	struct Intersection
	{
		math::Vec3f point;
		math::Vec3f normal;
		float t;

		void reset();
		bool occured() const;
	};

#pragma region Inline methods definitions
	inline void Intersection::reset()
	{
		t = std::numeric_limits<float>::infinity();
	}

	inline bool Intersection::occured() const
	{
		return t != std::numeric_limits<float>::infinity();
	}
#pragma endregion
}

#endif
