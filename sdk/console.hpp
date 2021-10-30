#pragma once

#include <Windows.h>
#include <iostream>
#include <sdk/imports.hpp>

namespace sdk::console
{
    static void init()
    {
        imports::AllocConsole();

        FILE *file_ptr;
        freopen_s(&file_ptr, "CONOUT$", "w", stdout);
        freopen_s(&file_ptr, "CONOUT$", "w", stderr);
        freopen_s(&file_ptr, "CONIN$", "r", stdin);
        std::cout.clear();
        std::clog.clear();
        std::cerr.clear();
        std::cin.clear();

        HANDLE handle_con_out = imports::CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        HANDLE handle_con_in = imports::CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		imports::SetStdHandle(STD_OUTPUT_HANDLE, handle_con_out);
		imports::SetStdHandle(STD_ERROR_HANDLE, handle_con_out);
		imports::SetStdHandle(STD_INPUT_HANDLE, handle_con_in);
        std::wcout.clear();
        std::wclog.clear();
        std::wcerr.clear();
        std::wcin.clear();
    }

    static void uninit()
    {
		imports::FreeConsole();
    }
}

#define sdk_con_wcout(x) std::wcout << x
#define sdk_con_cout(x) std::cout << x

#define sdk_con_wcin(x) std::wcin >> x
#define sdk_con_cin(x) std::cin >> x

// Automatically omit debug console messages on release mode
#if _DEBUG
    #define sdk_con_wcout_debug(x) std::wcout << x
    #define sdk_con_cout_debug(x) std::cout << x

    #define sdk_con_wcin_debug(x) std::wcin >> x
    #define sdk_con_cin_debug(x) std::cin >> x

    #define sdk_con_dump_ldr_debug(x) sdk::console::dump_ldr()
#else
    #define sdk_con_wcout_debug(x)
    #define sdk_con_cout_debug(x)

    #define sdk_con_wcin_debug(x)
    #define sdk_con_cin_debug(x)

    #define sdk_con_dump_ldr_debug(x)
#endif
