#include <cstdlib>
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;
import lira.fs.platform.std.FilesystemSTD;
import lira.fs.IFile;
import lira.math.Vector;
import lira.math.Types;
import lira.math.MathOperations;
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

	auto pipeline = context->CreateGraphicsPipeline();
	pipeline->SetVertexAttributesLayout(
		{
		IGraphicsPipeline::VertexAttribute { vtxBuffer, 2, EDataType::FLOAT32, false, 5 * sizeof(float) },
		IGraphicsPipeline::VertexAttribute { vtxBuffer, 3, EDataType::FLOAT32, false, 5 * sizeof(float) } 
		}
	);
	
	auto fs = std::make_shared<lira::fs::FilesystemSTD>();
	auto vertexFile = fs->CreateFile("vertex.vert", lira::fs::IFile::ECreateFlags::READ);
	auto fragmentFile = fs->CreateFile("fragment.frag", lira::fs::IFile::ECreateFlags::READ);
	lira::core::Buffer vertexSource(vertexFile->GetSize() + 1);
	lira::core::Buffer fragmentSource(fragmentFile->GetSize() + 1);
	vertexFile->Read(0, vertexFile->GetSize(), vertexSource);
	fragmentFile->Read(0, fragmentFile->GetSize(), fragmentSource);

	auto vertShader = context->CreateShader(EShaderStage::VERTEX, (const char*)vertexSource.Get());
	auto fragShader = context->CreateShader(EShaderStage::FRAGMENT, (const char*)fragmentSource.Get());
	pipeline->AttachShader(std::move(vertShader));
	pipeline->AttachShader(std::move(fragShader));

	auto computeFile = fs->CreateFile("compute.comp", lira::fs::IFile::ECreateFlags::READ);
	lira::core::Buffer computeSource(computeFile->GetSize() + 1);
	computeFile->Read(0, computeFile->GetSize(), computeSource);
	auto compPipeline = context->CreateComputePipeline();
	auto compShader = context->CreateShader(EShaderStage::COMPUTE, (const char*)computeSource.Get());
	compPipeline->AttachShader(std::move(compShader));
	
	//compPipeline->

	context->SetClearColor(1, 0, 0, 1);

	DrawIndexedParams params;
	params.mode = EDrawMode::TRIANGLES;
	params.dataType = EDataType::UINT32;
	params.count = 6;
	params.instanceCount = 2;
	params.enableDepthTesting = false;
	
	ITexture::CreationParams texParams;
	texParams.type = ETextureType::TEXTURE_2D;
	texParams.minFilter = ETextureMinFilter::LINEAR;
	texParams.magFilter = ETextureMagFilter::LINEAR;
	texParams.wrapS = ETextureWrapMode::CLAMP_TO_EDGE;
	texParams.wrapT = ETextureWrapMode::CLAMP_TO_EDGE;
	texParams.format = ETextureFormat::SRGBA8_UNORM;
	texParams.width = 600;
	texParams.height = 400;
	texParams.arrayLevels = 1;
	texParams.generateMipmaps = true;
	auto texture = context->CreateTexture(ITexture::CreationParams(texParams));

	auto fbo = context->CreateFramebuffer();
	fbo->AttachTexture(texture, EFBOAttachment::COLOR_0);
	context->BindFramebuffer(fbo.get(), EAccessMode::READ_WRITE);

	IPipeline::ShaderBinding texBinding;
	texBinding.unit = 0;
	texBinding.bindingType = EShaderBindingType::IMAGE_TEXTURE;
	texBinding.imageParams.texture = texture.get();
	texBinding.imageParams.layered = false;
	texBinding.imageParams.arrayLayer = 0;
	texBinding.imageParams.mipmapLevel = 0;
	texBinding.imageParams.accessMode = EAccessMode::READ_WRITE;
	texBinding.imageParams.textureFormat = ETextureFormat::RGBA8_SNORM;

	compPipeline->SetShaderBindingLayout(std::vector<IPipeline::ShaderBinding>{
		texBinding
	});

	float r = 1;
	context->Clear((uint32_t)lira::graphics::EFBOAttachmentType::COLOR_BUFFER);
	context->BindIndexBuffer(indexBuffer.get());
	context->BindGraphicsPipeline(pipeline.get());
	pipeline->SetUniform(IGraphicsPipeline::EStage::VERTEX, "rand", r);
	context->Draw(params);
	context->BindFramebuffer(nullptr, EAccessMode::READ_WRITE);

	mat3x2f m1;
	mat2x3f m2;
	m1[0] = f2a(1, 4);
	m1[1] = f2a(2, 5);
	m1[2] = f2a(3, 6);

	m2[0] = f3a(1, 2, 3);
	m2[1] = f3a(4, 5, 6);


	mat2f test1(1), test2(1);
	auto a = test1 * test2;
	auto m3 = m1 * m2;

	while (window->IsOpen())
	{
		window->PollEvents();

		context->Clear((uint32_t)lira::graphics::EFBOAttachmentType::COLOR_BUFFER);
		
		auto r = rand() / float(RAND_MAX);
		context->BindIndexBuffer(indexBuffer.get());
		context->BindGraphicsPipeline(pipeline.get());
		pipeline->SetUniform(IGraphicsPipeline::EStage::VERTEX, "rand", r);
		context->Draw(params);


		//context->BindComputePipeline(compPipeline.get());
		//context->Dispatch(64, 64, 1);

		context->SwapBuffers(window.get());
	}
}
extern "C" {  _declspec(dllexport) int NvOptimusEnablement = 0x00000001; }