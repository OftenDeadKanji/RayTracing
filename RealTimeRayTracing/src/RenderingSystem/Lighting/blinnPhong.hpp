#ifndef __BLINN_PHONG_HPP__
#define __BLINN_PHONG_HPP__
#include "../../Math/mathUtils.hpp"

struct DirectionalLight;
struct IntersectionInfo;

namespace math
{
	struct Ray;
}

class BlinnPhong
{
public:
	math::Vec3f calculateLighting(const DirectionalLight& light, const IntersectionInfo& intersectionInfo, const math::Ray& incidentRay);

private:
	math::Vec3f calculateLighting(const math::Vec3f& lightDirection, const math::Vec3f& viewDirection, const math::Vec3f& normal, const math::Vec3f& albedo, float shininess);
};

#endif
