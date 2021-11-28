#include <string>  // TODO: remove when VS can handle standart modules without build errors
export module lira.ui.IWindow;

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
		
		~IWindow() = default;
	protected:
		uint16_t m_width, m_height;
		std::string m_caption;

	};
}