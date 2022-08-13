#pragma once
#include "Object/object.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>

class Scene
{
public:
	Scene(const std::string& sceneFilePath = "scene.rt");
	Scene(std::ifstream& sceneFile);

	std::vector<std::unique_ptr<Object>>& getSceneObjects();

	__declspec(property(get=getSceneObjects)) std::vector<std::unique_ptr<Object>> SceneObjects;
private:
	void initScene(std::ifstream& sceneFile);
	void readSphere(std::ifstream& sceneFile);

	std::vector<std::unique_ptr<Object>> m_sceneObjects;
};

