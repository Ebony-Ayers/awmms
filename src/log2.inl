namespace awmms
{
	#if defined(AWMMS_COMPILER_GCC) || defined(AWMMS_COMPILER_CLANG)
		constexpr int log2(const unsigned int& x)
		{
			return static_cast<int>(sizeof(unsigned int) * 8) - __builtin_clz(x) - 1;
		}
		constexpr int log2(const unsigned long& x)
		{
			return static_cast<int>(sizeof(unsigned long) * 8) - __builtin_clzl(x) - 1;
		}
		constexpr int log2(const unsigned long long& x)
		{
			return static_cast<int>(sizeof(unsigned long long) * 8) - __builtin_clzll(x) - 1;
		}
	
	#elif defined(AWMMS_COMPILER_MSVC)
		constexpr int log2(const unsigned int& x)
		{
			unsigned long trailing_zero_index = 0;
			
			if(_BitScanForward(&trailing_zero_index, x))
			{
				return static_cast<int>(trailing_zero_index);
			}
			//equivilent of undefined behavior from gcc
			else
			{
				return 0;
			}
		}
		constexpr int log2(const unsigned long& x)
		{
			unsigned long trailing_zero_index = 0;
			
			if(_BitScanForward(&trailing_zero_index, x))
			{
				return static_cast<int>(trailing_zero_index);
			}
			//equivilent of undefined behavior from gcc
			else
			{
				return 0;
			}
		}
		constexpr int log2(const unsigned long long& x)
		{
			unsigned long trailing_zero_index = 0;
			
			if(_BitScanForward64(&trailing_zero_index, x))
			{
				return static_cast<int>(trailing_zero_index);
			}
			//equivilent of undefined behavior from gcc
			else
			{
				return 0;
			}
		}
	
	#elif defined(AWMMS_COMPILER_UNKNOWN)
		constexpr int log2(unsigned int x)
		{
			int result = 0;
			while(x >>= 1)
			{
				result++;
			}
			return result;
		}
		constexpr int log2(unsigned long x)
		{
			int result = 0;
			while(x >>= 1)
			{
				result++;
			}
			return result;
		}
		constexpr int log2(unsigned long long x)
		{
			int result = 0;
			while(x >>= 1)
			{
				result++;
			}
			return result;
		}
	#endif
}