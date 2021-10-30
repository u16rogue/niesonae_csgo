#pragma once

#include <dll/initialization/init_base.hpp>
#include <dll/vt_idx.hpp>

#include <sdk/utils/vfunc.hpp>

#include <dll/hooks/wndproc.hpp>
#include <dll/hooks/painttraverse.hpp>
#include <dll/hooks/clientcmd.hpp>
#include <dll/hooks/present.hpp>
#include <dll/hooks/reset.hpp>
#include <dll/hooks/sceneend.hpp>
#include <dll/hooks/createmove.hpp>
#include <dll/hooks/updateglows.hpp>

namespace init
{
	init::result hooks()
	{
		sdk::hook_init();

        hooks::new_wndproc       = hooks::hk_wndproc       .attach(reinterpret_cast<hooks::wndproc_t *>  (imports::GetWindowLongW(globals::hwndCSGO, GWLP_WNDPROC)));
      //hooks::new_painttraverse = hooks::hk_painttraverse .attach(sdk_get_vfunc(hooks::painttraverse_t, interfaces::panel,      vt_idx::PaintTraverse));
        hooks::new_clientcmd     = hooks::hk_clientcmd     .attach(sdk_get_vfunc(hooks::clientcmd_t,     interfaces::engine,     vt_idx::ClientCMD));
        hooks::new_present       = hooks::hk_present       .attach(sdk_get_vfunc(hooks::present_t,       interfaces::dxdevice,   vt_idx::Present));
        hooks::new_reset         = hooks::hk_reset         .attach(sdk_get_vfunc(hooks::reset_t,         interfaces::dxdevice,   vt_idx::Reset));
      //hooks::new_sceneend      = hooks::hk_sceneend      .attach(sdk_get_vfunc(hooks::sceneend_t,      interfaces::renderview, vt_idx::SceneEnd));
        hooks::new_createmove    = hooks::hk_createmove    .attach(sdk_get_vfunc(hooks::createmove_t,    interfaces::clientmode, vt_idx::CreateMove));
        hooks::new_updateglows   = hooks::hk_updateglows   .attach(modules::client.sigscan<hooks::updateglows_t>(sdk_sig_cache_as_arg_cx("55 8B EC 83 EC 44 53 56 8B 35 ?? ?? ?? ?? 8B")));

        sdk::hook_commit_all();

		return init::result::SUCCESS;
	}
}