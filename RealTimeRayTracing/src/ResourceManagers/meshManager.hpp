#ifndef __MESH_MANAGER_HPP__
#define __MESH_MANAGER_HPP__
#include <memory>
#include "../Utils/nonCopyable.hpp"
#include <unordered_map>
#include <string>
#include "../RenderingSystem/Mesh/mesh.hpp"


class MeshManager
	: public NonCopyable
{
public:
	static MeshManager* createInstance();
	static MeshManager* getInstance();
	void deleteInstance();

	void init();
	void deinit();

	std::shared_ptr<Mesh> getMesh(const std::string& name);
	std::shared_ptr<Mesh> getUnitCube();
private:
	static std::unique_ptr<MeshManager> s_instance;

	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_predefinedMeshes;

	const std::string PREDEFINED_MESH_NAME_CUBE = "UNIT_CUBE";

	void createUnitCube();
};

#pragma region Inline methods definitions

inline MeshManager* MeshManager::createInstance()
{
	s_instance = std::unique_ptr<MeshManager>(new MeshManager());

	return s_instance.get();
}

inline MeshManager* MeshManager::getInstance()
{
	return s_instance.get();
}

inline void MeshManager::deleteInstance()
{
	deinit();
	s_instance.release();
}

inline std::shared_ptr<Mesh> MeshManager::getMesh(const std::string& name)
{
	return m_meshes[name];
}

inline std::shared_ptr<Mesh> MeshManager::getUnitCube()
{
	return m_predefinedMeshes[PREDEFINED_MESH_NAME_CUBE];
}

#pragma endregion

#endif
