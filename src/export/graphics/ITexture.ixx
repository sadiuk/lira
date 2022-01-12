export module lira.graphics.ITexture;
import lira.graphics.Common;
import lira.math.Types;
import std.core;

export namespace lira::graphics
{
	class ITexture
	{
	public:
		struct CreationParams
		{
			ETextureType type;
			uint32_t width;
			uint32_t height;
			uint32_t depth;
			uint32_t arrayLevels;
			ETextureFormat format;
			bool generateMipmaps;
		};
	protected:
		CreationParams creationParams;
	public:
		ITexture(CreationParams&& params) : creationParams(std::move(params)) {}
		virtual ~ITexture() = default;
	};
}