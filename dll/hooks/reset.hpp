#pragma once

#include <d3dx9.h>
#include <sdk/utils/hook.hpp>

namespace hooks
{
	using  reset_t            = long(__stdcall)(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);
	inline reset_t* new_reset = nullptr;

	inline sdk::hook<hooks::reset_t> hk_reset([](IDirect3DDevice9 *dxdevice, D3DPRESENT_PARAMETERS *pPresentationParameters) -> HRESULT
	{
		return hooks::new_reset(dxdevice, pPresentationParameters);
	});
}