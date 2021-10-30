#pragma once

#include <Windows.h>
#include <iostream>

#include <sdk/types.hpp>
#include <sdk/imports.hpp>
#include <sdk/encryption/xorstr.hpp>

#include <loader/utils/utils.hpp>

bool load_0pll(HANDLE csgo_handle, MODULEENTRY32W *csgo_me32, const wchar_t *path_lib, sdk::size32_t path_len)
{
    sdk::ptr_t    adr_flag   = nullptr;
    sdk::uint32_t org_flag   = 0;
    sdk::size32_t path_size  = path_len * sizeof(wchar_t);
    bool          is_success = false;

    // Get flag address
    adr_flag = sigscan_external(csgo_handle, csgo_me32->modBaseAddr, csgo_me32->modBaseSize, sdk_sig_cache_as_arg_cx("A1 ?? ?? ?? ?? 81 EC ?? ?? ?? ?? 53 56 57"));
    assertif(adr_flag, L"Signature scan failed");
    assertif(ReadProcessMemory<sdk::ptr_t>(csgo_handle, adr_flag + 0x1, &adr_flag), L"Obtaining flag address failed!");

    // Store original flag value
    assertif(ReadProcessMemory<sdk::uint32_t>(csgo_handle, adr_flag, &org_flag), L"Failed to obtain original flag value");

    // Allocate memory
    LPVOID path_alloc = imports::VirtualAllocEx(csgo_handle, nullptr, path_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    assertif(path_alloc, "\nMemory allocation failed");

    // Write path
    assertifx(imports::WriteProcessMemory(csgo_handle, path_alloc, path_lib, path_size, nullptr), L"Failed to write path!", goto GOTO_LABEL_CLEANUP);

    // Set flag
    assertifx(WriteProcessMemory<sdk::uint32_t>(csgo_handle, adr_flag, 0x0), L"Failed writing to flag", goto GOTO_LABEL_CLEANUP);

    // Call LoadLibraryW
    HANDLE crt_handle;
    crt_handle = imports::CreateRemoteThread(csgo_handle, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(imports::LoadLibraryW), path_alloc, NULL, nullptr);
    assertifx((crt_handle && !(imports::WaitForSingleObject(crt_handle, 30000) & (WAIT_TIMEOUT | WAIT_ABANDONED))), "\nRemote thread failed", goto GOTO_LABEL_CLEANUP);

    // Cleanup
    is_success = true;
    GOTO_LABEL_CLEANUP:
    assertif(imports::VirtualFreeEx(csgo_handle, path_alloc, 0, MEM_RELEASE), "\nMemory de-allocation failed!");
    assertifx(WriteProcessMemory<sdk::uint32_t>(csgo_handle, adr_flag, org_flag), L"Failed to restore flag", goto GOTO_LABEL_CLEANUP);

    return is_success;
}