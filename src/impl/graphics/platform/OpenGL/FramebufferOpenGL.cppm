#include <glad/glad.h>
module lira.graphics.platform.OpenGL.FramebufferOpenGL;
import lira.graphics.platform.OpenGL.FramebufferOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;

export namespace lira::graphics
{
	lira::graphics::FramebufferOpenGL::FramebufferOpenGL()
	{
		glCreateFramebuffers(1, &m_id);
	}
	lira::graphics::FramebufferOpenGL::~FramebufferOpenGL()
	{
		glCreateFramebuffers(1, &m_id);
	}
	bool FramebufferOpenGL::AttachTexture(const std::shared_ptr<ITexture>& tex, EFBOAttachment type, uint32_t mipLevel)
	{
		glNamedFramebufferTexture(m_id, GraphicsContextOpenGL::getNativeFBOAttachment(type), static_cast<TextureOpenGL*>(tex.get())->GetId(), mipLevel);
		return glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}
}