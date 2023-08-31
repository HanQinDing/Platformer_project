#pragma once
#include "Base_Allocator.hpp"
#include <initializer_list>

class LinearAllocator : public BaseAllocator 
{
	public:


		//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
		// So we dont not allow copy construct and copy assignemnt for allocator class
		LinearAllocator(const  LinearAllocator&) = delete;
		LinearAllocator& operator=(LinearAllocator&) = delete;


		LinearAllocator() = default;

		~LinearAllocator() = default;

		template<typename T, std::size_t sz = 1>
		T* Reserve(const std::initializer_list<T>& initList = {});

		template<typename T>
		T* Reserve(T& object);

		//void Free() override;

		template<typename T>
		void Return(T*& ptr) noexcept;

		void Initialise(std::size_t sz) noexcept;
	


	protected:

		void* m_current;
};


/*
  My replacement for c++ new[] function (Allocate storage space for array)
  Tried to squeeze 3 different overloads into 1 function definition 

  1.  Reserve<int, sz>() 
	  - all the objects in the array will be default constructed

  2.  Reserve<int>(initializerList) 
	  - size of array  equal to size of initializer_list. 
	  - Copy everything in init_list to array

  3.  Reserve<int, sz>(initializerList)
	  - ONLY DO THIS IF YOUR ACTUAL ARRAY IS BIGGER THAN THE INITIALIZER LIST
	  - size of array equal to size entered in the "< >" angle braces.
	  - Copy everything in init_list to array, any empty slots left in the array will be filled with default constructed object
*/
template<typename T, std::size_t sz>
T* LinearAllocator::Reserve(const std::initializer_list<T>& initList)
{
	std::size_t count = (sz < initList.size()) ? initList.size() : sz;
	std::size_t sizeRequired = count * sizeof(T);

	assert(sizeRequired > 0 && BaseAllocator::m_usedBytes + sizeRequired <= (BaseAllocator::m_size));

	T* front = reinterpret_cast<T*>(m_current);
	T* pos =  front;
	T* end = pos + count;
	
	for (const T& obj : initList)
	{
		*(pos) = obj;
		++pos;
	}

	while(pos != end)
	{
		new (pos) T();
		++pos;
	}

	m_current = reinterpret_cast<char*>(m_current) + sizeRequired;
	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += sizeRequired;

	return front;
}

/*
	My replacement for c++ new function
	Allocate storage space for 1 object
	If you dont pass in any value/object inside, it will just default construct the object
*/
template<typename T>
T* LinearAllocator::Reserve(T& object)
{
	std::size_t sizeRequired = sizeof(T);
	assert(sizeRequired > 0 && BaseAllocator::m_usedBytes + sizeRequired <= (BaseAllocator::m_size));

	T* front = reinterpret_cast<T*>(m_current);
	*(front) = object;

	m_current = reinterpret_cast<char*>(m_current) + sizeRequired;
	++BaseAllocator::m_numAllocations;
	BaseAllocator::m_usedBytes += sizeRequired;

	return front;
}

/*
	My replacement for c++ delete function
	Rewind the pointer in the allocator to signify that the memory is freed
	the pointer passed in will be set to a nullptr (just like delete)
*/
template<typename T>
void LinearAllocator::Return(T*& ptr) noexcept
{
	assert(m_current >= ptr && BaseAllocator::m_start <= ptr && ptr != nullptr);
	std::size_t arraySize = reinterpret_cast<char*>(m_current) - reinterpret_cast<char*>(ptr);

	for (T* pos{ ptr }; pos != m_current; ++pos)
	{
		m_start->~T();
	}

	m_current = ptr;
	BaseAllocator::m_usedBytes += arraySize;
	--BaseAllocator::m_numAllocations;
	ptr = nullptr;

}
