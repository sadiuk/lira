#include <cstdlib>


import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import lira.graphics.IGraphicsContext;
import lira.fs.platform.std.FilesystemSTD;
import lira.fs.IFile;
import lira.math.Vector;
import lira.math.Types;
import lira.math.MathOperations;
import lira.math.CameraMath;
import lira.ui.IEventReceiver;
import lira.ui.KeyCodes;
import lira.core.Common;
import std.core;
import std.memory;	

import ModelLoader;

using namespace lira;
using namespace lira::graphics;
using namespace lira::ui;
using namespace lira::math;
using namespace lira::core;


class EventProcessor
{
	bool m_pressedKeys[KeyCode::KEY_COUNT];
	bool m_pressedMouseButtons[MouseButton::MOUSE_BUTTON_COUNT];
	float m_prevX, m_prevY, m_x, m_y;
	bool m_firstMove = true;
public:
	void SetKeyState(KeyCode code, KeyState state)
	{
		m_pressedKeys[code] = static_cast<bool>(state);
	}
	void SetMousePosition(float posX, float posY)
	{
		m_prevX = m_x;
		m_prevY = m_y;
		m_x = posX;
		m_y = posY;
		//std::cout << "{ " << m_x << " " << m_y << " }\n";

	}
	void SetMouseClick(MouseButton button, KeyState state)
	{
		m_pressedMouseButtons[button] = state;
		//std::cout << "MOUSE BUTTON CLICK: { " << m_x << " " << m_y << " }\n";
	}

	f2 GetMousePosition()
	{
		return f2(m_x, m_y);
	}
	bool IsKeyPressed(KeyCode code)
	{
		return m_pressedKeys[code];
	}
	bool isMouseButtonPressed(MouseButton button)
	{
		return m_pressedMouseButtons[button];
	}
};
class EventReceiver : public IEventReceiver
{
public:
	EventReceiver(IWindow* wnd, EventProcessor* processor) : IEventReceiver(wnd), m_processor(processor) {}
private:

	void OnKeyPressImpl(KeyCode key, KeyState state) override
	{
		m_processor->SetKeyState(key, state);
		//std::cout << "Key " << key << " " << (state ? "pressed" : "released") << "\n";
	}
	void OnMouseMoveImpl(double mouseX, double mouseY) override
	{
		m_processor->SetMousePosition(mouseX, mouseY);
	}
	void OnMouseButtonClickImpl(MouseButton button, KeyState state) override
	{
		m_processor->SetMouseClick(button, state);
	}
	EventProcessor* m_processor;
};

class Camera
{
	f3 m_position;
	f3 m_direction;
	ref_ptr<EventProcessor> m_processor;
	float m_moveSpeed;
	float m_mouseSensitivity;

	const f3 upHint = f3(0, 0, 1);

	f2 m_prevMousePos{0};
	f2 m_eulerAngles{0};

	bool m_firstMove = true;

