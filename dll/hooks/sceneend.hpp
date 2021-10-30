#pragma once

#include <sdk/utils/hook.hpp>
#include <sdk/valve_sdk/interface/IVRenderView.hpp>

#include <dll/hacks/engine_glow.hpp>

namespace hooks
{
	using  sceneend_t               = void(__fastcall)(sdk::valve::IVRenderView *, void *);
	inline sceneend_t *new_sceneend = nullptr;

	inline sdk::hook<hooks::sceneend_t> hk_sceneend([](sdk::valve::IVRenderView *thisptr, void *pad) -> void
	{
		hooks::new_sceneend(thisptr, nullptr);
	});
}