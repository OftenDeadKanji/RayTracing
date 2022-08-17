#include "model.h"

MVC::Model::Model(vec2i textureResolution)
	: m_camera(textureResolution, glm::radians(45.0f)), m_scene(), iteratorX(0), iteratorY(0)
{
	m_screenTexture.resize(static_cast<size_t>(textureResolution.x * textureResolution.y * 3));

	int threadsCount = std::thread::hardware_concurrency();

	for (int i = 0; i < threadsCount; i++)
	{
		threadPool.push_back(std::thread());
	}
}

MVC::Model::~Model()
{
	for (auto& thread : threadPool)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void MVC::Model::update()
{
	//generateImageOneIteration();
}

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
	for (int i = fromX; i <= toX; ++i)
	{
		for(int j = fromY; j <= toY; ++j)
		{
			Ray ray = generateRay(i, j);
			IntersectionInfo info = m_scene.intersect(ray);

			if (info.intersected)
			{
				vec3 color = { info.intersectedObject->getColor().r,info.intersectedObject->getColor().g, info.intersectedObject->getColor().b };
				setTexturePixelColor(i, j, color);
			}
			else
			{
				vec3 color = { m_scene.getBackgroundColor().r,m_scene.getBackgroundColor().g,m_scene.getBackgroundColor().b };
				setTexturePixelColor(i, j, color);
			}
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
	this->threadPool[0] = std::thread(&MVC::Model::generateImagePart, this, 0, 0, m_camera.Resolution.x - 1, 0, m_camera.Resolution.y - 1);
}

Ray MVC::Model::generateRay(int x, int y)
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
	auto v = static_cast<float>(y) / (height - 1);

	vec3 rayDirection = vec3(lowerLeftCorner + u * horizontal + v * vertical - rayOrigin);

	return Ray(rayOrigin, rayDirection);
}

void MVC::Model::setTexturePixelColor(int x, int y, vec3 color)
{
	int flippedX = m_camera.Resolution.x - x - 1;
	
	size_t coord = static_cast<size_t>(flippedX * m_camera.Resolution.y + y);

	m_screenTexture[coord * 3] = color.r;
	m_screenTexture[coord * 3 + 1] = color.g;
	m_screenTexture[coord * 3 + 2] = color.b;
}
