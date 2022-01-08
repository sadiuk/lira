export module lira.math.Matrix;
import lira.math.Common;
import lira.math.Vector;
import std.core;

export namespace lira::math
{
	enum EMatrixOrder
	{
		ROW_MAJOR,
		COLUMN_MAJOR
	};

	template<fundamental T, uint32_t RowCount, uint32_t ColCount, uint32_t Alignment = alignof(T), EMatrixOrder Order = EMatrixOrder::COLUMN_MAJOR>
	struct alignas(Alignment) matrix
	{

	};

	template<fundamental T, uint32_t R, uint32_t C, uint32_t Alignment>
	struct alignas(Alignment) matrix<T, R, C, Alignment, EMatrixOrder::COLUMN_MAJOR>
	{
		static constexpr uint32_t RowCount = R;
		static constexpr uint32_t ColCount = C;
		using this_type = matrix<T, RowCount, ColCount, Alignment, EMatrixOrder::COLUMN_MAJOR>;
		using vector_element_type = vector_unaligned<T, RowCount>;
		using type = T;

		union
		{
			T arr[ColCount][RowCount];
			vector_element_type vectors[ColCount];
		};

		matrix() {}
		matrix(uint32_t mainDiagonalFill)
		{
			for (int i = 0; i < C; i++)
				for (int j = 0; j < R; j++)
				{
					if (i == j) arr[i][j] = 1;
					else arr[i][j] = 0;
				}
		}
		vector_element_type& operator[](uint32_t index) { return vectors[index]; }
	};


}