	mat4f m_viewMatrix;
	mat4f m_projectionMatrix;
private:
	f2 GetRelativeMovement(f2 pos)
	{
		if (m_firstMove)
		{
			m_firstMove = false;
			m_prevMousePos = pos;
			return { 0 };
		}
		f2 diff = pos - m_prevMousePos;
		m_prevMousePos = pos;
		return diff;
	}
public:
	Camera(const ref_ptr<EventProcessor>& processor, float moveSpeed, float mouseSensitivity, const f3& pos, const f3& dir) : 
		m_processor(processor), m_position(pos), m_direction(dir),
		m_moveSpeed(moveSpeed), m_mouseSensitivity(mouseSensitivity)
	{
		UpdateMatrices();
	}
	void Update(float deltaTime)
	{
		m_direction.x = sin(m_eulerAngles.x) * cos(m_eulerAngles.y);
		m_direction.y = cos(m_eulerAngles.x);
		m_direction.z = sin(m_eulerAngles.x) * sin(m_eulerAngles.y);
		if (m_processor->IsKeyPressed(KEY_W))
		{
			m_position += m_direction * deltaTime * m_moveSpeed;
		}
		if (m_processor->IsKeyPressed(KEY_S))
		{
			m_position -= m_direction * deltaTime * m_moveSpeed;
		}
		if (m_processor->IsKeyPressed(KEY_A))
		{
			f3 left = cross(upHint, m_direction);
			m_position += left * deltaTime * m_moveSpeed;
		}
		if (m_processor->IsKeyPressed(KEY_D))
		{
			f3 right = cross(m_direction, upHint);
			m_position += right * deltaTime * m_moveSpeed;
		}
		
		if (m_processor->isMouseButtonPressed(MouseButton::LEFT_MOUSE_BUTTON))
		{
			f2 mousePos = m_processor->GetMousePosition();
			m_eulerAngles += GetRelativeMovement(mousePos) * m_mouseSensitivity;
			std::cout << "Direction: " << m_direction.x << " " << m_direction.y << " " << m_direction.z << "\n";
		}
		else
		{
			m_firstMove = true;
		}

		UpdateMatrices();
	}
	void UpdateMatrices()
	{
		m_viewMatrix = LookAt(m_position, m_direction, upHint);
		m_projectionMatrix = Perspective(60.f, 0.1f, 100.f, true);
		auto pos = m_viewMatrix * f4(0, 0, 0, 1);
		pos = m_projectionMatrix * pos;
		auto a = pos / pos.w;
	}
	const mat4f& GetViewMatrix() const
	{
		return m_viewMatrix;
	}
	const mat4f& GetProjMatrix() const
	{
		return m_projectionMatrix;
	}
};

float moveSpeed = 1;
float mouseSensitivity = 0.01;
f3 startPos(0, -1, 0);
f3 startDir(0, 1, 0);
int main()
{
	i2 v(1, 2);
	f2a va(1, 3);

	b2 b(true, false);
	f2 f(0.5, 0.6);
	auto k = dot(b, f);
	//bool same = std::is_same_v<std::vector, std::array>;
	lira::ui::IWindow::CreationParams wndParams; 
	wndParams.width = 1200;
	wndParams.height = 800;
	wndParams.caption = "Test";
	auto window = make_ref<lira::ui::WindowGLFW>(wndParams);
	auto eventProcessor = make_ref<EventProcessor>();
	auto receiver = make_ref<EventReceiver>(window.get(), eventProcessor.get());
	auto camera = make_ref<Camera>(eventProcessor, moveSpeed, mouseSensitivity, startPos, startDir);
	lira::graphics::IGraphicsContext::CreationParams ctxParams;
	ctxParams.apiType = lira::graphics::EAPIType::OPENGL;
	ctxParams.window = window.get();
	auto context = lira::graphics::IGraphicsContext::Create(ctxParams);

	//ModelLoader loader;
	//auto model = loader.LoadModel("../../media/sponza/sponza.obj");

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
	

	
	auto fs = make_ref<lira::fs::FilesystemSTD>();
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

	mat4f m4(1);
	m4 = Translate(m4, f3a(1, 2, 3));
	m4 = Scale(m4, f3a(1, 2, 3));

	auto rad = degrees(3.1415);
	while (window->IsOpen())
	{
		window->PollEvents();

		context->Clear((uint32_t)lira::graphics::EFBOAttachmentType::COLOR_BUFFER);
		
		auto viewMatrix = camera->GetViewMatrix();
		auto projMatrix = camera->GetProjMatrix();
		//f4 test(2, 0, 0, 1);
		//auto viewPos = viewMatrix * test;


		auto r = rand() / float(RAND_MAX);
		context->BindIndexBuffer(indexBuffer.get());
		context->BindGraphicsPipeline(pipeline.get());
		pipeline->SetUniform(IGraphicsPipeline::EStage::VERTEX, "rand", r);
		context->Draw(params);


		//context->BindComputePipeline(compPipeline.get());
		//context->Dispatch(64, 64, 1);

		camera->Update(1);
		context->SwapBuffers(window.get());
	}
}
extern "C" {  _declspec(dllexport) int NvOptimusEnablement = 0x00000001; }