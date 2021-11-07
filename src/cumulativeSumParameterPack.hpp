#pragma once

#include <array>

template<typename T, T... args>
constexpr std::array<T, sizeof...(args)> cumulativeSumParameterPack(T seed = 0)
{
	return{ seed += args ... };
}