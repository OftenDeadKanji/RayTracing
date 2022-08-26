#include "pointLight.h"
#include "../../Intersection/intersectionPoint.h"
#include "../../Intersection/ray.h"


PointLight::PointLight(const vec3& position, const vec3& diffuseIntensity, const vec3& specularIntensity)
	: LightSource{diffuseIntensity, specularIntensity}, m_position{position}
{
}

vec3 PointLight::calculateShadowRayColor(const IntersectionPoint& point, const Ray& incidenceRay) const
{
	vec3 shadowRayDirection = glm::normalize(m_position - point.position);

	const vec3& l = shadowRayDirection;
	const vec3& n = point.normal;
	
	const vec3 v = -incidenceRay.getDirection();
	const vec3 r = glm::reflect(l, n);
	const vec3 h = glm::normalize(l + v);

	return m_intensity.diffuse * glm::dot(l, n) + m_intensity.specular * glm::pow(glm::dot(h, n), 64.0f);
}

vec3& PointLight::getPosition()
{
	return m_position;
}

const vec3& PointLight::getPosition() const
{
	return m_position;
}

void PointLight::setPosition(const vec3& position)
{
	m_position = position;
}

vec3 PointLight::createShadowRay(const IntersectionPoint& point, const Ray& incidenceRay) const
{
	return glm::normalize(m_position - point.position);
}
