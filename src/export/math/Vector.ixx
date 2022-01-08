export module lira.math.Vector;
import lira.math.Common;
import std.core;

export namespace lira::math
{
	/*
		*******************
		No SIMD operations here yet
		*******************
	*/ 

	template<fundamental T, uint8_t Size>
	struct vector_unaligned
	{
		static_assert(Size >= 1 && Size <= 4, "A vector of size other than 1/2/3/4 cannot be instantiated");
	};

	template<fundamental T>
	struct vector_unaligned<T, 1>
	{
		using this_type = vector_unaligned<T, 1>;

		using type = T;
		static constexpr int size = 1;
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
		using type = T;
		static constexpr int size = 2;
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

		T& operator[](uint32_t index) { return *(arr + index); }
	};

	template<fundamental T>
	struct vector_unaligned<T, 3>
	{
		using this_type = vector_unaligned<T, 3>;
		using type = T;
		static constexpr int size = 3;
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

		T& operator[](uint32_t index) { return *(arr + index); }
	};

	template<fundamental T>
	struct vector_unaligned<T, 4>
	{
		using this_type = vector_unaligned<T, 4>;
		using type = T;
		static constexpr int size = 4;
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

		T& operator[](uint32_t index) { return *(arr + index); }
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


	/*
		Type Traits And Vector Concepts
	*/

	template <typename>
	struct is_vector : std::false_type {};
	template <typename>
	struct is_vector2 : std::false_type {};
	template <typename>
	struct is_vector3 : std::false_type {};
	template <typename>
	struct is_vector4 : std::false_type {};

	template <typename T, uint32_t I>
	struct is_vector<vector_unaligned<T, I>> : std::true_type {};
	template <typename T>
	struct is_vector2<vector_unaligned<T, 2>> : std::true_type {};
	template <typename T>
	struct is_vector3<vector_unaligned<T, 3>> : std::true_type {};
	template <typename T>
	struct is_vector4<vector_unaligned<T, 4>> : std::true_type {};

	template <typename T, uint8_t I>
	struct is_vector<vector_aligned<T, I>> : std::true_type {};
	template <typename T>
	struct is_vector2<vector_aligned<T, 2>> : std::true_type {};
	template <typename T>
	struct is_vector3<vector_aligned<T, 3>> : std::true_type {};
	template <typename T>
	struct is_vector4<vector_aligned<T, 4>> : std::true_type {};

	template <typename T>
	concept any_vector = is_vector<T>::value;
	template <typename T>
	concept any_vector2 = is_vector2<T>::value;
	template <typename T>
	concept any_vector3 = is_vector3<T>::value;
	template <typename T>
	concept any_vector4 = is_vector4<T>::value;

	// Resolve operation return type at compile time
	template<typename T1, typename T2>
	struct out_type
	{
		using type = decltype(T1::type(1) * T2::type(1));
	};
	template<typename T1, typename T2>
	using out_type_t = out_type<T1, T2>::type;

	// *********** Vector Functions *************

	// This one works for both aligned and unaligned
	template<any_vector2 V1, any_vector2 V2>
	out_type_t<V1, V2> dot(const V1& lhs, const V2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	template<any_vector3 V1, any_vector3 V2>
	out_type_t<V1, V2> dot(const V1& lhs, const V2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	template<any_vector4 V1, any_vector4 V2>
	out_type_t<V1, V2> dot(const V1& lhs, const V2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	//template<any_vector V>
	//V normalize(const any_vector& v)
	//{
	//
	//}

}