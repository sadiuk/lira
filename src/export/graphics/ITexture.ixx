export module lira.graphics.ITexture;
import lira.graphics.Common;
import lira.math.Types;

export namespace lira::graphics
{
	class ITexture
	{
	public:
		struct CreationParams
		{
			ETextureType type;
			ETextureMinFilter minFilter;
			ETextureMagFilter magFilter;
			ETextureWrapMode wrapS;
			ETextureWrapMode wrapT;
			ETextureWrapMode wrapR;
			ETextureFormat format;
			lira::math::f4 borderColor;
			uint32_t width;
			uint32_t height;
			uint32_t depth;
			uint32_t arrayLevels;
			bool generateMipmaps;

		};
	protected:
		CreationParams creationParams;
	public:
		ITexture(CreationParams&& params) : creationParams(std::move(params)) {}
		virtual ~ITexture() = default;
	};
}