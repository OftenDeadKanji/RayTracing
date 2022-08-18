#include "model.h"
#include "../Shading/shading.h"
#include "../Utilities/random.h"

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene(), sampelsPerPixel(100), maxDepth(50), iteratorX(0), iteratorY(0)
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

			tasks.push(std::make_pair(upperLeft, lowerRight));
		}
	}
	//int threadsCount = 1;
	//int threadsCount = std::thread::hardware_concurrency() - 1;
	//int threadsCount = std::thread::hardware_concurrency();
	int threadsCount = 8;

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
[[depricated("DON'T")]]
void MVC::Model::generateImageOneIteration()
{
	if (iteratorX < m_camera.Resolution.x)
	{
		if (iteratorY < m_camera.Resolution.y)
		{
			Ray ray = m_camera.generateRay(iteratorX, iteratorY);
			IntersectionInfo info = m_scene.intersect(ray);

			vec3 color(0.0f);
			if (info.intersected)
			{
				color = { info.intersectedObject->getColor().r,info.intersectedObject->getColor().g, info.intersectedObject->getColor().b };
			}
			else
			{
				color = { m_scene.getBackgroundColor().r,m_scene.getBackgroundColor().g,m_scene.getBackgroundColor().b };
			}
			setTexturePixelColor(iteratorX, iteratorY, color);

			iteratorY++;
		}
		else
		{
			iteratorY = 0;
			iteratorX++;
		}
	}
}

void MVC::Model::thread_task(int threadId)
{
	while (true)
	{
		taskMutex.lock();
		if (tasks.empty())
		{
			taskMutex.unlock();
			return;
		}

		auto task = tasks.front();
		tasks.pop();
		taskMutex.unlock();

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
			for (int s = 0; s < sampelsPerPixel; ++s)
			{
				if (threadTaskTermination[threadId])
				{
					return;
				}

				vec3 colorToAdd = m_scene.getBackgroundColor();

				float u = i + random->value();
				float v = j + random->value();

				Ray ray = m_camera.generateRay(u, v);
				IntersectionInfo info = m_scene.intersect(ray, maxDepth);

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

void MVC::Model::startThreadedGenerating(vec2 viewportSize)
{
	//float aspectRatio = viewportSize.x / viewportSize.y;
	//vec2 cameraResolution = m_camera.Resolution;

	//float x = (cameraResolution.x / aspectRatio);

	//int upper = (cameraResolution.y - x) / 2.0f;
	//int lower = cameraResolution.y - upper;

	auto threadsCount = threadPool.size();
	//float division = 1.0f / threadsCount;

	//int rangeY = std::ceil( cameraResolution.y * division);

	for (int i = 0; i < threadsCount; ++i)
	{
	//	int startY = i * rangeY;
	//	int endY = (i + 1) * rangeY - 1;

	//	if (endY >= cameraResolution.y)
	//	{
	//		endY = cameraResolution.y - 1;
	//	}

		this->threadPool[i] = std::thread(&MVC::Model::thread_task, this, i);
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
