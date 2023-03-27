#include "blinnPhong.hpp"
#include "../Scene/IntersectionInfo/intersectionInfo.hpp"
#include "../../Math/ray.hpp"
#include "directionalLight.hpp"
#include "pointLight.hpp"
#include "../Scene/SceneObjects/sphereObject.hpp"
#include "../Scene/SceneObjects/meshObject.hpp"

math::Vec3f BlinnPhong::calculateLighting(const DirectionalLight& light, const math::Vec3f& surfacePoint, const math::Vec3f& surfaceNormal, const math::Vec3f& viewDirection, const Material& material)
{
	math::Vec3f lightDirection = -light.direction;

	math::Vec3f blinnPhongResult = calculateLighting(lightDirection, viewDirection, surfaceNormal, material);

	math::Vec3f result = blinnPhongResult.cwiseProduct(light.color);
	return result;
}

math::Vec3f BlinnPhong::calculateLighting(const PointLight& light, const math::Vec3f& surfacePoint, const math::Vec3f& surfaceNormal, const math::Vec3f& viewDirection, const Material& material)
{
	math::Vec3f lightDirection = (light.position - surfacePoint).normalized();

	math::Vec3f blinnPhongResult = calculateLighting(lightDirection, viewDirection, surfaceNormal, material);

	float distance = (light.position - surfacePoint).norm();
	math::Vec3f result = blinnPhongResult.cwiseProduct(light.color / (distance * distance));
	return result;
}

math::Vec3f BlinnPhong::calculateLighting(const math::Vec3f& lightDirection, const math::Vec3f& viewDirection, const math::Vec3f& normal, const Material& material)
{
	math::Vec3f half_vector = (lightDirection + viewDirection).normalized();

	float diffuse = std::max(lightDirection.dot(normal), 0.0f);
	float specular = powf(std::max(half_vector.dot(normal), 0.0f), material.shininess);
	
	return (material.color * diffuse + math::Vec3f(specular, specular, specular));
}
