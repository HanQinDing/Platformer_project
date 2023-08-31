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
	char* Memory_end;
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
	//Determine the actual memory size needed (object + header)
	std::size_t count = (sz < initList.size()) ? initList.size() : sz;
	std::size_t object_size = count * sizeof(T);
	std::size_t padding = ( ( sizeof(Allocated_Block) + object_size) % 8 == 0) ? 0 : 8 - (( sizeof(Allocated_Block) + object_size) % 8);
	std::size_t size_required = sizeof(Allocated_Block) + object_size + padding;

	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	//Traverse through the List to find the Best suitable Memory block
	Freeblock* PrevBlock = nullptr;
	Freeblock* FreeMem = Free_Blocks_List;

	Freeblock* BestFit{ nullptr };

	//Memory blocks are arranged according to size (smallest at the front, largest at the back)
	while (FreeMem != nullptr) {
		if (FreeMem->size >= size_required) {
			BestFit = FreeMem;
			break;
		}
		PrevBlock = FreeMem;
		FreeMem = FreeMem->next;
	}

	if (!BestFit) { //Unable to find a fitting memory block 
		std::cout << "FAILED\n";
		return nullptr;
	}

	// Take out the memory chunk from the list 
	// Only take out the amount we need
	// The remainder will be place back into the list

	if (BestFit->size > size_required) { //Memmory block size is larger that what we need, we will put back the leftover free memories.
		Freeblock* new_block = reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(BestFit) + size_required);
		new_block->size = BestFit->size - (size_required);

		if (PrevBlock) {	 //The memory block we chose is in the middle of the list, we will slot the remaining block back into the gap
			Freeblock* Prev = Free_Blocks_List;
			Freeblock* larger = Free_Blocks_List;
			while (larger) {
				if (larger->size >= new_block->size && larger != BestFit) {
					break;
				}
				Prev = larger;
				larger = larger->next;
			}
			Prev->next = new_block;
			new_block->next = larger;
		}
		else {
			Free_Blocks_List = new_block; //The memory block we chose is at the front of the list, we will add the block back to the front
			new_block->next = BestFit->next;
	
		}
	}
	else {								 //Memory block size is just nice, we will just reconnect the memory block in the list
		if (PrevBlock) {	
			PrevBlock->next = BestFit->next;  //The memory block we chose is in the middle of the list, we will close the gap
		}
		else {
			Free_Blocks_List = BestFit->next; //The memory block we chose is at the front of the list, we will just move the list up by one
		}
	}
	// Fill up the Allocated memory block with objects
	Allocated_Block* head = reinterpret_cast<Allocated_Block*>(BestFit);
	T* start = reinterpret_cast<T*>(head + 1);
	T* end = start + count;
	T* construct_p = start;

	for (const T& obj : initList) {	//Fill up the memory block with objects from initializer_list
		*(construct_p) = obj;
		++construct_p;
	}
	
	while (construct_p != end) {	// Initialize objects into the rest of the Memory Chunk
		new (construct_p) T();
		++construct_p;
	}

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
	
	std::size_t padding = ((sizeof(Allocated_Block) + sizeof(T)) % 8 == 0) ? 0 : 8 - ((sizeof(Allocated_Block) + sizeof(T)) % 8);
	std::size_t size_required = sizeof(Allocated_Block) + sizeof(T) + padding;

	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	//Traverse through the List to find the Best suitable Memory block
	Freeblock* PrevBlock = nullptr;
	Freeblock* FreeMem = Free_Blocks_List;

	Freeblock* BestFit{ nullptr };

	//Memory blocks are arranged according to size (smallest at the front, largest at the back)
	while (FreeMem != nullptr) {
		if (FreeMem->size >= size_required) {
			BestFit = FreeMem;
			break;
		}
		PrevBlock = FreeMem;
		FreeMem = FreeMem->next;
	}

	if (!BestFit) { //Unable to find a fitting memory block 
		std::cout << "FAILED\n";
		return nullptr;
	}

	// Take out the memory chunk from the list 
	// Only take out the amount we need
	// The remainder will be place back into the list

	if (BestFit->size > size_required) { //Memmory block size is larger that what we need, we will put back the leftover free memories.
		Freeblock* new_block = reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(BestFit) + size_required);
		new_block->size = BestFit->size - (size_required);

		if (PrevBlock) {	 //The memory block we chose is in the middle of the list, we will slot the remaining block back into the gap
			Freeblock* Prev = Free_Blocks_List;
			Freeblock* larger = Free_Blocks_List;
			while (larger) {
				if (larger->size >= new_block->size && larger != BestFit) {
					break;
				}
				Prev = larger;
				larger = larger->next;
			}
			Prev->next = new_block;
			new_block->next = larger;
		}
		else {
			Free_Blocks_List = new_block; //The memory block we chose is at the front of the list, we will add the block back to the front
			new_block->next = BestFit->next;

		}
	}
	else {								 //Memory block size is just nice, we will just reconnect the memory block in the list
		if (PrevBlock) {
			PrevBlock->next = BestFit->next;  //The memory block we chose is in the middle of the list, we will close the gap
		}
		else {
			Free_Blocks_List = BestFit->next; //The memory block we chose is at the front of the list, we will just move the list up by one
		}
	}

	Allocated_Block* head = reinterpret_cast<Allocated_Block*>(BestFit);
	T* start = reinterpret_cast<T*>(head + 1);
	*start = object;

	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += size_required;


	head->size = size_required;

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

	if (ptr == nullptr) {	//Check if the pointer is null
		std::cout << "PLEASE DONT DELETE NULL POINTERS\n";
		return;
	}

	char* head_check = reinterpret_cast<char*>(ptr);
	if (head_check<BaseAllocator::start || head_check > Memory_end) { //Check if the memory block belongs to this Allocator
		std::cout << "THIS MEMORY BLOCK DOES NOT BELONG TO THIS ALLOCATOR \n";
		return;
	}
	Freeblock* cur = Free_Blocks_List;
	while (cur) {
		char* c_cur = reinterpret_cast<char*>(cur);
		if (c_cur == head_check) {
			std::cout << "You have already freed this mem\n";
			return;
		}
		if (c_cur < head_check && c_cur + (cur->size) > head_check) {
			std::cout << "You have already freed this mem\n";
			return;
		}
		cur = cur->next;
	}

	
	//Get the size of the memory block and the number of objects within it
	Allocated_Block* head = reinterpret_cast<Allocated_Block*>(ptr)-1;
	size_t size_required = head->size;
	size_t count = (size_required - sizeof(Allocated_Block) - ((size_required - sizeof(Allocated_Block)) % sizeof(T))) / sizeof(T);

	//Deconstruct all the objects within the memory block;
	T* obj = ptr;
	for (size_t i{ 0 }; i < count; ++i) {
		obj->~T();
	}

	//Merge the Memory block with any of the blocks within the list;

	char* front = reinterpret_cast<char*>(head);
	Freeblock* start = reinterpret_cast<Freeblock*>(head);
	Freeblock* end = reinterpret_cast<Freeblock*>(reinterpret_cast<char*>(head) + size_required);

	Freeblock* Before{ nullptr }, *Bef_Prev{ nullptr };
	Freeblock* After{ nullptr }, *Aft_Prev{ nullptr };

	cur = Free_Blocks_List;
	Freeblock* Prev{ nullptr };

	while (cur && !(Before && After)) {
		Aft_Prev = (cur == end) ? Prev : Aft_Prev;
		Bef_Prev = ((reinterpret_cast<char*>(cur) + cur->size) == front) ? Prev : Bef_Prev;

		After = (cur == end) ? cur: After;
	    Before = ((reinterpret_cast<char*>(cur) + cur->size) == front)? cur: Before;
	

		Prev = cur;
		cur = cur->next;
	}

	if (After) { //we can merge one of the block to the back of the current block;
		start->size += After->size;
		After->next = (After->next) ? (After->next == Before) ? (After->next)->next : After->next: After->next;
		if (Aft_Prev) {
			
			Aft_Prev->next = After->next;
		}
		else {
			Free_Blocks_List = After->next;
		}
		
	}


	if (Before) {
		Before->size = Before->size + start->size;
		Before->next = (Before->next) ? (Before->next == After) ? (Before->next)->next : Before->next:Before->next;

		if (Bef_Prev) {
			Bef_Prev->next = Before->next;
		}
		else {
			Free_Blocks_List = Before->next;
		}
		start = Before;
	}


	//Update the relevant values 
	BaseAllocator::m_usedBytes -= size_required;
	--BaseAllocator::m_numAllocations;

	//Slot the memory back into the list
	cur = Free_Blocks_List;
	Prev = nullptr;
	while (cur) {
		if (cur->size >= start->size) {
			if (Prev) {
				Prev->next = start;
			}
			else {
				Free_Blocks_List = start;
			}
			start->next = cur;
			return;	//We will return straight away after finding a slot in the list
		}
		Prev = cur;
		cur = cur->next;
	}

	if (Prev) {	//We reached the end of the list and we cant find a slot. so we will just append this memory at the back of the list
		Prev->next = start;
		
	}
	else{ //The list itself is already empty, so we will just set this as the start of the list
		Free_Blocks_List = start;
	}
	start->next = nullptr;

}