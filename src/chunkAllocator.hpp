#pragma once

#include <array>
#include <vector>
#include <utility>
#include <memory>

#include "log2.hpp"
#include "accessParameterPack.hpp"
#include "cumulativeSumParameterPack.hpp"
#include "standardAllocatorInterface.hpp"
#include "pow.hpp"


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

			private:
				constexpr static std::array<size_t, sizeof...(stackSizes)> sm_stackSizes = {stackSizes...};
				constexpr static std::array<size_t, sizeof...(stackSizes)> sm_stackBottoms = cumulativeSumParameterPack<size_t, stackSizes...>((-1 * accessParameterPack<size_t, 0, stackSizes...>()));
				
				std::array<size_t, sizeof...(stackSizes)> m_stackIndexes = {};

				void* m_container[(... + stackSizes)];
		};

		struct RawMemoryAllocationRecord
		{
			void* ptr;
			size_t size;
		};

		template<int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
		class GenericChunkAllocator
		{
			public:
				template<size_t n>
				constexpr void* allocate();
				template<size_t n>
				constexpr void deallocate(void* p);

				template<size_t size>
				constexpr void fill(double percentage = defaultFillPercentage);
				constexpr void fillAll(double percentage = defaultFillPercentage);

			private:
				template<size_t size>
				constexpr void emergencyFill();

				static awmms::memoryManagement::ArrayOfStacks<stackSizes...> sm_arrayOfStacks;

				static std::vector<RawMemoryAllocationRecord> sm_rawAllocations;
		};
	}

	template<typename T, int allocatorID, size_t extraAllocationSize, double defaultFillPercentage, size_t... stackSizes>
	class ChunkAllocator : public IStandardAllocator<T>
	{
		public:
			constexpr T* allocate(std::size_t n) override;
			constexpr void deallocate(T* p, std::size_t n) override;
		
		private:
			typedef memoryManagement::GenericChunkAllocator<allocatorID, extraAllocationSize, defaultFillPercentage, stackSizes...> AssociatedGenericAllocator;
	};
}

//inline implementation
#include "chunkAllocator.inl"