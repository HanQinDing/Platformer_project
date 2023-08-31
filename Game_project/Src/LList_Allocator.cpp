#include "LList_Allocator.hpp"


void ListAllocator::Initialise(std::size_t sz) noexcept {
	BaseAllocator::start = new void* [sz];
	Memory_end = reinterpret_cast<char*>(BaseAllocator::start) + sz;
	Free_Blocks_List = static_cast<Freeblock*>(BaseAllocator::start);
	Free_Blocks_List->next = nullptr;
	Free_Blocks_List->size = sz;
	BaseAllocator::m_size = sz;
	BaseAllocator::m_usedBytes = 0;
	BaseAllocator::m_numAllocations = 0;
	std::cout << "Free Block Header Size: " << sizeof(Freeblock) << "\n";
	std::cout << "Allocated Block Header Size: " << sizeof(Allocated_Block) << "\n";
}

void ListAllocator::Print_List() {
	Freeblock* block = Free_Blocks_List;
	int count{};
	std::cout << "LIST\n";
	while (block) {
		std::cout << count + 1 << ": " << block->size << "\n";
		++count;
		block = block->next;
	}
	std::cout << "List count: " << count << "\n\n";
}