#pragma once
#include "Base_Allocator.hpp"

template <typename T>
class LinearAllocator : public BaseAllocator<T> {
public:

	using typename BaseAllocator<T>::pointer;
	using typename BaseAllocator<T>::size_type;
	

	//Having two instances that manage the same underlying memory can lead to conflicts and unexpected behavior.
	// So we dont not allow copy construct and copy assignemnt for allocator class
	LinearAllocator(const  LinearAllocator&) = delete;
	LinearAllocator& operator=(LinearAllocator&) = delete;


	LinearAllocator() = default;

	~LinearAllocator() = default;

	pointer Allocate(size_type n) override;
	void Rewind(pointer ptr) noexcept;
	void Initialise(size_type sz) noexcept;
	


protected:

	void* current;
};
