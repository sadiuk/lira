export module lira.graphics.IComputePipeline;
import lira.graphics.IShader;
import lira.graphics.IBuffer;
import lira.graphics.Common;
import lira.math.Types;
import std.core;
import std.memory;
export namespace lira::graphics
{
	class IComputePipeline
	{
	public:
		virtual void AttachShader(std::shared_ptr<IShader>&& shader) = 0;

		virtual bool SetUniform(const std::string_view& name, float value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::f2 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::f3 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::f4 value) = 0;

		virtual bool SetUniform(const std::string_view& name, int32_t value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::i2 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::i3 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::i4 value) = 0;

		virtual bool SetUniform(const std::string_view& name, uint32_t value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::u2 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::u3 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::u4 value) = 0;

		virtual bool SetUniform(const std::string_view& name, bool value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::b2 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::b3 value) = 0;
		virtual bool SetUniform(const std::string_view& name, math::b4 value) = 0;
	};
}