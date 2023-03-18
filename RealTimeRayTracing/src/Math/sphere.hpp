#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__
#include "mathUtils.hpp"

namespace math
{
	struct Ray;
	struct Intersection;

	struct Sphere
	{
		math::Vec3f position;
		float radius;

		bool isIntersecting(const Ray& ray, Intersection& outIntersection) const;
	};
}

#endif
