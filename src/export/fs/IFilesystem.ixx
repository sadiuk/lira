export module lira.fs.IFilesystem;
import lira.fs.IFile;
import std.core;

export namespace lira::fs
{
	class IFilesystem
	{
	public:
		virtual std::shared_ptr<IFile> CreateFile(const std::string& name, IFile::ECreateFlags flags) = 0;
	};
}