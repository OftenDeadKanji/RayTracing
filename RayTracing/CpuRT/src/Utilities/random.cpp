#include "random.h"
#include <numbers>

std::unique_ptr<Random> Random::s_instance(new Random());

Random::Random()
    : m_distribution(0.0f, 1.0f)
{
}

Random* Random::getInstancePtr()
{
    return s_instance.get();
}

float Random::value()
{
    return m_distribution(m_generator);
}

vec2 Random::vector2()
{
    float phi = value() * 2.0f * std::numbers::pi;

    float x = std::cosf(phi);
    float y = std::sinf(phi);

    return vec2(x, y);
}

vec3 Random::vector3()
{
    float phi = value() * 2.0f * std::numbers::pi;
    float theta = value() * 2.0f * std::numbers::pi;

    float x = std::sinf(phi) * std::cosf(theta);
    float y = std::sinf(phi) * std::sinf(theta);
    float z = std::cosf(phi);

    return vec3(x, y, z);
}
