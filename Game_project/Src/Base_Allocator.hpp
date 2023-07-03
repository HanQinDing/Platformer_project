#pragma once
#include "Utils.hpp"
#include <cstddef>
#include <cstdint>

template <typename T>
class BaseAllocator {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = std::size_t;


	//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
	// So we dont not allow copy construct and copy assignemnt for allocator class
	BaseAllocator(const BaseAllocator&) = delete;
	BaseAllocator& operator=(BaseAllocator&) = delete;


	BaseAllocator() = default;

	~BaseAllocator() = default;

	virtual pointer Allocate(size_type n) = 0;

	const size_type& GetSize() const noexcept;
	const size_type& GetUsed() const noexcept;
	const size_type& GetNumAllocation() const noexcept;

protected:
	size_type m_size;
	size_type m_usedBytes;
	size_type m_numAllocations;

	void* start;
};
