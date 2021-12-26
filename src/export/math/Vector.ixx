export module lira.math.Vector;
import std.core;

export namespace lira::math
{
	/*
		*******************
		No SIMD operations here yet
		*******************
	*/ 
	template<typename T>
	concept fundamental = std::is_fundamental_v<T>;

	template<fundamental T, uint8_t Size>
	struct vector_unaligned
	{
		static_assert(Size >= 1 && Size <= 4, "A vector of size other than 1/2/3/4 cannot be instantiated");
	};

	template<fundamental T>
	struct vector_unaligned<T, 1>
	{
		using this_type = vector_unaligned<T, 1>;
	public:
		vector_unaligned() {}
		explicit vector_unaligned(T el) : x{ el } {}
		union
		{
			T x;
			T r;
		};
		const T* data() const { return &x; }
		T* data() { return &x; }

		this_type operator*(const this_type& other) { return this_type(x * other.x); }
		this_type operator*(T scalar) { return this_type(x * scalar); }
		this_type operator/(T scalar) { return this_type(x / scalar); }
		this_type operator+(const this_type& other) { return this_type(x + other.x); }
		this_type operator-(const this_type& other) { return this_type(x - other.x); }
	
		this_type& operator*=(const this_type& other) { x *= other.x; return *this; }
		this_type& operator*=(T scalar) { x *= scalar; return *this; }
		this_type& operator/=(T scalar) { x /= scalar; return *this; }
		this_type& operator+=(const this_type& other) { x += other.x; return *this; }
		this_type& operator-=(const this_type& other) { x -= other.x; return *this; }
	};

	template<fundamental T>
	struct vector_unaligned<T, 2>
	{
		using this_type = vector_unaligned<T, 2>;
	public:
		vector_unaligned() {}
		explicit vector_unaligned(T el1, T el2) : arr{ el1, el2 } {}
		union
		{
			T arr[2];
			struct
			{
				T x, y;
			};
			struct
			{
				T r, g;
			};
		};
		const T* data() const { return arr; }
		T* data() { return arr; }

		this_type operator*(const this_type& other) { return this_type(x * other.x, y * other.y); }
		this_type operator*(T scalar) { return this_type(x * scalar, y * scalar); }
		this_type operator/(T scalar) { return this_type(x / scalar, y / scalar); }
		this_type operator+(const this_type& other) { return this_type(x + other.x, y + other.y); }
		this_type operator-(const this_type& other) { return this_type(x - other.x, y - other.y); }

