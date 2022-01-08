export module lira.math.MathOperations;
import lira.math.Matrix;
import lira.math.Vector;
import lira.math.Common;
import std.core;

export namespace lira::math
{
	template<fundamental T, uint32_t D1, uint32_t D2, uint32_t D3, uint32_t Alignment1, uint32_t Alignment2>
	constexpr matrix<T, D1, D3, alignof(T), EMatrixOrder::COLUMN_MAJOR> operator* (
		matrix<T, D1, D2, Alignment1, EMatrixOrder::COLUMN_MAJOR> lhs,
		matrix<T, D2, D3, Alignment2, EMatrixOrder::COLUMN_MAJOR> rhs
		)
	{
		matrix<T, D1, D3, alignof(T), EMatrixOrder::COLUMN_MAJOR> res;
		for (int i = 0; i < D1; i++)
		{
			for (int j = 0; j < D3; j++)
			{
				res[j][i] = 0;
				for (int k = 0; k < D2; k++)
				{
					res[j][i] += lhs[k][j] * rhs[i][k];
				}
			}
		}
		return res;
	}

}