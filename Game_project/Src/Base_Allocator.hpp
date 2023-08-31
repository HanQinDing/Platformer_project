#pragma once
#include "Utils.hpp"
#include <cstddef>
#include <cstdint>


class BaseAllocator 
{
  public:


		//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
		// So we dont not allow copy construct and copy assignemnt for allocator class
		BaseAllocator(const BaseAllocator&) = delete;
		BaseAllocator& operator=(BaseAllocator&) = delete;


		BaseAllocator() = default;

		~BaseAllocator() = default;

		//virtual void Free() = 0;

		const std::size_t& GetSize() const noexcept;
		const std::size_t& GetUsed() const noexcept;
		const std::size_t& GetFree() const noexcept;
		const std::size_t& GetNumAllocation() const noexcept;

	protected:
		std::size_t m_size;
		std::size_t m_usedBytes;
		std::size_t m_numAllocations;

		void* m_start;
};
