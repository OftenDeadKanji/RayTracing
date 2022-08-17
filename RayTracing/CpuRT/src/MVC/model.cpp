#include "model.h"
#include "../Shading/shading.h"
#include "../Utilities/random.h"

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene(), sampelsPerPixel(4), iteratorX(0), iteratorY(0)
{
	m_screenTexture.resize(static_cast<size_t>(textureResolution.x * textureResolution.y * 3));

	int threadsCount = std::thread::hardware_concurrency() - 1;

	for (int i = 0; i < threadsCount; i++)
	{
		threadPool.push_back(std::thread());
		threadTaskTermination.push_back(false);
	}
}

MVC::Model::~Model()
{
	for (int i = 0; i < threadPool.size(); ++i)
	{
		threadTaskTermination[i] = true;
	}

	for (int i = 0; i < threadPool.size(); ++i)
	{
		if (threadPool[i].joinable())
		{
			threadPool[i].join();
		}
	}
}

void MVC::Model::update()
{
	//generateImageOneIteration();
}
[[depricated]]
void MVC::Model::generateImageOneIteration()
{
	if (iteratorX < m_camera.Resolution.x)
	{
		if (iteratorY < m_camera.Resolution.y)
		{
			Ray ray = generateRay(iteratorX, iteratorY);
			IntersectionInfo info = m_scene.intersect(ray);

			if (info.intersected)
			{
				vec3 color = { info.intersectedObject->getColor().r,info.intersectedObject->getColor().g, info.intersectedObject->getColor().b };
				setTexturePixelColor(iteratorX, iteratorY, color);
			}
			else
			{
				vec3 color = { m_scene.getBackgroundColor().r,m_scene.getBackgroundColor().g,m_scene.getBackgroundColor().b };
				setTexturePixelColor(iteratorX, iteratorY, color);
			}

			iteratorY++;
		}
		else
		{
			iteratorY = 0;
			iteratorX++;
		}
	}
}

void MVC::Model::generateImagePart(int threadId, int fromX, int toX, int fromY, int toY)
{
	Random* random = Random::getInstancePtr();
	for (int i = fromX; i <= toX; ++i)
	{
		for (int j = fromY; j <= toY; ++j)
		{
			vec3 color(0.0f);
			for (int s = 0; s < sampelsPerPixel; ++s)
			{
				if (threadTaskTermination[threadId])
				{
					return;
				}

				vec3 colorToAdd = m_scene.getBackgroundColor();
				
				float u = i + random->value();
				float v = j + random->value();
				
				Ray ray = generateRay(u, v);
				IntersectionInfo info = m_scene.intersect(ray);

				if (info.intersected)
				{
					size_t closestPointIndex = 0;
					for (auto n = 1; n < info.intersectionPoints.size(); ++n)
					{
						if (info.intersectionPoints[closestPointIndex].side == IntersectionPoint::FaceSide::front)
						{
							//found first front-sided point

							for (auto m = n + 1; n < info.intersectionPoints.size(); ++n)
							{
								if (info.intersectionPoints[closestPointIndex].side == IntersectionPoint::FaceSide::front)
								{
									float closestDist = glm::distance(ray.Origin, info.intersectionPoints[closestPointIndex].position);
									float newDist = glm::distance(ray.Origin, info.intersectionPoints[n].position);

									if (closestDist > newDist)
									{
										closestPointIndex = n;
									}
								}
							}

							IntersectionPoint closestPoint = info.intersectionPoints[closestPointIndex];

							vec3 objectColor = info.intersectedObject->getColor();
							vec3 position = info.intersectionPoints[closestPointIndex].position;
							vec3 normal = glm::normalize(info.intersectionPoints[closestPointIndex].normal);
							vec3 lightDirection = glm::normalize(vec3(-0.5f, -0.5f, -0.5f));
							vec3 viewDirection = glm::normalize(vec3(ray.Direction));

							colorToAdd = Shading::getColor_Phong(objectColor, position, normal, lightDirection, viewDirection);
							break;
						}
					}
				}
				color += colorToAdd;
			}

			color /= sampelsPerPixel;
			setTexturePixelColor(i, j, color);
		}
	}
}

const std::vector<float>& MVC::Model::getScreenTexture() const
{
	return m_screenTexture;
}

vec2i MVC::Model::getTextureResolution() const
{
	return m_camera.Resolution;
}

void MVC::Model::startThreadedGenerating()
{
	auto threadsCount = threadPool.size();
	
	float division = 1.0f / threadsCount;
	//int rangeX = std::ceil(m_camera.Resolution.x * division);
	int rangeY = std::ceil(m_camera.Resolution.y * division);

	for (int i = 0; i < threadsCount; ++i)
	{
		int startY = i * rangeY;
		int endY = (i + 1) * rangeY - 1;

		if (endY >= m_camera.Resolution.y)
		{
			endY = m_camera.Resolution.y - 1;
		}

		this->threadPool[i] = std::thread(&MVC::Model::generateImagePart, this, i, 0, m_camera.Resolution.x - 1, startY, endY);
	}
}

Ray MVC::Model::generateRay(float x, float y)
{
	int width = m_camera.Resolution.x;
	int height = m_camera.Resolution.y;
	float aspectRatio = static_cast<float>(width) / height;

	auto viewportHeight = 1.0f;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0f;

	vec3 rayOrigin = vec3(0.0f);
	vec3 horizontal = vec3(viewportWidth, 0.0f, 0.0f);
	vec3 vertical = vec3(0.0f, viewportHeight, 0.0f);

	auto lowerLeftCorner = rayOrigin - horizontal / 2.0f - vertical / 2.0f - vec3(0.0f, 0.0f, focalLength);

	auto u = static_cast<float>(x) / (width - 1);
	auto v = 1.0f - static_cast<float>(y) / (height - 1);

	vec3 rayDirection = glm::normalize(vec3(lowerLeftCorner + u * horizontal + v * vertical - rayOrigin));

	return Ray(rayOrigin, rayDirection);
}

void MVC::Model::setTexturePixelColor(int x, int y, vec3 color)
{
	int flippedY = m_camera.Resolution.y - y - 1;

	size_t coord = static_cast<size_t>(flippedY * m_camera.Resolution.x + x);

	m_screenTexture[coord * 3] = color.r;
	m_screenTexture[coord * 3 + 1] = color.g;
	m_screenTexture[coord * 3 + 2] = color.b;
}
