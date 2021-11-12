#pragma once

namespace awmms
{
	template<size_t x, size_t n>
	constexpr size_t pow()
	{
		size_t output = 1;
		for(size_t i = 0; i < n; i++)
		{
			output *= x;
		}
		return output;
	}
}