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

bool Sphere::isIntersecting(const Ray* ray, IntersectionPoint& intersectionPoint) const
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

	float delta_sqroot = glm::sqrt(delta);
	float t = (-half_b - delta_sqroot) / a;

	if (t > ray->MaxT || t < 0.00001f)
	{
		return false;
	}

	vec3 point = ray->Origin + t * ray->Direction;
	vec3 normal = glm::normalize(point - m_transform.position);
	FaceSide side = FaceSide::front;
	
	float dot = glm::dot(ray->Direction, normal);
	if (dot > 0.0f)
	{
		normal = -normal;
		side = FaceSide::back;
	}

	intersectionPoint = IntersectionPoint(point, normal, side);
	return true;
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}

