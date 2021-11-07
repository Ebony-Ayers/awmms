#pragma once

namespace awmms
{
	namespace memoryManagement
	{
		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr void arrayOfStacks<stackSizes...>::push(void* element)
		{
			typedef arrayOfStacks<stackSizes...> thisT; 

			if(m_stackIndexes[stackNum] < thisT::sm_stackSizes[stackNum])
			{
				this->m_container[thisT::sm_stackBottoms[stackNum] + this->m_stackIndexes[stackNum]] = element;
				this->m_stackIndexes[stackNum]++;
			}
		}
		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr void* arrayOfStacks<stackSizes...>::pop()
		{
			typedef arrayOfStacks<stackSizes...> thisT; 
			
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
		constexpr void* arrayOfStacks<stackSizes...>::top()
		{
			typedef arrayOfStacks<stackSizes...> thisT; 
			
			return this->m_container[thisT::sm_stackBottoms[stackNum] + this->m_stackIndexes[stackNum] - 1];
		}

		template<size_t... stackSizes>
		template<size_t stackNum>
		constexpr double arrayOfStacks<stackSizes...>::currentCapacity()
		{
			typedef arrayOfStacks<stackSizes...> thisT; 
			
			size_t spaceLeft = thisT::sm_stackSizes[stackNum] - this->m_stackIndexes[stackNum];
			size_t spaceTotal = thisT::sm_stackSizes[stackNum];
			return static_cast<double>(spaceLeft) / static_cast<double>(spaceTotal);
		}
	}
}