#pragma once

#include <type_traits>

namespace GLU
{
	// Overload bit operators to account for different "flags" being passed in
	// Using templates for reusability and assertions for type safety
#pragma region enum operators

	// Bitwise OR
	template <typename T>
	inline T operator |(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
	}

	// Bitwise AND
	template <typename T>
	inline T operator &(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
	}

	// Bitwise LEFT SHIFT
	template <typename T>
	inline T operator <<(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a)<< static_cast<int>(b));
	}

	// Bitwise RIGHT SHIFT
	template <typename T>
	inline T operator >>(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a)>> static_cast<int>(b));
	}

	// Bitwise XOR
	template <typename T>
	inline T operator ^(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a)^ static_cast<int>(b));
	}

	// Bitwise NOT
	template <typename T>
	inline T operator ~(T a)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(~static_cast<int>(a));
	}
#pragma endregion

#pragma region vertex

	struct vertex
	{
		float x, y, z;
		float r, g, b, a;
	};

#pragma endregion
}