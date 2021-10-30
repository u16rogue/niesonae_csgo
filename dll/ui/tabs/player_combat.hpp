#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/player_combat.hpp>

namespace ui::tabs
{
	inline ui::menu_tab player_combat(xorstr(L"Player Combat"), &ui::texture::player_combat, sizeof(ui::texture::player_combat));
}