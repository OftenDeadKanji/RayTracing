#include "scene.h"
#include <iostream>
#include "Object/sphere.h"
#include <limits>
#include "../Intersection/ray.h"
#include "glm/gtx/norm.hpp"
#include "../Utilities/random.h"
#include <optional>
#include <map>
#include "Lighting/pointLight.h"

Scene::Scene(const std::string& sceneFilePath)
	: m_backgroundColor{ 1.0f, 1.0f, 1.0f }
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

IntersectionInfo Scene::findIntersection(const Ray& ray, int depth) const
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
		if (m_sceneObjects[i].get() == ray.getStartingObject())
		{
			continue;
		}

		IntersectionPoint point;
		if (m_sceneObjects[i]->isIntersecting(&ray, point))
		{
			float distance2 = glm::distance2(ray.getOrigin(), point.position);

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
		auto info = IntersectionInfo(intersectedObject, intersectionPoint);

		return info;
	}

	return IntersectionInfo::NoIntersection;
}

vec3 Scene::calculateShadowRaysFinalColor(const IntersectionPoint& point, const Ray& cameraRay)
{
	vec3 color{ 0.0f };
	for (auto& lightSource : m_sceneLightSources)
	{
		vec3 shadowRayDirection = lightSource->createShadowRay(point, cameraRay);
		Ray ray{ point.position, shadowRayDirection };

		auto intercertion = findIntersection(ray);

		if (intercertion.intersectedObject == nullptr)
		{
			color += lightSource->calculateShadowRayColor(point, cameraRay);
		}
	}
	return color;
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
		else if (line == "StartSphere")
		{
			readSphere(sceneFile);
		}
		else if (line == "StartPointLight")
		{
			readPointLight(sceneFile);
		}
	} while (!sceneFile.eof());
}

void Scene::readSphere(std::ifstream& sceneFile)
{
	std::string line;
	std::map<std::string, std::string> attributes;
	do
	{
		std::getline(sceneFile, line);
		size_t equalSignPosition = line.find("=");
		if (equalSignPosition == line.npos)
		{
			continue;
		}
		std::string name = line.substr(0, equalSignPosition);
		std::string value = line.substr(equalSignPosition + 1, line.size() - (equalSignPosition + 1));

		attributes.insert(std::make_pair(name, value));
	} while (line != "EndSphere");

	auto sphere = new Sphere{};

	for (auto& [name, value] : attributes)
	{
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

			sphere->setPosition(vec3{ x, y, z });
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

			float r = std::stof(xStr);
			float g = std::stof(yStr);
			float b = std::stof(zStr);

			sphere->setColor(vec3{ r / 255.0f, g / 255.0f, b / 255.0f });
		}
	}

	m_sceneObjects.emplace_back(sphere);
}

void Scene::readPointLight(std::ifstream& sceneFile)
{
	std::string line;
	std::map<std::string, std::string> attributes;
	do
	{
		std::getline(sceneFile, line);
		size_t equalSignPosition = line.find("=");
		if (equalSignPosition == line.npos)
		{
			continue;
		}
		std::string name = line.substr(0, equalSignPosition);
		std::string value = line.substr(equalSignPosition + 1, line.size() - (equalSignPosition + 1));

		attributes.insert(std::make_pair(name, value));
	} while (line != "EndPointLight");

	auto light = new PointLight{};

	for (auto& [name, value] : attributes)
	{
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

			light->setPosition(vec3{ x, y, z });
		}
		else if (name == "DiffuseIntensity")
		{
			size_t leftBracketPos = value.find("(");
			size_t rightBracketPos = value.find(")");

			size_t firstCommaPos = value.find(",");
			size_t secondCommaPos = value.find(",", firstCommaPos + 1);

			std::string xStr = value.substr(leftBracketPos + 1, firstCommaPos - leftBracketPos - 1);
			std::string yStr = value.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
			std::string zStr = value.substr(secondCommaPos + 1, rightBracketPos - secondCommaPos - 1);

			float r = std::stof(xStr);
			float g = std::stof(yStr);
			float b = std::stof(zStr);

			light->setDiffuseIntensity(vec3{ r / 255.0f, g / 255.0f, b / 255.0f });
		}
		else if (name == "SpecularIntensity")
		{
			size_t leftBracketPos = value.find("(");
			size_t rightBracketPos = value.find(")");

			size_t firstCommaPos = value.find(",");
			size_t secondCommaPos = value.find(",", firstCommaPos + 1);

			std::string xStr = value.substr(leftBracketPos + 1, firstCommaPos - leftBracketPos - 1);
			std::string yStr = value.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
			std::string zStr = value.substr(secondCommaPos + 1, rightBracketPos - secondCommaPos - 1);

			float r = std::stof(xStr);
			float g = std::stof(yStr);
			float b = std::stof(zStr);

			light->setDiffuseIntensity(vec3{ r / 255.0f, g / 255.0f, b / 255.0f });
		}
	}

	m_sceneLightSources.emplace_back(light);
}
