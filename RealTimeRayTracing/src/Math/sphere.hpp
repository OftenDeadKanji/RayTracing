#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__
#include "mathUtils.hpp"

namespace math
{
	struct Ray;
	struct IntersectionInfo;

	struct Sphere
	{
		math::Vec3f position;
		float radius;

		bool isIntersecting(const Ray& ray, IntersectionInfo& outIntersection) const;
	};
}

#endif
