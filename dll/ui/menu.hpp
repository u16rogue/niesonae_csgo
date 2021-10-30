#pragma once

#include <Windows.h>
#include <windowsx.h>
#include <vector>
#include <filesystem>

#include <sdk/math_cx.hpp>
#include <sdk/imports.hpp>
#include <sdk/singleton.hpp>
#include <sdk/gui/control_base.hpp>

#include "values.hpp"
#include "tab.hpp"

#include "tabs/player_combat.hpp"
#include "tabs/combat.hpp"
#include "tabs/player_visuals.hpp"
#include "tabs/visuals.hpp"
#include "tabs/misc.hpp"
#include "tabs/movement.hpp"
#include "tabs/extension.hpp"
#include "tabs/player.hpp"
#include "tabs/config.hpp"

#define __m_ui_menu_title L"ニエソナエ.モイ"

// TODO: animations and other eye candy

namespace ui
{
	class main_menu : public sdk::singleton<main_menu>
	{
	public:
		bool init(float res_width, float res_height, float scale_factor_ = 1.f)
		{

			if (res_width)
				this->reso.width = res_width;

			if (res_height)
				this->reso.height = res_height;

			if (this->reso.width < 1 || this->reso.height < 1)
				return false;

			if (scale_factor_ > 0)
				this->scale_factor = scale_factor_;

			this->size                      = { ui::values::menu_width * this->scale_factor, ui::values::menu_height * this->scale_factor };
			this->margin                    = ui::values::margin * this->margin;

			this->header_margin             = ui::values::header_margin * this->scale_factor;
			this->header_icon_size          = ui::values::header_icon_size * this->scale_factor;
			this->header_icon_padding_lr    = ui::values::header_icon_padding_lr * this->scale_factor;
			this->header_padding_tb         = ui::values::header_padding_tb * this->scale_factor;
			this->header_size               = { this->size.width - this->header_margin * 2, this->header_icon_size + this->header_padding_tb * 2 };
			this->header_text_y_offset      = ui::values::header_text_y_offset * this->scale_factor;
			this->header_text_x_offset      = ui::values::header_text_x_offset * this->scale_factor;
			this->header_text_drop_offset   = ui::values::header_text_drop_offset * this->scale_factor;

			this->category_padding_tb       = ui::values::categoory_padding_tb * this->scale_factor;
			this->category_margin_lr        = ui::values::category_margin_lr * this->scale_factor;
			this->category_width            = ui::values::category_width * this->scale_factor;

			this->position = { this->reso.width / 2 - this->size.width / 2, this->reso.height / 2 - this->size.height / 2 };

			if (static const wchar_t *custom_bg_path = xorstr(L"nsne\\res\\bg.png"); std::filesystem::exists(custom_bg_path))
			{
				if (imports::D3DXCreateTextureFromFileExW(sdk::gui::control_base::rdevice, custom_bg_path, static_cast<UINT>(this->size.width), static_cast<UINT>(this->size.height), NULL, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, nullptr, nullptr, &this->bg_tex) != D3D_OK)
					return false;
			}

			// Category text font creation
			{
				if (imports::D3DXCreateFontW(sdk::gui::control_base::rdevice, static_cast<int>(ui::values::category_font_size * this->scale_factor), NULL, FW_EXTRALIGHT, 0, FALSE, 0, DEFAULT_CHARSET, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, xorstr(L"Segoe UI"), &this->category_text_font) != S_OK)
					return false;

				RECT header_size_result = { 0, 0, 0, 0 };
				this->category_text_font->DrawTextW(nullptr, xorstr(L"M"), -1, &header_size_result, DT_CALCRECT, NULL);
				this->category_text_height = static_cast<float>(header_size_result.bottom);
			}

			// Header text font creatiion
			{
				if (imports::D3DXCreateFontW(sdk::gui::control_base::rdevice, static_cast<int>(ui::values::header_text_font_size * this->scale_factor), NULL, FW_BOLD, 0, FALSE, 0, DEFAULT_CHARSET, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, xorstr(L"Corporate Logo Rounded"), &this->header_text_font) != S_OK)
					return false;

				RECT header_size_result = { 0, 0, 0, 0 };
				this->header_text_font->DrawTextW(nullptr, xorstr(__m_ui_menu_title), -1, &header_size_result, DT_CALCRECT, NULL);
				this->header_text_size = { static_cast<float>(header_size_result.right), static_cast<float>(header_size_result.bottom) };
			}

			for (ui::menu_tab *tab : ui::menu_tab::instances)
			{
				if (!tab->init(this->category_text_height, this->scale_factor))
					return false;
				
				this->header_icon_area_width += this->header_icon_size + this->header_icon_padding_lr * 2;
			}

			this->header_icon_area_width -= this->header_icon_padding_lr;

			{
				float _base_x = this->header_margin + this->header_text_x_offset + this->header_text_size.width;
				this->header_icon_rel_x = ((this->size.width - _base_x - this->header_margin) / 2 - this->header_icon_area_width / 2) + _base_x;
			}

			return true;
		}

