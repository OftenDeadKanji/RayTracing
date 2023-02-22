#pragma once

namespace RT
{
	class Application
	{
	public:
		Application() = default;

		void run();
	private:
		bool m_mainLoopCondition = true;

		void processInput();
	};
}