#pragma once

#include <sdk/gui/canvas.hpp>

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/player_visuals.hpp>

namespace ui::tabs
{
	inline sdk::gui::canvas category_glow(xorstr(L"Glow"));

	inline ui::menu_tab player_visuals(xorstr(L"Player Visuals"), &ui::texture::player_visuals, sizeof(ui::texture::player_visuals),
	{
		&category_glow
	});
}