export module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;
import lira.thread.IThreadRequestProcessor;
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import std.core;
import std.memory;

export namespace lira::graphics
{
	class GraphicsContextOpenGL : public IGraphicsContext
	{
	public:
		GraphicsContextOpenGL(const CreationParams& params);
		~GraphicsContextOpenGL() override;

		void SwapBuffers(lira::ui::IWindow* window) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void SetClearDepth(float d) override;
		void SetClearStencil(float s) override;
		void Clear(EFBOAttachmentType t) override;
	private:
		uint32_t getNativeAttachmentType(EFBOAttachmentType t);
	};
}

