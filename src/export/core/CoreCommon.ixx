#include <stdlib.h>
#ifdef _MSC_VER
#include "malloc.h"
#endif
export module lira.core.Common;
import std.core;

export namespace lira::core
{
	template<typename T>
	using ref_ptr = std::shared_ptr<T>;

	template<typename T, typename ... A>
	auto make_ref(A ... args) { return std::make_shared<T>(std::forward<A>(args)...); };

	void* AlignedAlloc(uint32_t alignment, size_t size)
	{
#ifdef _MSC_VER
		return _aligned_malloc(size, alignment);
#else
		return aligned_alloc(alignment, size);
#endif
	}
	void AlignedFree(void* data)
	{
#ifdef _MSVC_VER
		free(data);
#else
		_aligned_free(data);
#endif
	}
}