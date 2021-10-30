#pragma once

//#include <dll/globals.hpp>
#include <sdk/types.hpp>
#include <sdk/hash/fnv.hpp>
#include <sdk/valve_sdk/dt_recv.hpp>
#include <sdk/valve_sdk/client_class.hpp>

namespace sdk::netvar
{
	// TODO: find a better solution to this linking issue
	// c_baseentity.hpp cant include this if netvar_parser.hpp includes global.hpp since global.hpp includes this and c_baseentity.hpp indirectly
	inline sdk::valve::ClientClass *client_class_first_entry = nullptr; // ghetto linking error fix

	bool class_next(sdk::valve::ClientClass **class_ptr)
	{
		if (!class_ptr)
			return false;

		if (*class_ptr == nullptr)
		{
			*class_ptr = client_class_first_entry;
			return true;
		}

		if (*class_ptr != nullptr && ((*class_ptr)->m_pNext == nullptr || (*class_ptr)->m_pNext == client_class_first_entry))
			return false;

		*class_ptr = (*class_ptr)->m_pNext;
		return true;
	}

	// not really necessary
	bool prop_next(sdk::valve::ClientClass *client_class, sdk::valve::RecvProp **prop_ptr)
	{
		if (!client_class || client_class->m_pRecvTable->m_nProps == 0 || !prop_ptr)
			return false;

		if (*prop_ptr == nullptr)
		{
			*prop_ptr = client_class->m_pRecvTable->m_pProps;
			return true;
		}

		sdk::valve::RecvProp *next_prop = *prop_ptr + 1;

		if (next_prop >= client_class->m_pRecvTable->m_pProps + client_class->m_pRecvTable->m_nProps)
			return false;

		*prop_ptr = next_prop;
		return true;
	}

	sdk::offset_t get_offset(sdk::hash::fnv64_t table_name, sdk::hash::fnv64_t prop_name)
	{
		sdk::valve::ClientClass *cc = nullptr;
		while (sdk::netvar::class_next(&cc))
		{
			if (sdk::hash::fnv64(cc->m_pRecvTable->m_pNetTableName) == table_name
			||  sdk::hash::fnv64(cc->m_pNetworkName)                == table_name)
			{
				sdk::valve::RecvProp *rp = nullptr;
				while (sdk::netvar::prop_next(cc, &rp))
				{
					if (sdk::hash::fnv64(rp->m_pVarName) == prop_name)
					{
						sdk_con_cout_debug("\n[NETVAR] " << cc->m_pRecvTable->m_pNetTableName << "->" << rp->m_pVarName << " = " << rp->m_Offset);
						return rp->m_Offset;
					}
				}
			}
		}
		
		return 0;
	}
}

// TODO: make intellisense shut up (check c_baseentity.hpp using this macro as reference)
#define sdk_netvar_create_this(type, table_name, prop_name) \
type &prop_name##() \
{ \
	static sdk::offset_t offset##_##prop_name = sdk::netvar::get_offset(sdk_fnv64_cx(#table_name), sdk_fnv64_cx(#prop_name)); \
	return *reinterpret_cast<type*>(reinterpret_cast<sdk::ptr_t>(this) + offset##_##prop_name); \
}