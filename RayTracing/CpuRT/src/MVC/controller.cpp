#include "controller.h"

namespace MVC
{
	Controller::Controller()
		: m_view(*this, WindowProperties(1600, 900, "CPU RayTracing"))
	{
		initView();
	}

	void Controller::initView()
	{
		m_view.setWindowCloseCallback([this]()
		{
			closeWindowCallback();
		});
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
	{}

	void Controller::render(float deltaTime)
	{
		m_view.render(deltaTime);
	}

	void Controller::closeWindowCallback()
	{
		m_mainLoopCondition = false;
	}
}
