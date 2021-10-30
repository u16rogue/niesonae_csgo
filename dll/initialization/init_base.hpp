#pragma once

#include <dll/globals.hpp>
#include <sdk/encryption/xorstr.hpp>
#include <sdk/hash/fnv.hpp>
#include <sdk/imports.hpp>
#include <sdk/console.hpp>

namespace init
{
	enum class result
	{
		SUCCESS = false,
		FAIL    = true,
	};

    #define __init_eval(eval) \
        sdk_con_cout_debug("\n[INIT] Started: " #eval); \
        if (init::##eval##() == init::result::FAIL) return init::result::FAIL; \
        sdk_con_cout_debug("\n[INIT] Finished: " #eval);

	#if _DEBUG
        #define __init_wait_for_eval(eval, msg) if (!(init::___init_wait_for_eval([]() -> bool { return (eval); }, msg))) return init::result::FAIL;
    #else
        #define __init_wait_for_eval(eval, msg) if (!(init::___init_wait_for_eval([]() -> bool { return (eval); }, nullptr))) return init::result::FAIL;
    #endif
	
    inline bool ___init_wait_for_eval(bool (*eval_callback)(void), const wchar_t* message)
    {
        int time_to_wait = 60; 
        while (eval_callback()) 
        { 
            imports::Sleep(1000);
            
            if (--time_to_wait < 0) 
            { 
                sdk_con_wcout_debug("\n" << message);
                return false; 
            } 
        }

        return true;
    }

    #define __init_assert(eval, message) \
    if (!(eval)) \
    { \
        sdk_con_wcout_debug("\n" << message); \
        return (init::result::FAIL); \
    }

    #define __init_assert_fnv_cmp(str_tohash, fnv_tocmp, message) \
    if (sdk::hash::fnv64((str_tohash), sizeof(fnv_tocmp) - 1) != sdk_fnv64_cx(fnv_tocmp)) \
    { \
        sdk_con_wcout_debug("\n" << message); \
        return init::result::FAIL; \
    }

    #ifdef _DEBUG

    #define __init_dump() init::___init_dump()

    inline void ___init_dump()
    {
        if (!imports::GetAsyncKeyState(VK_PAUSE))
            return;

        sdk_con_cout_debug("\ndumping modules:");
        sdk::env::structs::PLDR_DATA_TABLE_ENTRY entry = nullptr;
        while (sdk::env::ldr_next(&entry))
        {
            if (!entry->DllBase)
                continue;

            sdk_con_wcout_debug("\n" << entry->BaseDllName.Buffer);
        }

        sdk_con_cout_debug("\ndumping client class:");
        sdk::valve::ClientClass *cc = nullptr;
        while (sdk::netvar::class_next(&cc))
        {
            sdk_con_cout_debug("\n" << cc->m_pNetworkName << "->" << cc->m_pRecvTable->m_pNetTableName);

            sdk::valve::RecvProp *rp = nullptr;
            while (sdk::netvar::prop_next(cc, &rp))
                sdk_con_cout_debug("\n\t" << rp->m_pVarName);
        }

        sdk_con_cout_debug("\ndumping hud elements:");
        for (int i = 0; i < interfaces::hud->m_HudList.m_Size; i++)
        {
            if (interfaces::hud->m_HudList.m_pMemory[i])
            {
                sdk_con_cout_debug("\n" << interfaces::hud->m_HudList.m_pMemory[i]->GetName());
            }
        }

        sdk_con_cout_debug("\nmat panel id: " << globals::matsystoppanel_id);
    }

    #else

    #define __init_dump() 

    #endif
}