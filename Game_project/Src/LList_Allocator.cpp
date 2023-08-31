#include "LList_Allocator.hpp"


void ListAllocator::Initialise(std::size_t sz) noexcept {
	BaseAllocator::m_start = new void* [sz];
	m_memEnd = reinterpret_cast<char*>(BaseAllocator::m_start) + sz;
	m_freeMemList = static_cast<FreeBlock*>(BaseAllocator::m_start);
	m_freeMemList->m_next = nullptr;
	m_freeMemList->m_size = sz;
	BaseAllocator::m_size = sz;
	BaseAllocator::m_usedBytes = 0;
	BaseAllocator::m_numAllocations = 0;
	std::cout << "Free Block Header Size: " << sizeof(FreeBlock) << "\n";
	std::cout << "Allocated Block Header Size: " << sizeof(AllocatedBlock) << "\n";
}

void ListAllocator::PrintDetails() {
	FreeBlock* block = m_freeMemList;
	int count{};
	std::cout << "LIST\n";
	while (block) {
		std::cout << count + 1 << ": " << block->m_size << "\n";
		++count;
		block = block->m_next;
	}
	std::cout << "List count: " << count << "\n\n";
}