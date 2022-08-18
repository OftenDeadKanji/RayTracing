#include "intersectionPoint.h"

IntersectionPoint::IntersectionPoint()
	: IntersectionPoint(vec3(0.0f), vec3(0.0f), FaceSide::front)
{
}

IntersectionPoint::IntersectionPoint(const vec3& position, const vec3& normal, FaceSide side)
	: position(position), normal(normal), side(side)
{

}

bool IntersectionPoint::isOnTheFrontSide() const
{
	return side == FaceSide::front;
}
