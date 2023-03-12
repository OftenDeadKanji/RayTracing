#ifndef __I_WINDOW_LISTENER_HPP__
#define __I_WINDOW_LISTENER_HPP__
#include "../../Math/mathUtils.hpp"

class IWindowListener
{
public:
	virtual void onWindowClose() = 0;
	virtual void onWindowResize(const math::Vec2i& newSize) = 0;
	virtual void onKeyPressed(int key) = 0;
	virtual void onKeyReleased(int key) = 0;
	virtual void onMouseMove(const math::Vec2i& newPos) = 0;
	virtual void onLeftMouseButtonPressed(const math::Vec2i& position) = 0;
	virtual void onLeftMouseButtonReleased(const math::Vec2i& position) = 0;
	virtual void onRightMouseButtonPressed(const math::Vec2i& position) = 0;
	virtual void onRightMouseButtonReleased(const math::Vec2i& position) = 0;
};

#endif