		void render()
		{
			if (!this->show)
				return;

			float header_x = this->position.x + this->header_margin;
			float header_y = this->position.y + this->header_margin;

			float header_border_width  = this->header_size.width  + this->header_margin * 2;
			float header_border_height = this->header_size.height + this->header_margin * 2;

			// Custom background render
			if (this->bg_tex)
			{
				sdk::gui::control_base::rsprite->Begin(D3DXSPRITE_ALPHABLEND);
				D3DXVECTOR3 pos = { this->position.x, this->position.y, 0 };
				sdk::gui::control_base::rsprite->Draw(this->bg_tex, nullptr, nullptr, &pos, -1);
				sdk::gui::control_base::rsprite->End();
			}

			DWORD windows_tick_count = imports::GetTickCount();

			// Main UI Render
			sdk::gui::vertex_t menu[] =
			{
				sdk_gui_make_tlist_square(this->position.x, this->position.y, this->size.width, this->size.height, this->bg_color),                  // Background
				sdk_gui_make_tlist_square(this->position.x, this->position.y, header_border_width, header_border_height, this->header_border_color), // Header Border
				sdk_gui_make_tlist_square(header_x, header_y, this->header_size.width, this->header_size.height, this->header_color)                 // Header
			};

			sdk::gui::control_base::rdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, sdk_gui_vertex_count_tlist(menu), menu, sizeof(sdk::gui::vertex_t));

			static const wchar_t *header_text = xorstr(__m_ui_menu_title);
			RECT  htext_drop_pos = {};
			float htext_x = header_x + this->header_text_x_offset;
			float htext_y = header_y + this->header_text_y_offset;

			if (this->animate_header_text) // Animated header drop text
			{
				float curr_angle      = (windows_tick_count % static_cast<int>(ui::values::header_text_rotate_speed) / ui::values::header_text_rotate_speed) * 360.f;
				float htext_pos_drop  = (this->header_text_drop_offset * 2.f ) * .5f;
				float htext_rot_scale = (this->header_text_drop_offset * .5f ) * .5f;
				htext_drop_pos.left   = static_cast<long>((htext_x + htext_pos_drop) - (cosf(curr_angle) * htext_rot_scale));
				htext_drop_pos.top    = static_cast<long>((htext_y + htext_pos_drop) - (sinf(curr_angle) * htext_rot_scale));
			}
			else // Static header drop text
			{
				htext_drop_pos.left  = static_cast<long>(htext_x + this->header_text_drop_offset);
				htext_drop_pos.top   = static_cast<long>(htext_y + this->header_text_drop_offset);
			}
			
			D3DCOLOR drop_color = !this->animate_header_color ? this->header_text_drop_color.raw : sdk::color::rrgb(windows_tick_count).raw; // Animated / Static header text drop color

			this->header_text_font->DrawTextW(nullptr, header_text, -1, &htext_drop_pos, DT_NOCLIP, drop_color);

			// Main header text
			RECT htext_main_pos = { static_cast<long>(htext_x), static_cast<long>(htext_y) };
			this->header_text_font->DrawTextW(nullptr, header_text, -1, &htext_main_pos, DT_NOCLIP, this->header_text_color.raw);

			// Render tab select
			D3DXVECTOR3 pos = { this->position.x + this->header_icon_rel_x, header_y + this->header_padding_tb, 0 };
			sdk::gui::control_base::rsprite->Begin(D3DXSPRITE_ALPHABLEND);
			for (ui::menu_tab *tab : ui::menu_tab::instances)
			{
				pos.x += this->header_icon_padding_lr;
				sdk::gui::control_base::rsprite->Draw(tab->icon_texture, nullptr, nullptr, &pos, -1);
				pos.x += this->header_icon_size + this->header_icon_padding_lr;
			}
			sdk::gui::control_base::rsprite->End();

			// Render selected tab
			if (!this->selected_tab || this->selected_tab->categories.empty())
				return;

			// Render categories
			float category_y = this->position.y + header_border_height + this->margin;
			RECT category_text_pos = { static_cast<long>(this->position.x + this->category_margin_lr), static_cast<long>(category_y) };
			for (sdk::gui::canvas *category : this->selected_tab->categories)
			{
				// Render selected category indicator
				if (this->selected_tab->selected_category == category)
				{
					sdk::gui::vertex_t category_selected_indicator[] =
					{
						sdk_gui_make_tlist_square(this->position.x, static_cast<float>(category_text_pos.top), this->category_margin_lr * .5f, (this->category_text_height + this->category_padding_tb * 2.f), this->category_selected_color)
					};
					
					sdk::gui::control_base::rdevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, sdk_gui_vertex_count_tlist(category_selected_indicator), category_selected_indicator, sizeof(sdk::gui::vertex_t));
				}

