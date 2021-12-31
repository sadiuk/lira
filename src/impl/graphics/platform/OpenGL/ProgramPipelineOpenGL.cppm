#include "glad/glad.h"
module lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.math.Types;
import std.memory;

namespace lira::graphics
{
	int ProgramPipelineOpenGL::getCachedLocation(EShaderStage stage, const std::string_view& name)
	{
		auto it = m_cachedUniformLocations.find(std::string(name));
		if (it != m_cachedUniformLocations.end())
		{
			return it->second;
		}
		else
		{
			int location = glGetUniformLocation(getShaderId(stage), name.data());
			if (location != -1)
			{
				m_cachedUniformLocations.insert(std::make_pair(name, location));
			}
			return location;
		}
	}
	ProgramPipelineOpenGL::ProgramPipelineOpenGL()
	{
		glGenProgramPipelines(1, &m_id);
		glGenVertexArrays(1, &m_vaoId);
	}
	ProgramPipelineOpenGL::~ProgramPipelineOpenGL()
	{
		glDeleteProgramPipelines(1, &m_id);
		glDeleteVertexArrays(1, &m_vaoId);
	}
	void ProgramPipelineOpenGL::AttachShader(std::shared_ptr<IShader>&& shader)
	{
		auto stage = shader->GetStage();
		auto* shader_native = static_cast<ShaderOpenGL*>(shader.get());
		m_shaderIDs.insert(std::make_pair(stage, shader_native->GetId()));
		switch (stage)
		{
		case VERTEX:
		{
			glUseProgramStages(m_id, GL_VERTEX_SHADER_BIT, shader_native->GetId());
			break;
		}
		case FRAGMENT:
		{
			glUseProgramStages(m_id, GL_FRAGMENT_SHADER_BIT, shader_native->GetId());
			break;
		}
		case TESSELATION_EVALUATION:
		{
			glUseProgramStages(m_id, GL_TESS_EVALUATION_SHADER_BIT, shader_native->GetId());
			break;
		}
		case TESSELATION_CONTROL:
		{
			glUseProgramStages(m_id, GL_TESS_CONTROL_SHADER_BIT, shader_native->GetId());
			break;
		}
		case GEOMETRY:
		{
			glUseProgramStages(m_id, GL_GEOMETRY_SHADER_BIT, shader_native->GetId());
			break;
		}
		case COMPUTE:
		{
			glUseProgramStages(m_id, GL_COMPUTE_SHADER_BIT, shader_native->GetId());
			break;
		}
		}
	}
	void ProgramPipelineOpenGL::SetVertexAttributesLayout(const std::vector<VertexAttribute>& layout)
	{
		glBindVertexArray(m_vaoId);
		uint32_t offset = 0;
		for (int i = 0; i < layout.size(); i++)
		{
			auto element = layout[i];
			glBindBuffer(GL_ARRAY_BUFFER, static_cast<BufferOpenGL*>(element.buffer.get())->GetId());
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				element.componentCount,
				GraphicsContextOpenGL::getNativeDataType(element.type),
				element.normalizeWhenAccessed,
				element.stride,
				(const void*)offset
			);
			offset += (getTypeSize(element.type) * element.componentCount);
		}
	}

	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, float value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1f(location, value);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::f2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2f(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::f3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3f(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::f4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4f(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}


	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, int32_t value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::i2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::i3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::i4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, uint32_t value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1ui(location, value);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::u2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2ui(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::u3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3ui(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::u4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4ui(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, bool value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::b2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::b3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ProgramPipelineOpenGL::SetUniform(EShaderStage stage, const std::string_view& name, math::b4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}
}