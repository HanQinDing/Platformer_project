/*!************************************************************************
\file Memory_manager.cpp
\author Han Qin Ding

\brief
This file contains functions for a memory manager system.
You can allocate/deallocate dynamic memory through this memory manager.
You can also print out details of each of the allocators.
By default, we will be using our custom allocator. (not std::allocator)

Functions you can use:

	- InitializeAllAlocators();
		initialize all the allocators in the memory manager

	- FreeAllAlocators();
		Free all the memories that were allocated in the memory manager

	- PrintAllDetails();
		Print out the details of all of the allocators in the memory manager

	- void ChangeAllocator(bool useCustomAllocator);
		In the event that the custom allocator does not work, you can call this
		function right after InitializeAllAlocators() to switch to std::allocator.
		You can proceed to use the other functions as normal

		template<typename T, std::size_t sz >
	- T* Reserve(const std::initializer_list<T>& initList);
		Call this function you want to allocate a memory for an array of objects and you already have an initializer list.
		Enter the object type in the < >

		template<typename T, std::size_t sz >
	- T* Reserve(const std::initializer_list<T>& initList);
		Call this function you want to allocate a memory for an array of objects but you only know the array size.
		Enter the object type and the array size in the < >

		template<typename T>
	- T* Reserve(T& obj);
		Call this function you want to allocate a memory 1 lvalue object.
		Enter the object type in the < >

		template<typename T>
	- T* Reserve(const T& obj);
		 Call this function you want to allocate a memory 1 rvalue object.
		 Enter the object type in the < >

		template<typename T, ALLOCATOR_TYPE allocatorType = LIST_ALLOCATOR>
	- void Return(T*&);
		Call this function when you want to free a dynamic allcoated memory
		you can just pass in the pointer into the function param
		IF YOU PASS IN AN INVALID MEMORY OR A MEMORY THATS NOT ALLOCATED BY THIS MEMORY MANAGER, IT WILL PRINT OUT ERROR MESSAGE



EXAMPLE ON HOW TO ALLOCATE:

			[ Allocate memory for single object ]
	 1. int* ptr = Reserve<int>( obj );  // allocating memory for 1 int object

			[ Allocate memory for an array ( using initializer list ) ]
	 2. int* array = Reserve<int>( initializer_list );  // allocating memory for an array filled with objects from initializer list

			[ Allocate memory for an array ( using array size ) ]
	 3. int* array = Reserve< int, 20 >( );  // allocating memory for an array of size 20. All objects inside are default constructed


EXAMPLE ON HOW TO DEALLOCATE:

			[ Deallocate memory for any memory that was dynamically allocated by memory manager ]
	 1. Return( ptr );  // You just need to pass in the pointer, the allocator will know if its an array or a single object

**************************************************************************/
#include "Memory_manager.hpp"
#include <chrono>
#include <algorithm>
#include <Windows.h>
#include <sstream>

namespace CustomAllocators
{
	ListAllocator g_listAllocator;
	LinearAllocator g_linearAllocator;
	bool g_useMyAllocator{ true };
  std::vector<void*>g_arrayMem;
  std::vector<void*>g_objMem;
}



/************************************************************************/ /*!
\ brief
Initialize all the Allocators in the memory manager.
*/
/************************************************************************/
void InitializeAllAlocators()
{
	CustomAllocators::g_linearAllocator.Initialise(100);
	CustomAllocators::g_listAllocator.Initialise(10000000);

}

/************************************************************************/ /*!
\ brief
Free all the Allocators in the memory manager.
*/
/************************************************************************/
void FreeAllAlocators() 
{
	if (CustomAllocators::g_useMyAllocator) 
	{
		CustomAllocators::g_linearAllocator.PrintMemLeak();
		CustomAllocators::g_listAllocator.PrintMemLeak();
	}
	else
	{
		PrintMemLeak();
	}

	CustomAllocators::g_linearAllocator.Free();
	CustomAllocators::g_listAllocator.Free();
	//for (void* v : CustomAllocators::g_arrayMem) {
	//	delete[] v;
	//}
	//for (void* v : CustomAllocators::g_objMem) {
	//	delete v;
	//}
}



