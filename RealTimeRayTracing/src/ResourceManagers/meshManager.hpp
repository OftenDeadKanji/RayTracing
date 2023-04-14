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
	friend class FileWriter;
public:
	static MeshManager* createInstance();
	static MeshManager* getInstance();
	static void deleteInstance();

	void init();
	void deinit();

	std::shared_ptr<Mesh> getMesh(const std::string& name);
	const std::string& getMeshName(std::shared_ptr<Mesh> mesh) const;

	std::shared_ptr<Mesh> getUnitCube();
	const std::string& getUnitCubeMeshName() const;
private:
	static std::unique_ptr<MeshManager> s_instance;

	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_predefinedMeshes;

	const std::string PREDEFINED_MESH_NAME_CUBE = "UNIT_CUBE";
	
	const std::string NO_SUCH_MESH_KEY = "NOT_FOUND";

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
	s_instance->deinit();
	s_instance.release();
}

inline std::shared_ptr<Mesh> MeshManager::getMesh(const std::string& name)
{
	if (auto pos = m_meshes.find(name); pos != m_meshes.end())
	{
		return pos->second;
	}

	if (auto pos = m_predefinedMeshes.find(name); pos != m_predefinedMeshes.end())
	{
		return pos->second;
	}

	return {};
}

inline const std::string& MeshManager::getMeshName(std::shared_ptr<Mesh> mesh) const
{
	for (auto iter = m_meshes.cbegin(); iter != m_meshes.cend(); iter++)
	{
		if (iter->second == mesh)
		{
			return iter->first;
		}
	}

	for (auto iter = m_predefinedMeshes.cbegin(); iter != m_predefinedMeshes.cend(); iter++)
	{
		if (iter->second == mesh)
		{
			return iter->first;
		}
	}

	return NO_SUCH_MESH_KEY;
}

inline std::shared_ptr<Mesh> MeshManager::getUnitCube()
{
	return m_predefinedMeshes[PREDEFINED_MESH_NAME_CUBE];
}

inline const std::string& MeshManager::getUnitCubeMeshName() const
{
	return PREDEFINED_MESH_NAME_CUBE;
}

#pragma endregion

#endif
