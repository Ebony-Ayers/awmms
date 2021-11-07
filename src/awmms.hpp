#pragma once

#if defined(__clang__)
	#define AWMMS_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define AWMMS_COMPILER_GCC
#elif defined(_MSC_VER)
	#define AWMMS_COMPILER_MSVC
#else
	#define AWMMS_COMPILER_UNKNOWN
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
	#define AWMMS_PLATFORM_WINDOWS
#elif defined(__linux__)
	#define AWMMS_PLATFORM_LINUX
#elif defined(__APPLE__)
	#define AWMMS_PLATFORM_APPLE
#else
	#define AWMMS_PLATFORM_UNKNOWN
#endif

#ifdef AWMMS_COMPILER_GCC
	#define AWMMS_EXPECT(condition, outcome) __builtin_expect(condition, outcome)
#else
	#define AWMMS_EXPECT(condition, outcome) condition
#endif

#include "chunkAllocator.hpp"