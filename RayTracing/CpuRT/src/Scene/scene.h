#pragma once
#include "Object/object.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "../Intersection/intersectionInfo.h"

class Scene
{
public:
	Scene(const std::string& sceneFilePath = "scene.rt");
	Scene(std::ifstream& sceneFile);

	IntersectionInfo findIntersection(const Ray& ray, int depth = 1) const;

	vec3 getBackgroundColor() const;
private:
	void initScene(std::ifstream& sceneFile);
	void readSphere(std::ifstream& sceneFile);

	std::vector<std::unique_ptr<Object>> m_sceneObjects;

	vec3 m_backgroundColor;
};

