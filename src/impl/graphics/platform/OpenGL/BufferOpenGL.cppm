#include <glad/glad.h>
module lira.graphics.platform.OpenGL.BufferOpenGL;
import lira.graphics.platform.OpenGL.BufferOpenGL;

export namespace lira::graphics
{
	lira::graphics::BufferOpenGL::BufferOpenGL()
	{
		glGenBuffers(1, &m_id);
	}
	lira::graphics::BufferOpenGL::~BufferOpenGL()
	{
		glDeleteBuffers(1, &m_id);
	}
}