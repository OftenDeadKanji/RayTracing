#ifndef __MESH_OBJECT_HPP__
#define __MESH_OBJECT_HPP__
#include "../../Mesh/mesh.hpp"
#include "../../Material/material.hpp"
#include "../../../Math/transform.hpp"

struct IntersectionInfo;
class Scene;

class MeshObject
{
	friend class Scene;
public:
	bool isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo);

	void setMesh(std::shared_ptr<Mesh> mesh);

	const Material& getMaterial() const;
private:
	std::shared_ptr<Mesh> m_mesh;
	Material m_material;
	math::Transform m_transform;
};

#pragma region Inline methods definitions

inline void MeshObject::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

inline const Material& MeshObject::getMaterial() const
{
	return m_material;
}

#pragma endregion

#endif
