export module lira.graphics.IGraphicsContext;
import lira.ui.IWindow;
import lira.graphics.Common;
import lira.graphics.IShader;
import lira.graphics.IBuffer;

import std.memory;

export namespace lira::graphics
{
	class IGraphicsContext
	{
	public:
		struct CreationParams
		{
			EAPIType apiType;
			ui::IWindow* window;
		};
		
		static std::shared_ptr<IGraphicsContext> Create(const CreationParams& params);

		virtual void SwapBuffers(lira::ui::IWindow* window) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetClearDepth(float d) = 0;
		virtual void SetClearStencil(float s) = 0;
		virtual void Clear(std::underlying_type_t<EFBOAttachmentType> t) = 0;
		virtual void Draw(DrawIndexedParams&& params) = 0;


		virtual std::shared_ptr<IShader> CreateShader(EShaderStage stage, const std::string_view& source) = 0;
		
		virtual std::shared_ptr<IBuffer> CreateBuffer() = 0;
		virtual void AllocateBuffer(IBuffer* buffer, uint32_t sizeInBytes, const void* data = nullptr) = 0;
		virtual void FillBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, const void* data) = 0;
		virtual void MemsetBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, uint8_t data) = 0;
		
		virtual void BindVertexBuffer(IBuffer* buffer) = 0;
		virtual ~IGraphicsContext() = default;
		
	};
}
