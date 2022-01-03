export module lira.fs.IFile;
import lira.core.Buffer;
import std.core;

export namespace lira::fs
{
	class IFile
	{
	public:
		enum ECreateFlags
		{
			READ = 1,
			WRITE = 2,
			CREATE_NEW = 4,
		};
		virtual std::string GetName() const = 0;
		virtual std::underlying_type_t<ECreateFlags> GetFlags() const = 0;
		virtual size_t GetSize() const = 0;

		virtual size_t Read(size_t pos, size_t size, void* buffer) = 0;
		virtual size_t Write(size_t pos, size_t size, const void* buffer) = 0;
		virtual size_t Read(size_t pos, size_t size, lira::core::Buffer& buffer) = 0;
		virtual size_t Write(size_t pos, size_t size, const lira::core::Buffer& buffer) = 0;

		virtual ~IFile() = default;
	};
}