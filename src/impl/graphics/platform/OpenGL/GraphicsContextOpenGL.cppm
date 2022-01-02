#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cassert>
module lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsContextOpenGL;
import lira.graphics.platform.OpenGL.GraphicsPipelineOpenGL;
import lira.graphics.platform.OpenGL.ComputePipelineOpenGL;
import lira.graphics.platform.OpenGL.ShaderOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;
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
		glBindProgramPipeline(nativePipeline->getId());
	}
	void GraphicsContextOpenGL::BindComputePipeline(IComputePipeline* p)
	{
		auto nativePipeline = static_cast<ComputePipelineOpenGL*>(p);
		glBindProgramPipeline(nativePipeline->getId());
	}
	void GraphicsContextOpenGL::BindIndexBuffer(IBuffer* b)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<BufferOpenGL*>(b)->GetId());
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
	std::shared_ptr<IShader> GraphicsContextOpenGL::CreateShader(EShaderStage s, const std::string_view& source)
	{
		return std::make_shared<ShaderOpenGL>(s, source);
	}
	std::shared_ptr<IBuffer> GraphicsContextOpenGL::CreateBuffer()
	{
		return std::make_shared<BufferOpenGL>();
	}
	std::shared_ptr<IGraphicsPipeline> GraphicsContextOpenGL::CreateProgramPipeline()
	{
		return std::make_shared<GraphicsPipelineOpenGL>();
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
		if (t & EFBOAttachmentType::COLOR_BUFFER)
		{
			res |= GL_COLOR_BUFFER_BIT;
		}
		if (t & EFBOAttachmentType::DEPTH_BUFFER)
		{
			res |= GL_DEPTH_BUFFER_BIT;
		}
		if (t & EFBOAttachmentType::STENCIL_BUFFER)
		{
			res |= GL_STENCIL_BUFFER_BIT;
		}
		return res;
	}
	uint32_t GraphicsContextOpenGL::getNativeShaderStage(EShaderStage s)
	{
		switch (s)
		{
			case VERTEX:
			{
				return GL_VERTEX_SHADER;
			}
			case FRAGMENT:
			{
				return GL_FRAGMENT_SHADER;
			}
			case TESSELATION_EVALUATION:
			{
				return GL_TESS_EVALUATION_SHADER;
			}
			case TESSELATION_CONTROL:
			{
				return GL_TESS_CONTROL_SHADER;
			}
			case GEOMETRY:
			{
				return GL_GEOMETRY_SHADER;
			}
			case COMPUTE:
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
		case POINTS: return GL_POINTS;
		case LINE_STRIP: return GL_LINE_STRIP;
		case LINE_LOOP: return GL_LINE_LOOP;
		case LINES: return GL_LINES;
		case LINE_STRIP_ADJACENCY: return GL_LINE_STRIP_ADJACENCY;
		case LINES_ADJACENCY: return GL_LINES_ADJACENCY;
		case TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
		case TRIANGLE_FAN: return GL_TRIANGLE_FAN;
		case TRIANGLES: return GL_TRIANGLES;
		case TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
		case TRIANGLES_ADJACENCY: return GL_TRIANGLES_ADJACENCY;
		case PATCHES: return GL_PATCHES;
		default:
			assert(false);
		}
	}
	uint32_t GraphicsContextOpenGL::getNativeDataType(EDataType dt)
	{
		switch (dt)
		{
		case INT8: return GL_BYTE;
		case UINT8: return GL_UNSIGNED_BYTE;
		case INT16: return GL_SHORT;
		case UINT116: return GL_UNSIGNED_SHORT;
		case INT32: return GL_INT;
		case UINT32: return GL_UNSIGNED_INT;
		case FLOAT32: return GL_FLOAT;
		case FLOAT64: return GL_DOUBLE;
		default:
			assert(false); // TODO other type enums
		}
	}
}