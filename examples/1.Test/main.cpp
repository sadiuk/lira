#include <cstdlib>
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;
import lira.fs.platform.std.FilesystemSTD;
import lira.fs.IFile;
import lira.math.Vector;
import lira.math.Types;
import std.core;
import std.memory;

using namespace lira::graphics;

int main()
{
	using namespace lira::math;
	i2 v(1, 2);
	f2a va(1, 3);

	b2 b(true, false);
	f2 f(0.5, 0.6);
	auto k = dot(b, f);
	//bool same = std::is_same_v<std::vector, std::array>;
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
		 0,    0.5, 0, 0, 1,
		 0,   -0.5, 0, 1, 1,
	};
	uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
	auto vtxBuffer = context->CreateBuffer();
	context->AllocateBuffer(vtxBuffer.get(), sizeof(vtc), vtc);
	auto indexBuffer = context->CreateBuffer();
	context->AllocateBuffer(indexBuffer.get(), sizeof(indices), indices);

	auto pipeline = context->CreateProgramPipeline();
	pipeline->SetVertexAttributesLayout(
		{
		IGraphicsPipeline::VertexAttribute { vtxBuffer, 2, EDataType::FLOAT32, false, 5 * sizeof(float) },
		IGraphicsPipeline::VertexAttribute { vtxBuffer, 3, EDataType::FLOAT32, false, 5 * sizeof(float) } 
		}
	);
	
	auto a = strlen(R"(#version 460 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;
layout(location = 0) out vec3 fragColor;

uniform float rand;
out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main()
{
	fragColor = color * rand;
	gl_Position = vec4(pos.x + 0.5 * gl_InstanceID, pos.y, 0, 1);
})");
	auto fs = std::make_shared<lira::fs::FilesystemSTD>();
	auto vertexFile = fs->CreateFile("C:/dev/lira/examples/1.Test/vertex.vert", lira::fs::IFile::ECreateFlags::READ);
	auto fragmentFile = fs->CreateFile("C:/dev/lira/examples/1.Test/fragment.frag", lira::fs::IFile::ECreateFlags::READ);
	char* vertexSource = new char[vertexFile->GetSize() + 1];
	char* fragmentSource = new char[fragmentFile->GetSize() + 1];
	vertexSource[vertexFile->GetSize()] = '\0';
	fragmentSource[fragmentFile->GetSize()] = '\0';
	vertexFile->Read(0, vertexFile->GetSize(), vertexSource);
	fragmentFile->Read(0, fragmentFile->GetSize(), fragmentSource);

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
		
		auto r = rand() / float(RAND_MAX);
		context->BindIndexBuffer(indexBuffer.get());
		context->BindProgramPipeline(pipeline.get());
		pipeline->SetUniform(IGraphicsPipeline::EStage::VERTEX, "rand", r);
		context->Draw(params);
		context->SwapBuffers(window.get());
	}
}