export module lira.graphics.ICommandBuffer;
import lira.ui.IWindow;

export namespace lira::graphics
{
	class IGraphicsContext;
	enum EFBOAttachmentType;
	class ICommandBuffer
	{
		virtual GLRequest Pop() = 0;
		virtual void SwapBuffers(ui::IWindow* window) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetClearDepth(float d) = 0;
		virtual void SetClearStencil(float s) = 0;
		virtual void Clear(EFBOAttachmentType t) = 0;
	};
}