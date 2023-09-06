/*!************************************************************************
\file ListAllocator.cpp
\author Han Qin Ding

\brief
This file functions for a linked list Allocator.
The allocator uses a linked list to keep track of how many free memory chunks left in the allocator,
and the size of each free meory chunk
**************************************************************************/

#include "LList_Allocator.hpp"
#include <sstream>
#include <Windows.h>

/************************************************************************/ /*!
\ brief
Initialize the linked list allocator. Allocate/reserve dynamic memory using std::allocator
and initializer all the data members

\param [sz]std::size_t 
	size of the Allocator (bytes)

*/
/************************************************************************/
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

/************************************************************************/ /*!
\ brief
Print out the details of the linked list allocator.
e.g.( total size, total memory left )

*/
/************************************************************************/
void ListAllocator::PrintDetails() {

	std::cout << "List Allocator:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "Total Memory Size: " << BaseAllocator::m_size << " bytes\n";
	std::cout << "Memory Used	: " << BaseAllocator::m_usedBytes << " bytes\n";
	std::cout << "Memory left: " << BaseAllocator::GetFree() << " bytes\n";
	std::cout << "Number of Allocations: " << BaseAllocator::m_numAllocations << "\n";
	FreeBlock* block = m_freeMemList;
	int count{};
	std::cout << "LIST\n";
	while (block) {
		std::cout << "	Chunk " << count + 1 << ": " << block->m_size << "\n";
		++count;
		block = block->m_next;
	}
	std::cout << "----------------------------------------------\n";
}


/************************************************************************/ /*!
\ brief
Print out the details of memory leak in linked list allocator, if any

*/
/************************************************************************/
void ListAllocator::PrintMemLeak() 
{
	if (m_usedBytes != 0) { // We will print mem leak details if required
		OutputDebugStringA("\nList Allocator Mem Leak:\n");
		OutputDebugStringA("---------------------------------------------\n");
		std::string output1 = "Total Memory not freed	: " + std::to_string(BaseAllocator::m_usedBytes) + " bytes\n";
		std::string output2 = "Number of Allocations not free: " + std::to_string(BaseAllocator::m_numAllocations) + "\n";
		OutputDebugStringA(output1.c_str());
		OutputDebugStringA(output2.c_str());
		OutputDebugStringA("----------------------------------------------\n\n");
	}
}


//
//std::string output = "Number of Objects not free: " + std::to_string(CustomAllocators::g_objMem.size()) + "\n";
//OutputDebugStringA(output.c_str());




/************************************************************************/ /*!
\ brief
Free/delete the memory thats wa previously allocated/reserved at the start.

*/
/************************************************************************/
void ListAllocator::Free() {
	delete[] BaseAllocator::m_start;
}