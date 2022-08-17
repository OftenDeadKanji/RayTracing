#pragma once
#include "../Scene/scene.h"
#include "../Scene/camera.h"
#include "stb_image/stb_image.h"
#include <array>
#include "../Intersection/ray.h"
#include <thread>

namespace MVC
{
	class Model
	{
	public:
		Model(vec2i textureResolution);
		~Model();
		void update();

		void generateImageOneIteration();
		void generateImagePart(int threadId, int fromX, int toX, int fromY, int toY);

		const std::vector<float>& getScreenTexture() const;
		__declspec(property(get = getScreenTexture)) std::vector<float> ScreenTexture;

		vec2i getTextureResolution() const;

		void startThreadedGenerating();
	private:
		Ray generateRay(int x, int y);
		void setTexturePixelColor(int x, int y, vec3 color);

		Scene m_scene;
		Camera m_camera;
		std::vector<float> m_screenTexture;

		int iteratorX, iteratorY;

		std::vector<std::thread> threadPool;
	};
}
