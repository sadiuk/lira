export module lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.IProgramPipeline;
import std.memory;
export namespace lira::graphics
{
	class ProgramPipelineOpenGL : public IProgramPipeline
	{
		uint32_t m_id;
	public:
		ProgramPipelineOpenGL();
		~ProgramPipelineOpenGL();
		void AttachShader(std::shared_ptr<IShader>&& shader) override;
	};
}