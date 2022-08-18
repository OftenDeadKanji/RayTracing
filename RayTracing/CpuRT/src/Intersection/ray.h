#pragma once
#include "../Utilities/types.h"
#include <limits>

class Object;

class Ray
{
public:
	Ray();
	Ray(vec3 origin, vec3 direction, Object* startingObject = nullptr, float maxT = std::numeric_limits<float>::max());

	vec3& getOrigin();
	const vec3& getOrigin() const;
	void setOrigin(vec3 origin);
	__declspec(property(get = getOrigin, put = setOrigin)) vec3 Origin;

	vec3& getDirection();
	const vec3& getDirection() const;
	void setDirection(vec3 direction);
	__declspec(property(get = getDirection, put = setDirection)) vec3 Direction;

	float getMaxT() const;
	void setMaxT(float maxT);
	__declspec(property(get = getMaxT, put = setMaxT)) float MaxT;

	Object* getStartingObject();
	Object* const getStartingObject() const;
	void setStartingObject(Object* object);
	__declspec(property(get = getStartingObject, put = setStartingObject)) Object* StartingObject;

private:
	vec3 m_origin;
	vec3 m_direction;
	float m_maxT;
	Object* m_startingObject;

};

