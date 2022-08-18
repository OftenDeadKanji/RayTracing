#include "scene.h"
#include <iostream>
#include "Object/sphere.h"
#include <limits>
#include "../Intersection/ray.h"
#include "glm/gtx/norm.hpp"
#include "../Utilities/random.h"

Scene::Scene(const std::string& sceneFilePath)
	: m_backgroundColor(1.0f, 1.0f, 1.0f)
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
	: m_backgroundColor(1.0f, 1.0f, 1.0f)
{
	initScene(sceneFile);
}

std::vector<std::unique_ptr<Object>>& Scene::getSceneObjects()
{
	return m_sceneObjects;
}

IntersectionInfo Scene::intersect(const Ray& ray, int depth) const
{
	if (depth <= 0)
	{
		return IntersectionInfo::NoIntersection;
	}

	const size_t noIntersection = -1;

	size_t closestObjectIndex = noIntersection;
	IntersectionPoint intersectionPoint;

	float closestPointDistance2 = std::numeric_limits<float>::max();

	for (size_t i = 0; i < m_sceneObjects.size(); ++i)
	{
		if (m_sceneObjects[i].get() == ray.StartingObject)
		{
			continue;
		}
		IntersectionPoint point;
		if (m_sceneObjects[i]->isIntersecting(&ray, point))
		{
			float distance2 = glm::distance2(ray.Origin, point.position);

			if (distance2 < closestPointDistance2)
			{
				closestPointDistance2 = distance2;
				closestObjectIndex = i;
				intersectionPoint = point;
			}

		}
	}

	if (closestObjectIndex != noIntersection)
	{
		Object* intersectedObject = m_sceneObjects[closestObjectIndex].get();
		auto info =  IntersectionInfo(true, intersectionPoint, intersectedObject->getColor(), intersectedObject);

		auto random = Random::getInstancePtr();

		vec3 direction = intersectionPoint.position + intersectionPoint.normal + glm::normalize(random->vector3());
		Ray newRay = Ray(intersectionPoint.position, glm::normalize(direction - intersectionPoint.position), intersectedObject);
		
		IntersectionInfo info2 = intersect(newRay, depth - 1);
		info.color = 0.5f * info2.color;

		return info;
	}

	auto no = IntersectionInfo::NoIntersection;
	no.color = m_backgroundColor;
	return no;
}

vec3 Scene::getBackgroundColor() const
{
	return m_backgroundColor;
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
		else if (name == "Color")
		{
			size_t leftBracketPos = value.find("(");
			size_t rightBracketPos = value.find(")");

			size_t firstCommaPos = value.find(",");
			size_t secondCommaPos = value.find(",", firstCommaPos + 1);

			std::string xStr = value.substr(leftBracketPos + 1, firstCommaPos - leftBracketPos - 1);
			std::string yStr = value.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
			std::string zStr = value.substr(secondCommaPos + 1, rightBracketPos - secondCommaPos - 1);

			int r = std::stoi(xStr);
			int g = std::stoi(yStr);
			int b = std::stoi(zStr);

			sphere->setColor(vec3(r / 255.0f, g / 255.0f, b / 255.0f));
		}

	} while (attribute != "EndSphere");

	m_sceneObjects.emplace_back(sphere);
}
