export module lira.graphics.platform.OpenGL.GraphicsPipelineOpenGL;
import lira.graphics.IGraphicsPipeline;
import lira.graphics.Common;
import lira.math.Types;
import std.memory;
import std.core;
export namespace lira::graphics
{
	class GraphicsPipelineOpenGL : public IGraphicsPipeline
	{
		uint32_t m_id;
		uint32_t m_vaoId;
		std::unordered_map<EStage, std::unordered_map<std::string, uint32_t>> m_cachedUniformLocations;
		std::map<EStage, uint32_t> m_shaderIDs;
	private:

		int getCachedLocation(EStage stage, const std::string_view& name);
		int getShaderId(EStage stage)
		{
			auto val = m_shaderIDs.find(stage);
			if (val != m_shaderIDs.end()) return val->second;
			return -1;
		}
	public:
		GraphicsPipelineOpenGL();
		~GraphicsPipelineOpenGL();
		void AttachShader(std::shared_ptr<IShader>&& shader) override;
		void SetVertexAttributesLayout(const std::vector<VertexAttribute>& layout);

		uint32_t getId() const { return m_id; }
		uint32_t getVAOId() const { return m_vaoId; }

		bool SetUniform(EStage stage, const std::string_view& name, float value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::f2 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::f3 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::f4 value) override;

		bool SetUniform(EStage stage, const std::string_view& name, int32_t value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::i2 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::i3 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::i4 value) override;

		bool SetUniform(EStage stage, const std::string_view& name, uint32_t value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::u2 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::u3 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::u4 value) override;

		bool SetUniform(EStage stage, const std::string_view& name, bool value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::b2 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::b3 value) override;
		bool SetUniform(EStage stage, const std::string_view& name, math::b4 value) override;
	};
}