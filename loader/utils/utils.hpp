#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include <sdk/console.hpp>
#include <sdk/imports.hpp>
#include <sdk/utils/sigscan.hpp>
#include <sdk/hash/fnv.hpp>

#define assertif(eval, msg) \
if (!(eval)) \
{ \
	sdk_con_cout_debug(msg); \
	return false; \
}

#define assertifx(eval, msg, extra) \
if (!(eval)) \
{ \
	sdk_con_cout_debug(msg); \
	extra;\
	return false; \
}

#ifdef _DEBUG
	#define DBG_MSG "[DEBUG]"
#else
	#define DBG_MSG
#endif

bool get_proc_entry(PROCESSENTRY32W *pe32_result, sdk::hash::fnv64_t proc_name)
{
	PROCESSENTRY32W pe32 = { sizeof(PROCESSENTRY32W) };

	HANDLE proc_snap = imports::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!proc_snap)
		return false;

	while (imports::Process32NextW(proc_snap, &pe32))
	{
		if (sdk::hash::fnv64(pe32.szExeFile) == proc_name)
		{
			memcpy(pe32_result, &pe32, sizeof(PROCESSENTRY32W));
			return true;
		}
	}

	return false;
}

bool get_mod_entry(MODULEENTRY32W *me32_result, DWORD proc_id, sdk::hash::fnv64_t mod_name)
{
	MODULEENTRY32W me32 = { sizeof(MODULEENTRY32W) };

	HANDLE mod_snap = imports::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc_id);

	if (!mod_snap)
		return false;

	while (imports::Module32NextW(mod_snap, &me32))
	{
		if (sdk::hash::fnv64(me32.szModule) == mod_name)
		{
			memcpy(me32_result, &me32, sizeof(MODULEENTRY32W));
			return true;
		}
	}

	return false;
}

sdk::ptr_t sigscan_external(HANDLE handle, sdk::ptr_t base, sdk::size32_t size, sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count)
{
	std::unique_ptr<sdk::byte_t> scan_buffer(new sdk::byte_t[size]);

	if (!imports::ReadProcessMemory(handle, base, scan_buffer.get(), size, nullptr))
		return nullptr;

	sdk::ptr_t sig_result = sdk::sig::scan<sdk::byte_t>(scan_buffer.get(), size, cached_sig, pattern_count);

	if (!sig_result)
		return nullptr;

	return base + 
		   (sig_result - scan_buffer.get()); // RVA
}

template <typename T>
bool WriteProcessMemory(HANDLE handle, sdk::ptr_t address, T value)
{
	return imports::WriteProcessMemory(handle, address, &value, sizeof(T), nullptr);
}

template <typename T>
bool ReadProcessMemory(HANDLE handle, sdk::ptr_t address, T *dest)
{
	return imports::ReadProcessMemory(handle, address, dest, sizeof(T), nullptr);
}

sdk::size32_t get_full_path(const wchar_t *file_name, wchar_t *result)
{
	return imports::GetFullPathNameW(file_name, 256, result, nullptr);
}