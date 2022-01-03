#include <stdlib.h>
#ifdef _MSC_VER
#include "malloc.h"
#endif
export module lira.core.Common;
import std.core;

export namespace lira::core
{
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