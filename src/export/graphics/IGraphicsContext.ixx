#include <memory> // TODO: remove when VS can handle standart modules without build errors
export module lira.graphics.IGraphicsContext;
//import std.memory;

export namespace lira::graphics
{
	class IGraphicsContext
	{
	public:
		enum class EAPIType
		{
			OPENGL
		};
		struct CreationParams
		{
			EAPIType apiType;
		};
		static std::shared_ptr<IGraphicsContext> Create(const CreationParams& params);
	};
}
