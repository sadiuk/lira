#include <glad/glad.h>
#include <cassert>
module lira.graphics.platform.OpenGL.SamplerOpenGL;
import lira.graphics.platform.OpenGL.SamplerOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.ISampler;

export namespace lira::graphics
{
	SamplerOpenGL::SamplerOpenGL(CreationParams&& params) : ISampler(std::move(params))
	{
		glGenSamplers(1, &m_id);
		glSamplerParameteri(m_id, GL_TEXTURE_WRAP_S, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapS));
		glSamplerParameteri(m_id, GL_TEXTURE_WRAP_T, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapT));
		glSamplerParameteri(m_id, GL_TEXTURE_WRAP_R, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapR));
		if (params.wrapS == ETextureWrapMode::CLAMP_TO_BORDER ||
			params.wrapT == ETextureWrapMode::CLAMP_TO_BORDER ||
			params.wrapR == ETextureWrapMode::CLAMP_TO_BORDER)
		{
			glSamplerParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, params.borderColor.data());
		}
		glSamplerParameteri(m_id, GL_TEXTURE_MIN_FILTER, GraphicsContextOpenGL::getNativeTextureMinFilter(params.minFilter));
		glSamplerParameteri(m_id, GL_TEXTURE_MAG_FILTER, GraphicsContextOpenGL::getNativeTextureMagFilter(params.magFilter));
	}

	SamplerOpenGL::~SamplerOpenGL()
	{
		glDeleteSamplers(1, &m_id);
	}

}