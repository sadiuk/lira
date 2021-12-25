#include <cassert>
#include <glad/glad.h>
module lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.IShader;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import std.core;
namespace lira::graphics
{
	ShaderOpenGL::ShaderOpenGL(EShaderStage s, const std::string_view& source) : IShader(s)
	{
		const char* src_c = source.data();
		m_id = glCreateShaderProgramv(GraphicsContextOpenGL::getNativeShaderStage(s), 1, static_cast<const char**>(&src_c));
	}
	ShaderOpenGL::~ShaderOpenGL()
	{
		glDeleteProgram(m_id);
	}
	
}