		this_type& operator*=(const this_type& other) { x *= other.x; y *= other.y; return *this; }
		this_type& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }
		this_type& operator/=(T scalar) { x /= scalar; y /= scalar; return *this; }
		this_type& operator+=(const this_type& other) { x += other.x; y += other.y; return *this; }
		this_type& operator-=(const this_type& other) { x -= other.x; y -= other.y; return *this; }
	};

	template<fundamental T>
	struct vector_unaligned<T, 3>
	{
		using this_type = vector_unaligned<T, 3>;
	public:
		vector_unaligned() {}
		explicit vector_unaligned(T el1, T el2, T el3) : arr{ el1, el2, el3 } {}
		union
		{
			T arr[3];
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
		};
		const T* data() const { return arr; }
		T* data() { return arr; }

		this_type operator*(const this_type& other) { return this_type(x * other.x, y * other.y, z * other.z); }
		this_type operator*(T scalar) { return this_type(x * scalar, y * scalar, z * scalar); }
		this_type operator/(T scalar) { return this_type(x / scalar, y / scalar, z / scalar); }
		this_type operator+(const this_type& other) { return this_type(x + other.x, y + other.y, z + other.z); }
		this_type operator-(const this_type& other) { return this_type(x - other.x, y - other.y, z - other.z); }

		this_type& operator*=(const this_type& other) { x *= other.x; y *= other.y; z += other.z; return *this; }
		this_type& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
		this_type& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }
		this_type& operator+=(const this_type& other) { x += other.x; y += other.y; z+= other.z; return *this; }
		this_type& operator-=(const this_type& other) { x -= other.x; y -= other.y; z-= other.z; return *this; }
	};

	template<fundamental T>
	struct vector_unaligned<T, 4>
	{
		using this_type = vector_unaligned<T, 4>;
	public:
		vector_unaligned() {}
		explicit vector_unaligned(T el1, T el2, T el3, T el4) : arr{ el1, el2, el3, el4 } {}
		union
		{
			T arr[4];
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
		};
		const T* data() const { return arr; }
		T* data() { return arr; }

		this_type operator*(const this_type& other) { return this_type(x * other.x, y * other.y, z * other.z, w * other.w); }
		this_type operator*(T scalar) { return this_type(x * scalar, y * scalar, z * scalar, w * scalar); }
		this_type operator/(T scalar) { return this_type(x / scalar, y / scalar, z / scalar, w / scalar); }
		this_type operator+(const this_type& other) { return this_type(x + other.x, y + other.y, z + other.z, w + other.w); }
		this_type operator-(const this_type& other) { return this_type(x - other.x, y - other.y, z - other.z, w - other.w); }

		this_type& operator*=(const this_type& other) { x *= other.x; y *= other.y; z += other.z; w += other.w; return *this; }
		this_type& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
		this_type& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }
		this_type& operator+=(const this_type& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
		this_type& operator-=(const this_type& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	};

	// GLSL aligned vectors
	template<fundamental Y, uint8_t Size>
	struct vector_aligned
	{
		static_assert(Size >= 1 && Size <= 4, "A vector of size other than 1/2/3/4 cannot be instantiated");
	};

	//This vec1 is only useful with booleans
	template<fundamental T>
	struct alignas(4) vector_aligned<T, 1> : vector_unaligned<T, 1> 
	{
		explicit vector_aligned(T el) : vector_unaligned<T, 1>(el) {}
	};
	template<>
	struct alignas(8) vector_aligned<double, 1> : vector_unaligned<double, 1> 
	{
		explicit vector_aligned(double el) : vector_unaligned<double, 1>(el) {}
	};

	template<fundamental T>
	struct alignas(8) vector_aligned<T, 2> : vector_unaligned<T, 2> 
	{
		explicit vector_aligned(T el1, T el2) : vector_unaligned<T, 2>(el1, el2) {}
	};
	template<>
	struct alignas(16) vector_aligned<double, 2> : vector_unaligned<double, 2>
	{
		explicit vector_aligned(double el1, double el2) : vector_unaligned<double, 2>(el1, el2) {}
	};
	
	template<fundamental T>
	struct alignas(16) vector_aligned<T, 3> : vector_unaligned<T, 3>
	{
		explicit vector_aligned(T el1, T el2, T el3) : vector_unaligned<T, 3>(el1, el2, el3) {}
	};
	template<>
	struct alignas(32) vector_aligned<double, 3> : vector_unaligned<double, 3> 
	{
		explicit vector_aligned(double el1, double el2, double el3) : vector_unaligned<double, 3>(el1, el2, el3) {}
	};

	template<fundamental T>
	struct alignas(16) vector_aligned<T, 4> : vector_unaligned<T, 4>
	{	
		explicit vector_aligned(T el1, T el2, T el3, T el4) : vector_unaligned<T, 4>(el1, el2, el3, el4) {}
	};
	template<>
	struct alignas(32) vector_aligned<double, 4> : vector_unaligned<double, 4> 
	{
		explicit vector_aligned(double el1, double el2, double el3, double el4) : vector_unaligned<double, 4>(el1, el2, el3, el4) {}
	};




	// *********** Vector Functions *************

	// This one works for both aligned and unaligned
	template<fundamental T>
	T dot(const vector_unaligned<T, 2>& lhs, const vector_unaligned<T, 2>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	template<fundamental T>
	T dot(const vector_unaligned<T, 3>& lhs, const vector_unaligned<T, 3>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	template<fundamental T>
	T dot(const vector_unaligned<T, 4>& lhs, const vector_unaligned<T, 4>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}
}