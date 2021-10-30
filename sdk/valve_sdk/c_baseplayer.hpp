#pragma once

#include <sdk/utils/netvar_parser.hpp>
#include "c_baseentity.hpp"

namespace sdk::valve
{
	class C_BasePlayer : public C_BaseEntity
	{
	public:
		sdk_netvar_create_this(int, DT_BasePlayer, m_iHealth);
	};
}