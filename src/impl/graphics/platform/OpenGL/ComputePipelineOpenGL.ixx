export module lira.graphics.platform.OpenGL.ComputePipelineOpenGL;
import lira.graphics.IComputePipeline;
import lira.graphics.Common;
import lira.math.Types;
import std.memory;
import std.core;
export namespace lira::graphics
{
	class ComputePipelineOpenGL : public IComputePipeline
	{
		uint32_t m_id;
		std::unordered_map<std::string, uint32_t> m_cachedUniformLocations;
		std::shared_ptr<IShader> m_shader;
	private:

		int getCachedLocation(const std::string_view& name);
	public:
		ComputePipelineOpenGL();
		~ComputePipelineOpenGL();
		void AttachShader(std::shared_ptr<IShader>&& shader) override;

		uint32_t getId() const { return m_id; }

		bool SetUniform(const std::string_view& name, float value) override;
		bool SetUniform(const std::string_view& name, math::f2 value) override;
		bool SetUniform(const std::string_view& name, math::f3 value) override;
		bool SetUniform(const std::string_view& name, math::f4 value) override;

		bool SetUniform(const std::string_view& name, int32_t value) override;
		bool SetUniform(const std::string_view& name, math::i2 value) override;
		bool SetUniform(const std::string_view& name, math::i3 value) override;
		bool SetUniform(const std::string_view& name, math::i4 value) override;

		bool SetUniform(const std::string_view& name, uint32_t value) override;
		bool SetUniform(const std::string_view& name, math::u2 value) override;
		bool SetUniform(const std::string_view& name, math::u3 value) override;
		bool SetUniform(const std::string_view& name, math::u4 value) override;

		bool SetUniform(const std::string_view& name, bool value) override;
		bool SetUniform(const std::string_view& name, math::b2 value) override;
		bool SetUniform(const std::string_view& name, math::b3 value) override;
		bool SetUniform(const std::string_view& name, math::b4 value) override;
	};
}