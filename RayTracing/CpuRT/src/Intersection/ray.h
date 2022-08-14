#pragma once
#include "../Utilities/types.h"
#include <limits>

class Ray
{
public:
	Ray();
	Ray(vec3 origin, vec3 direction, float maxT = std::numeric_limits<float>::max());

	vec3& getOrigin();
	const vec3& getOrigin() const;
	void setOrigin(vec3 origin);
	__declspec(property(get = getOrigin, put = setOrigin)) vec3 Origin;

	vec3& getDirection();
	const vec3& getDirection() const;
	void setDirection(vec3 direction);
	__declspec(property(get = getDirection, put = setDirection)) vec3 Direction;

	float getMaxT();
	void setMaxT(float maxT);
	__declspec(property(get = getMaxT, put = setMaxT)) float MaxT;
private:
	vec3 m_origin;
	vec3 m_direction;
	float m_maxT;
};

