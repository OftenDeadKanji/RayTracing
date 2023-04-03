#ifndef __MATERIAL_MANAGER_HPP__
#define __MATERIAL_MANAGER_HPP__
#include "../Utils/nonCopyable.hpp"
#include <memory>
#include "../RenderingSystem/Material/material.hpp"
#include <unordered_map>

class MaterialManager
	: public NonCopyable
{
	friend class FileWriter;
private:
	MaterialManager() = default;

public:
	static MaterialManager* createInstance();
	static MaterialManager* getInstance();
	static void deleteInstance();

	void addMaterial(std::shared_ptr<Material> material, const std::string& name);
	std::shared_ptr<Material> getMaterial(const std::string& name);
	const std::string& getMaterialName(std::shared_ptr<Material> material);

private:
	static std::unique_ptr<MaterialManager> s_instance;

	std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
	const std::string NO_SUCH_MATERIAL_KEY = "";
};

#pragma region Inline methods definitions

inline MaterialManager* MaterialManager::createInstance()
{
	s_instance = std::unique_ptr<MaterialManager>(new MaterialManager());
	return s_instance.get();
}

inline MaterialManager* MaterialManager::getInstance()
{
	return s_instance.get();
}

inline void MaterialManager::deleteInstance()
{
	s_instance.release();
}

inline void MaterialManager::addMaterial(std::shared_ptr<Material> material, const std::string& name)
{
	m_materials[name] = material;
}
inline std::shared_ptr<Material> MaterialManager::getMaterial(const std::string& name)
{
	return m_materials[name];
}

inline const std::string& MaterialManager::getMaterialName(std::shared_ptr<Material> material)
{
	for (auto iter = m_materials.cbegin(); iter != m_materials.cend(); iter++)
	{
		if (iter->second == material)
		{
			return iter->first;
		}
	}

	return NO_SUCH_MATERIAL_KEY;
}

#pragma endregion

inline std::unique_ptr<MaterialManager> MaterialManager::s_instance = nullptr;

#endif
