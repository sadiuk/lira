export module lira.graphics.IProgramPipeline;
import lira.graphics.IShader;
import lira.graphics.IBuffer;
import lira.graphics.Common;
import lira.math.Types;
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

		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, float value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::f2 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::f3 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::f4 value) = 0;

		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, int32_t value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::i2 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::i3 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::i4 value) = 0;

		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, uint32_t value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::u2 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::u3 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::u4 value) = 0;

		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, bool value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::b2 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::b3 value) = 0;
		virtual bool SetUniform(EShaderStage stage, const std::string_view& name, math::b4 value) = 0;
	};
}