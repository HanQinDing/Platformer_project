#pragma once
#include "Base_Allocator.hpp"
#include <initializer_list>

struct Freeblock {
	size_t size{};
	Freeblock* next;
};


struct Allocated_Block {
	size_t size{};
};


class ListAllocator : public BaseAllocator {
public:


	//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
	// So we dont not allow copy construct and copy assignemnt for allocator class
	ListAllocator(const  ListAllocator&) = delete;
	ListAllocator& operator=(ListAllocator&) = delete;


	ListAllocator() = default;

	~ListAllocator() = default;

	template<typename T, std::size_t sz = 1>
	T* Allocate(const std::initializer_list<T>& initList = {});

	template<typename T>
	T* Allocate(T& object);



	//void Free() override;

	template<typename T>
	void Rewind(T*& ptr) noexcept;

	void Initialise(std::size_t sz) noexcept;
	void Print_List();



protected:

	Freeblock* Free_Blocks_List;
};


/*
  My replacement for c++ new[] function (Allocate storage space for array)
  Tried to squeeze 3 different overloads into 1 function definition

  1.  Allocate<int, size>()
	  - all the objects in the array will be default constructed

  2.  Allocate<int>(initializer_list)
	  - size of array  equal to size of initializer_list.
	  - Copy everything in init_list to array

  3.  Allocate<int, size>(initializer_list)
	  - ONLY DO THIS IF YOUR ACTUAL ARRAY IS BIGGER THAN THE INITIALIZER LIST
	  - size of array equal to size entered in the "< >" angle braces.
	  - Copy everything in init_list to array, any empty slots left in the array will be filled with default constructed object
*/

template<typename T, std::size_t sz>
T* ListAllocator::Allocate(const std::initializer_list<T>& initList) {

	std::size_t count = (sz < initList.size()) ? initList.size() : sz;

	std::size_t object_size = count * sizeof(T);
	std::size_t padding = ( ( sizeof(Allocated_Block) + object_size) % 8 == 0) ? 0 : 8 - (( sizeof(Allocated_Block) + object_size) % 8);
	std::size_t size_required = sizeof(Allocated_Block) + object_size + padding;

	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	Freeblock* PrevBlock = nullptr;
	Freeblock* FreeMem = Free_Blocks_List;

	Freeblock* BestFit_Prev{ nullptr };
	Freeblock* BestFit{ nullptr };

	while (FreeMem != nullptr) {

		if (FreeMem->size == size_required) { //Check if this memory block has enough space
			BestFit = FreeMem;
			break;
		}
		else if (FreeMem->size > size_required) { //Check if this memory block has enough space

			if (BestFit) { //Check if we already have a best fit
				if (BestFit->size < FreeMem->size) {
					BestFit_Prev = PrevBlock;
					BestFit = FreeMem; //Choose the Smallest memory block that is big enough to contain the objects
					
				}
			}
			else {
				BestFit = FreeMem;

			}
		}
		PrevBlock = FreeMem;
		FreeMem = FreeMem->next;
	}

	if (!BestFit) { //Unable to find a fitting memory block 
		return nullptr;
	}

	size_t Block_size = BestFit->size;
	Freeblock* next_block = BestFit->next;

	Allocated_Block* head = reinterpret_cast<Allocated_Block*>(reinterpret_cast<char*>(BestFit) + padding);
	T* start = reinterpret_cast<T*>(head + 1);
	T* end = start + count;
	T* construct_p = start;

	for (const T& obj : initList) {
		*(construct_p) = obj;
		++construct_p;
	}

	while (construct_p != end) {
		new (construct_p) T();
		++construct_p;
	}

	if (Block_size > size_required) { //Memmory block size is larger that what we need, we will put back the leftover free memories.
		Freeblock* newfree_block = reinterpret_cast<Freeblock*>(end);
		newfree_block->size = Block_size - (size_required);
		newfree_block->next = next_block;
	
		if (BestFit_Prev) {
			BestFit_Prev->next = newfree_block;
		}
		else {	//The memory we allcoated is at the start of the list.
			Free_Blocks_List = newfree_block;
			
		}
	}
	else {
		if (BestFit_Prev) {
			BestFit_Prev->next = next_block;
		}
		else {	//The memory we allcoated is at the start of the list.
			Free_Blocks_List = next_block;
		}
	}

	//Block_size->next = reinterpret_cast<Freeblock*>(end);
	head->size = size_required;


	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += size_required;

	return start;
}


