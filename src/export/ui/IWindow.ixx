export module lira.ui.IWindow;
import std.core;
export namespace lira::ui
{
	class IWindow
	{
	public:
		struct CreationParams
		{
			uint16_t width, height;
			std::string caption;
		};

		IWindow(const CreationParams& params) :
			m_width(params.width),
			m_height(params.height),
			m_caption(params.caption)
		{}

		virtual bool IsOpen() const = 0;
		virtual void PollEvents() = 0;
		virtual void SwapBuffers() = 0;
		
		virtual ~IWindow() = default;
	protected:
		uint16_t m_width, m_height;
		std::string m_caption;

	};
}