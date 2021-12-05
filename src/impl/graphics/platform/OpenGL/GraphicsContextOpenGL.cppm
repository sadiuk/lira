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
		GLRequest r;
		r.type = ERequestType::CREATE_CONTEXT;
		r.requests.createContextRequest.window = (ui::WindowGLFW*)params.window;
		Push(&r);
	}
	GraphicsContextOpenGL::~GraphicsContextOpenGL()
	{
		GLRequest r;
		r.type = ERequestType::DESTROY_CONTEXT;
		Push(&r);
	}
	uint32_t GraphicsContextOpenGL::getNativeAttachmentType(IGraphicsContext::EFBOAttachmentType t)
	{
		switch (t)
		{
		case IGraphicsContext::EFBOAttachmentType::COLOR_BUFFER: return GL_COLOR_BUFFER_BIT;
		case IGraphicsContext::EFBOAttachmentType::DEPTH_BUFFER: return GL_DEPTH_BUFFER_BIT;
		case IGraphicsContext::EFBOAttachmentType::STENCIL_BUFFER: return GL_STENCIL_BUFFER_BIT;
		}
	}
	void GraphicsContextOpenGL::ProcessRequest(const lira::graphics::GLRequest& r)
	{
		switch (r.type)
		{
		case ERequestType::CREATE_CONTEXT:
		{
			auto req = r.requests.createContextRequest;
			glfwMakeContextCurrent(req.window->GetNative());
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			break;
		}
		case ERequestType::SWAP_BUFFERS:
		{
			auto req = r.requests.swapBuffersRequest;
			glfwSwapBuffers(req.window->GetNative());
			break;
		}
		case ERequestType::DESTROY_CONTEXT:
		{
			glfwMakeContextCurrent(nullptr);
			break;
		}
		case ERequestType::SET_CLEAR_COLOR:
		{
			auto req = r.requests.setClearColorRequest;
			glClearColor(req.r, req.g, req.b, req.a);
			break;
		}
		case ERequestType::SET_CLEAR_DEPTH:
		{
			auto req = r.requests.setClearDepthRequest;
			glClearDepthf(req.d);
			break;
		}
		case ERequestType::SET_CLEAR_STENCIL:
		{
			auto req = r.requests.setClearStencilRequest;
			glClearStencil(req.s);
			break;
		}
		case ERequestType::CLEAR_FBO:
		{
			auto req = r.requests.clearFBORequest;
			glClear(getNativeAttachmentType(req.attachmentType));
			break;
		}
		}
	}
}