#pragma once
#include "../../Utilities/types.h"

class IntersectionPoint;
class Ray;

class LightSource
{
public:
	LightSource(const vec3& diffuseIntensity = vec3{0.8f, 0.8f, 0.8f}, const vec3& specularIntensity = vec3{1.0f, 1.0f, 1.0f});

	virtual vec3 calculateShadowRayColor(const IntersectionPoint& point, const Ray& incidenceRay) const = 0;

	vec3 getDiffuseIntensity() const;
	void setDiffuseIntensity(const vec3& intensity);

	vec3 getSpecularIntensity() const;
	void setSpecularIntensity(const vec3& intensity);

	virtual vec3 createShadowRay(const IntersectionPoint& point, const Ray& incidenceRay) const = 0;

protected:
	struct Intensity
	{
		vec3 diffuse;
		vec3 specular;
	} m_intensity;
};

