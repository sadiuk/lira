#include "glad/glad.h"
#include <cassert>
module lira.graphics.platform.OpenGL.GraphicsPipelineOpenGL;
import lira.graphics.platform.OpenGL.GraphicsPipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.math.Types;
import std.memory;

namespace lira::graphics
{
	int GraphicsPipelineOpenGL::getCachedLocation(EStage stage, const std::string_view& name)
	{
		auto st = m_cachedUniformLocations.find(stage);
		auto it = st->second.find(std::string(name));
		if (it != st->second.end())
		{
			return it->second;
		}
		else
		{
			int location = glGetUniformLocation(getShaderId(stage), name.data());
			if (location != -1)
			{
				st->second.insert(std::make_pair(name, location));
			}
			return location;
		}
	}
	GraphicsPipelineOpenGL::GraphicsPipelineOpenGL()
	{
		glGenProgramPipelines(1, &m_id);
		glGenVertexArrays(1, &m_vaoId);
	}
	GraphicsPipelineOpenGL::~GraphicsPipelineOpenGL()
	{
		glDeleteProgramPipelines(1, &m_id);
		glDeleteVertexArrays(1, &m_vaoId);
	}
	void GraphicsPipelineOpenGL::AttachShader(std::shared_ptr<IShader>&& shader)
	{
		auto stage = shader->GetStage();
		auto* shader_native = static_cast<ShaderOpenGL*>(shader.get());
		switch (stage)
		{
		case EShaderStage::VERTEX:
		{
			glUseProgramStages(m_id, GL_VERTEX_SHADER_BIT, shader_native->GetId());
			break;
		}
		case EShaderStage::FRAGMENT:
		{
			glUseProgramStages(m_id, GL_FRAGMENT_SHADER_BIT, shader_native->GetId());
			break;
		}
		case EShaderStage::TESSELATION_EVALUATION:
		{
			glUseProgramStages(m_id, GL_TESS_EVALUATION_SHADER_BIT, shader_native->GetId());
			break;
		}
		case EShaderStage::TESSELATION_CONTROL:
		{
			glUseProgramStages(m_id, GL_TESS_CONTROL_SHADER_BIT, shader_native->GetId());
			break;
		}
		case EShaderStage::GEOMETRY:
		{
			glUseProgramStages(m_id, GL_GEOMETRY_SHADER_BIT, shader_native->GetId());
			break;
		}
		case EShaderStage::COMPUTE:
		{
			assert(false);
			return;
		}
		}
		m_cachedUniformLocations.insert(std::make_pair(static_cast<EStage>(stage), std::unordered_map<std::string, uint32_t>()));
		m_shaderIDs.insert(std::make_pair(static_cast<EStage>(stage), shader_native->GetId()));
	}
	void GraphicsPipelineOpenGL::SetVertexAttributesLayout(const std::vector<VertexAttribute>& layout)
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

	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, float value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1f(location, value);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::f2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2f(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::f3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3f(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::f4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4f(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}


	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, int32_t value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::i2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::i3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::i4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, uint32_t value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1ui(location, value);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::u2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2ui(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::u3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3ui(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::u4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4ui(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}

	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, bool value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform1i(location, value);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::b2 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform2i(location, value.x, value.y);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::b3 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform3i(location, value.x, value.y, value.z);
		glUseProgram(0);

		return true;
	}
	bool GraphicsPipelineOpenGL::SetUniform(EStage stage, const std::string_view& name, math::b4 value)
	{
		int location = getCachedLocation(stage, name);
		if (location == -1) return false;
		glUseProgram(getShaderId(stage));
		glUniform4i(location, value.x, value.y, value.z, value.w);
		glUseProgram(0);

		return true;
	}
}