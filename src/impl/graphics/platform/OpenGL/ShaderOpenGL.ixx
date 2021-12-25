export module lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.IShader;
import std.core;

export namespace lira::graphics
{
	class ShaderOpenGL : public IShader
	{
		uint32_t m_id;
	public:
		ShaderOpenGL(EShaderStage s, const std::string_view& source);
		~ShaderOpenGL();
		uint32_t GetId() { return m_id; }
	};
}