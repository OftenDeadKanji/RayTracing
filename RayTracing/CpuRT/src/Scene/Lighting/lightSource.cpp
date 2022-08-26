#include "lightSource.h"

LightSource::LightSource(const vec3& diffuseIntensity, const vec3& specularIntensity)
	: m_intensity{ vec3{diffuseIntensity}, vec3{specularIntensity} }
{
}

vec3 LightSource::getDiffuseIntensity() const
{
	return m_intensity.diffuse;
}

void LightSource::setDiffuseIntensity(const vec3& intensity)
{
	m_intensity.diffuse = intensity;
}

vec3 LightSource::getSpecularIntensity() const
{
	return m_intensity.specular;
}

void LightSource::setSpecularIntensity(const vec3& intensity)
{
	m_intensity.specular = intensity;
}