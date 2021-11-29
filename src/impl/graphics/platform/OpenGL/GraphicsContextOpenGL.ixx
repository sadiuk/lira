export module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;
import lira.thread.IThreadRequestProcessor;
import lira.ui.IWindow;
import std.core;
export namespace lira::graphics
{
	enum class ERequestType
	{
		CREATE_CONTEXT
	};
	struct GLRequest
	{
		GLRequest() {}
		ERequestType type;

		struct SNullRequest {};
		struct SCreateContext
		{
			ui::IWindow* window;
		};
		union Requests
		{
			SNullRequest nullRequest;
			SCreateContext createContextRequest;
		} requests;
	};

	class GraphicsContextOpenGL : public IGraphicsContext, public thread::IThreadRequestProcessor<GLRequest>
	{
	protected:
		void ProcessRequest(const GLRequest& r);
	public:
		GraphicsContextOpenGL(const CreationParams& params);
		//GraphicsContextOpenGL();
	};
}

