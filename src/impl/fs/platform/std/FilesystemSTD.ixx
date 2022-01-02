export module lira.fs.platform.std.FilesystemSTD;
import lira.fs.IFilesystem;
import lira.fs.IFile;
import lira.fs.platform.std.FileSTD;
import std.core;

export namespace lira::fs
{
	class FilesystemSTD : public IFilesystem
	{
	public:
		virtual std::shared_ptr<IFile> CreateFile(const std::string& name, IFile::ECreateFlags flags) override
		{
			return FileSTD::Create(name, flags);
		}
	};
}