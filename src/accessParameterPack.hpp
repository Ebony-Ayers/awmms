#pragma once

template<typename T, size_t N, T first, T... args>
constexpr T accessParameterPack()
{
	if constexpr(N == 0)
	{
		return first;
	}
	else
	{
		return accessParameterPack<T, N-1, args...>();
	}
}