import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;
import std.core;
import std.memory;
int main()
{
	lira::ui::IWindow::CreationParams wndParams; 
	wndParams.width = 600;
	wndParams.height = 400;
	wndParams.caption = "Test";
	auto window = std::make_shared<lira::ui::WindowGLFW>(wndParams);

	lira::graphics::IGraphicsContext::CreationParams ctxParams;
	ctxParams.apiType = lira::graphics::IGraphicsContext::EAPIType::OPENGL;
	ctxParams.window = window.get();
	auto context = lira::graphics::IGraphicsContext::Create(ctxParams);

	context->SetClearColor(1, 0, 0, 1);
	while (window->IsOpen())
	{
		window->PollEvents();

		context->Clear(lira::graphics::IGraphicsContext::COLOR_BUFFER);
		
		context->SwapBuffers(window.get());
	}
}