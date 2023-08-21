#include "Linear_Allocator.hpp"
#include <utility>





void LinearAllocator::Initialise(std::size_t sz) noexcept {
	BaseAllocator::start = new void*[sz];
	current = BaseAllocator::start;
	BaseAllocator::m_size = sz;
	BaseAllocator::m_usedBytes = 0;
	BaseAllocator::m_numAllocations = 0;
}