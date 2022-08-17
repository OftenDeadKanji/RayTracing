#pragma once
#include <random>
#include <memory>
#include "types.h"

class Random
{
private:
	Random();

public:
	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;

	static Random* getInstancePtr();

	float value();
	vec2 vector2();
	vec3 vector3();
private:
	static std::unique_ptr<Random> s_instance;

	std::uniform_real_distribution<float> m_distribution;
	std::mt19937 m_generator;
};

