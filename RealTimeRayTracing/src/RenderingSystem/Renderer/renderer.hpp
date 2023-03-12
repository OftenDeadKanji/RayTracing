#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__
#include "../../Utils/nonCopyable.hpp"
#include "../../RenderingSystem/Scene/scene.hpp"
#include <memory>
#include "glad/glad.h"

class Window;
class Camera;

class Renderer
	: public NonCopyable
{
private:
	Renderer();
public:
	~Renderer();

	static Renderer* createInstance()
	{
		s_instance = std::unique_ptr<Renderer>(new Renderer());
		return s_instance.get();
	}
	static void deleteInstance()
	{
		s_instance.release();
	}

	static Renderer* getInstance()
	{
		return s_instance.get();
	}

	void initScreenTexture(const math::Vec2i& size);

	void render(const Window& window, const Camera& camera);
private:
	static std::unique_ptr<Renderer> s_instance;

	math::Vec2i m_textureSize;
	std::vector<math::Vec3f> m_texels;
	GLuint m_screenTexture{};
	GLuint m_vao;

	GLuint m_shader{};
};

#pragma region Inline methods definitions
inline Renderer* Renderer::createInstance()
{
	s_instance = std::unique_ptr<Renderer>(new Renderer());
	return s_instance.get();
}
inline void Renderer::deleteInstance()
{
	s_instance.release();
}

inline Renderer* Renderer::getInstance()
{
	return s_instance.get();
}
#pragma endregion

#endif
