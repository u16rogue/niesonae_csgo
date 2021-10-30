#pragma once

#include <sdk/types.hpp>
#include "dt_recv.hpp"

namespace sdk::valve
{
	class ClientClass
	{
		class IClientNetworkable;

		using CreateClientClassFn = IClientNetworkable*(*)(int entnum, int serialNum); // typedef IClientNetworkable*	(*CreateClientClassFn)( int entnum, int serialNum );
		using CreateEventFn       = IClientNetworkable*(*)(void);                      // typedef IClientNetworkable*	(*CreateEventFn)();

	public:
		CreateClientClassFn  m_pCreateFn;
		CreateEventFn        m_pCreateEventFn;
		char                *m_pNetworkName;
		RecvTable           *m_pRecvTable;
		ClientClass         *m_pNext;
		int			         m_ClassID;
		const char          *m_pMapClassname;
	};
}