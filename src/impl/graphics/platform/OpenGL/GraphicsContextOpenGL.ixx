export module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.IGraphicsContext;
import lira.thread.IThreadRequestProcessor;
import lira.ui.IWindow;
import lira.ui.platform.GLFW.WindowGLFW;
import std.core;
import std.memory;

export namespace lira::graphics
{
	class GraphicsContextOpenGL : public IGraphicsContext
	{
	public:
		GraphicsContextOpenGL(const CreationParams& params);
		~GraphicsContextOpenGL() override;

		void BindGraphicsPipeline(IGraphicsPipeline* p) override;
		void BindComputePipeline(IComputePipeline* p) override;
		void BindIndexBuffer(IBuffer*) override;

		void SwapBuffers(lira::ui::IWindow* window) override;
		void SetClearColor(float r, float g, float b, float a) override;
		void SetClearDepth(float d) override;
		void SetClearStencil(float s) override;
		void Clear(std::underlying_type_t<EFBOAttachmentType> t) override;
		void Draw(const DrawIndexedParams& params) override;
		void Dispatch(uint32_t xCount, uint32_t yCount, uint32_t zCount) override;

		std::shared_ptr<ITexture> CreateTexture(ITexture::CreationParams&& params) override;
		std::shared_ptr<IShader> CreateShader(EShaderStage stage, const std::string_view& source) override;
		std::shared_ptr<IBuffer> CreateBuffer() override;
		std::shared_ptr<IGraphicsPipeline> CreateGraphicsPipeline() override;
		std::shared_ptr<IComputePipeline>  CreateComputePipeline() override;

		void AllocateBuffer(IBuffer* buffer, uint32_t sizeInBytes, const void* data = nullptr) override;
		void FillBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, const void* data) override;
		void MemsetBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, uint8_t data) override;


	private:
		uint32_t getNativeAttachmentType(std::underlying_type_t<EFBOAttachmentType> t);
	public:
		static uint32_t getNativeShaderStage(EShaderStage s);
		static uint32_t getNativeDrawingMode(EDrawMode mode);
		static uint32_t getNativeDataType(EDataType dt);
		static uint32_t getNativeTextureType(ETextureType t);
		static uint32_t getNativeTextureMinFilter(ETextureMinFilter f);
		static uint32_t getNativeTextureMagFilter(ETextureMagFilter f);
		static uint32_t getNativeTextureWrapMode(ETextureWrapMode m);
		static uint32_t getNativeTextureFormat(ETextureFormat f);
		static uint32_t getNativeAccessMode(EAccessMode f);
	};
}

