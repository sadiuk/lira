export module lira.math.CameraMath;
#include <cassert>
import lira.math.Vector;
import lira.math.Matrix;
import lira.math.Common;
import std.core;
export namespace lira::math
{
	template<fundamental T>
	matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> LookAt(const vector_unaligned<T, 3>& pos, const vector_unaligned<T, 3>& forward, const vector_unaligned<T, 3>& upHint)
	{
		matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> ret(0);
		vector_unaligned<T, 3> right = cross(forward, upHint);
		vector_unaligned<T, 3> up = cross(right, forward);
		/*ret[0] = vector_unaligned<T, 4>(right.x,   right.y,   right.z,   0);
		ret[1] = vector_unaligned<T, 4>(forward.x, forward.y, forward.z, 0);
		ret[2] = vector_unaligned<T, 4>(up.x,      up.y,      up.z,      0);
		ret[3] = vector_unaligned<T, 4>(-pos.x,    -pos.y,   -pos.z,     1);*/
		ret[0] = vector_unaligned<T, 4>(right.x, forward.x, up.x, -pos.x);
		ret[1] = vector_unaligned<T, 4>(right.y, forward.y, up.y, -pos.y);
		ret[2] = vector_unaligned<T, 4>(right.z, forward.z, up.z, -pos.z);
		ret[3] = vector_unaligned<T, 4>(0,		 0,			0,	  1);
		return ret;
	}

	template<fundamental T>
	matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> Perspective(const T& fov, const T& near, const T& far, bool reversedZ)
	{
		assert(reversedZ);
		matrix<T, 4, 4, alignof(vector_aligned<T, 4>), EMatrixOrder::COLUMN_MAJOR> ret(0);
		auto fovRad = radians(fov) * 0.5;
		T scale = T(1) / tan(radians(fov) * T(0.5));

		ret[0][0] = scale;  //scale the x coordinates of the projected point 
		ret[1][2] = -scale;  //scale the y coordinates of the projected point 
		ret[2][1] = far / (far - near);  //used to remap z to [0,1] 
		ret[2][3] = -1;  //set w = -z 
		ret[3][1] = far * near / (far - near);  //used to remap z [0,1] 
		ret[3][3] = 0;
		return ret;
	}

}