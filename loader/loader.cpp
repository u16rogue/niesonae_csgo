#pragma warning(disable : 26495) // for directx sdk

// TODO: cleanup

#include <iostream>

#include <sdk/encryption/xorstr.hpp>
#include <sdk/imports.hpp>
#include <sdk/hash/fnv.hpp>

#include "utils/utils.hpp"

#include "utils/load_bytepatch.hpp"
#include "utils/load_windir.hpp"
#include "utils/load_0pll.hpp"

int __cdecl main()
{
    HANDLE          csgo_handle = nullptr;
    PROCESSENTRY32W csgo_pe32   = { sizeof(PROCESSENTRY32W) };
    MODULEENTRY32W  csgo_me32   = { sizeof(MODULEENTRY32W) };
    wchar_t         path[256]   = { '\0' };
    sdk::size32_t   path_len    = 0;

    std::cout << xorstr("\nniesonae loader (" __DATE__ " " __TIME__ ") " DBG_MSG);
    
    // Wait for csgo.exe
    while (!get_proc_entry(&csgo_pe32, sdk_fnv64_cx(L"csgo.exe")))
    {
        if (static int wait_for = 120; --wait_for <= 0)
        {
            sdk_con_cout_debug("\nFailed to obtain process entry for csgo.exe");
            return 0;
        }
    }

    // Create open handle
    csgo_handle = imports::OpenProcess(PROCESS_ALL_ACCESS, false, csgo_pe32.th32ProcessID);
    assertif(csgo_handle, "\nFailed to obtain handle...");

    // Get module entry struct
    assertif(get_mod_entry(&csgo_me32, csgo_pe32.th32ProcessID, sdk_fnv64_cx(L"csgo.exe")), L"Failed to obtain module entry for csgo.exe");

    // Get path to dll
    path_len = get_full_path(xorstr(L"dll.dll"), path);
    assertif(path_len, L"Failed to obtain dll's full path");

    // Load the dll
    #if _DEBUG
        load_bytepatch(csgo_handle, &csgo_me32, path, path_len);
    #else
        load_0pll(csgo_handle, &csgo_me32, path, path_len);
        //load_windir(csgo_handle, path);
    #endif

    return 0;
}