#include "glad/glad.h"
#include "GLFW/glfw3.h"
module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;
import lira.ui.platform.GLFW.WindowGLFW;


namespace lira::graphics
{
	GraphicsContextOpenGL::GraphicsContextOpenGL(const CreationParams& params)
	{
		glfwMakeContextCurrent(static_cast<ui::WindowGLFW*>(params.window)->GetNative());
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	GraphicsContextOpenGL::~GraphicsContextOpenGL()
	{
		glfwMakeContextCurrent(nullptr);
	}
	void GraphicsContextOpenGL::SwapBuffers(lira::ui::IWindow* window)
	{
		glfwSwapBuffers(static_cast<ui::WindowGLFW*>(window)->GetNative());
	}
	void GraphicsContextOpenGL::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void GraphicsContextOpenGL::SetClearDepth(float d)
	{
		glClearDepthf(d);
	}
	void GraphicsContextOpenGL::SetClearStencil(float s)
	{
		glClearStencil(s);
	}
	void GraphicsContextOpenGL::Clear(EFBOAttachmentType t)
	{
		glClear(getNativeAttachmentType(t));
	}
	uint32_t GraphicsContextOpenGL::getNativeAttachmentType(EFBOAttachmentType t)
	{
		switch (t)
		{
		case EFBOAttachmentType::COLOR_BUFFER: return GL_COLOR_BUFFER_BIT;
		case EFBOAttachmentType::DEPTH_BUFFER: return GL_DEPTH_BUFFER_BIT;
		case EFBOAttachmentType::STENCIL_BUFFER: return GL_STENCIL_BUFFER_BIT;
		}
	}
}