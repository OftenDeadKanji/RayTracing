#pragma once
#include "../Scene/scene.h"
#include "../Scene/camera.h"
#include "stb_image/stb_image.h"
#include <queue>
#include <utility>
#include "../Intersection/ray.h"
#include <thread>
#include <mutex>

namespace MVC
{
	class Model
	{
	public:
		Model(vec2i textureResolution);
		~Model();
		void update();

		void thread_task(int threadId);
		void generateImagePart(int threadId, int fromX, int toX, int fromY, int toY);

		const std::vector<float>& getScreenTexture() const;
		__declspec(property(get = getScreenTexture)) std::vector<float> ScreenTexture;

		vec2i getTextureResolution() const;

		void startThreadedGenerating(vec2 viewportSize);
	private:
		void setTexturePixelColor(int x, int y, vec3 color);

		Scene m_scene;
		Camera m_camera;
		std::vector<float> m_screenTexture;

		int m_sampelsPerPixel;
		int m_maxDepth;

		std::queue<std::pair<vec2i, vec2i>> m_tasks;
		std::mutex m_taskMutex;
		std::vector<std::thread> m_threadPool;
		std::vector<bool> m_threadTaskTermination;
	};
}
