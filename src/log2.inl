namespace awmms
{
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
}