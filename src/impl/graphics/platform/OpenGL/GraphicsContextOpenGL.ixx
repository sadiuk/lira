export module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;
import lira.thread.IThreadRequestProcessor;
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import std.core;
import std.memory;

export namespace lira::graphics
{
	enum ERequestType
	{
		CREATE_CONTEXT,
		DESTROY_CONTEXT,

		SWAP_BUFFERS,

		SET_CLEAR_COLOR,
		SET_CLEAR_DEPTH,
		SET_CLEAR_STENCIL,
		CLEAR_FBO
	};
	struct GLRequest : lira::thread::IRequestBase
	{
		GLRequest() {}
		ERequestType type;

		struct NullRequest {};
		struct CreateContext
		{
			ui::WindowGLFW* window;
		};
		struct SwapBuffers
		{
			ui::WindowGLFW* window;
		};
		struct SetClearColor
		{
			float r, g, b, a;
		};
		struct SetClearDepth
		{
			float d;
		};
		struct SetClearStencil
		{
			float s;
		};
		struct ClearFBO
		{
			IGraphicsContext::EFBOAttachmentType attachmentType;
		};
		union Requests
		{
			NullRequest nullRequest;
			CreateContext createContextRequest;
			SetClearColor setClearColorRequest;
			SetClearDepth setClearDepthRequest;
			SetClearStencil setClearStencilRequest;
			SwapBuffers swapBuffersRequest;
			ClearFBO clearFBORequest;
		} requests;
	};

	class GraphicsContextOpenGL : public IGraphicsContext, public thread::IThreadRequestProcessor<GLRequest>
	{
	protected:
		void ProcessRequest(const GLRequest& r);
	public:
		GraphicsContextOpenGL(const CreationParams& params);
		~GraphicsContextOpenGL() override;

		void SwapBuffers(lira::ui::IWindow* window) override
		{
			GLRequest req;
			req.type = SWAP_BUFFERS;
			req.requests.swapBuffersRequest.window = (ui::WindowGLFW*)window;
			Push(&req);
		}
		void SetClearColor(float r, float g, float b, float a) override
		{
			GLRequest req;
			req.type = SET_CLEAR_COLOR;
			req.requests.setClearColorRequest.r = r;
			req.requests.setClearColorRequest.g = g;
			req.requests.setClearColorRequest.b = b;
			req.requests.setClearColorRequest.a = a;
			Push(&req);
		}
		void SetClearDepth(float d) override 
		{
			GLRequest req;
			req.type = SET_CLEAR_DEPTH;
			req.requests.setClearDepthRequest.d = d;
			Push(&req);
		}
		void SetClearStencil(float s) override 
		{
			GLRequest req;
			req.type = SET_CLEAR_STENCIL;
			req.requests.setClearStencilRequest.s = s;
			Push(&req);
		}
		void Clear(EFBOAttachmentType t) override 
		{
			GLRequest req;
			req.type = CLEAR_FBO;
			req.requests.clearFBORequest.attachmentType = t;
			Push(&req);
		}
	private:
		uint32_t getNativeAttachmentType(IGraphicsContext::EFBOAttachmentType t);
	};
}

