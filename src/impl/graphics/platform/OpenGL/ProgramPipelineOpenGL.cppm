#include "glad/glad.h"
module lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.platform.OpenGL.ProgramPipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import std.memory;

namespace lira::graphics
{
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
}