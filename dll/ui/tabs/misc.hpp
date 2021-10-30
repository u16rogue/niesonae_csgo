#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/misc.hpp>

namespace ui::tabs
{
	inline ui::menu_tab misc(xorstr(L"Misc"), &ui::texture::misc, sizeof(ui::texture::misc));
}