				category_text_pos.top += static_cast<long>(this->category_padding_tb);
				this->category_text_font->DrawTextW(nullptr, category->title, -1, &category_text_pos, DT_NOCLIP, this->category_text_color.raw);
				category_text_pos.top += static_cast<long>(this->category_text_height + this->category_padding_tb);
			}
		}

		bool wndproc(UINT msg, WPARAM wparam, LPARAM lparam)
		{
			if (msg == WM_KEYDOWN && wparam == this->show_key)
			{
				this->show ^= true;
				return true;
			}

			if (!this->show)
				return false;

			sdk::gui::pos2d_t mouse_pos(lparam);

			// Stop dragging
			if (this->is_dragging && msg == WM_LBUTTONUP)
			{
				this->is_dragging = false;
				return true;
			}

			// Tab select
			//if (!ui::menu_tab::instances.empty())
			{
				float tab_x = this->position.x + this->header_icon_rel_x;
				float tab_y = this->position.y + this->header_margin;

				if (msg == WM_LBUTTONDOWN
				&& mouse_pos.x >= tab_x && mouse_pos.x <= tab_x + this->header_icon_area_width
				&& mouse_pos.y >= tab_y && mouse_pos.y <= tab_y + this->header_icon_size + this->header_padding_tb * 2
				) {
					int idx = static_cast<int>((mouse_pos.x - tab_x) / (this->header_icon_size + this->header_icon_padding_lr * 2) );
					this->selected_tab = ui::menu_tab::instances[idx];
					return true;
				}
			}

			// Start dragging
			if (msg == WM_LBUTTONDOWN
			&&  mouse_pos.x >= this->position.x && mouse_pos.x <= this->position.x + this->size.width
			&&  mouse_pos.y >= this->position.y && mouse_pos.y <= this->position.y + this->size.height
			) {
				this->is_dragging  = true;
				this->drag_rel_pos = { mouse_pos.x - this->position.x, mouse_pos.y - this->position.y };
				return true;
			}

			// Do dragging
			if (this->is_dragging && msg == WM_MOUSEMOVE)
			{
				this->position = { mouse_pos.x - this->drag_rel_pos.x, mouse_pos.y - this->drag_rel_pos.y };
				return true;
			}

			return true;
		}

	public:
		bool   show                 = false;
		bool   animate_header_text  = true;
		bool   animate_header_color = true;
		LPARAM show_key             = VK_INSERT;

	private:
		bool is_dragging = false;
		sdk::gui::pos2d_t drag_rel_pos {};

		// Main UI
		float margin = 0.f;
		sdk::color bg_color = sdk::color(40, 42, 54) % .9f;
		sdk::gui::size2d_t reso     = sdk::gui::size2d_t(0.f, 0.f);
		sdk::gui::size2d_t size     = sdk::gui::size2d_t(0.f, 0.f);
		sdk::gui::pos2d_t  position = sdk::gui::pos2d_t(0.f, 0.f);
		LPDIRECT3DTEXTURE9 bg_tex   = nullptr;

		// Header
		float              header_margin             = 0.f;
		float              header_padding_tb         = 0.f;
		float              header_icon_size          = 0.f;
		float              header_icon_padding_lr     = 0.f;
		float              header_icon_area_width    = 0.f;
		float              header_icon_rel_x         = 0.f;
		sdk::color         header_color              = sdk::color(245, 169, 203) % .6f;
		sdk::color         header_border_color       = sdk::color(173, 216, 230) % .4f;
		sdk::gui::size2d_t header_size               = sdk::gui::size2d_t(0.f, 0.f);

		// Header Text
		float              header_text_y_offset      = 0.f;
		float	           header_text_x_offset      = 0.f;
		float              header_text_drop_offset   = 0.f;
		sdk::color         header_text_color         = sdk::color(255, 255, 255);
		sdk::color         header_text_drop_color    = sdk::color(173, 216, 230);
		sdk::gui::size2d_t header_text_size          = sdk::gui::size2d_t(0.f, 0.f);
		LPD3DXFONT		   header_text_font		     = nullptr;

		// Categories text
		sdk::color category_selected_color = sdk::color(245, 169, 203);
		sdk::color category_text_color     = sdk::color(255, 255, 255);
		float      category_margin_lr      = 0.f;
		float      category_text_height    = 0.f;
		float      category_padding_tb     = 0.f;
		float      category_width          = 0.f;
		LPD3DXFONT category_text_font	   = nullptr;

		// State
		ui::menu_tab *selected_tab = nullptr;

		float scale_factor = 1.f;
	};
}