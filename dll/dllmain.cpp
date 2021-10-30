#pragma warning(disable : 26495) // for directx sdk

#include "initialization/initialization.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        globals::dllhandle = hModule;
		imports::CloseHandle(imports::CreateThread(nullptr, NULL, [](LPVOID dummy) -> DWORD
        {
            if (init::initialize() == init::result::FAIL)
				imports::FreeLibraryAndExitThread(globals::dllhandle, 1);

            return 0;
        }, nullptr, NULL, nullptr));
    }

    return TRUE;
}