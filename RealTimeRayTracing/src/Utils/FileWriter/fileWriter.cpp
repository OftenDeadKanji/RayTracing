#include "fileWriter.hpp"
#include "../../RenderingSystem/Scene/scene.hpp"
#include <fstream>
#include "../cast.hpp"
#include "../../ResourceManagers/materialManager.hpp"
#include "../../ResourceManagers/meshManager.hpp"
#include "../../RenderingSystem/TransformSystem/transformManager.hpp"

void FileWriter::saveToBinaryFile(std::ofstream& file, const MaterialManager& materialManager)
{
	auto managerVersion = MaterialManagerClassVersion::vCurrent;
	file.write(rCast(const char*, &managerVersion), sizeof(managerVersion));

	// m_materials
	size_t materialsCount = materialManager.m_materials.size();
	file.write(rCast(const char*, &materialsCount), sizeof(materialsCount));

	for (auto cIter = materialManager.m_materials.cbegin(); cIter != materialManager.m_materials.cend(); cIter++)
	{
		size_t nameLength = cIter->first.size();
		file.write(rCast(const char*, &nameLength), sizeof(nameLength));
		file.write(cIter->first.c_str(), cIter->first.size());

		saveToBinaryFile(file, cIter->second);
	}
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, MaterialManager& materialManager)
{
	size_t bajty;
	MaterialManagerClassVersion managerVersion;
	file.read(rCast(char*, &managerVersion), sizeof(managerVersion));

	if (managerVersion == MaterialManagerClassVersion::v1_0)
	{
		size_t materialsCount;
		file.read(rCast(char*, &materialsCount), sizeof(materialsCount));

		for (int i = 0; i < materialsCount; i++)
		{
			size_t nameLength;
			file.read(rCast(char*, &nameLength), sizeof(nameLength));

			std::string name;
			name.resize(nameLength);
			file.read(&name[0], nameLength);

			auto material = std::make_shared<Material>();
			loadFromBinaryFile(file, material);

			materialManager.m_materials[name] = material;
		}
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, std::shared_ptr<const Material> material)
{
	auto materialVersion = MaterialClassVersion::vCurrent;
	file.write(rCast(const char*, &materialVersion), sizeof(materialVersion));

	file.write(rCast(const char*, &material->color), sizeof(material->color));
	file.write(rCast(const char*, &material->shininess), sizeof(material->shininess));
	file.write(rCast(const char*, &material->isEmmisive), sizeof(material->isEmmisive));
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, std::shared_ptr<Material> material)
{
	MaterialClassVersion materialVersion;
	file.read(rCast(char*, &materialVersion), sizeof(materialVersion));

	if (materialVersion == MaterialClassVersion::v1_0)
	{
		file.read(rCast(char*, &material->color), sizeof(material->color));
		file.read(rCast(char*, &material->shininess), sizeof(material->shininess));
		file.read(rCast(char*, &material->isEmmisive), sizeof(material->isEmmisive));
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const TransformManager& transformManager)
{
	auto transformManagerVersion = TransformManagerClassVersion::vCurrent;
	file.write(rCast(const char*, &transformManagerVersion), sizeof(transformManagerVersion));

	size_t transformsCount = transformManager.m_transforms.size();
	file.write(rCast(const char*, &transformsCount), sizeof(transformsCount));

	for (auto cIter = transformManager.m_transforms.cbegin(); cIter != transformManager.m_transforms.cend(); cIter++)
	{
		file.write(rCast(const char*, &cIter->first), sizeof(cIter->first));
		file.write(rCast(const char*, &cIter->second), sizeof(cIter->second));
	}

	file.write(rCast(const char*, &transformManager.m_nextID), sizeof(transformManager.m_nextID));

	size_t freeIDsCount = transformManager.m_freeIDs.size();
	file.write(rCast(const char*, &freeIDsCount), sizeof(freeIDsCount));

	auto freeIDs = transformManager.m_freeIDs;

	while (!freeIDs.empty())
	{
		unsigned int nextID = freeIDs.front();
		freeIDs.pop();

		file.write(rCast(const char*, &freeIDs), sizeof(freeIDs));
	}
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, TransformManager& transformManager)
{
	TransformManagerClassVersion transformManagerVersion;
	file.read(rCast(char*, &transformManagerVersion), sizeof(transformManagerVersion));

	if (transformManagerVersion == TransformManagerClassVersion::v1_0)
	{
		size_t transformsCount;
		file.read(rCast(char*, &transformsCount), sizeof(transformsCount));

		for (int i = 0; i < transformsCount; i++)
		{
			unsigned int id;
			file.read(rCast(char*, &id), sizeof(id));

			math::Transform transform;
			file.read(rCast(char*, &transform), sizeof(transform));

			transformManager.m_transforms[id] = transform;
		}

		file.read(rCast(char*, &transformManager.m_nextID), sizeof(transformManager.m_nextID));

		size_t freeIDsCount;
		file.read(rCast(char*, &freeIDsCount), sizeof(freeIDsCount));

		for (int i = 0; i < freeIDsCount; i++)
		{
			unsigned int id;
			file.read(rCast(char*, &id), sizeof(id));

			transformManager.m_freeIDs.push(id);
		}
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const MeshManager& meshManager)
{
	auto managerVersion = MeshManagerClassVersion::vCurrent;
	file.write(rCast(const char*, &managerVersion), sizeof(managerVersion));

	// m_meshes
	size_t meshesCount = meshManager.m_meshes.size();
	file.write(rCast(const char*, &meshesCount), sizeof(meshesCount));

	for (auto cIter = meshManager.m_meshes.cbegin(); cIter != meshManager.m_meshes.cend(); cIter++)
	{
		size_t nameLength = cIter->first.size();
		file.write(rCast(const char*, &nameLength), sizeof(nameLength));
		file.write(cIter->first.c_str(), cIter->first.size());

		saveToBinaryFile(file, cIter->second);
	}
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, MeshManager& meshManager)
{
	MeshManagerClassVersion managerVersion;
	file.read(rCast(char*, &managerVersion), sizeof(managerVersion));

	if (managerVersion == MeshManagerClassVersion::v1_0)
	{
		// m_meshes
		size_t meshesCount;
		file.read(rCast(char*, &meshesCount), sizeof(meshesCount));

		for (int i = 0; i < meshesCount; i++)
		{
			size_t nameLength;
			file.read(rCast(char*, &nameLength), sizeof(nameLength));

			std::string name;
			name.resize(nameLength);
			file.read(&name[0], nameLength);

			auto mesh = std::make_shared<Mesh>();

			loadFromBinaryFile(file, mesh);

			meshManager.m_meshes[name] = mesh;
		}
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, std::shared_ptr<const Mesh> mesh)
{
	auto meshVersion = MeshClassVersion::vCurrent;
	file.write(rCast(const char*, &meshVersion), sizeof(meshVersion));

	size_t trianglesCount = mesh->triangles.size();
	file.write(rCast(const char*, &trianglesCount), sizeof(trianglesCount));

	for (const auto& triangle : mesh->triangles)
	{
		file.write(rCast(const char*, &triangle), sizeof(triangle));
	}
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, std::shared_ptr<Mesh> mesh)
{
	MeshClassVersion meshVersion;
	file.read(rCast(char*, &meshVersion), sizeof(meshVersion));

	if (meshVersion == MeshClassVersion::v1_0)
	{
		size_t trianglesCount;
		file.read(rCast(char*, &trianglesCount), sizeof(trianglesCount));

		mesh->triangles.resize(trianglesCount);

		for (int i = 0; i < trianglesCount; i++)
		{
			Mesh::Triangle triangle;
			file.read(rCast(char*, &mesh->triangles[i]), sizeof(triangle));
		}
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const Scene& scene)
{
	auto sceneVersion = SceneClassVersion::vCurrent;
	file.write(rCast(const char*, &sceneVersion), sizeof(sceneVersion));

	//m_backgroundColor
	file.write(rCast(const char*, &scene.m_backgroundColor), sizeof(scene.m_backgroundColor));

	//m_spheres
	size_t spheresCount = scene.m_spheres.size();
	file.write(rCast(const char*, &spheresCount), sizeof(spheresCount));

	for (auto cIter = scene.m_spheres.cbegin(); cIter != scene.m_spheres.cend(); cIter++)
	{
		saveToBinaryFile(file, *cIter);
	}
	
	//m_meshes
	size_t meshesCount = scene.m_meshes.size();
	file.write(rCast(const char*, &meshesCount), sizeof(meshesCount));

	for (auto cIter = scene.m_meshes.cbegin(); cIter != scene.m_meshes.cend(); cIter++)
	{
		saveToBinaryFile(file, *cIter);
	}

	//lights
	file.write(rCast(const char*, &scene.m_ambientLight), sizeof(scene.m_ambientLight));

	size_t dirLightsCount = scene.m_directionalLights.size();
	file.write(rCast(const char*, &dirLightsCount), sizeof(dirLightsCount));

	for (const auto& dirLight : scene.m_directionalLights)
	{
		saveToBinaryFile(file, dirLight);
	}

	size_t pointLightsCount = scene.m_pointLights.size();
	file.write(rCast(const char*, &pointLightsCount), sizeof(pointLightsCount));

	for (const auto& pointLight : scene.m_pointLights)
	{
		saveToBinaryFile(file, pointLight);
	}
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, Scene& scene)
{
	SceneClassVersion sceneVersion;
	file.read(rCast(char*, &sceneVersion), sizeof(sceneVersion));

	if (sceneVersion == SceneClassVersion::v1_0)
	{
		//m_backgroundColor
		file.read(rCast(char*, &scene.m_backgroundColor), sizeof(scene.m_backgroundColor));

		//m_spheres
		size_t spheresCount;
		file.read(rCast(char*, &spheresCount), sizeof(spheresCount));

		scene.m_spheres.resize(spheresCount);

		for (int i = 0; i < spheresCount; i++)
		{
			loadFromBinaryFile(file, scene.m_spheres[i]);
		}

		//m_meshes
		size_t meshesCount;
		file.read(rCast(char*, &meshesCount), sizeof(meshesCount));

		scene.m_meshes.resize(meshesCount);

		for (int i = 0; i < meshesCount; i++)
		{
			loadFromBinaryFile(file, scene.m_meshes[i]);
		}

		//lights
		file.read(rCast(char*, &scene.m_ambientLight), sizeof(scene.m_ambientLight));

		size_t dirLightsCount;
		file.read(rCast(char*, &dirLightsCount), sizeof(dirLightsCount));

		scene.m_directionalLights.resize(dirLightsCount);

		for (int i = 0; i < dirLightsCount; i++)
		{
			loadFromBinaryFile(file, scene.m_directionalLights[i]);
		}

		size_t pointLightsCount;
		file.read(rCast(char*, &pointLightsCount), sizeof(pointLightsCount));

		scene.m_pointLights.resize(pointLightsCount);

		for (int i = 0; i < pointLightsCount; i++)
		{
			loadFromBinaryFile(file, scene.m_pointLights[i]);
		}
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const SphereObject& sphere)
{
	auto sphereObjectVersion = SphereObjectClassVersion::vCurrent;
	file.write(rCast(const char*, &sphereObjectVersion), sizeof(sphereObjectVersion));

	file.write(rCast(const char*, &sphere.m_transformID), sizeof(sphere.m_transformID));

	const auto& materialName = MaterialManager::getInstance()->getMaterialName(sphere.m_material);

	size_t nameLength = materialName.size();
	file.write(rCast(const char*, &nameLength), sizeof(nameLength));

	file.write(materialName.c_str(), nameLength);
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, SphereObject& sphere)
{
	SphereObjectClassVersion sphereObjectVersion;
	file.read(rCast(char*, &sphereObjectVersion), sizeof(sphereObjectVersion));

	if (sphereObjectVersion == SphereObjectClassVersion::v1_0)
	{
		math::Vec3f position;
		file.read(rCast(char*, &position), sizeof(position));

		float radius;
		file.read(rCast(char*, &radius), sizeof(radius));

		auto* transformManager = TransformManager::getInstance();
		auto transform = transformManager->getNewTransform();
		transform.second.setTranslation(position);
		transform.second.setScale(math::Vec3f(radius, radius, radius));

		sphere.m_transformID = transform.first;

		size_t nameLength;
		file.read(rCast(char*, &nameLength), sizeof(nameLength));

		std::string materialName;
		materialName.resize(nameLength);

		file.read(&materialName[0], nameLength);

		sphere.m_material = MaterialManager::getInstance()->getMaterial(materialName);
	}
	else if (sphereObjectVersion == SphereObjectClassVersion::v1_1)
	{
		file.read(rCast(char*, &sphere.m_transformID), sizeof(sphere.m_transformID));

		size_t nameLength;
		file.read(rCast(char*, &nameLength), sizeof(nameLength));

		std::string materialName;
		materialName.resize(nameLength);

		file.read(&materialName[0], nameLength);

		sphere.m_material = MaterialManager::getInstance()->getMaterial(materialName);
	}
	else
	{
		// error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const MeshObject& mesh)
{
	auto meshObjectVersion = MeshObjectClassVersion::vCurrent;
	file.write(rCast(const char*, &meshObjectVersion), sizeof(meshObjectVersion));

	const auto& meshName = MeshManager::getInstance()->getMeshName(mesh.m_mesh);

	size_t meshNameLength = meshName.size();
	file.write(rCast(const char*, &meshNameLength), sizeof(meshNameLength));

	file.write(meshName.c_str(), meshNameLength);

	const auto& materialName = MaterialManager::getInstance()->getMaterialName(mesh.m_material);

	size_t materialNameLength = materialName.size();
	file.write(rCast(const char*, &materialNameLength), sizeof(materialNameLength));

	file.write(materialName.c_str(), materialNameLength);

	file.write(rCast(const char*, &mesh.m_transformID), sizeof(mesh.m_transformID));
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, MeshObject& mesh)
{
	MeshObjectClassVersion meshObjectVersion;
	file.read(rCast(char*, &meshObjectVersion), sizeof(meshObjectVersion));

	if (meshObjectVersion == MeshObjectClassVersion::v1_0)
	{
		size_t meshNameLength;
		file.read(rCast(char*, &meshNameLength), sizeof(meshNameLength));
		
		std::string meshName;
		meshName.resize(meshNameLength);

		file.read(&meshName[0], meshNameLength);

		mesh.m_mesh = MeshManager::getInstance()->getMesh(meshName);

		size_t materialNameLength;
		file.read(rCast(char*, &materialNameLength), sizeof(materialNameLength));

		std::string materialName;
		materialName.resize(materialNameLength);

		file.read(&materialName[0], materialNameLength);

		mesh.m_material = MaterialManager::getInstance()->getMaterial(materialName);

		math::Transform transform;
		file.read(rCast(char*, &transform), sizeof(math::Transform));

		auto* transformManager = TransformManager::getInstance();
		auto newTransform = transformManager->getNewTransform();
		newTransform.second = transform;

		mesh.m_transformID = newTransform.first;
	}
	else if (meshObjectVersion == MeshObjectClassVersion::v1_1)
	{
		size_t meshNameLength;
		file.read(rCast(char*, &meshNameLength), sizeof(meshNameLength));

		std::string meshName;
		meshName.resize(meshNameLength);

		file.read(&meshName[0], meshNameLength);

		mesh.m_mesh = MeshManager::getInstance()->getMesh(meshName);

		size_t materialNameLength;
		file.read(rCast(char*, &materialNameLength), sizeof(materialNameLength));

		std::string materialName;
		materialName.resize(materialNameLength);

		file.read(&materialName[0], materialNameLength);

		mesh.m_material = MaterialManager::getInstance()->getMaterial(materialName);

		file.read(rCast(char*, &mesh.m_transformID), sizeof(mesh.m_transformID));
	}
	else
	{
		//error ?
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const DirectionalLight& light)
{
	auto lightVersion = DirectionalLightClassVersion::vCurrent;
	file.write(rCast(const char*, &lightVersion), sizeof(lightVersion));

	file.write(rCast(const char*, &light.color), sizeof(light.color));
	file.write(rCast(const char*, &light.direction), sizeof(light.direction));
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, DirectionalLight& light)
{
	DirectionalLightClassVersion lightVersion;
	file.read(rCast(char*, &lightVersion), sizeof(lightVersion));

	if (lightVersion == DirectionalLightClassVersion::v1_0)
	{
		file.read(rCast(char*, &light.color), sizeof(light.color));
		file.read(rCast(char*, &light.direction), sizeof(light.direction));
	}
}

void FileWriter::saveToBinaryFile(std::ofstream& file, const PointLight& light)
{
	auto lightVersion = PointLightClassVersion::vCurrent;
	file.write(rCast(const char*, &lightVersion), sizeof(lightVersion));

	file.write(rCast(const char*, &light.color), sizeof(light.color));
	file.write(rCast(const char*, &light.position), sizeof(light.position));
}

void FileWriter::loadFromBinaryFile(std::ifstream& file, PointLight& light)
{
	PointLightClassVersion lightVersion;
	file.read(rCast(char*, &lightVersion), sizeof(lightVersion));

	if (lightVersion == PointLightClassVersion::v1_0)
	{
		file.read(rCast(char*, &light.color), sizeof(light.color));
		file.read(rCast(char*, &light.position), sizeof(light.position));
	}
}
