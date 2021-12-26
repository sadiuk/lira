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

		int32_t infoLogLength;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			std::unique_ptr infoLog = std::make_unique<char[]>(infoLogLength);
			int32_t length;
			glGetProgramInfoLog(m_id, infoLogLength, &length, infoLog.get());
			std::cout << infoLog.get();
		}
	}
	ShaderOpenGL::~ShaderOpenGL()
	{
		glDeleteProgram(m_id);
	}
	
}