#include <cstdio>
export module lira.fs.platform.std.FileSTD;
import lira.fs.IFile;
import lira.core.Buffer;
import std.core;


export namespace lira::fs
{
	class FileSTD : public IFile
	{
		std::string m_name;
		std::underlying_type_t<ECreateFlags> m_flags;
		FILE* m_handle;
		bool m_createdProperly = true;
	public:
		FileSTD(const std::string_view& name, std::underlying_type_t<ECreateFlags> flags) :
			m_name(name), m_flags(flags)
		{
			const char* mode;
			if ((flags & (ECreateFlags::WRITE | ECreateFlags::READ)) == (ECreateFlags::WRITE | ECreateFlags::READ))
			{
				if (flags & ECreateFlags::CREATE_NEW)
				{
					mode = "wb+";
				}
				else
				{
					mode = "rb+";
				}
			}
			else if(flags & ECreateFlags::READ)
			{
				mode = "rb";
			}
			else if (flags & ECreateFlags::WRITE)
			{
				mode = "wb";
			}

			m_handle = fopen(m_name.data(), mode);

			if (!m_handle)
			{
				m_createdProperly = false;
			}
		}
		static std::shared_ptr<FileSTD> Create(const std::string_view& name, std::underlying_type_t<ECreateFlags> flags)
		{
			auto res = std::make_shared<FileSTD>(name, flags);
			if (!res->m_createdProperly) return nullptr;
			return res;
		}

		std::string GetName() const override
		{
			return m_name;
		}
		std::underlying_type_t<ECreateFlags> GetFlags() const override
		{
			return m_flags;
		}
		size_t GetSize() const override
		{
			fseek(m_handle, 0L, SEEK_END);
			return ftell(m_handle);
		}

		size_t Read(size_t pos, size_t size, void* buffer) override
		{
			fseek(m_handle, pos, SEEK_SET);
			return fread(buffer, 1, size, m_handle);
		}
		size_t Write(size_t pos, size_t size, const void* buffer) override
		{
			fseek(m_handle, pos, SEEK_SET);
			return fwrite(buffer, 1, size, m_handle);
		}
		size_t Read(size_t pos, size_t size, lira::core::Buffer& buffer) override
		{
			fseek(m_handle, pos, SEEK_SET);
			auto count = fread(buffer.Get(), 1, size, m_handle);
			return count;
		}
		size_t Write(size_t pos, size_t size, const lira::core::Buffer& buffer) override
		{
			fseek(m_handle, pos, SEEK_SET);
			auto count = fwrite(buffer.Get(), 1, size, m_handle);
			return count;
		}

		~FileSTD()
		{
			fclose(m_handle);
		}
	};
}