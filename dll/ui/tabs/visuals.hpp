#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/visuals.hpp>

namespace ui::tabs
{
	inline ui::menu_tab visuals(xorstr(L"Visuals"), &ui::texture::visuals, sizeof(ui::texture::visuals));
}