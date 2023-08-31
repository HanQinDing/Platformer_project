#include "Linear_Allocator.hpp"
#include <utility>



void LinearAllocator::Initialise(std::size_t sz) noexcept 
{
	BaseAllocator::m_start = new void*[sz];
	m_current = BaseAllocator::m_start;
	BaseAllocator::m_size = sz;
	BaseAllocator::m_usedBytes = 0;
	BaseAllocator::m_numAllocations = 0;
}