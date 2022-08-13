#pragma once
#include "../Utilities/types.h"

class Camera
{
public:
	Camera(vec2 resolution, float fov);

	vec2 getResolution() const;
	__declspec(property(get = getResolution)) vec2 Resolution;
	
	float getFov() const;
	__declspec(property(get = getFov)) float Fov;
private:
	vec2 m_resolution;
	float m_fov;
};

