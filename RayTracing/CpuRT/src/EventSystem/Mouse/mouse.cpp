#include "mouse.h"

std::array<bool, static_cast<size_t>(MouseButton::Count)> Mouse::buttons;
vec2 Mouse::position;
