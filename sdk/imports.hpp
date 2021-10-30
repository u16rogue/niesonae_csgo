#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <TlHelp32.h>
#include <d3dx9.h>
#include <sdk/winternal/environment.hpp>

#define sdk_create_runtime_import(fn) \
	using fn##_t = decltype(fn); \
	inline fn##_t *fn = sdk::env::import_function<fn##_t>(sdk_fnv64_cx(#fn))

namespace imports
{
	sdk_create_runtime_import(CreateThread);
	sdk_create_runtime_import(DisableThreadLibraryCalls);
	sdk_create_runtime_import(FreeLibraryAndExitThread);

	sdk_create_runtime_import(D3DXCreateSprite);
	sdk_create_runtime_import(D3DXCreateTextureFromFileInMemoryEx);
	sdk_create_runtime_import(D3DXCreateTextureFromFileExW);
	sdk_create_runtime_import(D3DXCreateFontW);

	sdk_create_runtime_import(CloseHandle);

	sdk_create_runtime_import(FindWindowW);
	sdk_create_runtime_import(GetWindowLongW);

	sdk_create_runtime_import(Sleep);

	sdk_create_runtime_import(AllocConsole);
	sdk_create_runtime_import(FreeConsole);
	sdk_create_runtime_import(CreateFileW);
	sdk_create_runtime_import(SetStdHandle);

	sdk_create_runtime_import(GetAsyncKeyState);

	sdk_create_runtime_import(VirtualProtect);

	sdk_create_runtime_import(OpenProcess);
	sdk_create_runtime_import(CreateToolhelp32Snapshot);
	sdk_create_runtime_import(Process32NextW);
	sdk_create_runtime_import(Module32NextW);
	sdk_create_runtime_import(ReadProcessMemory);
	sdk_create_runtime_import(WriteProcessMemory);
	sdk_create_runtime_import(LoadLibraryW);
	sdk_create_runtime_import(VirtualAllocEx);
	sdk_create_runtime_import(VirtualFreeEx);
	sdk_create_runtime_import(CreateRemoteThread);
	sdk_create_runtime_import(WaitForSingleObject);

	sdk_create_runtime_import(GetFullPathNameW);
	sdk_create_runtime_import(CopyFileW);
	sdk_create_runtime_import(DeleteFileW);

	sdk_create_runtime_import(CreateFileMappingW);
	sdk_create_runtime_import(MapViewOfFile);
	sdk_create_runtime_import(UnmapViewOfFile);
	sdk_create_runtime_import(OpenFileMappingW);

	sdk_create_runtime_import(GetLastError);

	//sdk_create_runtime_import(HeapAlloc);
	//sdk_create_runtime_import(HeapReAlloc);
	//sdk_create_runtime_import(HeapCreate);
	sdk_create_runtime_import(GetThreadContext);
	sdk_create_runtime_import(SetThreadContext);
	sdk_create_runtime_import(Thread32First);
	sdk_create_runtime_import(Thread32Next);
	sdk_create_runtime_import(GetCurrentProcessId);
	sdk_create_runtime_import(GetCurrentThreadId);
	sdk_create_runtime_import(SuspendThread);
	sdk_create_runtime_import(ResumeThread);
	sdk_create_runtime_import(FlushInstructionCache);
	sdk_create_runtime_import(OpenThread);
	//sdk_create_runtime_import(HeapFree);
	//sdk_create_runtime_import(HeapDestroy);
	sdk_create_runtime_import(GetCurrentProcess);
	sdk_create_runtime_import(GetModuleHandleW);
	sdk_create_runtime_import(GetProcAddress);
	sdk_create_runtime_import(VirtualFree);
	sdk_create_runtime_import(VirtualQuery);
	sdk_create_runtime_import(VirtualAlloc);

	sdk_create_runtime_import(GetTickCount);
}