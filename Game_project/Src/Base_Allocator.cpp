#include "Base_Allocator.hpp"

template<typename T>
const typename BaseAllocator<T>::size_type& BaseAllocator<T>::GetSize() const noexcept {
	return m_size;
}


template<typename T>
const typename BaseAllocator<T>::size_type& BaseAllocator<T>::GetUsed() const noexcept {
	return m_usedBytes;
}

template<typename T>
const typename BaseAllocator<T>::size_type& BaseAllocator<T>::GetNumAllocation() const noexcept {
	return m_numAllocations;
}

