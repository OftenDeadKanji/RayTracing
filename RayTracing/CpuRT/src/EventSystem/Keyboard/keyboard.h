#pragma once
#include <array>
#include "keyboardKey.h"

	struct Keyboard
	{
		static std::array<bool, static_cast<size_t>(KeyboardKey::Count)> keys;
	};

