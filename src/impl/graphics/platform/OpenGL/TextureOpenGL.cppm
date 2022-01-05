#include <glad/glad.h>
#include <cassert>
module lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.ITexture;

export namespace lira::graphics
{
	TextureOpenGL::TextureOpenGL(CreationParams&& params) : ITexture(std::move(params))
	{
		auto type = GraphicsContextOpenGL::getNativeTextureType(params.type);
		glCreateTextures(type, 1, &m_id);
		switch (params.type)
		{
		case ETextureType::TEXTURE_1D:
		{
			glTextureStorage1D(m_id, params.arrayLevels, GraphicsContextOpenGL::getNativeTextureFormat(params.format), params.width);
			break;
		}
		case ETextureType::TEXTURE_2D: [[fallthrough]];
		case ETextureType::TEXTURE_CUBE_MAP:
		{
			glTextureStorage2D(m_id, params.arrayLevels, GraphicsContextOpenGL::getNativeTextureFormat(params.format), params.width, params.height);
			break;
		}
		case ETextureType::TEXTURE_3D:
		{
			glTextureStorage3D(m_id, params.arrayLevels, GraphicsContextOpenGL::getNativeTextureFormat(params.format), params.width, params.height, params.depth);
			break;
		}
		case ETextureType::TEXTURE_2D_MULTISAMPLE:
		{
			assert(false);
			break;
		}
		}
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapS));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapT));
		if (params.type == ETextureType::TEXTURE_3D)
		{
			glTextureParameteri(m_id, GL_TEXTURE_WRAP_R, GraphicsContextOpenGL::getNativeTextureWrapMode(params.wrapR));
		}
		if (params.wrapS == ETextureWrapMode::CLAMP_TO_BORDER ||
			params.wrapT == ETextureWrapMode::CLAMP_TO_BORDER ||
			params.wrapR == ETextureWrapMode::CLAMP_TO_BORDER)
		{
			glTextureParameterfv(m_id, GL_TEXTURE_BORDER_COLOR, params.borderColor.data());
		}
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GraphicsContextOpenGL::getNativeTextureMinFilter(params.minFilter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GraphicsContextOpenGL::getNativeTextureMagFilter(params.magFilter));
		if (params.generateMipmaps)
		{
			glGenerateTextureMipmap(m_id);
		}
	}

	TextureOpenGL::~TextureOpenGL()
	{
		glDeleteTextures(1, &m_id);
	}

}