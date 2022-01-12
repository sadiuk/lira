export module lira.graphics.platform.OpenGL.SamplerOpenGL;
import lira.graphics.ISampler;
import std.core;

export namespace lira::graphics
{
	class SamplerOpenGL : public ISampler
	{
		uint32_t m_id;
	public:
		SamplerOpenGL(CreationParams&& params);
		~SamplerOpenGL();
		uint32_t GetId() const { return m_id; uint32_t; }
	};
}