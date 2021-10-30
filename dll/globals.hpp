#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include <d3dx9.h>

#include <sdk/module/module.hpp>
#include <sdk/module/module_csgo.hpp>

#include <sdk/valve_sdk/interface/IVEngineClient.hpp>
#include <sdk/valve_sdk/interface/IPanel.hpp>
#include <sdk/valve_sdk/interface/ISurface.hpp>
#include <sdk/valve_sdk/interface/IClientMode.hpp>
#include <sdk/valve_sdk/interface/IVRenderView.hpp>
#include <sdk/valve_sdk/interface/IBaseClientDLL.hpp>

#include <sdk/valve_sdk/cliententitylist.hpp>
#include <sdk/valve_sdk/hud.hpp>
#include <sdk/valve_sdk/cs_hud_chat.hpp>
#include <sdk/valve_sdk/c_cs_player.hpp>

namespace globals
{
	inline HMODULE                  dllhandle	      = nullptr;
	inline HWND                     hwndCSGO		  = nullptr;
	inline sdk::uint32_t            matsystoppanel_id = 0;
	inline sdk::valve::C_CSPlayer **localplayer       = nullptr; // static C_BasePlayer *s_pLocalPlayer[ MAX_SPLITSCREEN_PLAYERS ]; // ~\cstrike15_src\game\client\c_baseplayer.cpp
}

namespace modules
{
	inline sdk::module_csgo client         (sdk_fnv_contracted_len_cx("client"));
	inline sdk::module_csgo engine         (sdk_fnv_contracted_len_cx("engine"));
	inline sdk::module_csgo vgui2          (sdk_fnv_contracted_len_cx("vgui2"));
	inline sdk::module_csgo vguimatsurface (sdk_fnv_contracted_len_cx("vguimatsurface"));
	inline sdk::module_csgo shaderapidx9   (sdk_fnv_contracted_len_cx("shaderapidx9"));
}

namespace interfaces
{
	inline IDirect3DDevice9              *dxdevice   = nullptr;
	inline sdk::valve::IVEngineClient    *engine     = nullptr;
	inline sdk::valve::IPanel            *panel      = nullptr;
	inline sdk::valve::ISurface          *surface    = nullptr;
	inline sdk::valve::IClientMode       *clientmode = nullptr;
	inline sdk::valve::IVRenderView      *renderview = nullptr;
	inline sdk::valve::CClientEntityList *entitylist = nullptr;
	inline sdk::valve::IBaseClientDLL    *client     = nullptr;
	inline sdk::valve::CHud              *hud        = nullptr;
	inline sdk::valve::CHudChat          *hudchat    = nullptr;
};