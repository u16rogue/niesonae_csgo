#pragma once

#include <dll/initialization/init_base.hpp>

namespace init
{
	init::result interfaces()
	{
		interfaces::engine     = modules::engine         .create_interface <sdk::valve::IVEngineClient>    (sdk_fnv_contracted_len_cx("VEngineClient0"));
        interfaces::panel      = modules::vgui2          .create_interface <sdk::valve::IPanel>            (sdk_fnv_contracted_len_cx("VGUI_Panel"));
        interfaces::surface    = modules::vguimatsurface .create_interface <sdk::valve::ISurface>          (sdk_fnv_contracted_len_cx("VGUI_Surface"));
        interfaces::renderview = modules::engine         .create_interface <sdk::valve::IVRenderView>      (sdk_fnv_contracted_len_cx("VEngineRenderView0"));
        interfaces::entitylist = modules::client         .create_interface <sdk::valve::CClientEntityList> (sdk_fnv_contracted_len_cx("VClientEntityList0"));
        interfaces::client     = modules::client         .create_interface <sdk::valve::IBaseClientDLL>    (sdk_fnv_contracted_len_cx("VClient0"));
        interfaces::dxdevice   = **modules::shaderapidx9 .sigscan_traverse <IDirect3DDevice9 **>           (sdk_sig_cache_as_arg_cx("A3 ?? ?? ?? ?? 8D 47"), 0x1); // mov dx9device*, eax
        interfaces::clientmode = **sdk::ptr::             traverse         <sdk::valve::IClientMode **>    (sdk_to_ptr(interfaces::client), 0x0, 0x28, 0x5);
        interfaces::hud        = *modules::client        .sigscan_traverse <sdk::valve::CHud *>            (sdk_sig_cache_as_arg_cx("E8 ?? ?? ?? ?? 80 3D ?? ?? ?? ?? ?? 74 2A"), 0x14); // mov ecx, offset CHud*
        interfaces::hudchat    = interfaces::hud        ->find_element     <sdk::valve::CHudChat>          (sdk_fnv_contracted_len_cx("CHudChat"));

        __init_assert(interfaces::engine,     L"\nIVEngineClient interface was not found");
        __init_assert(interfaces::panel,      L"\nIPanel interface was not found");
        __init_assert(interfaces::surface,    L"\nISurface interface was not found");
        __init_assert(interfaces::renderview, L"\nIVRenderView interface was not found");
        __init_assert(interfaces::entitylist, L"\nCClientEntityList class was not found");
        __init_assert(interfaces::client,     L"\nIBaseClientDLL interface was not found");
        __init_assert(interfaces::dxdevice,   L"\nIDirect3DDevice9 interface was not found");
        __init_assert(interfaces::clientmode, L"\nIClientMode interface was not found");
        __init_assert(interfaces::hud,        L"\nCHud class was not found");
        __init_assert(interfaces::hudchat,    L"\nCHudChat class was not found");

		return init::result::SUCCESS;
	}
}