#include <glad/glad.h>
module lira.graphics.platform.OpenGL.PipelineOpenGL;
import lira.graphics.platform.OpenGL.PipelineOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import std.core;

export namespace lira::graphics
{
	void PipelineOpenGL::BindAttachedBindings()
	{
		for (auto binding : m_bindingsLayout)
		{
			switch (binding.bindingType)
			{
			case EShaderBindingType::SHADER_STORAGE_BUFFER:
			{
				auto bufferOpenGL = static_cast<BufferOpenGL*>(binding.bufferParams.buffer);
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding.unit, bufferOpenGL->GetId());
				break;
			}
			case EShaderBindingType::UNIFORM_BUFFER:
			{
				auto bufferOpenGL = static_cast<BufferOpenGL*>(binding.bufferParams.buffer);
				glBindBufferBase(GL_UNIFORM_BUFFER, binding.unit, bufferOpenGL->GetId());
				break;
			}
			case EShaderBindingType::ATOMIC_COUNTER_BUFFER:
			{
				auto bufferOpenGL = static_cast<BufferOpenGL*>(binding.bufferParams.buffer);
				glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, binding.unit, bufferOpenGL->GetId());
				break;
			}
			case EShaderBindingType::TRANSFORM_FEEDBACK_BUFFER:
			{
				auto bufferOpenGL = static_cast<BufferOpenGL*>(binding.bufferParams.buffer);
				glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, binding.unit, bufferOpenGL->GetId());
				break;
			}
			case EShaderBindingType::SAMPLER:
			{
				auto textureOpenGL = static_cast<TextureOpenGL*>(binding.samplerParams.texture);
				glBindTextureUnit(binding.unit, textureOpenGL->GetId());
				break;
			}
			case EShaderBindingType::IMAGE_TEXTURE:
			{
				auto textureOpenGL = static_cast<TextureOpenGL*>(binding.imageParams.texture);
				glBindImageTexture(
					binding.unit,
					textureOpenGL->GetId(),
					binding.imageParams.mipmapLevel,
					binding.imageParams.layered,
					binding.imageParams.arrayLayer,
					GraphicsContextOpenGL::getNativeAccessMode(binding.imageParams.accessMode),
					GraphicsContextOpenGL::getNativeTextureFormat(binding.imageParams.textureFormat)
				);
				break;
			}
			}
		}
	}
	void lira::graphics::PipelineOpenGL::SetShaderBindingLayout(const std::vector<ShaderBinding>& layout)
	{
		m_bindingsLayout = layout;
	}
}