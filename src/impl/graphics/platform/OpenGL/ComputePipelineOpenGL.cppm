#include "glad/glad.h"
#include <cassert>
module lira.graphics.platform.OpenGL.ComputePipelineOpenGL;
import lira.graphics.platform.OpenGL.ComputePipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.math.Types;
import std.memory;

namespace lira::graphics
{
	int ComputePipelineOpenGL::getCachedLocation(const std::string_view& name)
	{
		auto it = m_cachedUniformLocations.find(std::string(name));
		if (it != m_cachedUniformLocations.end())
		{
			return it->second;
		}
		else
		{
			int location = glGetUniformLocation(static_cast<ShaderOpenGL*>(m_shader.get())->GetId(), name.data());
			if (location != -1)
			{
				m_cachedUniformLocations.insert(std::make_pair(name, location));
			}
			return location;
		}
	}
	ComputePipelineOpenGL::ComputePipelineOpenGL()
	{
		glGenProgramPipelines(1, &m_id);
	}
	ComputePipelineOpenGL::~ComputePipelineOpenGL()
	{
		glDeleteProgramPipelines(1, &m_id);
	}
	void ComputePipelineOpenGL::AttachShader(std::shared_ptr<IShader>&& shader)
	{
		auto stage = shader->GetStage();
		assert(stage == EShaderStage::COMPUTE);
		if (stage != EShaderStage::COMPUTE) return;
		auto* shader_native = static_cast<ShaderOpenGL*>(shader.get());
		switch (stage)
		{
		case EShaderStage::COMPUTE:
		{
			glUseProgramStages(m_id, GL_COMPUTE_SHADER_BIT, shader_native->GetId());
			return;
		}
		default:
		{
			assert(false);
		}
		}
	}

	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, float value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform1f(location, value);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::f2 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform2f(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::f3 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform3f(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::f4 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform4f(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}


	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, int32_t value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::i2 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::i3 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::i4 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, uint32_t value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform1ui(location, value);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::u2 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform2ui(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::u3 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform3ui(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::u4 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform4ui(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, bool value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::b2 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::b3 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool ComputePipelineOpenGL::SetUniform(const std::string_view& name, math::b4 value)
	{
		int location = getCachedLocation(name);
		if (location == -1) return false;
		glUseProgram(static_cast<ShaderOpenGL*>(m_shader.get())->GetId());
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}
}