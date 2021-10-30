#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/player.hpp>

namespace ui::tabs
{
	inline ui::menu_tab player(xorstr(L"Players"), &ui::texture::player, sizeof(ui::texture::player));
}