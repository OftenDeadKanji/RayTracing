#pragma once
#include "../Utilities/types.h"

class Shading
{
public:
	static vec3 getColor_Phong(vec3 albedo, vec3 position, vec3 normal, vec3 lightDirecction, vec3 viewDirection);

};

