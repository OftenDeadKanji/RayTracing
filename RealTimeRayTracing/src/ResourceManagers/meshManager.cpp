#include "meshManager.hpp"

std::unique_ptr<MeshManager> MeshManager::s_instance = nullptr;

void MeshManager::init()
{
	createUnitCube();
}

void MeshManager::deinit()
{
	m_meshes.clear();
}

void MeshManager::createUnitCube()
{
	std::shared_ptr<Mesh> mesh(new Mesh());
	mesh->triangles.reserve(12);

	math::Vec3f FLB(-1.0f, -1.0f, -1.0f);	// 0
	math::Vec3f FLT(-1.0f,  1.0f, -1.0f);	// 1
	math::Vec3f FRB( 1.0f, -1.0f, -1.0f);	// 2
	math::Vec3f FRT( 1.0f,  1.0f, -1.0f);	// 3
	math::Vec3f BLB(-1.0f, -1.0f,  1.0f);	// 4
	math::Vec3f BLT(-1.0f,  1.0f,  1.0f);	// 5
	math::Vec3f BRB( 1.0f, -1.0f,  1.0f);	// 6
	math::Vec3f BRT( 1.0f,  1.0f,  1.0f);	// 7

	mesh->triangles.push_back({ {FLB, FLT, FRT}, {0.0f, 0.0f, -1.0f} });
	mesh->triangles.push_back({ {FLB, FRT, FRB}, {0.0f, 0.0f, -1.0f} });

	mesh->triangles.push_back({ {FRB, FRT, BRT}, {1.0f, 0.0f, 0.0f} });
	mesh->triangles.push_back({ {FRB, BRT, BRB}, {1.0f, 0.0f, 0.0f} });

	mesh->triangles.push_back({ {FLT, BLT, BRT}, {0.0f, 1.0f, 0.0f} });
	mesh->triangles.push_back({ {FLT, BRT, FRT}, {0.0f, 1.0f, 0.0f} });

	mesh->triangles.push_back({ {BRB, BRT, BLT}, {0.0f, 0.0f, 1.0f} });
	mesh->triangles.push_back({ {BRB, BLT, BLB}, {0.0f, 0.0f, 1.0f} });

	mesh->triangles.push_back({ {BLB, BLT, FLT}, {-1.0f, 0.0f, 0.0f} });
	mesh->triangles.push_back({ {BLB, FLT, FLB}, {-1.0f, 0.0f, 0.0f} });

	mesh->triangles.push_back({ {BLB, FLB, FRB}, {0.0f, -1.0f, 0.0f} });
	mesh->triangles.push_back({ {BLB, FRB, BRB}, {0.0f, -1.0f, 0.0f} });

	m_meshes.insert({ PREDEFINED_MESH_NAME_CUBE, mesh });
}
