#include "blinnPhong.hpp"
#include "../Scene/IntersectionInfo/intersectionInfo.hpp"
#include "../../Math/ray.hpp"
#include "directionalLight.hpp"
#include "../Scene/SceneObjects/sphereObject.hpp"
#include "../Scene/SceneObjects/meshObject.hpp"

math::Vec3f BlinnPhong::calculateLighting(const DirectionalLight& light, const IntersectionInfo& intersectionInfo, const math::Ray& incidentRay)
{
	math::Vec3f lightDirection = -light.direction;
	math::Vec3f viewDirection = -incidentRay.direction;

	math::Vec3f albedo;
	float shininess;

	switch (intersectionInfo.type)
	{
	case IntersectionType::Sphere:
	{
		SphereObject* sphere = static_cast<SphereObject*>(intersectionInfo.intersectedObject);

		const Material& mat = sphere->getMaterial();

		albedo = mat.color;
		shininess = mat.shininess;
	}
		break;
	case IntersectionType::Mesh:
	{
		MeshObject* mesh = static_cast<MeshObject*>(intersectionInfo.intersectedObject);

		const Material& mat = mesh->getMaterial();

		albedo = mat.color;
		shininess = mat.shininess;

		break;
	}
	case IntersectionType::None:
		[[fallthrough]];
	default:
		assert(0);
	}

	math::Vec3f blinnPhongResult = calculateLighting(lightDirection, viewDirection, intersectionInfo.intersection.normal, albedo, shininess);

	math::Vec3f result = blinnPhongResult.cwiseProduct(light.color);
	return result;
}

math::Vec3f BlinnPhong::calculateLighting(const math::Vec3f& lightDirection, const math::Vec3f& viewDirection, const math::Vec3f& normal, const math::Vec3f& albedo, float shininess)
{
	math::Vec3f half_vector = (lightDirection + viewDirection).normalized();

	float diffuse = std::max(lightDirection.dot(normal), 0.0f);
	float specular = powf(std::max(half_vector.dot(normal), 0.0f), shininess);

	return (albedo * diffuse + math::Vec3f(specular, specular, specular)).cwiseMin(1.0f).cwiseMax(0.0f);
}
