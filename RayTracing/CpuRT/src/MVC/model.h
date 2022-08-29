#pragma once
#include "../Scene/scene.h"
#include "../Scene/camera.h"
#include <queue>
#include <utility>
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

		void startThreadedGenerating();
		void thread_task(int threadId);
		void generateImagePart(int threadId, int yStart, int yEnd);

		const std::vector<float>& getScreenTexture() const;

		vec2i getTextureResolution() const;

	private:
		void setTexturePixelColor(vec2i position, vec3 color);

		Scene m_scene;
		Camera m_camera;
		std::vector<float> m_screenTexture;

		int m_samplesPerPixel;
		int m_maxDepth;

		std::queue<std::pair<int, int>> m_tasks;
		std::mutex m_taskMutex;
		std::vector<std::thread> m_threadPool;
		std::vector<bool> m_threadTaskTermination;
	};
}
