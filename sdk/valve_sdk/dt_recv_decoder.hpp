#pragma once

#include "dt_recv.hpp"
#include "utlvector.hpp"

namespace sdk::valve
{
	class CRecvDecoder
	{
	public:
		sdk::ptr_t             m_pTable;
		sdk::ptr_t             m_pClientSendTable;
		sdk::byte_t	           m_Precalc[0x12c]; // padded, lazy to implement. will do in the future
		CUtlVector<sdk::ptr_t> m_Props;
		CUtlVector<sdk::ptr_t> m_DatatableProps;
		sdk::ptr_t             m_pDTITable;
	};
}