#include "GLFW/glfw3.h"
#include <cassert>

module lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.IWindow;
import lira.ui.KeyCodes;
import lira.ui.IEventReceiver;
namespace lira::ui
{
	WindowGLFW::WindowGLFW(const CreationParams& params) : IWindow(params)
	{
		if (!glfwInit())
		{
			m_createdProperly = false;
		}
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		m_native = glfwCreateWindow(m_width, m_height, m_caption.c_str(), nullptr, nullptr);
		if (!m_native)
		{
			m_createdProperly = false;
		}
		glfwSetWindowUserPointer(m_native, this);
		auto KeyCallback = [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			WindowGLFW* wnd = (WindowGLFW*)glfwGetWindowUserPointer(window);
			KeyCode key;
			KeyState state;
			if (wnd->m_eventReceiver.get())
			{
				switch (keyCode)
				{
					case GLFW_KEY_A: key = KeyCode::KEY_A; break;
					case GLFW_KEY_B: key = KeyCode::KEY_B; break;
					case GLFW_KEY_C: key = KeyCode::KEY_C; break;
					case GLFW_KEY_D: key = KeyCode::KEY_D; break;
					case GLFW_KEY_E: key = KeyCode::KEY_E; break;
					case GLFW_KEY_F: key = KeyCode::KEY_F; break;
					case GLFW_KEY_G: key = KeyCode::KEY_G; break;
					case GLFW_KEY_H: key = KeyCode::KEY_H; break;
					case GLFW_KEY_I: key = KeyCode::KEY_I; break;
					case GLFW_KEY_J: key = KeyCode::KEY_J; break;
					case GLFW_KEY_K: key = KeyCode::KEY_K; break;
					case GLFW_KEY_L: key = KeyCode::KEY_L; break;
					case GLFW_KEY_M: key = KeyCode::KEY_M; break;
					case GLFW_KEY_N: key = KeyCode::KEY_N; break;
					case GLFW_KEY_O: key = KeyCode::KEY_O; break;
					case GLFW_KEY_P: key = KeyCode::KEY_P; break;
					case GLFW_KEY_Q: key = KeyCode::KEY_Q; break;
					case GLFW_KEY_R: key = KeyCode::KEY_R; break;
					case GLFW_KEY_S: key = KeyCode::KEY_S; break;
					case GLFW_KEY_T: key = KeyCode::KEY_T; break;
					case GLFW_KEY_U: key = KeyCode::KEY_U; break;
					case GLFW_KEY_V: key = KeyCode::KEY_V; break;
					case GLFW_KEY_W: key = KeyCode::KEY_W; break;
					case GLFW_KEY_X: key = KeyCode::KEY_X; break;
					case GLFW_KEY_Y: key = KeyCode::KEY_Y; break;
					case GLFW_KEY_Z: key = KeyCode::KEY_Z; break;
					case GLFW_KEY_0: key = KeyCode::KEY_0; break;
					case GLFW_KEY_1: key = KeyCode::KEY_1; break;
					case GLFW_KEY_2: key = KeyCode::KEY_2; break;
					case GLFW_KEY_3: key = KeyCode::KEY_3; break;
					case GLFW_KEY_4: key = KeyCode::KEY_4; break;
					case GLFW_KEY_5: key = KeyCode::KEY_5; break;
					case GLFW_KEY_6: key = KeyCode::KEY_6; break;
					case GLFW_KEY_7: key = KeyCode::KEY_7; break;
					case GLFW_KEY_8: key = KeyCode::KEY_8; break;
					case GLFW_KEY_9: key = KeyCode::KEY_9; break;
					case GLFW_KEY_LEFT_SHIFT:		key = KEY_LEFT_SHIFT; break;
					case GLFW_KEY_RIGHT_SHIFT:		key = KEY_RIGHT_SHIFT; break;
					case GLFW_KEY_LEFT_CONTROL:		key = KEY_LEFT_CTRL; break;
					case GLFW_KEY_RIGHT_CONTROL:	key = KEY_RIGHT_CTRL; break;
					case GLFW_KEY_LEFT_ALT:			key = KEY_LEFT_ALT; break;
					case GLFW_KEY_RIGHT_ALT:		key = KEY_RIGHT_ALT; break;
					case GLFW_KEY_SPACE:			key = KEY_SPACE; break;
					case GLFW_KEY_ENTER:			key = KEY_ENTER; break;
				}
				switch (action)
				{
					case GLFW_PRESS : state = STATE_PRESSED; break;
					case GLFW_RELEASE : state = STATE_RELEASED; break;
					default: return;
				}
				wnd->m_eventReceiver->OnKeyPress(key, state);
			}
		};
		auto MousePosCallback = [](GLFWwindow* window, double x, double y)
		{
			WindowGLFW* wnd = (WindowGLFW*)glfwGetWindowUserPointer(window);
			if (wnd->m_eventReceiver.get())
			{
				wnd->m_eventReceiver->OnMouseMove(x, y);
			}
		};
		auto MouseButtonCallback = [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowGLFW* wnd = (WindowGLFW*)glfwGetWindowUserPointer(window);
			if (wnd->m_eventReceiver.get())
			{
				MouseButton btn = MouseButton::LEFT_MOUSE_BUTTON;
				KeyState state = KeyState::STATE_PRESSED;
				switch (button)
				{
				case GLFW_MOUSE_BUTTON_1: btn = MouseButton::LEFT_MOUSE_BUTTON; break;
				case GLFW_MOUSE_BUTTON_2: btn = MouseButton::RIGHT_MOUSE_BUTTON; break;
				case GLFW_MOUSE_BUTTON_3: btn = MouseButton::MIDDLE_MOUSE_BUTTON; break;
				default: assert(false);  return;
				}
				switch (action)
				{
				case GLFW_PRESS: state = KeyState::STATE_PRESSED; break;
				case GLFW_RELEASE: state = KeyState::STATE_RELEASED; break;
				default: assert(false); return;
				}
				wnd->m_eventReceiver->OnMouseButtonClick(btn, state);
			}
		};
		glfwSetKeyCallback(m_native, KeyCallback);
		glfwSetCursorPosCallback(m_native, MousePosCallback);
		glfwSetMouseButtonCallback(m_native, MouseButtonCallback);
	}
	WindowGLFW::~WindowGLFW()
	{
		glfwDestroyWindow(m_native);
	}

	bool WindowGLFW::IsOpen() const
	{
		return !glfwWindowShouldClose(m_native);
	}

	void WindowGLFW::PollEvents()
	{
		glfwPollEvents();
	}
	void WindowGLFW::SwapBuffers()
	{
		glfwSwapBuffers(m_native);
	}
}