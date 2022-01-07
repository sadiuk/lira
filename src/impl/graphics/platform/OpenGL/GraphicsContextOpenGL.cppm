#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cassert>
module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsPipelineOpenGL;
import lira.graphics.platform.OpenGL.ComputePipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.platform.OpenGL.FramebufferOpenGL;
import lira.graphics.IGraphicsContext;
import lira.graphics.IGraphicsPipeline;
import lira.ui.platform.GLFW.WindowGLFW;
import std.core;
namespace lira::graphics
{
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data)
	{
		const char* _source;
		const char* _type;
		const char* _severity;

		switch (source) {
		case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW SYSTEM";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER COMPILER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			_source = "UNKNOWN";
			break;

		default:
			_source = "UNKNOWN";
			break;
		}

		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			_type = "ERROR";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UDEFINED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE";
			break;

		case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER";
			break;

		case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER";
			break;

		default:
			_type = "UNKNOWN";
			break;
		}

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			_severity = "HIGH";
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			_severity = "MEDIUM";
			break;

		case GL_DEBUG_SEVERITY_LOW:
			_severity = "LOW";
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			_severity = "NOTIFICATION";
			break;

		default:
			_severity = "UNKNOWN";
			break;
		}

		printf("%d: %s of %s severity, raised from %s: %s\n",
			id, _type, _severity, _source, msg);
	}

	GraphicsContextOpenGL::GraphicsContextOpenGL(const CreationParams& params)
	{
		glfwMakeContextCurrent(static_cast<ui::WindowGLFW*>(params.window)->GetNative());
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	}
	GraphicsContextOpenGL::~GraphicsContextOpenGL()
	{
		glfwMakeContextCurrent(nullptr);
	}
	void GraphicsContextOpenGL::BindGraphicsPipeline(IGraphicsPipeline* p)
	{
		auto nativePipeline = static_cast<GraphicsPipelineOpenGL*>(p);
		glBindVertexArray(nativePipeline->getVAOId());
		nativePipeline->BindAttachedBindings();
		glBindProgramPipeline(nativePipeline->getId());
	}
	void GraphicsContextOpenGL::BindComputePipeline(IComputePipeline* p)
	{
		auto nativePipeline = static_cast<ComputePipelineOpenGL*>(p);
		nativePipeline->BindAttachedBindings();
		glBindProgramPipeline(nativePipeline->getId());
	}
	void GraphicsContextOpenGL::BindIndexBuffer(IBuffer* b)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<BufferOpenGL*>(b)->GetId());
	}
	void GraphicsContextOpenGL::BindFramebuffer(IFramebuffer* fb, EAccessMode am)
	{
		auto fbNative = static_cast<FramebufferOpenGL*>(fb);
		glBindFramebuffer(GraphicsContextOpenGL::getNativeFramebufferAccessMode(am), fbNative->GetId());
	}
	void GraphicsContextOpenGL::SwapBuffers(lira::ui::IWindow* window)
	{
		glfwSwapBuffers(static_cast<ui::WindowGLFW*>(window)->GetNative());
	}
	void GraphicsContextOpenGL::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void GraphicsContextOpenGL::SetClearDepth(float d)
	{
		glClearDepthf(d);
	}
	void GraphicsContextOpenGL::SetClearStencil(float s)
	{
		glClearStencil(s);
	}
	void GraphicsContextOpenGL::Clear(std::underlying_type_t<EFBOAttachmentType> t)
	{
		glClear(getNativeAttachmentType(t));
	}
	void GraphicsContextOpenGL::Draw(const DrawIndexedParams& params)
	{
		uint32_t nativeMode = getNativeDrawingMode(params.mode);
		uint32_t nativeDataType = getNativeDataType(params.dataType);
		glDrawElementsInstancedBaseVertexBaseInstance(
			nativeMode,
			params.count,
			nativeDataType,
			nullptr,
			params.instanceCount,
			params.baseVertex,
			params.baseInstance
		);
	}
	void GraphicsContextOpenGL::Dispatch(uint32_t xCount, uint32_t yCount, uint32_t zCount)
	{
		glDispatchCompute(xCount, yCount, zCount);
	}
	std::shared_ptr<IFramebuffer> GraphicsContextOpenGL::CreateFramebuffer()
	{
		return std::make_shared<FramebufferOpenGL>();
	}
	std::shared_ptr<ITexture> GraphicsContextOpenGL::CreateTexture(ITexture::CreationParams&& params)
	{
		return std::make_shared<TextureOpenGL>(std::move(params));
	}
	std::shared_ptr<IShader> GraphicsContextOpenGL::CreateShader(EShaderStage s, const std::string_view& source)
	{
		return std::make_shared<ShaderOpenGL>(s, source);
	}
	std::shared_ptr<IBuffer> GraphicsContextOpenGL::CreateBuffer()
	{
		return std::make_shared<BufferOpenGL>();
	}
	std::shared_ptr<IGraphicsPipeline> GraphicsContextOpenGL::CreateGraphicsPipeline()
	{
		return std::make_shared<GraphicsPipelineOpenGL>();
	}
	std::shared_ptr<IComputePipeline> GraphicsContextOpenGL::CreateComputePipeline()
	{
		return std::make_shared<ComputePipelineOpenGL>();
	}
	void GraphicsContextOpenGL::AllocateBuffer(IBuffer* buffer, uint32_t sizeInBytes, const void* data)
	{
		auto* native_ptr = static_cast<BufferOpenGL*>(buffer);
		glNamedBufferData(native_ptr->GetId(), sizeInBytes, data, GL_STATIC_DRAW); // TODO: add HINT param ??
	}
	void GraphicsContextOpenGL::FillBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, const void* data)
	{
		auto* native_ptr = static_cast<BufferOpenGL*>(buffer);
		glNamedBufferSubData(native_ptr->GetId(), offset, size, data);
	}
	void GraphicsContextOpenGL::MemsetBufferSubdata(IBuffer* buffer, uint32_t offset, uint32_t size, uint8_t data)
	{
		auto* native_ptr = static_cast<BufferOpenGL*>(buffer);
		glClearNamedBufferData(native_ptr->GetId(), GL_R8UI, GL_R8UI, GL_UNSIGNED_BYTE, &data);
	}
	uint32_t GraphicsContextOpenGL::getNativeAttachmentType(std::underlying_type_t<EFBOAttachmentType> t)
	{
		uint32_t res = 0;
		if (t & (uint8_t)EFBOAttachmentType::COLOR_BUFFER)
		{
			res |= GL_COLOR_BUFFER_BIT;
		}
		if (t & (uint8_t)EFBOAttachmentType::DEPTH_BUFFER)
		{
			res |= GL_DEPTH_BUFFER_BIT;
		}
		if (t & (uint8_t)EFBOAttachmentType::STENCIL_BUFFER)
		{
			res |= GL_STENCIL_BUFFER_BIT;
		}
		return res;
	}
	uint32_t GraphicsContextOpenGL::getNativeShaderStage(EShaderStage s)
	{
		switch (s)
		{
			case EShaderStage::VERTEX:
			{
				return GL_VERTEX_SHADER;
			}
			case EShaderStage::FRAGMENT:
			{
				return GL_FRAGMENT_SHADER;
			}
			case EShaderStage::TESSELATION_EVALUATION:
			{
				return GL_TESS_EVALUATION_SHADER;
			}
			case EShaderStage::TESSELATION_CONTROL:
			{
				return GL_TESS_CONTROL_SHADER;
			}
			case EShaderStage::GEOMETRY:
			{
				return GL_GEOMETRY_SHADER;
			}
			case EShaderStage::COMPUTE:
			{
				return GL_COMPUTE_SHADER;
			}
		}
		assert(false);
	}
	uint32_t GraphicsContextOpenGL::getNativeDrawingMode(EDrawMode mode)
	{
		switch (mode)
		{
		case EDrawMode::POINTS:						return GL_POINTS;
		case EDrawMode::LINE_STRIP:					return GL_LINE_STRIP;
		case EDrawMode::LINE_LOOP:					return GL_LINE_LOOP;
		case EDrawMode::LINES:						return GL_LINES;
		case EDrawMode::LINE_STRIP_ADJACENCY:		return GL_LINE_STRIP_ADJACENCY;
		case EDrawMode::LINES_ADJACENCY:			return GL_LINES_ADJACENCY;
		case EDrawMode::TRIANGLE_STRIP:				return GL_TRIANGLE_STRIP;
		case EDrawMode::TRIANGLE_FAN:				return GL_TRIANGLE_FAN;
		case EDrawMode::TRIANGLES:					return GL_TRIANGLES;
		case EDrawMode::TRIANGLE_STRIP_ADJACENCY:	return GL_TRIANGLE_STRIP_ADJACENCY;
		case EDrawMode::TRIANGLES_ADJACENCY:		return GL_TRIANGLES_ADJACENCY;
		case EDrawMode::PATCHES:					return GL_PATCHES;
		default:
			assert(false);
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeDataType(EDataType dt)
	{
		switch (dt)
		{
		case EDataType::INT8:		return GL_BYTE;
		case EDataType::UINT8:		return GL_UNSIGNED_BYTE;
		case EDataType::INT16:		return GL_SHORT;
		case EDataType::UINT116:	return GL_UNSIGNED_SHORT;
		case EDataType::INT32:		return GL_INT;
		case EDataType::UINT32:		return GL_UNSIGNED_INT;
		case EDataType::FLOAT32:	return GL_FLOAT;
		case EDataType::FLOAT64:	return GL_DOUBLE;
		default:
			assert(false); // TODO other type enums
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeTextureType(ETextureType t)
	{
		switch (t)
		{
		case ETextureType::TEXTURE_1D:
		{
			return GL_TEXTURE_1D;
		}
		case ETextureType::TEXTURE_2D:
		{

			return GL_TEXTURE_2D;
		}
		case ETextureType::TEXTURE_3D:
		{
			return GL_TEXTURE_3D;
		}
		case ETextureType::TEXTURE_CUBE_MAP:
		{
			return GL_TEXTURE_CUBE_MAP;
		}
		case ETextureType::TEXTURE_2D_MULTISAMPLE:
		{
			return GL_TEXTURE_2D_MULTISAMPLE;
		}
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeTextureMinFilter(ETextureMinFilter f)
	{
		switch (f)
		{
		case ETextureMinFilter::NEAREST:				return GL_NEAREST;
		case ETextureMinFilter::LINEAR:					return GL_LINEAR;
		case ETextureMinFilter::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
		case ETextureMinFilter::NEAREST_MIPMAP_LINEAR:	return GL_NEAREST_MIPMAP_LINEAR;
		case ETextureMinFilter::LINEAR_MIPMAP_LINEAR:	return GL_LINEAR_MIPMAP_LINEAR;
		case ETextureMinFilter::LINEAR_MIPMAP_NEAREST:	return GL_LINEAR_MIPMAP_NEAREST;
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeTextureMagFilter(ETextureMagFilter f)
	{
		switch (f)
		{
		case ETextureMagFilter::NEAREST:	return GL_NEAREST;
		case ETextureMagFilter::LINEAR:		return GL_LINEAR;
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeTextureWrapMode(ETextureWrapMode m)
	{
		switch (m)
		{
		case ETextureWrapMode::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case ETextureWrapMode::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
		case ETextureWrapMode::REPEAT:			return GL_REPEAT;
		case ETextureWrapMode::MIRROR:			return GL_MIRRORED_REPEAT;
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeTextureFormat(ETextureFormat f)
	{
		switch (f)
		{
		case ETextureFormat::R8_UNORM:		return GL_R8;
		case ETextureFormat::R8_SNORM:		return GL_R8_SNORM;
		case ETextureFormat::R16_UNORM:		return GL_R16;
		case ETextureFormat::R16_SNORM:		return GL_R16_SNORM;
		case ETextureFormat::RG8_UNORM:		return GL_RG8;
		case ETextureFormat::RG8_SNORM:		return GL_RG8_SNORM;
		case ETextureFormat::RG16_UNORM:	return GL_RG16;
		case ETextureFormat::RG16_SNORM:	return GL_RG16_SNORM;
		case ETextureFormat::RGB8_UNORM:	return GL_RGB8;
		case ETextureFormat::RGB8_SNORM:	return GL_RGB8_SNORM;
		case ETextureFormat::RGB16_UNORM:	return GL_RGB16;
		case ETextureFormat::RGB16_SNORM:	return GL_RGB16_SNORM;
		case ETextureFormat::RGBA8_UNORM:	return GL_RGBA8;
		case ETextureFormat::RGBA8_SNORM:	return GL_RGBA8_SNORM;
		case ETextureFormat::RGBA16_UNORM:	return GL_RGBA16;
		case ETextureFormat::RGBA16_SNORM:	return GL_RGBA16_SNORM;
		case ETextureFormat::SRGB8_UNORM:	return GL_SRGB8;
		case ETextureFormat::SRGBA8_UNORM:	return GL_SRGB8_ALPHA8;
		case ETextureFormat::R32_F:			return GL_R32F;
		case ETextureFormat::RG32_F:		return GL_RG32F;
		case ETextureFormat::RGB32_F:		return GL_RGB32F;
		case ETextureFormat::RGBF32_F:		return GL_RGBA32F;
		default: assert(false);
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeAccessMode(EAccessMode f)
	{
		switch (f)
		{
		case EAccessMode::READ: return GL_READ_ONLY;
		case EAccessMode::WRITE: return GL_WRITE_ONLY;
		case EAccessMode::READ_WRITE: return GL_READ_WRITE;
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeFramebufferAccessMode(EAccessMode f)
	{
		switch (f)
		{
		case EAccessMode::READ: return GL_READ_FRAMEBUFFER;
		case EAccessMode::WRITE: return GL_DRAW_FRAMEBUFFER;
		case EAccessMode::READ_WRITE: return GL_FRAMEBUFFER;
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeFBOAttachment(EFBOAttachment a)
	{
		switch (a)
		{
		case COLOR_0: return GL_COLOR_ATTACHMENT0;
		case COLOR_1: return GL_COLOR_ATTACHMENT1;
		case DEPTH: return GL_DEPTH_ATTACHMENT;
		case STENCIL: return GL_STENCIL_ATTACHMENT;
		}
	}
}