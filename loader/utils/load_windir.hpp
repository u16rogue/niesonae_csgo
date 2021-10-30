#pragma once

#include <Windows.h>
#include <iostream>

#include <sdk/types.hpp>
#include <sdk/imports.hpp>
#include <sdk/encryption/xorstr.hpp>

#include <loader/utils/utils.hpp>

#define WINDIR_LOAD_PATH L"C:\\Windows\\nsnecsgo.dll"

bool load_windir(HANDLE csgo_handle, const wchar_t *path_lib)
{
	static const wchar_t *path_dest = xorstr(WINDIR_LOAD_PATH);
    bool is_success = false;

    // Check if load library is imported
    assertif(imports::LoadLibraryW, "\nLoadLibraryW not found!");

	// If delete file fails but its due to the file not existing, ignore
	assertif((imports::DeleteFileW(path_dest) || imports::GetLastError() == ERROR_FILE_NOT_FOUND), "\nFailed to delete file! (Insufficient priviledge or dll is loaded)");

    // Copy the dll
	assertif(imports::CopyFileW(path_lib, path_dest, FALSE), "\nFailed to copy file! (Insufficient priviledge or dll is loaded)");

    // Allocate memory
    LPVOID path_alloc = imports::VirtualAllocEx(csgo_handle, nullptr, sizeof(WINDIR_LOAD_PATH), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    assertif(path_alloc, "\nMemory allocation failed!");

    // Write the path
    assertifx(imports::WriteProcessMemory(csgo_handle, path_alloc, path_dest, sizeof(WINDIR_LOAD_PATH), nullptr), "\nWriting path failed!", goto GOTO_LABEL_CLEANUP);

    // Execute loadlibrary
    HANDLE crt_handle;
    crt_handle = imports::CreateRemoteThread(csgo_handle, nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(imports::LoadLibraryW), path_alloc, NULL, nullptr);
    assertifx((crt_handle && !(imports::WaitForSingleObject(crt_handle, 30000) & (WAIT_TIMEOUT | WAIT_ABANDONED))), "\nRemote thread failed!", goto GOTO_LABEL_CLEANUP);

    // Cleanup
    is_success = true;
    GOTO_LABEL_CLEANUP:
    assertif(imports::VirtualFreeEx(csgo_handle, path_alloc, 0, MEM_RELEASE), "\nMemory de-allocation failed!");

	return is_success;
}