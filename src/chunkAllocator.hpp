#pragma once

#include <array>
#include <memory>

#include "log2.hpp"
#include "accessParameterPack.hpp"
#include "cumulativeSumParameterPack.hpp"
#include "standardAllocatorInterface.hpp"


namespace awmms
{
	
	namespace memoryManagement
	{
		template<size_t... stackSizes>
		class ArrayOfStacks
		{
			public:
				template<size_t stackNum>
				constexpr void push(void* element);
				template<size_t stackNum>
				constexpr void* pop();
				template<size_t stackNum>
				constexpr void* top();

				template<size_t stackNum>
				constexpr double currentCapacity();

			//private:
				constexpr static std::array<size_t, sizeof...(stackSizes)> sm_stackSizes = {stackSizes...};
				constexpr static std::array<size_t, sizeof...(stackSizes)> sm_stackBottoms = cumulativeSumParameterPack<size_t, stackSizes...>((-1 * accessParameterPack<size_t, 0, stackSizes...>()));
				
				std::array<size_t, sizeof...(stackSizes)> m_stackIndexes = {};

				void* m_container[(... + stackSizes)];
		};
	}
}

//inline implementation
#include "chunkAllocator.inl"