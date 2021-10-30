#pragma once

#include <sdk/color.hpp>
#include <sdk/console.hpp>
#include <sdk/hash/fnv.hpp>
#include <sdk/valve_sdk/utlvector.hpp>

#include "hudelement.hpp"

namespace sdk::valve
{
	class CHud
	{
	public:
		static const int			    HUDPB_HORIZONTAL;
		static const int			    HUDPB_VERTICAL;
		static const int			    HUDPB_HORIZONTAL_INV;
		int							    m_iKeyBits;
		float						    m_flMouseSensitivity;
		float						    m_flMouseSensitivityFactor;
		float						    m_flFOVSensitivityAdjust;
		sdk::color						m_clrNormal;
		sdk::color						m_clrCaution;
		sdk::color						m_clrYellowish;
		CUtlVector<CHudElement *>	    m_HudList;
		CUtlVector<sdk::ptr_t>	        m_HudPanelList;
		CUtlVector<const char *>		m_RenderGroupNames;
		sdk::byte_t                     m_RenderGroups[0x1c]; // padded. lazy to implement. original: CUtlMap< int, CHudRenderGroup * >
		float						    m_flScreenShotTime;
		int							    m_nSplitScreenSlot;
		bool						    m_bEngineIsInGame;
		int							    m_iDisabledCount;

		template <typename hud_t>
		hud_t *find_element(sdk::hash::fnv_contracted_t hashed_name)
		{
			sdk::hash::fnv32_t name = sdk_fnv_contracted_hi(hashed_name);
			sdk::size32_t      len  = sdk_fnv_contracted_lo(hashed_name);

			for (int idx = 0; idx < this->m_HudList.m_Size; idx++)
			{
				if (this->m_HudList.m_pMemory[idx] && sdk::hash::fnv32(this->m_HudList.m_pMemory[idx]->GetName(), len) == name)
				{
					sdk_con_cout_debug("\n[HUD ELEMENT] Found: " << this->m_HudList.m_pMemory[idx]->GetName());
					return reinterpret_cast<hud_t *>(this->m_HudList.m_pMemory[idx]);
				}
			}

			return nullptr;
		}
	};
}