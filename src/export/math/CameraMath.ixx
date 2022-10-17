export module lira.math.CameraMath;
#include <cassert>
import lira.math.Vector;
import lira.math.Matrix;
import lira.math.Common;
import std.core;
export namespace lira::math
{
	template<fundamental T>
	matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> LookAt(const vector_unaligned<T, 3>& forward, const vector_unaligned<T, 3>& upHint)
	{
		matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> ret(0);
		vector_unaligned<T, 3> right = cross(forward, upHint);
		vector_unaligned<T, 3> up = cross(right, forward);
		ret[0] = vector_unaligned<T, 4>(right.x,   right.y,   right.z,   0);
		ret[1] = vector_unaligned<T, 4>(forward.x, forward.y, forward.z, 0);
		ret[2] = vector_unaligned<T, 4>(up.x,      up.y,      up.z,      0);
		ret[3] = vector_unaligned<T, 4>(0,         0,         0,         1);
		return ret;
	}

	template<fundamental T>
	matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> Perspective(const T& fov, const T& near, const T& far, bool reversedZ)
	{
		assert(reversedZ);
		static constexpr T M_PI = std::numbers::pi_v<T>;
		matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> ret(0);
		T scale = T(1) / tan(fov * T(0.5) * M_PI / T(180));

		ret[0][0] = scale;  //scale the x coordinates of the projected point 
		ret[1][1] = scale;  //scale the y coordinates of the projected point 
		ret[2][2] = -far / (far - near);  //used to remap z to [0,1] 
		ret[3][2] = -far * near / (far - near);  //used to remap z [0,1] 
		ret[2][3] = -1;  //set w = -z 
		ret[3][3] = 0;
		return ret;
	}

}