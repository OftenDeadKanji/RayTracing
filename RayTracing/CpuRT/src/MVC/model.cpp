#include "model.h"
#include "../Utilities/random.h"
#include <cassert>

MVC::Model::Model(vec2i textureResolution)
	: m_camera{ textureResolution, glm::radians(45.0f) }, m_scene{}, m_sampelsPerPixel{ 100 }, m_maxDepth{ 50 }
{
	assert(textureResolution.x >= textureResolution.y);

	m_screenTexture.resize(static_cast<size_t>(textureResolution.x * textureResolution.y * 3));

	const int taskSize = 90;

	int yTaskCount = std::ceil(static_cast<float>(textureResolution.y) / taskSize);

	for (int j = 0; j < yTaskCount; ++j)
	{
		int upper = j * taskSize;
		int lower = (j + 1) * taskSize;

		lower = std::min(lower, textureResolution.y - 1);

		m_tasks.push(std::make_pair(upper, lower));
	}

	//int threadsCount = 1;
	int threadsCount = std::thread::hardware_concurrency() - 1;
	//int threadsCount = std::thread::hardware_concurrency();
	//int threadsCount = 8;

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

		generateImagePart(threadId, task.first, task.second);
	}
}

void MVC::Model::generateImagePart(int threadId, int yStart, int yEnd)
{
	Random* random = Random::getInstancePtr();

	for (int j = yStart; j <= yEnd; ++j)
	{
		for (int i = 0; i < m_camera.getResolution().x; ++i)
		{
			vec3 color{ 0.0f };
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
				IntersectionInfo info = m_scene.findIntersection(ray, m_maxDepth);

				if (info.intersectedObject != nullptr)
				{
					if (info.intersectionPoint->side == IntersectionPoint::FaceSide::Front)
					{
						colorToAdd = info.intersectedObject->getColor();
					}
				}
				color += colorToAdd;
			}

			color /= m_sampelsPerPixel;
			setTexturePixelColor(vec2i{ i, j }, color);
		}
	}
}

const std::vector<float>& MVC::Model::getScreenTexture() const
{
	return m_screenTexture;
}

const vec2i& MVC::Model::getTextureResolution() const
{
	return m_camera.getResolution();
}

void MVC::Model::startThreadedGenerating()
{
	auto threadsCount = m_threadPool.size();

	for (int i = 0; i < threadsCount; ++i)
	{
		this->m_threadPool[i] = std::thread(&MVC::Model::thread_task, this, i);
	}
}

void MVC::Model::setTexturePixelColor(vec2i position, vec3 color)
{
	int flippedY = m_camera.getResolution().y - position.y - 1;

	size_t coord = static_cast<size_t>(flippedY * m_camera.getResolution().x + position.x);

	m_screenTexture[coord * 3 + 0] = color.r;
	m_screenTexture[coord * 3 + 1] = color.g;
	m_screenTexture[coord * 3 + 2] = color.b;
}
