export module lira.math.Types;
import lira.math.Vector;
import std.core;

export namespace lira::math
{
	// Unaligned vectors
	using f2 = vector_unaligned<float, 2>;
	using f3 = vector_unaligned<float, 3>;
	using f4 = vector_unaligned<float, 4>;

	using d2 = vector_unaligned<double, 2>;
	using d3 = vector_unaligned<double, 3>;
	using d4 = vector_unaligned<double, 4>;

	using i2 = vector_unaligned<int32_t, 2>;
	using i3 = vector_unaligned<int32_t, 3>;
	using i4 = vector_unaligned<int32_t, 4>;

	using u2 = vector_unaligned<uint32_t, 2>;
	using u3 = vector_unaligned<uint32_t, 3>;
	using u4 = vector_unaligned<uint32_t, 4>;

	using b2 = vector_unaligned<bool, 2>;
	using b3 = vector_unaligned<bool, 3>;
	using b4 = vector_unaligned<bool, 4>;


	// Aligned vectors
	using f2a = vector_aligned<float, 2>;
	using f3a = vector_aligned<float, 3>;
	using f4a = vector_aligned<float, 4>;

	using d2a = vector_aligned<double, 2>;
	using d3a = vector_aligned<double, 3>;
	using d4a = vector_aligned<double, 4>;

	using i2a = vector_aligned<int32_t, 2>;
	using i3a = vector_aligned<int32_t, 3>;
	using i4a = vector_aligned<int32_t, 4>;

	using u2a = vector_aligned<uint32_t, 2>;
	using u3a = vector_aligned<uint32_t, 3>;
	using u4a = vector_aligned<uint32_t, 4>;

	using b2a = vector_aligned<bool, 2>;
	using b3a = vector_aligned<bool, 3>;
	using b4a = vector_aligned<bool, 4>;

}