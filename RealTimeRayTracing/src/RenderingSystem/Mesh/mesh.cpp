#include "mesh.hpp"
#include "../../Math/ray.hpp"
#include "../../Math/intersection.hpp"

void Mesh::Triangle::calculateNormal()
{
	math::Vec3f v01 = vertices[1] - vertices[0];
	math::Vec3f v02 = vertices[2] - vertices[0];

	normal = v01.cross(v02).normalized();
}

bool Mesh::Triangle::isIntersecting(const math::Ray& ray, math::Intersection& outIntersection) const
{
    float denominator = normal.dot(ray.direction);

    if (std::abs(denominator) > std::numeric_limits<float>::epsilon())
    {
        const math::Vec3f& v0 = vertices[0];

        float D = -normal.dot(v0);
        float t = -(normal.dot(ray.origin) + D) / denominator;

        if (t >= 0.0f && t < outIntersection.t)
        {
            math::Vec3f P = ray.origin + ray.direction * t;

            const math::Vec3f& v1 = vertices[1];
            const math::Vec3f& v2 = vertices[2];

            math::Vec3f edge01 = v0 - v1;
            math::Vec3f edge12 = v1 - v2;
            math::Vec3f edge20 = v2 - v0;

            math::Vec3f C0 = P - v0;
            math::Vec3f C1 = P - v1;
            math::Vec3f C2 = P - v2;

            auto dot0 = normal.dot(C0 .cross(edge01));
            auto dot1 = normal.dot(C1 .cross(edge12));
            auto dot2 = normal.dot(C2 .cross(edge20));

            if (dot0 > 0 &&
                dot1 > 0 &&
                dot2 > 0)
            {
                outIntersection.t = t;
                outIntersection.point = P;
                outIntersection.normal = normal;

                return true;
            }
        }
    }

    return false;
}

bool Mesh::isIntersecting(const math::Ray& ray, math::Intersection& outIntersection) const
{
    bool intersected = false;
    for (const auto& triangle : triangles)
    {
        if (triangle.isIntersecting(ray, outIntersection))
        {
            intersected = true;
        }
    }

    return intersected;
}
