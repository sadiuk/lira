export module lira.graphics.IPipeline;
import lira.graphics.IShader;
import lira.graphics.IBuffer;
import lira.graphics.ITexture;
import lira.graphics.ISampler;
import lira.graphics.Common;
import lira.math.Types;
import std.core;
import std.memory;

export namespace lira::graphics
{
	class IPipeline
	{
	public:
		struct ShaderBinding
		{
			ShaderBinding() {}
			struct BufferBindingParams
			{
				IBuffer* buffer = nullptr;
			};
			struct ImageBindingParams
			{
				ITexture* texture = nullptr;
				bool layered = false;
				uint32_t arrayLayer = 0;
				uint32_t mipmapLevel = 0;
				EAccessMode accessMode = EAccessMode::READ;
				ETextureFormat textureFormat = ETextureFormat::RGBA8_UNORM;
			};
			struct SamplerBindingParams
			{
				ISampler* sampler;
				ITexture* texture;
			};
			uint32_t unit = 0;
			EShaderBindingType bindingType;
			union
			{
				//TODO: Ref<Buffer>, Ref<Texture>
				BufferBindingParams bufferParams;
				ImageBindingParams imageParams;
				SamplerBindingParams samplerParams;
			};
			//TODO: shared_ptr<Sampler> sampler;
		};
		virtual void SetShaderBindingLayout(const std::vector<ShaderBinding>& layout) = 0;
		virtual void AttachShader(std::shared_ptr<IShader>&& shader) = 0;
	};
}