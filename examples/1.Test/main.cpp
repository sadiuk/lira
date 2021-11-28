#include <memory>
#include <vector>
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;

int main()
{
	lira::ui::IWindow::CreationParams params;
	params.width = 600;
	params.height = 400;
	params.caption = "Test";
	auto window = std::make_shared<lira::ui::WindowGLFW>(params);

	while (window->IsOpen())
	{
		window->PollEvents();
	}
}