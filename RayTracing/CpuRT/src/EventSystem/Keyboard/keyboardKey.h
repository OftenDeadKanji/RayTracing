#pragma once
#include "GLFW/glfw3.h"

enum class KeyboardKey
{
	KeyNone = -1,

	KeyA,
	KeyB,
	KeyC,
	KeyD,
	KeyE,
	KeyF,
	KeyG,
	KeyH,
	KeyI,
	KeyJ,
	KeyK,
	KeyL,
	KeyM,
	KeyN,
	KeyO,
	KeyQ,
	KeyP,
	KeyR,
	KeyS,
	KeyT,
	KeyU,
	KeyW,
	KeyV,
	KeyX,
	KeyY,
	KeyZ,

	Key1,
	Key2,
	Key3,
	Key4,
	Key5,
	Key6,
	Key7,
	Key8,
	Key9,
	Key0,

	KeyF1,
	KeyF2,
	KeyF3,
	KeyF4,
	KeyF5,
	KeyF6,
	KeyF7,
	KeyF8,
	KeyF9,
	KeyF10,
	KeyF11,
	KeyF12,

	KeyArrowUp,
	KeyArrowLeft,
	KeyArrowRight,
	KeyArrowDown,

	KeySpace,

	KeyComma,
	KeyDot,
	KeySlash,
	KeySemicolon,
	KeyApostrophe,
	KeyBackslash,
	LeftBracket,
	RightBracket,
	KeyGraveAccent,
	KeyMinus,
	KeyEqual,
	KeyBackspace,
	KeyEscape,

	Count
};

inline KeyboardKey convertToKeyboardKey(int glfwKey)
{
	switch (glfwKey)
	{
	default:
		return KeyboardKey::KeyNone;
	case GLFW_KEY_A:
		return KeyboardKey::KeyA;
	case GLFW_KEY_B:
		return KeyboardKey::KeyB;
	case GLFW_KEY_C:
		return KeyboardKey::KeyC;
	case GLFW_KEY_D:
		return KeyboardKey::KeyD;
	case GLFW_KEY_E:
		return KeyboardKey::KeyE;
	case GLFW_KEY_F:
		return KeyboardKey::KeyF;
	case GLFW_KEY_G:
		return KeyboardKey::KeyG;
	case GLFW_KEY_H:
		return KeyboardKey::KeyH;
	case GLFW_KEY_I:
		return KeyboardKey::KeyI;
	case GLFW_KEY_J:
		return KeyboardKey::KeyJ;
	case GLFW_KEY_K:
		return KeyboardKey::KeyK;
	case GLFW_KEY_L:
		return KeyboardKey::KeyL;
	case GLFW_KEY_M:
		return KeyboardKey::KeyM;
	case GLFW_KEY_N:
		return KeyboardKey::KeyN;
	case GLFW_KEY_O:
		return KeyboardKey::KeyO;
	case GLFW_KEY_Q:
		return KeyboardKey::KeyQ;
	case GLFW_KEY_P:
		return KeyboardKey::KeyP;
	case GLFW_KEY_R:
		return KeyboardKey::KeyR;
	case GLFW_KEY_S:
		return KeyboardKey::KeyS;
	case GLFW_KEY_T:
		return KeyboardKey::KeyT;
	case GLFW_KEY_U:
		return KeyboardKey::KeyU;
	case GLFW_KEY_W:
		return KeyboardKey::KeyW;
	case GLFW_KEY_V:
		return KeyboardKey::KeyV;
	case GLFW_KEY_X:
		return KeyboardKey::KeyX;
	case GLFW_KEY_Y:
		return KeyboardKey::KeyY;
	case GLFW_KEY_Z:
		return KeyboardKey::KeyZ;
	case GLFW_KEY_1:
		return KeyboardKey::Key1;
	case GLFW_KEY_2:
		return KeyboardKey::Key2;
	case GLFW_KEY_3:
		return KeyboardKey::Key3;
	case GLFW_KEY_4:
		return KeyboardKey::Key4;
	case GLFW_KEY_5:
		return KeyboardKey::Key5;
	case GLFW_KEY_6:
		return KeyboardKey::Key6;
	case GLFW_KEY_7:
		return KeyboardKey::Key7;
	case GLFW_KEY_8:
		return KeyboardKey::Key8;
	case GLFW_KEY_9:
		return KeyboardKey::Key9;
	case GLFW_KEY_0:
		return KeyboardKey::Key0;
	case GLFW_KEY_F1:
		return KeyboardKey::KeyF1;
	case GLFW_KEY_F2:
		return KeyboardKey::KeyF2;
	case GLFW_KEY_F3:
		return KeyboardKey::KeyF3;
	case GLFW_KEY_F4:
		return KeyboardKey::KeyF4;
	case GLFW_KEY_F5:
		return KeyboardKey::KeyF5;
	case GLFW_KEY_F6:
		return KeyboardKey::KeyF6;
	case GLFW_KEY_F7:
		return KeyboardKey::KeyF7;
	case GLFW_KEY_F8:
		return KeyboardKey::KeyF8;
	case GLFW_KEY_F9:
		return KeyboardKey::KeyF9;
	case GLFW_KEY_F10:
		return KeyboardKey::KeyF10;
	case GLFW_KEY_F11:
		return KeyboardKey::KeyF11;
	case GLFW_KEY_F12:
		return KeyboardKey::KeyF12;
	case GLFW_KEY_UP:
		return KeyboardKey::KeyArrowUp;
	case GLFW_KEY_LEFT:
		return KeyboardKey::KeyArrowLeft;
	case GLFW_KEY_RIGHT:
		return KeyboardKey::KeyArrowRight;
	case GLFW_KEY_DOWN:
		return KeyboardKey::KeyArrowDown;
	case GLFW_KEY_SPACE:
		return KeyboardKey::KeySpace;
	case GLFW_KEY_COMMA:
		return KeyboardKey::KeyComma;
	case GLFW_KEY_PERIOD:
		return KeyboardKey::KeyDot;
	case GLFW_KEY_SLASH:
		return KeyboardKey::KeySlash;
	case GLFW_KEY_SEMICOLON:
		return KeyboardKey::KeySemicolon;
	case GLFW_KEY_APOSTROPHE:
		return KeyboardKey::KeyApostrophe;
	case GLFW_KEY_BACKSLASH:
		return KeyboardKey::KeyBackslash;
	case GLFW_KEY_LEFT_BRACKET:
		return KeyboardKey::LeftBracket;
	case GLFW_KEY_RIGHT_BRACKET:
		return KeyboardKey::RightBracket;
	case GLFW_KEY_GRAVE_ACCENT:
		return KeyboardKey::KeyGraveAccent;
	case GLFW_KEY_MINUS:
		return KeyboardKey::KeyMinus;
	case GLFW_KEY_EQUAL:
		return KeyboardKey::KeyEqual;
	case GLFW_KEY_BACKSPACE:
		return KeyboardKey::KeyBackspace;
	case GLFW_KEY_ESCAPE:
		return KeyboardKey::KeyEscape;
	}
}
