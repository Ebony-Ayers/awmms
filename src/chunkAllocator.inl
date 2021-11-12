namespace awmms
{
	namespace memoryManagement
	{
		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr void ArrayOfStacks<stackSizes...>::push(void* element)
		{
			typedef ArrayOfStacks<stackSizes...> thisT; 

			if(m_stackIndexes[stackNum] < thisT::sm_stackSizes[stackNum])
			{
				this->m_container[thisT::sm_stackBottoms[stackNum] + this->m_stackIndexes[stackNum]] = element;
				this->m_stackIndexes[stackNum]++;
			}
			else
			{
				std::cout << "pushing with no space left" << std::endl;
			}
		}
		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr void* ArrayOfStacks<stackSizes...>::pop()
		{
			typedef ArrayOfStacks<stackSizes...> thisT; 
			
			if(AWMMS_EXPECT(this->m_stackIndexes[stackNum] == 0, false))
			{
				return nullptr;
			}
			else
			{
				auto returnValue = this->m_container[thisT::sm_stackBottoms[stackNum] + this->m_stackIndexes[stackNum] - 1];
				this->m_stackIndexes[stackNum]--;
				return returnValue;
			}
		}
		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr void* ArrayOfStacks<stackSizes...>::top()
		{
			typedef ArrayOfStacks<stackSizes...> thisT; 
			
			return this->m_container[thisT::sm_stackBottoms[stackNum] + this->m_stackIndexes[stackNum] - 1];
		}

		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr double ArrayOfStacks<stackSizes...>::currentCapacity()
		{
			typedef ArrayOfStacks<stackSizes...> thisT; 
			
			size_t spaceLeft = thisT::sm_stackSizes[stackNum] - this->m_stackIndexes[stackNum];
			size_t spaceTotal = thisT::sm_stackSizes[stackNum];
			return static_cast<double>(spaceLeft) / static_cast<double>(spaceTotal);
		}




		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		awmms::memoryManagement::ArrayOfStacks<stackSizes...> GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::sm_arrayOfStacks;
		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		std::vector<RawMemoryAllocationRecord> GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::sm_rawAllocations = {};

		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		template<size_t n>
		constexpr void* GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::allocate()
		{
			typedef GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...> thisT;
			
			constexpr size_t maximumAllocationSize = awmms::pow<2, sizeof...(stackSizes) - 1>() * 4;
			static_assert(n <= maximumAllocationSize, "awmms::GenericChunkAllocator::allocate cannot allocate required amount of memory");
			
			constexpr size_t ptrSize = !(n<4) ? static_cast<size_t>(awmms::log2(n-1)) - 1 : 0;
			void* ptr = thisT::sm_arrayOfStacks.template pop<ptrSize>();

			std::cout << "allocating " << awmms::pow<2, ptrSize>() * 4 << " bytes" << std::endl;
			
			if(AWMMS_EXPECT(ptr == nullptr, false))
			{
				std::cout << "emergency fill" << std::endl;
				thisT::emergencyFill<ptrSize>();
				ptr = thisT::sm_arrayOfStacks.template pop<ptrSize>();
			}
			
			return ptr;
		}
		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		template<size_t n>
		constexpr void GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::deallocate(void* p)
		{
			typedef GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...> thisT;
			
			constexpr size_t maximumAllocationSize = awmms::pow<2, sizeof...(stackSizes) - 1>() * 4;
			static_assert(n <= maximumAllocationSize, "awmms::GenericChunkAllocator::deallocate cannot deallocate required amount of memory");
			
			constexpr size_t ptrSize = n<4 ? static_cast<size_t>(awmms::log2(n-1)) - 1 : 0;
			thisT::sm_arrayOfStacks.template push<ptrSize>(p);

			std::cout << "deallocating " << awmms::pow<2, ptrSize>() * 4 << " bytes" << std::endl;

			return;
		}

		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		template<size_t size>
		constexpr void GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::fill(double percentage)
		{
			return;
		}
		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		constexpr void GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::fillAll(double percentage)
		{
			return;
		}
		
		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		template<size_t size>
		constexpr void GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...>::emergencyFill()
		{
			return;
		}
	}
}