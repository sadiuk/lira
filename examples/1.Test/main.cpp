import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;
import std.core;
import std.memory;


using namespace lira::graphics;



const char* vertexSource = R"(
#version 460 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;
layout(location = 0) out vec3 fragColor;

out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main()
{
	fragColor = color;
	gl_Position = vec4(pos.x + 0.5 * gl_InstanceID, pos.y, 0, 1);
}
)";

const char* fragmentSource = R"(
#version 460 core
layout(location = 0) in vec3 col;
out vec3 fragColor;

void main()
{
	fragColor = col;
}
)";
int main()
{
	lira::ui::IWindow::CreationParams wndParams; 
	wndParams.width = 600;
	wndParams.height = 400;
	wndParams.caption = "Test";
	auto window = std::make_shared<lira::ui::WindowGLFW>(wndParams);

	lira::graphics::IGraphicsContext::CreationParams ctxParams;
	ctxParams.apiType = lira::graphics::EAPIType::OPENGL;
	ctxParams.window = window.get();
	auto context = lira::graphics::IGraphicsContext::Create(ctxParams);

	float vtc[] = {
		-0.5, -0.5, 1, 0, 0,
		-0.5,  0.5, 0, 1, 0,
		 0,  0.5, 0, 0, 1,
		 0, -0.5, 0, 1, 1,
	};
	uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
	auto vtxBuffer = context->CreateBuffer();
	context->AllocateBuffer(vtxBuffer.get(), sizeof(vtc), vtc);
	auto indexBuffer = context->CreateBuffer();
	context->AllocateBuffer(indexBuffer.get(), sizeof(indices), indices);

	auto pipeline = context->CreateProgramPipeline();
	pipeline->SetVertexAttributesLayout(
		{
		IProgramPipeline::VertexAttribute { vtxBuffer, 2, EDataType::FLOAT32, false, 5 * sizeof(float) },
		IProgramPipeline::VertexAttribute { vtxBuffer, 3, EDataType::FLOAT32, false, 5 * sizeof(float) } 
		}
	);
	auto vertShader = context->CreateShader(EShaderStage::VERTEX, vertexSource);
	auto fragShader = context->CreateShader(EShaderStage::FRAGMENT, fragmentSource);
	pipeline->AttachShader(std::move(vertShader));
	pipeline->AttachShader(std::move(fragShader));

	context->SetClearColor(1, 0, 0, 1);

	DrawIndexedParams params;
	params.mode = EDrawMode::TRIANGLES;
	params.dataType = EDataType::UINT32;
	params.count = 6;
	params.instanceCount = 2;
	while (window->IsOpen())
	{
		window->PollEvents();

		context->Clear(lira::graphics::COLOR_BUFFER);
		
		context->BindIndexBuffer(indexBuffer.get());
		context->BindProgramPipeline(pipeline.get());
		context->Draw(params);
		context->SwapBuffers(window.get());
	}
}