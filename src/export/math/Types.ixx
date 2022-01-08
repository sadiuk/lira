export module lira.math.Types;
import lira.math.Vector;
import lira.math.Matrix;
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



	//Matrices

	template<fundamental T, uint32_t R, uint32_t C, uint32_t Alignment>
	using matrix_column_major = matrix<T, R, C, Alignment, EMatrixOrder::COLUMN_MAJOR>;
	
	template<fundamental T, uint32_t R, uint32_t C, uint32_t Alignment>
	using matrix_row_major = matrix<T, R, C, Alignment, EMatrixOrder::ROW_MAJOR>;



	template<fundamental T, uint32_t Alignment>
	using mat2 = matrix_column_major<T, 2, 2, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat2x3 = matrix_column_major<T, 3, 2, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat2x4 = matrix_column_major<T, 4, 2, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat3 = matrix_column_major<T, 3, 3, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat3x2 = matrix_column_major <T, 2, 3, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat3x4 = matrix_column_major <T, 4, 3, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat4 = matrix_column_major<T, 4, 4, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat4x2 = matrix_column_major<T, 2, 4, Alignment>;

	template<fundamental T, uint32_t Alignment>
	using mat4x3 = matrix_column_major<T, 3, 4, Alignment>;



	using mat2f = mat2<float, alignof(f2a)>;
	using mat2i = mat2<float, alignof(i2a)>;
	using mat2u = mat2<float, alignof(u2a)>;
	using mat2b = mat2<float, alignof(b2a)>;
	using mat2d = mat2<float, alignof(d2a)>;

	using mat2x3f = mat2x3<float, alignof(f3a)>;
	using mat2x3i = mat2x3<float, alignof(i3a)>;
	using mat2x3u = mat2x3<float, alignof(u3a)>;
	using mat2x3b = mat2x3<float, alignof(b3a)>;
	using mat2x3d = mat2x3<float, alignof(d3a)>;

	using mat2x4f = mat2x4<float, alignof(f4a)>;
	using mat2x4i = mat2x4<float, alignof(i4a)>;
	using mat2x4u = mat2x4<float, alignof(u4a)>;
	using mat2x4b = mat2x4<float, alignof(b4a)>;
	using mat2x4d = mat2x4<float, alignof(d4a)>;

	using mat3f = mat3<float, alignof(f3a)>;
	using mat3i = mat3<float, alignof(i3a)>;
	using mat3u = mat3<float, alignof(u3a)>;
	using mat3b = mat3<float, alignof(b3a)>;
	using mat3d = mat3<float, alignof(d3a)>;

	using mat3x2f = mat3x2<float, alignof(f2a)>;
	using mat3x2i = mat3x2<float, alignof(i2a)>;
	using mat3x2u = mat3x2<float, alignof(u2a)>;
	using mat3x2b = mat3x2<float, alignof(b2a)>;
	using mat3x2d = mat3x2<float, alignof(d2a)>;

	using mat3x4f = mat3x4<float, alignof(f4a)>;
	using mat3x4i = mat3x4<float, alignof(i4a)>;
	using mat3x4u = mat3x4<float, alignof(u4a)>;
	using mat3x4b = mat3x4<float, alignof(b4a)>;
	using mat3x4d = mat3x4<float, alignof(d4a)>;

	using mat4f = mat4<float, alignof(f4a)>;
	using mat4i = mat4<float, alignof(i4a)>;
	using mat4u = mat4<float, alignof(u4a)>;
	using mat4b = mat4<float, alignof(b4a)>;
	using mat4d = mat4<float, alignof(d4a)>;

	using mat4x2f = mat4x2<float, alignof(f2a)>;
	using mat4x2i = mat4x2<float, alignof(i2a)>;
	using mat4x2u = mat4x2<float, alignof(u2a)>;
	using mat4x2b = mat4x2<float, alignof(b2a)>;
	using mat4x2d = mat4x2<float, alignof(d2a)>;

	using mat4x3f = mat4x3<float, alignof(f3a)>;
	using mat4x3i = mat4x3<float, alignof(i3a)>;
	using mat4x3u = mat4x3<float, alignof(u3a)>;
	using mat4x3b = mat4x3<float, alignof(b3a)>;
	using mat4x3d = mat4x3<float, alignof(d3a)>;

}