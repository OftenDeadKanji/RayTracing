#ifndef __BLINN_PHONG_HPP__
#define __BLINN_PHONG_HPP__
#include "../../Math/mathUtils.hpp"

struct DirectionalLight;
struct IntersectionInfo;

namespace math
{
	struct Ray;
}

struct Material;

class BlinnPhong
{
public:
	math::Vec3f calculateLighting(const DirectionalLight& light, const math::Vec3f& surfacePoint, const math::Vec3f& surfaceNormal, const math::Vec3f& viewDirection, const Material& material);

private:
	math::Vec3f calculateLighting(const math::Vec3f& lightDirection, const math::Vec3f& viewDirection, const math::Vec3f& normal, const Material& material);
};

#pragma region Inline mathods definitions

#pragma endregion

#endif
