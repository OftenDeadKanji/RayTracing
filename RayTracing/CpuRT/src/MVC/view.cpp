#include "view.h"

#include "controller.h"

namespace MVC
{
	View::View(Controller& controller, const WindowProperties& windowProperties)
		: controller(&controller), window(windowProperties)
	{
		window.attachEventManager(eventManager);
	}

	void View::checkInput()
	{
		eventManager.checkForEvents();

		while(!eventManager.isEventQueueEmpty())
		{
			switch (eventManager.getEventTypeFromQueue())
			{
			default:
				break;
			case EventType::WindowResized:
				break;
			case EventType::WindowClosed:
				if (m_windowCloseCallback != nullptr)
				{
					m_windowCloseCallback();
				}
				break;
			case EventType::KeyboardKeyPressed:
				break;
			case EventType::KeyboardKeyReleased:
				break;
			case EventType::MouseButtonPressed:
				break;
			case EventType::MouseButtonReleased:
				break;
			case EventType::MouseCursorMoved:
				break;
			}
		}
	}

	void View::render(float deltaTime)
	{
		window.fillWithColorRGB({ 0, 100, 0 });

		window.swapBuffers();
	}

	void View::setWindowCloseCallback(std::function<void()> callback)
	{
		m_windowCloseCallback = std::move(callback);
	}
}
