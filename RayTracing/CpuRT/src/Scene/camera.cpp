#include "camera.h"
#include "../Intersection/ray.h"

Camera::Camera(vec2 resolution, float fov, vec3 position)
    : m_resolution(resolution), m_fov(fov), m_position(position)
{
	initRayGenerationVariables();
}

vec2 Camera::getResolution() const
{
    return m_resolution;
}

float Camera::getFov() const
{
    return m_fov;
}

Ray Camera::generateRay(float x, float y)
{
	auto u = static_cast<float>(x) / (m_resolution.x - 1);
	auto v = 1.0f - static_cast<float>(y) / (m_resolution.y - 1);

	vec3 rayOrigin = m_position;
	vec3 rayDirection = glm::normalize(vec3(m_lowerLeftCorner + u * m_horizontal + v * m_vertical - rayOrigin));

	return Ray(rayOrigin, rayDirection);
}

void Camera::initRayGenerationVariables()
{
	int width = m_resolution.x;
	int height = m_resolution.y;
	float aspectRatio = static_cast<float>(width) / height;

	auto viewportHeight = 1.0f;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0f;

	vec3 rayOrigin = m_position;
	m_horizontal = vec3(viewportWidth, 0.0f, 0.0f);
	m_vertical = vec3(0.0f, viewportHeight, 0.0f);

	m_lowerLeftCorner = rayOrigin - m_horizontal / 2.0f - m_vertical / 2.0f - vec3(0.0f, 0.0f, focalLength);
}
