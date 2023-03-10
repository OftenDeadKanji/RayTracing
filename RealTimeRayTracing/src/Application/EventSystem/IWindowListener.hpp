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
};

#endif