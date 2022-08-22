#pragma once
#include "../Utilities/types.h"

class Ray;

class Camera
{
public:
	Camera(vec2 resolution, float fov, vec3 m_position = vec3(0.0f, 0.0f, 0.0f));

	vec2 getResolution() const;
	
	float getFov() const;

	Ray generateRay(float x, float y);
private:
	void initRayGenerationVariables();

	vec2 m_resolution;
	float m_fov;
	vec3 m_position;

#pragma region Ray generation variables
	vec3 m_lowerLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
#pragma endregion
};

