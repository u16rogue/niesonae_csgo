#include <Windows.h>
#include <d3d9.h>

#include <sdk/gui/control_base.hpp>
#include <sdk/vertex.hpp>

#include <dll/ui/menu.hpp>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "D3dx9.lib")

#define WND_WIDTH 1040
#define WND_HEIGHT 807

#define WND_CLASSNAME L"gui_test"
#define WND_TITLE     L"niesonae gui test"

bool instance_running = true;
LRESULT CALLBACK wndproc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    HWND                    main_window   = nullptr;
    LPDIRECT3D9             direct        = Direct3DCreate9(D3D_SDK_VERSION);
    LPDIRECT3DDEVICE9       device        = nullptr;
    LPDIRECT3DTEXTURE9      bg_texture    = nullptr;
    LPD3DXSPRITE            bg_sprite     = nullptr;

    {
        WNDCLASSEXW wndclass =
        {
            sizeof(WNDCLASSEXW),
            (CS_HREDRAW | CS_VREDRAW),
            wndproc,
            0,
            0,
            hInstance,
            NULL,
            LoadCursorW(nullptr, IDC_ARROW),
            reinterpret_cast<HBRUSH>(2),
            NULL,
            WND_CLASSNAME,
            NULL
        };

        if (!RegisterClassExW(&wndclass))
        {
            MessageBoxW(NULL, L"Failed to register class!", WND_TITLE, 0);
            return 1;
        }
    }

    main_window = CreateWindowExW(
        0, WND_CLASSNAME, WND_TITLE, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
        WND_WIDTH, WND_HEIGHT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(main_window, 5);
    UpdateWindow(main_window);
    
    {
        D3DPRESENT_PARAMETERS params = {};
        params.Windowed         = true;
        params.SwapEffect       = D3DSWAPEFFECT_DISCARD;
        params.hDeviceWindow    = main_window;

        direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, main_window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &params, &device);
    }

    sdk::gui::control_base::rdevice = device;
    
    if (D3DXCreateTextureFromFileExW(device, L"demo_1024_768.png", 1024, 768, NULL, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, nullptr, nullptr, &bg_texture) != D3D_OK)
    {
        DebugBreak();
        return 1;
    }

    if (D3DXCreateSprite(device, &sdk::gui::control_base::rsprite) != D3D_OK)
    {
        DebugBreak();
        return 1;
    }

    if (!ui::main_menu::instance().init(1024, 768, 1.f))
        DebugBreak();

    ui::main_menu::instance().show = true;

    MSG msg = {};
    while (instance_running)
    {
        while (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        device->BeginScene();
        device->SetFVF(sdk_flag_dx9_vertex_ut);

        device->SetRenderState       (D3DRS_FOGENABLE,         FALSE);
        device->SetRenderState       (D3DRS_SRGBWRITEENABLE,   FALSE);
        device->SetRenderState       (D3DRS_LIGHTING,          FALSE);
        device->SetRenderState       (D3DRS_ZENABLE,           FALSE);
        device->SetRenderState       (D3DRS_ALPHATESTENABLE,   FALSE);
        device->SetRenderState       (D3DRS_ALPHABLENDENABLE,  TRUE);
        device->SetRenderState       (D3DRS_SCISSORTESTENABLE, TRUE);
        device->SetRenderState       (D3DRS_CULLMODE,          D3DCULL_NONE);
        device->SetRenderState       (D3DRS_COLORWRITEENABLE,  0xFFFFFFFF);
        device->SetRenderState       (D3DRS_BLENDOP,           D3DBLENDOP_ADD);
        device->SetRenderState       (D3DRS_SRCBLEND,          D3DBLEND_SRCALPHA);
        device->SetRenderState       (D3DRS_DESTBLEND,         D3DBLEND_INVSRCALPHA);
        device->SetRenderState       (D3DRS_SHADEMODE,         D3DSHADE_GOURAUD);
        device->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSU,     D3DTADDRESS_WRAP);
        device->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSV,     D3DTADDRESS_WRAP);
        device->SetSamplerState      (NULL,                    D3DSAMP_ADDRESSW,     D3DTADDRESS_WRAP);
        device->SetTextureStageState (NULL,                    D3DTSS_COLOROP,       D3DTOP_MODULATE);
        device->SetTextureStageState (NULL,                    D3DTSS_COLORARG1,     D3DTA_TEXTURE);
        device->SetTextureStageState (NULL,                    D3DTSS_COLORARG2,     D3DTA_DIFFUSE);
        device->SetTextureStageState (NULL,                    D3DTSS_ALPHAOP,       D3DTOP_MODULATE);
        device->SetTextureStageState (NULL,                    D3DTSS_ALPHAARG1,     D3DTA_TEXTURE);
        device->SetTextureStageState (NULL,                    D3DTSS_ALPHAARG2,     D3DTA_DIFFUSE);
        device->SetSamplerState      (NULL,                    D3DSAMP_MINFILTER,    D3DTEXF_LINEAR);
        device->SetSamplerState      (NULL,                    D3DSAMP_MAGFILTER,    D3DTEXF_LINEAR);

        // render fake csgo
        sdk::gui::control_base::rsprite->Begin(D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 pos = { 0, 0, 0 };
        sdk::gui::control_base::rsprite->Draw(bg_texture, nullptr, nullptr, &pos, -1);
        sdk::gui::control_base::rsprite->End();
        //

        ui::main_menu::instance().render();
        
        device->EndScene();
        device->Present(NULL, NULL, NULL, NULL);
    }
    
    device->Release();
    direct->Release();

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK wndproc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{

    if (ui::main_menu::instance().wndproc(uMsg, wParam, lParam))
        return TRUE;

    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            instance_running = false;
            break;
        }
    }

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}