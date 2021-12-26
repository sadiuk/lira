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
			m_createdProperly = false;
		}
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		m_native = glfwCreateWindow(m_width, m_height, m_caption.c_str(), nullptr, nullptr);
		if (!m_native)
		{
			m_createdProperly = false;
		}
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