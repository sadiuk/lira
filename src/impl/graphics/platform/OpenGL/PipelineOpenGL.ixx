export module lira.graphics.platform.OpenGL.PipelineOpenGL;
import lira.graphics.IPipeline;

export namespace lira::graphics
{
	class PipelineOpenGL : virtual public IPipeline
	{
		std::vector<ShaderBinding> m_bindingsLayout;
	public:
		void BindAttachedBindings();
		void SetShaderBindingLayout(const std::vector<ShaderBinding>& layout) override;
	};
}