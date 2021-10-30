#pragma once

#include <dll/initialization/init_base.hpp>

namespace init
{
	init::result entry()
	{
        sdk::console::init();

        sdk_con_cout(xorstr("niesonae build " __DATE__ " " __TIME__));
        sdk_con_cout_debug(" [DEBUG]");

        sdk_con_cout_debug("\ninitializing niesonae...");

        if (globals::dllhandle)
            imports::DisableThreadLibraryCalls(globals::dllhandle);

        __init_wait_for_eval
        (
            (globals::hwndCSGO = imports::FindWindowW(xorstr(L"Valve001"), xorstr(L"Counter-Strike: Global Offensive"))) == nullptr,
            L"\nTimed out attempting to obtain window handle"
        );

        __init_wait_for_eval
        (
            sdk::env::ldr_find(sdk_fnv_contracted_len_cx("serverbrowser")) == nullptr,
            L"\nTimed out waiting for serverbrowser.dll"
        );

        return init::result::SUCCESS;
	}
}