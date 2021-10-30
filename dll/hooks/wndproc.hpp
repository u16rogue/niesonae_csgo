#pragma once

#include <Windows.h>
#include <sdk/utils/hook.hpp>
#include <sdk/console.hpp>

#include <dll/ui/menu.hpp>

namespace hooks
{
	using  wndproc_t              = long(__stdcall)(HWND, UINT, WPARAM, LPARAM);
	inline wndproc_t* new_wndproc = nullptr;

	inline sdk::hook<hooks::wndproc_t> hk_wndproc([](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) -> long
	{
		if (ui::main_menu::instance().wndproc(msg, wparam, lparam))
			return TRUE;

		return hooks::new_wndproc(hwnd, msg, wparam, lparam);
	});
}