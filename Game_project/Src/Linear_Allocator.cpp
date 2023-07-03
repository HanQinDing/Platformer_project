#include "Linear_Allocator.hpp"
#include <utility>


template<typename T>
void LinearAllocator<T>::Rewind(pointer ptr) noexcept {
	assert(current >= ptr && BaseAllocator<T>::start <= ptr);

	current = ptr;
	BaseAllocator<T>::m_usedBytes = static_cast<size_type>(current - BaseAllocator<T>::start);
}

template<typename T>
typename LinearAllocator<T>::pointer  LinearAllocator<T>::Allocate(size_type n) {
	assert(n > 0 && BaseAllocator<T>::m_usedBytes + n <= (BaseAllocator<T>::m_size));

	pointer new_p = current;
	current += n;
	

	return new_p;
}

template<typename T>
void LinearAllocator<T>::Initialise(size_type sz) noexcept {
	BaseAllocator<T>::start = new T[sz];
	current = BaseAllocator<T>::start;
	BaseAllocator<T>::m_size = sz;
	BaseAllocator<T>::m_usedBytes = 0;
	BaseAllocator<T>::m_numAllocations = 0;
}