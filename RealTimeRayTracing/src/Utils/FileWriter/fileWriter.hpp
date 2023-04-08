#ifndef __FILE_WRITER_HPP__
#define __FILE_WRITER_HPP__
#include <fstream>
#include <memory>

class MaterialManager;
struct Material;

class TransformManager;

class MeshManager;
class Mesh;
struct Triangle;

class Scene;
class SphereObject;
class MeshObject;

struct DirectionalLight;
struct PointLight;

class FileWriter
{
public:
	void saveToBinaryFile(std::ofstream& file, const MaterialManager& materialManager);
	void loadFromBinaryFile(std::ifstream& file, MaterialManager& materialManager);

	void saveToBinaryFile(std::ofstream& file, std::shared_ptr<const Material> material);
	void loadFromBinaryFile(std::ifstream& file, std::shared_ptr<Material> material);

	void saveToBinaryFile(std::ofstream& file, const TransformManager& transformManager);
	void loadFromBinaryFile(std::ifstream& file, TransformManager& transformManager);

	void saveToBinaryFile(std::ofstream& file, const MeshManager& meshManager);
	void loadFromBinaryFile(std::ifstream& file, MeshManager& meshManager);

	void saveToBinaryFile(std::ofstream& file, std::shared_ptr<const Mesh> mesh);
	void loadFromBinaryFile(std::ifstream& file, std::shared_ptr<Mesh> mesh);

	void saveToBinaryFile(std::ofstream& file, const Scene& scene);
	void loadFromBinaryFile(std::ifstream& file, Scene& scene);

	void saveToBinaryFile(std::ofstream& file, const SphereObject& sphere);
	void loadFromBinaryFile(std::ifstream& file, SphereObject& sphere);

	void saveToBinaryFile(std::ofstream& file, const MeshObject& mesh);
	void loadFromBinaryFile(std::ifstream& file, MeshObject& mesh);

	void saveToBinaryFile(std::ofstream& file, const DirectionalLight& light);
	void loadFromBinaryFile(std::ifstream& file, DirectionalLight& light);

	void saveToBinaryFile(std::ofstream& file, const PointLight& light);
	void loadFromBinaryFile(std::ifstream& file, PointLight& light);


private:
	enum class MaterialManagerClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class MaterialClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class TransformManagerClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class MeshManagerClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class MeshClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class SceneClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class SphereObjectClassVersion
	{
		v1_0,
		v1_1,

		vCurrent = v1_1
	};

	enum class MeshObjectClassVersion
	{
		v1_0,
		v1_1,

		vCurrent = v1_1
	};

	enum class DirectionalLightClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};

	enum class PointLightClassVersion
	{
		v1_0,

		vCurrent = v1_0
	};
};

#endif
