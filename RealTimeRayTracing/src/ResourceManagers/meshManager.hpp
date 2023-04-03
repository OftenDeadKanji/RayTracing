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
	const std::string& getMeshName(std::shared_ptr<Mesh> mesh);

	std::shared_ptr<Mesh> getUnitCube();
	const std::string& getUnitCubeMeshName();

private:
	static std::unique_ptr<MeshManager> s_instance;

	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;

	const std::string PREDEFINED_MESH_NAME_CUBE = "UNIT_CUBE";
	
	const std::string NO_SUCH_MESH_KEY = "";

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
	return m_meshes[name];
}

inline const std::string& MeshManager::getMeshName(std::shared_ptr<Mesh> mesh)
{
	for (auto iter = m_meshes.cbegin(); iter != m_meshes.cend(); iter++)
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
	return m_meshes[PREDEFINED_MESH_NAME_CUBE];
}

inline const std::string& MeshManager::getUnitCubeMeshName()
{
	return PREDEFINED_MESH_NAME_CUBE;
}

#pragma endregion

#endif
