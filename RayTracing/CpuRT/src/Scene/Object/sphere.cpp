#include "sphere.h"
#include "../../Intersection/ray.h"
#include <cmath>
#include "glm/gtx/norm.hpp"
#include "glm/gtx/optimum_pow.hpp"

Sphere::Sphere()
	: Object(), m_radius(1.0f)
{
}

Sphere::Sphere(float radius, vec3 position)
	: Object(position), m_radius(radius)
{
}

Sphere::Sphere(float radius, Transform transform)
	: Object(transform), m_radius(radius)
{
}

bool Sphere::isIntersecting(const Ray* ray, std::vector<IntersectionPoint>& intersectionPoints) const
{
	using FaceSide = IntersectionPoint::FaceSide;

	//at2 + bt + c = 0
	vec3 origin_center = ray->Origin - m_transform.position;

	float a = glm::length2(ray->Direction);
	float half_b = glm::dot(ray->Direction, origin_center);
	float c = glm::length2(origin_center) - glm::pow2(m_radius);

	//solving quadriatic equation
	float delta = glm::pow2(half_b) - a * c;
	if (delta < 0.0f)
	{
		return false;
	}

	if (delta < std::numeric_limits<float>::epsilon())
	{
		float t = -half_b / a;

		vec3 point = ray->Origin + t * ray->Direction;
		vec3 normal = point - m_transform.position;
		
		float dot = glm::dot(ray->Direction, normal);
		FaceSide side = dot > 0.0f ? FaceSide::front : FaceSide::back;

		intersectionPoints.emplace_back(point, normal, side);

		return true;
	}
	float delta_sqroot = glm::sqrt(delta);
	float t1 = (-half_b - delta_sqroot) / a;
	float t2 = (-half_b + delta_sqroot) / a;

	vec3 point1 = ray->Origin + t1 * ray->Direction;
	vec3 normal1 = glm::normalize(point1 - m_transform.position);
	FaceSide side1 = FaceSide::front;
	
	float dot1 = glm::dot(ray->Direction, normal1);
	if (dot1 > 0.0f)
	{
		normal1 = -normal1;
		side1 = FaceSide::back;
	}

	vec3 point2 = ray->Origin + t2 * ray->Direction;
	vec3 normal2 = glm::normalize(point2 - m_transform.position);
	FaceSide side2 = FaceSide::front;

	float dot2 = glm::dot(ray->Direction, normal2);
	if (dot2 > 0.0f)
	{
		normal2 = -normal2;
		side2 = FaceSide::back;
	}

	intersectionPoints.emplace_back(point1, normal1, side1);
	intersectionPoints.emplace_back(point2, normal2, side2);

	return true;
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}

