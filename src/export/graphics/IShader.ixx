export module lira.graphics.IShader;
import lira.graphics.Common;

export namespace lira::graphics
{
	class IShader
	{
		EShaderStage m_stage;

	protected:
		IShader(EShaderStage stage) : m_stage(stage) {}
		virtual ~IShader() = default;
	public:
		EShaderStage GetStage() const { return m_stage; }
	};
}