export module lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.IProgramPipeline;
import std.memory;
export namespace lira::graphics
{
	class ProgramPipelineOpenGL : public IProgramPipeline
	{
		uint32_t m_id;
		uint32_t m_vaoId;
	public:
		ProgramPipelineOpenGL();
		~ProgramPipelineOpenGL();
		void AttachShader(std::shared_ptr<IShader>&& shader) override;
		void SetVertexAttributesLayout(const std::vector<VertexAttribute>& layout);

		uint32_t getId() const { return m_id; }
		uint32_t getVAOId() const { return m_vaoId; }
	};
}