export module lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.IBuffer;
import std.core;

export namespace lira::graphics
{
	class BufferOpenGL : public IBuffer
	{
		uint32_t m_id;
	public:
		BufferOpenGL();
		~BufferOpenGL() override;
		uint32_t GetId() const { return m_id; }
	};
}