#include <cassert>
export module lira.graphics.Common;
import lira.math.Types;
import std.core;
export namespace lira::graphics
{
	enum class EDataType
	{
		INT8,
		UINT8,
		INT16,
		UINT116,
		INT32,
		UINT32,
		FLOAT32,
		FLOAT64,
	};
	enum class EAPIType
	{
		OPENGL
	};
	enum class EFBOAttachmentType : uint32_t
	{
		COLOR_BUFFER = 1,
		DEPTH_BUFFER = 2,
		STENCIL_BUFFER = 4
	};
	enum class EShaderStage : uint8_t
	{
		VERTEX = 1,
		FRAGMENT = 2,
		TESSELATION_EVALUATION = 4,
		TESSELATION_CONTROL = 8,
		GEOMETRY = 16,
		COMPUTE = 32
	};
	enum class EDrawMode : uint8_t
	{
		POINTS,
		LINE_STRIP,
		LINE_LOOP,
		LINES,
		LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY,
		PATCHES
	};
	enum class ETextureType
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_CUBE_MAP,
		TEXTURE_2D_MULTISAMPLE,
	};
	enum class ETextureMinFilter
	{
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST
	};
	enum class ETextureMagFilter
	{
		NEAREST,
		LINEAR
	};
	enum class ETextureWrapMode
	{
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		REPEAT,
		MIRROR
	};
	//TODO Add all when needed
	enum class ETextureFormat
	{
		R8_UNORM,
		R8_SNORM,
		R16_UNORM,
		R16_SNORM,
		RG8_UNORM,
		RG8_SNORM,
		RG16_UNORM,
		RG16_SNORM,
		RGB8_UNORM,
		RGB8_SNORM,
		RGB16_UNORM,
		RGB16_SNORM,
		RGBA8_UNORM,
		RGBA8_SNORM,
		RGBA16_UNORM,
		RGBA16_SNORM,
		SRGB8_UNORM,
		SRGBA8_UNORM,
		R32_F,
		RG32_F,
		RGB32_F,
		RGBF32_F,
	};
	enum class EShaderBindingType
	{
		SHADER_STORAGE_BUFFER,
		UNIFORM_BUFFER,
		ATOMIC_COUNTER_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER,
		SAMPLER,
		IMAGE_TEXTURE
	};
	enum class EAccessMode
	{
		READ,
		WRITE,
		READ_WRITE,
	};
	enum class EAttachmentTarget
	{
		TEXTURE_2D,
		CUBE_MAP_PLUS_X,
		CUBE_MAP_MINUS_X,
		CUBE_MAP_PLUS_Y,
		CUBE_MAP_MINUS_Y,
		CUBE_MAP_PLUS_Z,
		CUBE_MAP_MINUS_Z,
	};
	enum EFBOAttachment
	{
		COLOR_0,
		COLOR_1,
		DEPTH,
		STENCIL
	};




	struct DrawIndexedParams
	{
		EDrawMode mode;
		EDataType dataType; // the type of data stored in the index buffer
		uint32_t instanceCount = 1;
		uint32_t count;
		uint32_t offset = 0;
		uint32_t baseVertex = 0;
		uint32_t baseInstance = 0;
		bool enableDepthTesting = true;
	};


	uint32_t getTypeSize(EDataType t)
	{
		switch (t)
		{
		case EDataType::INT8: [[fallthrough]];
		case EDataType::UINT8: return 1;
		case EDataType::INT16: [[fallthrough]];
		case EDataType::UINT116: return 2;
		case EDataType::INT32: [[fallthrough]];
		case EDataType::FLOAT32: [[fallthrough]];
		case EDataType::UINT32: return 4;
		case EDataType::FLOAT64: return 8;
		}
		assert(false);
		return 0;
	}
}