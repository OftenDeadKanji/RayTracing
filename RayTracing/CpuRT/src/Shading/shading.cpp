#include "shading.h"

vec3 Shading::getColor_Phong(vec3 albedo, vec3 position, vec3 normal, vec3 lightDirecction, vec3 viewDirection)
{
    float ambient = 0.1f;
    float diffuse = 0.8f * glm::max(glm::dot(-lightDirecction, normal), 0.0f);
    float specular = 1.0f * std::powf(glm::max(glm::dot(-lightDirecction, -viewDirection), 0.0f), 64);

    return (ambient + diffuse + specular) * albedo;
}
