#pragma once

#if defined(AWMMS_COMPILER_MSVC)
	#include <intrin.h>
#endif

namespace awmms
{
	constexpr int log2(unsigned int x);
	constexpr int log2(unsigned long x);
	constexpr int log2(unsigned long long x);
}

#include "log2.inl"