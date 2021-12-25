export module lira.graphics.Common;

import std.core;
export namespace lira::graphics
{
	enum EDataType
	{
		INT8,
		UINT8,
		INT16,
		UINT116,
		INT32,
		UINT32,
	};
	enum EAPIType
	{
		OPENGL
	};
	enum EFBOAttachmentType : uint8_t
	{
		COLOR_BUFFER = 1,
		DEPTH_BUFFER = 2,
		STENCIL_BUFFER = 4
	};
	enum EShaderStage : uint8_t
	{
		VERTEX = 1,
		FRAGMENT = 2,
		TESSELATION_EVALUATION = 4,
		TESSELATION_CONTROL = 8,
		GEOMETRY = 16,
		COMPUTE = 32
	};
	enum EDrawMode : uint8_t
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


	struct DrawIndexedParams
	{
		EDrawMode mode;
		EDataType dataType; // the type of data stored in the index buffer
		uint32_t instanceCount = 1;
		uint32_t count;
		uint32_t offset = 0;
		uint32_t baseVertex = 0;
		uint32_t baseInstance = 0;
	};
}