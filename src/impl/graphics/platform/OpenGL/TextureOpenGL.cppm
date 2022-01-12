#include <glad/glad.h>
#include <cassert>
module lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.ITexture;
import std.core;

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