#include "scene.h"
#include <iostream>
#include "Object/sphere.h"

Scene::Scene(const std::string& sceneFilePath)
{
	std::ifstream sceneFile(sceneFilePath, std::ios::in);

	if (sceneFile.is_open())
	{
		initScene(sceneFile);
	}
	else
	{
		std::cout << "Couldn't open file " << sceneFilePath << std::endl;
	}
}

Scene::Scene(std::ifstream& sceneFile)
{
	initScene(sceneFile);
}

std::vector<std::unique_ptr<Object>>& Scene::getSceneObjects()
{
	return m_sceneObjects;
}

void Scene::initScene(std::ifstream& sceneFile)
{
	std::string line;

	do
	{
		std::getline(sceneFile, line);

		if (line.empty())
		{
			continue;
		}

		if (line == "StartSphere")
		{
			readSphere(sceneFile);
		}
	} while (!sceneFile.eof());
}

void Scene::readSphere(std::ifstream& sceneFile)
{
	auto sphere = new Sphere();

	std::string attribute;
	do
	{
		std::getline(sceneFile, attribute);
		size_t equalSignPosition = attribute.find("=");
		if (equalSignPosition == attribute.npos)
		{
			continue;
		}
		std::string name = attribute.substr(0, equalSignPosition);
		std::string value = attribute.substr(equalSignPosition + 1, attribute.size() - (equalSignPosition + 1));

		if (name == "Position")
		{
			size_t leftBracketPos = value.find("(");
			size_t rightBracketPos = value.find(")");

			size_t firstCommaPos = value.find(",");
			size_t secondCommaPos = value.find(",", firstCommaPos + 1);

			std::string xStr = value.substr(leftBracketPos + 1, firstCommaPos - leftBracketPos - 1);
			std::string yStr = value.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
			std::string zStr = value.substr(secondCommaPos + 1, rightBracketPos - secondCommaPos - 1);

			float x = std::stof(xStr);
			float y = std::stof(yStr);
			float z = std::stof(zStr);

			sphere->setPosition(vec3(x, y, z));
		}
		else if (name == "Radius") 
		{
			float radius = std::stof(value);

			sphere->setRadius(radius);
		}

	} while (attribute != "EndSphere");

	m_sceneObjects.emplace_back(sphere);
}
