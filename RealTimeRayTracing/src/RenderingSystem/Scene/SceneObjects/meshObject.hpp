#ifndef __MESH_OBJECT_HPP__
#define __MESH_OBJECT_HPP__
#include "../../Mesh/mesh.hpp"
#include "../../Material/material.hpp"
#include "../../TransformSystem/transformManager.hpp"

struct IntersectionInfo;

class MeshObject
{
	friend class Scene;
	friend class FileWriter;
public:
	bool isIntersecting(const math::Ray& ray, IntersectionInfo& outIntersectionInfo);

	void setMesh(std::shared_ptr<Mesh> mesh);

	std::shared_ptr<Material> getMaterial() const;
private:
	std::shared_ptr<Mesh> m_mesh;

	std::shared_ptr<Material> m_material;
	TransformManager::TransformID m_transformID;
};

#pragma region Inline methods definitions

inline void MeshObject::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

inline std::shared_ptr<Material> MeshObject::getMaterial() const
{
	return m_material;
}

#pragma endregion

#endif
