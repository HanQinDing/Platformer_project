#pragma once
#include "Base_Allocator.hpp"
#include <initializer_list>

class LinearAllocator : public BaseAllocator {
public:


	//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
	// So we dont not allow copy construct and copy assignemnt for allocator class
	LinearAllocator(const  LinearAllocator&) = delete;
	LinearAllocator& operator=(LinearAllocator&) = delete;


	LinearAllocator() = default;

	~LinearAllocator() = default;

	template<typename T, std::size_t sz = 1>
	T* Allocate(const std::initializer_list<T>& initList = {});

	template<typename T>
	T* Allocate(T& object);



	//void Free() override;

	template<typename T>
	void Rewind(T*& ptr) noexcept;

	void Initialise(std::size_t sz) noexcept;
	


protected:

	void* current;
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
T* LinearAllocator::Allocate(const std::initializer_list<T>& initList) {

	std::size_t count = (sz < initList.size()) ? initList.size() : sz;
	std::size_t size_required = count * sizeof(T);

	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	T* new_p = static_cast<T*>(current);
	T* construct_p =  new_p;
	T* end_p = construct_p + count;
	
	
	for (const T& obj : initList) {
		*(construct_p) = obj;
		++construct_p;
	}


	while(construct_p!=end_p) {
		*(construct_p) = T();
		++construct_p;
	}

	
	current = static_cast<char*>(current) + size_required;

	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += size_required;

	return new_p;
}

/*
	My replacement for c++ new function
	Allocate storage space for 1 object
	If you dont pass in any value/object inside, it will just default construct the object
*/
template<typename T>
T* LinearAllocator::Allocate(T& object) {

	std::size_t size_required = sizeof(T);
	assert(size_required > 0 && BaseAllocator::m_usedBytes + size_required <= (BaseAllocator::m_size));

	T* new_p = static_cast<T*>(current);
	*(new_p) = object;
	current = static_cast<char*>(current) + size_required;

	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += size_required;

	return new_p;
}

/*
	My replacement for c++ delete function
	Rewind the pointer in the allocator to signify that the memory is freed
	the pointer passed in will be set to a nullptr (just like delete)
*/
template<typename T>
void LinearAllocator::Rewind(T*& ptr) noexcept {
	assert(current >= ptr && BaseAllocator::start <= ptr && ptr != nullptr);

	std::size_t array_size = static_cast<char*>(current) - static_cast<char*>(ptr);
	for (T* start{ ptr }; start != current; ++start) {
		//start->~T();
	}

	current = ptr;
	

	BaseAllocator::m_usedBytes += array_size;
	--BaseAllocator::m_numAllocations;
	ptr = nullptr;
}
