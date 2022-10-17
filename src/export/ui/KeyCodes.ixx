export module lira.ui.KeyCodes;

import std.core;
export namespace lira::ui
{
	enum KeyCode
	{
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_LEFT_SHIFT,
		KEY_RIGHT_SHIFT,
		KEY_LEFT_CTRL,
		KEY_RIGHT_CTRL,
		KEY_LEFT_ALT,
		KEY_RIGHT_ALT,
		KEY_SPACE,
		KEY_ENTER,

		KEY_COUNT
	};

	enum KeyState : uint8_t
	{
		STATE_RELEASED,
		STATE_PRESSED,
	};

	enum MouseButton : uint8_t
	{
		LEFT_MOUSE_BUTTON,
		RIGHT_MOUSE_BUTTON,
		MIDDLE_MOUSE_BUTTON,

		MOUSE_BUTTON_COUNT
	};
}