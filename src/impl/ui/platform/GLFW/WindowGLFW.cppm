#include "GLFW/glfw3.h"

module lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.IWindow;
namespace lira::ui
{
	WindowGLFW::WindowGLFW(const CreationParams& params) : IWindow(params)
	{
		if (!glfwInit())
		{
			createdProperly = false;
		}
		m_native = glfwCreateWindow(m_width, m_height, m_caption.c_str(), nullptr, nullptr);
		if (!m_native)
		{
			createdProperly = false;
		}
	}

	bool WindowGLFW::IsOpen() const
	{
		return !glfwWindowShouldClose(m_native);
	}

	void WindowGLFW::PollEvents()
	{
		glfwPollEvents();
	}
}