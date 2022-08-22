#pragma once
#include "../Utilities/types.h"
#include <limits>

class Object;

class Ray
{
public:
	Ray();
	Ray(vec3 origin, vec3 direction, float minT = 0.0f, float maxT = std::numeric_limits<float>::max(), Object* startingObject = nullptr);

	//vec3& getOrigin();
	const vec3& getOrigin() const;
	void setOrigin(vec3 origin);

	//vec3& getDirection();
	const vec3& getDirection() const;
	void setDirection(vec3 direction);

	float getMaxT() const;
	void setMaxT(float maxT);

	float getMinT() const;
	void setMinT(float maxT);

	//Object* getStartingObject();
	Object* const getStartingObject() const;
	void setStartingObject(Object* object);

private:
	vec3 m_origin;
	vec3 m_direction;
	float m_minT;
	float m_maxT;
	Object* m_startingObject;
};

