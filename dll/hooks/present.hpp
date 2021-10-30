#include <d3dx9.h>
#include <sdk/utils/hook.hpp>
#include <sdk/vertex.hpp>

#include <dll/ui/menu.hpp>

namespace hooks
{
	using  present_t              = long(__stdcall)(IDirect3DDevice9 *, const RECT*, const RECT*, HWND, const RGNDATA*);
	inline present_t *new_present = nullptr;

	inline sdk::hook<hooks::present_t> hk_present([] (IDirect3DDevice9 *dxdevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) -> HRESULT
	{
		static IDirect3DVertexDeclaration9 *orig_vert_decl   = []() -> IDirect3DVertexDeclaration9* { IDirect3DVertexDeclaration9 *ret; interfaces::dxdevice->GetVertexDeclaration(&ret);                   return ret; } ();
		static DWORD                        orig_cwe         = []() -> DWORD                        { DWORD                        ret; interfaces::dxdevice->GetRenderState(D3DRS_COLORWRITEENABLE, &ret); return ret; } ();
		static IDirect3DStateBlock9        *dx_state_block   = []() -> IDirect3DStateBlock9*        { IDirect3DStateBlock9        *ret; interfaces::dxdevice->CreateStateBlock(D3DSBT_PIXELSTATE, &ret);    return ret; } ();

		dx_state_block->Capture();

		dxdevice->SetFVF               (sdk_flag_dx9_vertex_ut);
		dxdevice->SetPixelShader       (nullptr);
		dxdevice->SetVertexShader      (nullptr);
		dxdevice->SetRenderState       (D3DRS_FOGENABLE,         FALSE);
		dxdevice->SetRenderState       (D3DRS_SRGBWRITEENABLE,   FALSE);
		dxdevice->SetRenderState       (D3DRS_LIGHTING,          FALSE);
		dxdevice->SetRenderState       (D3DRS_ZENABLE,           FALSE);
		dxdevice->SetRenderState       (D3DRS_ALPHATESTENABLE,   FALSE);
		dxdevice->SetRenderState       (D3DRS_ALPHABLENDENABLE,  TRUE);
		dxdevice->SetRenderState       (D3DRS_SCISSORTESTENABLE, TRUE);
		dxdevice->SetRenderState       (D3DRS_CULLMODE,          D3DCULL_NONE);
		dxdevice->SetRenderState       (D3DRS_COLORWRITEENABLE,  0xFFFFFFFF);
		dxdevice->SetRenderState       (D3DRS_BLENDOP,           D3DBLENDOP_ADD);
		dxdevice->SetRenderState       (D3DRS_SRCBLEND,          D3DBLEND_SRCALPHA);
		dxdevice->SetRenderState       (D3DRS_DESTBLEND,         D3DBLEND_INVSRCALPHA);
		dxdevice->SetRenderState       (D3DRS_SHADEMODE,         D3DSHADE_GOURAUD);
		dxdevice->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSU,     D3DTADDRESS_WRAP);
		dxdevice->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSV,     D3DTADDRESS_WRAP);
		dxdevice->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSW,     D3DTADDRESS_WRAP);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_COLOROP,       D3DTOP_MODULATE);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_COLORARG1,     D3DTA_TEXTURE);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_COLORARG2,     D3DTA_DIFFUSE);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_ALPHAOP,       D3DTOP_MODULATE);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_ALPHAARG1,     D3DTA_TEXTURE);
		dxdevice->SetTextureStageState (NULL,                    D3DTSS_ALPHAARG2,     D3DTA_DIFFUSE);
		dxdevice->SetSamplerState      (NULL,                    D3DSAMP_MINFILTER,    D3DTEXF_LINEAR);
		dxdevice->SetSamplerState      (NULL,                    D3DSAMP_MAGFILTER,    D3DTEXF_LINEAR);
		
		ui::main_menu::instance().render();
		
		dx_state_block->Apply();
		dxdevice->SetRenderState(D3DRS_SRGBWRITEENABLE, TRUE);
		dxdevice->SetRenderState(D3DRS_COLORWRITEENABLE, orig_cwe);
		dxdevice->SetVertexDeclaration(orig_vert_decl);

		return hooks::new_present(dxdevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	});
}