#ifndef __MESH_HPP__
#define __MESH_HPP__
#include "../../Math/mathUtils.hpp"
#include <vector>

namespace math
{
	struct Ray;
	struct Intersection;
}

struct Mesh
{
	struct Triangle
	{
		math::Vec3f vertices[3];
		math::Vec3f normal;

		void calculateNormal();
		bool isIntersecting(const math::Ray& ray, math::Intersection& outIntersection) const;
	};

	std::vector<Triangle> triangles;

	bool isIntersecting(const math::Ray& ray, math::Intersection& outIntersection) const;
};

#endif
