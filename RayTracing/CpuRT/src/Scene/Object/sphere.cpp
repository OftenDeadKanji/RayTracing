#include "sphere.h"
#include "../../Intersection/ray.h"
#include <cmath>
#include "glm/gtx/norm.hpp"
#include "glm/gtx/optimum_pow.hpp"

Sphere::Sphere(const vec3& color)
	: Object{ color }, m_radius{ 1.0f }
{
}

Sphere::Sphere(float radius, const Transform& position, const vec3& color)
	: Object{ position, color }, m_radius{ radius }
{
}

bool Sphere::isIntersecting(const Ray* ray, IntersectionPoint& intersectionPoint) const
{
	using FaceSide = IntersectionPoint::FaceSide;

	//at2 + bt + c = 0
	vec3 origin_center = ray->getOrigin() - m_transform.position;

	float a = glm::length2(ray->getDirection());
	float half_b = glm::dot(ray->getDirection(), origin_center);
	float c = glm::length2(origin_center) - glm::pow2(m_radius);

	//solving quadriatic equation
	float delta = glm::pow2(half_b) - a * c;
	
	if (delta < 0.0f)
	{
		return false;
	}

	float delta_sqroot = glm::sqrt(delta);
	float t = (-half_b - delta_sqroot) / a;

	if (t > ray->getMaxT() || t < ray->getMinT())
	{
		return false;
	}

	vec3 point = ray->getOrigin() + t * ray->getDirection();
	vec3 normal = glm::normalize(point - m_transform.position);
	FaceSide side = FaceSide::Front;
	
	float dot = glm::dot(ray->getDirection(), normal);
	if (dot > 0.0f)
	{
		normal = -normal;
		side = FaceSide::Back;
	}

	intersectionPoint = IntersectionPoint(point, normal, side);
	return true;
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}

