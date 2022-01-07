export module lira.graphics.IFramebuffer;
import lira.graphics.ITexture;
import std.core;

export namespace lira::graphics
{
	class IFramebuffer
	{
	public:
		virtual bool AttachTexture(const std::shared_ptr<ITexture>& tex, EFBOAttachment type, uint32_t mipLevel = 0) = 0;
		virtual ~IFramebuffer() = default;
	};
}