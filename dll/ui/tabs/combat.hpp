#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/combat.hpp>

namespace ui::tabs
{
	inline ui::menu_tab combat(xorstr(L"Combat"), &ui::texture::combat, sizeof(ui::texture::combat));
}