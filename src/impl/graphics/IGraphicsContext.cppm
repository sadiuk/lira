#include <cassert>
module lira.graphics.IGraphicsContext;
import lira.graphics.IGraphicsContext; // dafuq why doesn't it compile without this import if it's the same module??
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import std.memory;

namespace lira::graphics
{
	std::shared_ptr<IGraphicsContext> IGraphicsContext::Create(const CreationParams& params)
	{
		switch (params.apiType)
		{
		case EAPIType::OPENGL:
		{
			return std::make_shared<GraphicsContextOpenGL>(params);
			break;
		}
		}
		assert(false);
	}
}