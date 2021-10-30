#pragma once

#include <d3dx9.h>

#include <dll/ui/values.hpp>

#include <sdk/imports.hpp>
#include <sdk/encryption/xorstr.hpp>
#include <sdk/gui/control_base.hpp>

#include <sdk/gui/canvas.hpp>

namespace ui
{
	class menu_tab
	{
	public:

		menu_tab(const wchar_t *text_, const void *icon_tex_bin_, sdk::size32_t icon_tex_bin_size_, std::vector<sdk::gui::canvas *> categories_ = {}) : text(text_), icon_tex_bin(icon_tex_bin_), icon_tex_bin_size(icon_tex_bin_size_), categories(categories_)
		{
			menu_tab::instances.push_back(this);
		}

		bool init(float font_height, float scale = 1.f)
		{
			if (imports::D3DXCreateTextureFromFileInMemoryEx(sdk::gui::control_base::rdevice,
				this->icon_tex_bin, this->icon_tex_bin_size,
				static_cast<UINT>(ui::values::header_icon_size * scale), static_cast<UINT>(ui::values::header_icon_size * scale),
				NULL, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, nullptr, nullptr, &this->icon_texture) != D3D_OK)
				return false;

			float padding_tb = ui::values::categoory_padding_tb * scale;
			for (sdk::gui::canvas *category : this->categories)
			{
				if (!category->init(scale))
					return false;

				this->categories_height += font_height + padding_tb * 2.f;
			}

			if (!this->categories.empty())
				this->selected_category = this->categories[0];

			return true;
		}

	public:
		const wchar_t                  *text                    = nullptr;
		LPDIRECT3DTEXTURE9              icon_texture            = nullptr;
		float                           categories_height       = 0.f;
		sdk::gui::canvas               *selected_category       = nullptr;
		std::vector<sdk::gui::canvas *> categories              = {};

	private:
		const void         *icon_tex_bin      = nullptr;
		sdk::size32_t       icon_tex_bin_size = 0;

	public:
		inline static std::vector<ui::menu_tab *> instances = {};
	};
}