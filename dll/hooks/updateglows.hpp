#pragma once

#include <dll/hacks/engine_glow.hpp>
#include <sdk/types.hpp>
#include <sdk/valve_sdk/c_cs_player.hpp>
#include <sdk/utils/hook.hpp>

namespace hooks
{
	using  updateglows_t                  = void (__fastcall)(sdk::valve::C_CSPlayer *);
	inline updateglows_t *new_updateglows = nullptr;

	inline sdk::hook<hooks::updateglows_t> hk_updateglows([](sdk::valve::C_CSPlayer *thisptr) -> void
	{
		if (hacks::engine_glow::instance().enable) // dont update glow if we're already doing it ourself
			return;

		new_updateglows(thisptr);
	});
}