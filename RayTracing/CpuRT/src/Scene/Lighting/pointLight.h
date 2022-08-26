#pragma once
#include "lightSource.h"

class PointLight
	: public LightSource
{
public:
	PointLight(const vec3& position = vec3{ 0.0f, 0.0f, 0.0f }, const vec3& diffuseIntensity = vec3{ 0.8f, 0.8f, 0.8f }, const vec3& specularIntensity = vec3{ 1.0f, 1.0f, 1.0f });

	virtual vec3 calculateShadowRayColor(const IntersectionPoint& point, const Ray& incidenceRay) const override;

	vec3& getPosition();
	const vec3& getPosition() const;
	void setPosition(const vec3& position);

	vec3 createShadowRay(const IntersectionPoint& point, const Ray& incidenceRay) const;
private:
	vec3 m_position;

};

