#include "intersectionPoint.h"

IntersectionPoint::IntersectionPoint()
	: IntersectionPoint{ vec3{0.0f}, vec3{0.0f}, FaceSide::Front }
{
}

IntersectionPoint::IntersectionPoint(const vec3& position, const vec3& normal, FaceSide side)
	: position{ position }, normal{ normal }, side{ side }
{

}