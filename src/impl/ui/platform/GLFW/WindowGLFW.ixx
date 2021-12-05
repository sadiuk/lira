#include "GLFW/glfw3.h"

export module lira.ui.platform.GLFW.WindowGLFW;
import lira.ui.IWindow;

export namespace lira::ui
{
	class WindowGLFW : public IWindow
	{
		GLFWwindow* m_native;
		bool createdProperly = true;
	public:
		WindowGLFW(const CreationParams& params);
		~WindowGLFW() override;
		bool IsOpen() const override;
		void PollEvents() override;
		void SwapBuffers() override;
		GLFWwindow* GetNative() { return m_native; }
	};
}
