#include "camera.h"

Camera::Camera(vec2 resolution, float fov)
    : m_resolution(resolution), m_fov(fov)
{
}

vec2 Camera::getResolution() const
{
    return m_resolution;
}

float Camera::getFov() const
{
    return m_fov;
}