/*
	My replacement for c++ new function
	Allocate storage space for 1 object
	If you dont pass in any value/object inside, it will just default construct the object
*/
template<typename T>
T* ListAllocator::Allocate(T& object) {
	std::size_t size_required = sizeof(Allocated_Block) + sizeof(T);

	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	Freeblock* PrevBlock = nullptr;
	Freeblock* FreeMem = Free_Blocks_List;

	Freeblock* BestFit_Prev{ nullptr };
	Freeblock* BestFit{ nullptr };


	while (FreeMem != nullptr) {

		if (FreeMem->size == size_required) { //Check if this memory block has enough space
			BestFit = FreeMem;
			break;
		}
		else if (FreeMem->size > size_required) { //Check if this memory block has enough space

			if (BestFit) { //Check if we already have a best fit
				if (BestFit->size < FreeMem->size) {
					BestFit_Prev = PrevBlock;
					BestFit = FreeMem; //Choose the Smallest memory block that is big enough to contain the objects
				}
			}
			else {
				BestFit = FreeMem;
			}
		}

		PrevBlock = FreeMem;
		FreeMem = FreeMem->next;
	}

	if (!BestFit) { //Unable to find a fitting memory block 
		return nullptr;
	}

	Allocated_Block* head = reinterpret_cast<Allocated_Block*>(BestFit);
	T* start = reinterpret_cast<T*>(head + 1);
	T* end = start + 1;
	*start = object;


	if (BestFit->size > size_required) { //Memmory block size is larger that what we need, we will put back the leftover free memories.
		Freeblock* newfree_block = reinterpret_cast<Freeblock*>(end);
		newfree_block->size = BestFit->size - (size_required);
		newfree_block->next = BestFit->next;
		if (BestFit_Prev) {
			BestFit_Prev->next = newfree_block;
		}
		else {	//The memory we allcoated is at the start of the list.
			Free_Blocks_List = newfree_block;
		}
	}
	else {
		if (BestFit_Prev) {
			BestFit_Prev->next = BestFit->next;
		}
		else {	//The memory we allcoated is at the start of the list.
			Free_Blocks_List = BestFit->next;
		}
	}

	BestFit->next = reinterpret_cast<Freeblock*>(end);
	BestFit->size = size_required;

	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += size_required;

	return start;
}


/*
	My replacement for c++ delete function
	Rewind the pointer in the allocator to signify that the memory is freed
	the pointer passed in will be set to a nullptr (just like delete)
*/
template<typename T>
void ListAllocator::Rewind(T*& ptr) noexcept {
	Freeblock* start = reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(ptr)-sizeof(Freeblock));
	Freeblock* end = start->next;
	
	Freeblock* prev = nullptr;
	Freeblock* check = Free_Blocks_List;

	while (check) {
		if (check == end) { //We found a free block thats connected to the end of the current block
			BaseAllocator::m_usedBytes -= start->size;
			--BaseAllocator::m_numAllocations;
			if (prev) {
				std::cout << "A\n";
				if (reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(prev) + prev->size) == start) { //Check if the prev block is adjacent to the current block
					prev->size += start->size + check->size;
					prev->next = check->next;
				}
				else {
					start->size += check->size;
					start->next = check->next;
					prev->next = start;
				}
			}
			else {	
				std::cout << "B\n";
				//Current block is all the way at the front
				start->size += check->size;
				start->next = check->next; 
				Free_Blocks_List = start;  //Set the current block as the first block in the list
			}
	
			return;
		}
		else if (check > end) { //We have already went past all the memory blocks thats near the current one
			std::cout << "over\n";
			BaseAllocator::m_usedBytes -= start->size;
			--BaseAllocator::m_numAllocations;
			if (prev) {
				if (reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(prev) + prev->size) == start) { //Check if the prev block is adjacent to the current block
					prev->size += start->size;
				}
				else {						  //Current block is all the way at the front
					start->next = check;
					Free_Blocks_List = start; //Set the current block as the first block in the list
				}
			}
			else {
				start->next = Free_Blocks_List;
				Free_Blocks_List = start;
			}
			
			return;
		}
		prev = check;
		check = check->next;
	}

	if (prev) { //We have looped through all the memories, and the current block is all the way at the back
		check->next = start;
	}
	else { //The linked list is empty, the current block will be the first memory block in the list
		Free_Blocks_List = start;
	}

	BaseAllocator::m_usedBytes -= start->size;
	--BaseAllocator::m_numAllocations;

}