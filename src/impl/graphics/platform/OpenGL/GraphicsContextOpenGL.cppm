module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;


namespace lira::graphics
{
	GraphicsContextOpenGL::GraphicsContextOpenGL(const CreationParams& params)
	{
	
	}
	void GraphicsContextOpenGL::ProcessRequest(const lira::graphics::GLRequest& r)
	{
		switch (r.type)
		{
		case ERequestType::CREATE_CONTEXT:
		{

			break;
		}
		}
	}
}