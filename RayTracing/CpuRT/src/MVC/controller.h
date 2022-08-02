#pragma once
#include "view.h"
#include "model.h"

namespace MVC
{
	class Controller
	{
	public:
		Controller();

		void initView();
#pragma region Properties
		bool __declspec(property(get = getMainLoopCondition)) MainLoopCondition;
		bool getMainLoopCondition() const;
#pragma endregion

		void processInput(float deltaTime);
		void update(float deltaTime);
		void render(float deltaTime);

	private:
		void closeWindowCallback();

		Model m_model;
		View m_view;

		bool m_mainLoopCondition = true;
	};

}
