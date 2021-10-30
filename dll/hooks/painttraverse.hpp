#pragma once

#include "../globals.hpp"
#include <sdk/utils/hook.hpp>
#include <sdk/valve_sdk/interface/IPanel.hpp>

namespace hooks
{
	using  painttraverse_t                    = void(__fastcall)(sdk::valve::IPanel *, void*, unsigned long, bool, bool);
	inline painttraverse_t *new_painttraverse = nullptr;

	inline sdk::hook<hooks::painttraverse_t> hk_painttraverse([](sdk::valve::IPanel *thisptr, void *pad, unsigned long panel, bool forceRepaint, bool allowForce) -> void
	{
		hooks::new_painttraverse(thisptr, pad, panel, forceRepaint, allowForce);

		if (panel != globals::matsystoppanel_id)
			return;
	});

}
