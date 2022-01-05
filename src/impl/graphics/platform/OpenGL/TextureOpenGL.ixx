export module lira.graphics.platform.OpenGL.TextureOpenGL;
import lira.graphics.ITexture;

export namespace lira::graphics
{
	class TextureOpenGL : public ITexture
	{
		uint32_t m_id;
	public:
		TextureOpenGL(CreationParams&& params);
		~TextureOpenGL();
		uint32_t GetId() const { return m_id; uint32_t; }
	};
}