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
	virtual void onLeftMouseButtonPressed() = 0;
	virtual void onLeftMouseButtonReleased() = 0;
	virtual void onRightMouseButtonPressed() = 0;
	virtual void onRightMouseButtonReleased() = 0;
};

#endif