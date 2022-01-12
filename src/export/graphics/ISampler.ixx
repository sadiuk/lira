export module lira.graphics.ISampler;
import lira.graphics.Common;
import lira.math.Types;

export namespace lira::graphics
{
	class ISampler
	{
	public:
		struct CreationParams
		{
			ETextureMinFilter minFilter;
			ETextureMagFilter magFilter;
			ETextureWrapMode wrapS;
			ETextureWrapMode wrapT;
			ETextureWrapMode wrapR;
			lira::math::f4 borderColor;
		};
	protected:
		CreationParams creationParams;
	public:
		ISampler(CreationParams&& params) : creationParams(std::move(params)) {}
		virtual ~ISampler() = default;
	};
}