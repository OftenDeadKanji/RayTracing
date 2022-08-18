#include "model.h"
#include "../Shading/shading.h"
#include "../Utilities/random.h"

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene(), m_sampelsPerPixel(100), m_maxDepth(50)
{
	m_screenTexture.resize(static_cast<size_t>(textureResolution.x * textureResolution.y * 3));
	const vec2i taskSize = vec2i(128, 128);

	int xTaskCount = std::ceil(static_cast<float>(textureResolution.x) / taskSize.x);
	int yTaskCount = std::ceil(static_cast<float>(textureResolution.y) / taskSize.y);

	for (int i = 0; i < xTaskCount; ++i)
	{
		for (int j = 0; j < yTaskCount; ++j)
		{
			vec2i upperLeft = vec2i(i * taskSize.x, j * taskSize.y);
			vec2i lowerRight = vec2i((i + 1) * taskSize.x, (j + 1) * taskSize.y);

			lowerRight.x = std::min(lowerRight.x, textureResolution.x - 1);
			lowerRight.y = std::min(lowerRight.y, textureResolution.y - 1);

			m_tasks.push(std::make_pair(upperLeft, lowerRight));
		}
	}
	//int threadsCount = 1;
	//int threadsCount = std::thread::hardware_concurrency() - 1;
	//int threadsCount = std::thread::hardware_concurrency();
	int threadsCount = 8;

	for (int i = 0; i < threadsCount; i++)
	{
		m_threadPool.push_back(std::thread());
		m_threadTaskTermination.push_back(false);
	}
}

MVC::Model::~Model()
{
	for (int i = 0; i < m_threadPool.size(); ++i)
	{
		m_threadTaskTermination[i] = true;
	}

	for (int i = 0; i < m_threadPool.size(); ++i)
	{
		if (m_threadPool[i].joinable())
		{
			m_threadPool[i].join();
		}
	}
}

void MVC::Model::update()
{
}

void MVC::Model::thread_task(int threadId)
{
	while (true)
	{
		m_taskMutex.lock();
		if (m_tasks.empty())
		{
			m_taskMutex.unlock();
			return;
		}

		auto task = m_tasks.front();
		m_tasks.pop();
		m_taskMutex.unlock();

		generateImagePart(threadId, task.first.x, task.second.x, task.first.y, task.second.y);
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
			for (int s = 0; s < m_sampelsPerPixel; ++s)
			{
				if (m_threadTaskTermination[threadId])
				{
					return;
				}

				vec3 colorToAdd = m_scene.getBackgroundColor();

				float u = i + random->value();
				float v = j + random->value();

				Ray ray = m_camera.generateRay(u, v);
				IntersectionInfo info = m_scene.intersect(ray, m_maxDepth);

				if (info.intersected)
				{
					if (info.intersectionPoint.side == IntersectionPoint::FaceSide::front)
					{
						vec3 objectColor = info.color * info.intersectedObject->getColor();
						vec3 position = info.intersectionPoint.position;
						vec3 normal = glm::normalize(info.intersectionPoint.normal);
						vec3 lightDirection = glm::normalize(vec3(0.5f, -0.5f, -0.5f));
						vec3 viewDirection = glm::normalize(vec3(ray.Direction));

						//colorToAdd = Shading::getColor_Phong(objectColor, position, normal, lightDirection, viewDirection);
						colorToAdd = objectColor;
					}
				}
				color += colorToAdd;
			}

			color /= m_sampelsPerPixel;
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

void MVC::Model::startThreadedGenerating(vec2 viewportSize)
{
	auto threadsCount = m_threadPool.size();

	for (int i = 0; i < threadsCount; ++i)
	{
		this->m_threadPool[i] = std::thread(&MVC::Model::thread_task, this, i);
	}
}

void MVC::Model::setTexturePixelColor(int x, int y, vec3 color)
{
	int flippedY = m_camera.Resolution.y - y - 1;

	size_t coord = static_cast<size_t>(flippedY * m_camera.Resolution.x + x);

	m_screenTexture[coord * 3] = color.r;
	m_screenTexture[coord * 3 + 1] = color.g;
	m_screenTexture[coord * 3 + 2] = color.b;
}
