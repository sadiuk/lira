export module lira.graphics.IProgramPipeline;
import lira.graphics.IShader;
import lira.graphics.IBuffer;
import lira.graphics.Common;
import std.core;
import std.memory;
export namespace lira::graphics
{
	class IProgramPipeline
	{
	public:
		struct VertexAttribute
		{
			std::shared_ptr<IBuffer> buffer;
			uint32_t componentCount; // 1/2/3/4
			EDataType type;
			bool normalizeWhenAccessed;
			uint32_t stride; // distance between consecutive attributes of the same type
		};
		virtual void SetVertexAttributesLayout(const std::vector<VertexAttribute>& layout) = 0;
		virtual void AttachShader(std::shared_ptr<IShader>&& shader) = 0;
	};
}