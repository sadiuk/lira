export module lira.graphics.IGraphicsContext;
import std.memory;
import lira.ui.IWindow;

export namespace lira::graphics
{
	enum EAPIType
	{
		OPENGL
	};
	enum EFBOAttachmentType : uint8_t
	{
		COLOR_BUFFER = 1,
		DEPTH_BUFFER = 2,
		STENCIL_BUFFER = 4
	};
	class IGraphicsContext
	{
	public:
		struct CreationParams
		{
			EAPIType apiType;
			ui::IWindow* window;
		};
		
		static std::shared_ptr<IGraphicsContext> Create(const CreationParams& params);

		virtual void SwapBuffers(lira::ui::IWindow* window) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetClearDepth(float d) = 0;
		virtual void SetClearStencil(float s) = 0;
		virtual void Clear(EFBOAttachmentType t) = 0;
		
		virtual ~IGraphicsContext() = default;
		
	};
}
