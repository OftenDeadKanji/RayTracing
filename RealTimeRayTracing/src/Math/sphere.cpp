#include "sphere.hpp"
#include <math.h>
#include "ray.hpp"
#include "intersection.hpp"

namespace math
{
	bool Sphere::isIntersecting(const Ray& ray, IntersectionInfo& outIntersection) const
	{
        //optimized version, source - Real Time Rendering (4th edition)
        math::Vec3f l = position - ray.origin;
        float s = l.dot(ray.direction);
        float l2 = l.dot(l);
        float r2 = radius * radius;

        if (s < 0 && l2 > r2)
        {
            return false;
        }

        float m2 = l2 - s * s;
        if (m2 > r2)
        {
            return false;
        }
        
        float q = sqrtf(r2 - m2);
        float t = l2 > r2 ? s - q : s + q;

        if (t > outIntersection.t)
        {
            return false;
        }

        outIntersection.t = t;
        outIntersection.point = ray.origin + t * ray.direction;

        return true;

	}
}