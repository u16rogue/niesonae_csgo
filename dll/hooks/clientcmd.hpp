#pragma once

#include <dll/chat_commands/cm_manager.hpp>
#include <sdk/valve_sdk/interface/IVEngineClient.hpp>
#include <sdk/utils/hook.hpp>

namespace hooks
{
	using  clientcmd_t                = void(__fastcall)(sdk::valve::IVEngineClient*, void*, const char*);
	inline clientcmd_t *new_clientcmd = nullptr;

	inline sdk::hook<hooks::clientcmd_t> hk_clientcmd( [](sdk::valve::IVEngineClient *thisptr, void *pad, const char *cmdstring) -> void
	{
		if (cm::manager::instance().ClientCMD(cmdstring) == cm::manager::e_result::ABORT)
			return;

		return hooks::new_clientcmd(thisptr, nullptr, cmdstring);
	});
}