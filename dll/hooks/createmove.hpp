#pragma once

#include <sdk/utils/hook.hpp>
#include <sdk/valve_sdk/interface/IClientMode.hpp>
#include <sdk/valve_sdk/usercmd.hpp>

namespace hooks
{
	// this is a __stdcall, the this pointer is never passed, shouldn't cause any performance/runtime issue since first 2
	// params are in registers rather than stack, 2nd parameter is also used by the patch to point somewhere in the stack
	// containing the pushed bSendPacket
	using  createmove_t                 = void (__fastcall)(sdk::valve::IClientMode *, bool *, float , sdk::valve::CUserCmd *);
	inline createmove_t *new_createmove = nullptr;

	// TODO: investigate issue with smoothing
	inline sdk::hook<hooks::createmove_t> hk_createmove([](sdk::valve::IClientMode *thisptr, bool *send_packet, float flInputSampleTime, sdk::valve::CUserCmd *cmd) -> void
	{
		if (cmd->command_number == 0)
			return;

		return;
	});
}
