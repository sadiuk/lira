#include "GLFW/glfw3.h"

export module lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.IWindow;

export namespace lira::ui
{
	GLFWwindow* m_native;
	bool createdProperly = true;
	class WindowGLFW : public IWindow
	{
	public:
		WindowGLFW(const CreationParams& params);
		bool IsOpen() const override;
		void PollEvents() override;
	};
}
