export module lira.graphics.IProgramPipeline;
import lira.graphics.IShader;
import std.core;

export namespace lira::graphics
{
	class IProgramPipeline
	{
		virtual void AttachShader(std::shared_ptr<IShader>&& shader) = 0;
	};
}