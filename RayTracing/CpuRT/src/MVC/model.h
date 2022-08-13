#pragma once
#include "../Scene/scene.h"
#include "../Scene/camera.h"
#include "stb_image/stb_image.h"
#include <array>

namespace MVC
{
	class Model
	{
	public:
		Model(vec2i textureResolution);

		void update();
	private:

		Scene m_scene;
		Camera m_camera;
		std::vector<std::vector<std::array<float, 3>>> m_screenTexture;

		int iterator;
	};
}
