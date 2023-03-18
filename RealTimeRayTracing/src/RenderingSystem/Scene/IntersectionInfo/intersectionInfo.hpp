#ifndef __INTERSECTION_INFO_HPP__
#define __INTERSECTION_INFO_HPP__
#include "../../../Math/intersection.hpp"
//#include "../../Material/material.hpp"
#include "intersectionType.hpp"

struct IntersectionInfo
{
	math::Intersection intersection;
	//Material material;
	IntersectionType type;
	void* intersectedObject;

	void reset();
	bool occured() const;
};

#pragma region Inline methods definitions

inline void IntersectionInfo::reset()
{
	intersection.reset();
	type = IntersectionType::None;
	intersectedObject = nullptr;
}

inline bool IntersectionInfo::occured() const
{
	return intersectedObject != nullptr;
}

#pragma endregion

#endif