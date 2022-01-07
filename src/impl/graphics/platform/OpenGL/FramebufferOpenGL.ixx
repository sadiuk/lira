export module lira.graphics.platform.OpenGL.FramebufferOpenGL;
import lira.graphics.IFramebuffer;
import lira.graphics.Common;
import std.core;

export namespace lira::graphics
{
	class FramebufferOpenGL : public IFramebuffer
	{
		uint32_t m_id;
	public:
		FramebufferOpenGL();
		~FramebufferOpenGL() override;
		bool AttachTexture(const std::shared_ptr<ITexture>& tex, EFBOAttachment type, uint32_t mipLevel = 0) override;
		uint32_t GetId() const { return m_id; }
	};
}