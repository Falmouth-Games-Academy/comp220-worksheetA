#pragma once

#include <type_traits>

namespace GLU
{
#pragma region enum Helper
	template <typename T>
	inline T operator |(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
	}

	template <typename T>
	inline T operator &(T a, T b)
	{
		// Make sure an enum was passed to the function
		static_assert(std::is_enum<T>::value, "Cannot perform operation with type");
		return static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
	}
#pragma endregion
}