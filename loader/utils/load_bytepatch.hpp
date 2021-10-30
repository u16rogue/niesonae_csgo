#pragma once

#include <Windows.h>
#include <iostream>

#include <sdk/types.hpp>
#include <sdk/imports.hpp>
#include <sdk/encryption/xorstr.hpp>

#include <loader/utils/utils.hpp>

// trusted mode info is from https://github.com/danielkrupinski/OneByteLdr

bool load_bytepatch(HANDLE csgo_handle, MODULEENTRY32W *csgo_me32, const wchar_t *path_lib, sdk::size32_t path_len)
{
    sdk::ptr_t      ntopen_jump = nullptr;
    sdk::size32_t   path_size   = path_len * sizeof(wchar_t);
    bool            is_success  = false;

    // Check if load lib is imported
    assertif(imports::LoadLibraryW, "\nLoadLibraryW not found!");

    // Find check in hooked function
    ntopen_jump = sigscan_external(csgo_handle, csgo_me32->modBaseAddr, csgo_me32->modBaseSize, sdk_sig_cache_as_arg_cx("74 1B F6"));
    assertif(ntopen_jump, "\nSignature scan failed!");

    // Patch memory
    assertif(WriteProcessMemory<sdk::byte_t>(csgo_handle, ntopen_jump, 0xEB), "\nJump byte patch failed!");
    
    // Allocate memory
    LPVOID path_alloc = imports::VirtualAllocEx(csgo_handle, nullptr, path_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    assertif(path_alloc, "\nMemory allocation failed!");

    // Write Path
    assertifx(imports::WriteProcessMemory(csgo_handle, path_alloc, path_lib, path_size, nullptr), "\nWriting path failed!", goto GOTO_LABEL_CLEANUP);

    // Call LoadLibraryW
    HANDLE crt_handle;
    crt_handle = imports::CreateRemoteThread(csgo_handle, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(imports::LoadLibraryW), path_alloc, NULL, nullptr);
    assertifx((crt_handle && !(imports::WaitForSingleObject(crt_handle, 30000) & (WAIT_TIMEOUT | WAIT_ABANDONED))), "\nRemote thread failed!", goto GOTO_LABEL_CLEANUP);
    
    // Cleanup
    is_success = true;
    GOTO_LABEL_CLEANUP:
    assertif(imports::VirtualFreeEx(csgo_handle, path_alloc, 0, MEM_RELEASE), "\nMemory de-allocation failed!");
    assertif(WriteProcessMemory<sdk::byte_t>(csgo_handle, ntopen_jump, 0x74), "\nRestoring ntopenfile patch failed!");

	return is_success;
}