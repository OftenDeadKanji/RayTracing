#include "sphere.h"
#include "../../Intersection/ray.h"
#include <cmath>

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

bool Sphere::isIntersecting(const Ray* ray, std::vector<vec3>& intersectionPoints) const
{
	//at2 + bt + c = 0

	float a = glm::dot(ray->Direction, ray->Direction);
	float b = 2 * glm::dot(ray->Direction, ray->Origin);
	float c = glm::dot(ray->Origin, ray->Origin) - m_radius * m_radius;

	//solving quadriatic equation
	float delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		return false;
	}

	if (delta < std::numeric_limits<float>::epsilon())
	{
		float t = b / (2 * a);

		vec3 point = ray->Origin + t * ray->Direction;
		intersectionPoints.push_back(point);
	
		return true;
	}

	float t1 = (b - std::sqrt(delta)) / (2 * a);
	float t2 = (b + std::sqrt(delta)) / (2 * a);

	vec3 point1 = ray->Origin + t1 * ray->Direction;
	vec3 point2 = ray->Origin + t2 * ray->Direction;

	intersectionPoints.push_back(point1);
	intersectionPoints.push_back(point2);

	return true;
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}

