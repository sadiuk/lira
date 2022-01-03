export module lira.core.Buffer;
import lira.core.Common;
import std.core;

export namespace lira::core
{
	class Buffer
	{
		std::byte* m_buffer = nullptr;
		size_t m_size = 0;
	public:
		std::byte* Get()
		{
			return m_buffer;
		}
		const std::byte* Get() const
		{
			return m_buffer;
		}
		size_t GetSize() const
		{
			return m_size;
		}
		Buffer() = default;
		Buffer(size_t size, char fill = 0) : m_size(size)
		{
			m_buffer = (std::byte*)malloc(size);
			memset(m_buffer, fill, m_size);
		}
		Buffer(std::byte* data, size_t size) : m_buffer(data), m_size(size)
		{
		
		}
		~Buffer()
		{
			if(m_buffer)
				free(m_buffer);
		}

		void Reallocate(size_t size)
		{
			if (m_buffer)
				realloc(m_buffer, size);
			else m_buffer = (std::byte*)malloc(size);
		}
	};
}