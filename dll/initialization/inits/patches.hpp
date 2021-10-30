#pragma once

#include <dll/initialization/init_base.hpp>
#include <dll/patches/cm_calls.hpp>

namespace init
{
	init::result patches()
	{
		__init_assert(patches::cmove_sendpacket_cinput_cm. set_write(modules::client.sigscan<sdk::byte_t>(sdk_sig_cache_as_arg_cx("FF D0 84 C0 74 0C 8B 0D"))),    "\nFailed to patch CInput::CreateMove call!");
		__init_assert(patches::cmove_cinput_ems.           set_write(modules::client.sigscan<sdk::byte_t>(sdk_sig_cache_as_arg_cx("8B 06 8B CE 6A 00 FF 50 08"))), "\nFailed to patch CInput::ExtraMouseSample call setup!");

		return init::result::SUCCESS;
	}
}