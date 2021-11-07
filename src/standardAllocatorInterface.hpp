#pragma once

//for c++23
//#include <memory>

template<typename T>
class IStandardAllocator
{
	typedef T value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	using propagate_on_container_move_assignment = std::true_type;

	[[nodiscard]] constexpr virtual T* allocate(std::size_t n) = 0;
	constexpr void virtual deallocate(T* p, std::size_t n) = 0;
	
	//for c++23
	//[[nodiscard]] constexpr virtual std::allocation_result<T*> allocate_at_least(std::size_t n);
};