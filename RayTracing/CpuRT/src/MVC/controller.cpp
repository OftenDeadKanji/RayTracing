#include "controller.h"

namespace MVC
{
	Controller::Controller()
		: m_view(*this, WindowProperties(1600, 900, "CPU RayTracing")), m_model(vec2( 1600, 900 ))
	{
		initView();
		m_model.startThreadedGenerating(vec2(1600, 900));
	}

	void Controller::initView()
	{
		m_view.setWindowCloseCallback([this]()
		{
			closeWindowCallback();
		});

		auto& textureVector = m_model.ScreenTexture;
		auto textureSize = m_model.getTextureResolution();

		m_view.generateTexture(textureVector, textureSize.x, textureSize.y);
	}

	bool Controller::getMainLoopCondition() const
	{
		return m_mainLoopCondition;
	}

	void Controller::processInput(float deltaTime)
	{
		m_view.checkInput();
	}

	void Controller::update(float deltaTime)
	{
		m_model.update();
	}

	void Controller::render(float deltaTime)
	{
		const auto& textureVector = m_model.getScreenTexture();
		auto textureSize = m_model.getTextureResolution();

		m_view.render(deltaTime, textureVector, textureSize.x, textureSize.y);
	}

	void Controller::closeWindowCallback()
	{
		m_mainLoopCondition = false;
	}
}
