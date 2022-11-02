export module lira.math.MathOperations;
import lira.math.Matrix;
import lira.math.Vector;
import lira.math.Common;
import std.core;

export namespace lira::math
{
	template<fundamental T, uint32_t D1, uint32_t D2, uint32_t D3, uint32_t Alignment1, uint32_t Alignment2>
	constexpr matrix<T, D1, D3, alignof(T), EMatrixOrder::COLUMN_MAJOR> operator* (
		const matrix<T, D1, D2, Alignment1, EMatrixOrder::COLUMN_MAJOR>& lhs,
		const matrix<T, D2, D3, Alignment2, EMatrixOrder::COLUMN_MAJOR>& rhs
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

	template<fundamental T, uint32_t D1, uint32_t D2, uint32_t Alignment1>
	constexpr vector_unaligned<T, D2> operator* (
		const matrix<T, D1, D2, Alignment1, EMatrixOrder::COLUMN_MAJOR>& mat,
		const vector_unaligned<T, D2>& vector
		)
	{
		vector_unaligned<T, D2> res;
		for (int i = 0; i < D2; i++)
		{
			res[i] = 0;
			for (int j = 0; j < D1; j++)
			{
				res[i] += mat[i][j] * vector[j];
			}
		}
		return res;
	}

	template<std::floating_point T>
	constexpr T radians(T degrees)
	{
		return degrees / (T)180 * std::numbers::pi_v<T>;
	}
	template<std::floating_point T>
	constexpr T degrees(T radians)
	{
		return radians / std::numbers::pi_v<T> * 180;
	}

	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector2 V>
	matrix<T, 3, 3, Alignment, Order> Translate(const matrix<T, 3, 3, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 3, 3, Alignment, Order> res = m;
		res[2][0] += vec[0];
		res[2][1] += vec[1];
		return res;
	}
	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector3 V>
	matrix<T, 4, 4, Alignment, Order> Translate(const matrix<T, 4, 4, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 4, 4, Alignment, Order> res = m;
		res[3][0] += vec[0];
		res[3][1] += vec[1];
		res[3][2] += vec[2];
		return res;
	}
	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector3 V>
	matrix<T, 4, 3, Alignment, Order> Translate(const matrix<T, 4, 3, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 4, 3, Alignment, Order> res = m;
		res[3][0] += vec[0];
		res[3][1] += vec[1];
		res[3][2] += vec[2];
		return res;
	}

	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector3 V>
	matrix<T, 4, 3, Alignment, Order> Rotate(const matrix<T, 4, 3, Alignment, Order>& m, const V& axis, float degrees)
	{

	}

	
	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector2 V>
	matrix<T, 3, 3, Alignment, Order> Scale(const matrix<T, 3, 3, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 3, 3, Alignment, Order> res = m;
		res[0][0] *= vec[0];
		res[1][1] *= vec[1];
		return res;
	}
	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector3 V>
	matrix<T, 4, 4, Alignment, Order> Scale(const matrix<T, 4, 4, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 4, 4, Alignment, Order> res = m;
		res[0][0] *= vec[0];
		res[1][1] *= vec[1];
		res[2][2] *= vec[2];
		return res;
	}
	template<fundamental T, uint32_t Alignment, EMatrixOrder Order, any_vector3 V>
	matrix<T, 4, 3, Alignment, Order> Scale(const matrix<T, 4, 3, Alignment, Order>& m, const V& vec)
	{
		matrix<T, 4, 3, Alignment, Order> res = m;
		res[0][0] *= vec[0];
		res[1][1] *= vec[1];
		res[2][2] *= vec[2];
		return res;
	}


}