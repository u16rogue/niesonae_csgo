#pragma once

namespace sdk::valve
{
	template <typename T>
	class CUtlVector
	{
	public:
		// ~\cstrike15_src\public\tier1\utlmemory.h (implemented by member variable: CAllocator m_Memory)
		T  *m_pMemory;
		int m_nAllocationCount;
		int m_nGrowSize;
		// --
		int m_Size;
		T  *m_pElements;
	};
}