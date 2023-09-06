/*!************************************************************************
\file BaseAllocator.hpp
\author Han Qin Ding

\brief
This file contains the base class for all allocators
The base class contains essential data members like Allocator sizee and Number of Allocation
**************************************************************************/
#include "Base_Allocator.hpp"

/************************************************************************/ /*!
\ brief
Return the total size of the Allocator

\return
 total size of the Allocator
*/
/************************************************************************/
const std::size_t& BaseAllocator::GetSize() const noexcept 
{
  return m_size;
}


/************************************************************************/ /*!
\ brief
Return the total number of memory used (bytes)

\return
 size of the memory used (bytes)
*/
/************************************************************************/
const std::size_t& BaseAllocator::GetUsed() const noexcept 
{
	return m_usedBytes;
}

/************************************************************************/ /*!
\ brief
Return the total number of free memory left (bytes)

\return
 size of the free memory left
*/
/************************************************************************/
const std::size_t BaseAllocator::GetFree() const noexcept 
{
  return (m_size - m_usedBytes);
}


/************************************************************************/ /*!
\ brief
Return the total number allocations left in the allocator

\return
 number of allocations left in the allocator
*/
/************************************************************************/
const std::size_t& BaseAllocator::GetNumAllocation() const noexcept 
{
	return m_numAllocations;
}