/************************************************************************/ /*!
\ brief
Print out the details of all the Allocators in the memory manager
*/
/************************************************************************/
void PrintAllDetails() 
{
	CustomAllocators::g_linearAllocator.PrintDetails();
	CustomAllocators::g_listAllocator.PrintDetails();
}

/************************************************************************/ /*!
\ brief
This function is used for testing all the allocators in the memory manager.
It will put test objects into each allocator to test if they are working fine
(this function is used for testing and debugging)
*/
/************************************************************************/
void TestAllAllocators()
{
	//	auto startTime = std::chrono::high_resolution_clock::now();
//
//	test_Obj* test2 = new test_Obj[100];
//	auto endTime = std::chrono::high_resolution_clock::now();
//
//	//int* test4 = Test_allocator.Reserve<int>({ 10 });
//
//	
//
//	test_Obj* test = Test_allocator.Reserve<test_Obj,100>();
//	auto endTime2 = std::chrono::high_resolution_clock::now();
//
//	Test_allocator.Print_List();
//
////	test_Obj* test5 = Test_allocator.Reserve<test_Obj, 100>();
//
//
//
//	auto first_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
//	auto second_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - endTime);
//
//	std::cout << sizeof(test_Obj);
//	std::cout << "ALLOCATOR TIME: " << second_duration.count() << "\n";
//	std::cout << "NEW TIME: " << first_duration.count() << "\n\n\n";
}

/************************************************************************/ /*!
\ brief
This function will be called if you want to change the allocator we are using.
In the event that the custom allocator does not work properly, we will go back to std::allocator instead

\param useCustomAllocator
	bool variable to determine whether to use our custom allocator or go back to std::allocator (new, delete)
*/
/************************************************************************/
void ChangeAllocator(bool useCustomAllocator) 
{
	CustomAllocators::g_useMyAllocator = useCustomAllocator;
}

void AddMemStd(void* ptr, bool isArray) 
{
	if (isArray) 
	{
		CustomAllocators::g_arrayMem.push_back(ptr);
	}
	else 
	{
		CustomAllocators::g_objMem.push_back(ptr);
	}
}

/************************************************************************/ /*!
\ brief
Checks if the memory is for an array or an object

\param [ptr]void*
	pointer to the allocated memory

\return
 bool variable to determine whether to the memory is for an array or an object
*/
/************************************************************************/
bool isArrayMem(void* ptr) 
{

	//Check if the ptr is an Array ptr
	std::vector<void*>::iterator it{ std::find(CustomAllocators::g_arrayMem.begin(), CustomAllocators::g_arrayMem.end(), ptr) };

	if (it != CustomAllocators::g_arrayMem.end()) 
	{
		CustomAllocators::g_arrayMem.erase(it);
		return true;
	}

	it = std::find(CustomAllocators::g_objMem.begin(), CustomAllocators::g_objMem.end(), ptr);
	CustomAllocators::g_objMem.erase(it);
	return false;
}


/************************************************************************/ /*!
\ brief
Prints out the details of the memory leaks if any.
*/
/************************************************************************/
void PrintMemLeak()
{
	if ((CustomAllocators::g_arrayMem.size() != 0) || (CustomAllocators::g_objMem.size() != 0))
	{
		OutputDebugStringA("\n std::Allocator Mem Leak:\n");
		OutputDebugStringA("---------------------------------------------\n");
		if (CustomAllocators::g_arrayMem.size() != 0)
		{ // We will print mem leak details if required
			std::string output = "Number of Arrays not free: " + std::to_string(CustomAllocators::g_arrayMem.size()) + "\n";
			OutputDebugStringA(output.c_str());
		}
		if (CustomAllocators::g_objMem.size() != 0)
		{ // We will print mem leak details if required
			std::string output = "Number of Objects not free: " + std::to_string(CustomAllocators::g_objMem.size()) + "\n";
			OutputDebugStringA(output.c_str());
		}
		OutputDebugStringA("----------------------------------------------\n\n");
	}
}