#pragma once

#include <dll/initialization/init_base.hpp>
#include <dll/offsets.hpp>
#include <sdk/gui/control_base.hpp>

namespace init
{
	init::result values()
	{
		globals::matsystoppanel_id               = *reinterpret_cast<sdk::uint32_t *>(modules::vguimatsurface.get_entry()->DllBase + offsets::matsystoppanel_id);
        globals::localplayer                     = *modules::client.sigscan_traverse<sdk::valve::C_CSPlayer **>(sdk_sig_cache_as_arg_cx("0F 45 15 ?? ?? ?? ?? 56"), 0x3); // cmovnz  edx, localplayer**
        sdk::netvar::client_class_first_entry    = interfaces::client->GetAllClasses();
        sdk::gui::control_base::rdevice          = interfaces::dxdevice;

        if (imports::D3DXCreateSprite(interfaces::dxdevice, &sdk::gui::control_base::rsprite) != D3D_OK)
            return init::result::FAIL;

        __init_assert_fnv_cmp(*sdk::ptr::traverse<const char *>(sdk_to_ptr(globals::matsystoppanel_id), 0x24, 0x50), "MatSystemTopPanel", L"\nInvalid MatSystemTopPanel ID!"); // MOV EAX,DWORD PTR DS:[ECX+24] // LEA ESI,DWORD PTR DS:[ECX+50]
        __init_assert(globals::localplayer, "\nInvalid Local Player!");
        __init_assert(sdk::netvar::client_class_first_entry, "\nInvalid class entry!");

		return init::result::SUCCESS;
	}
}