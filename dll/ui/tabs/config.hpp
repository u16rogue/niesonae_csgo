#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/config.hpp>

namespace ui::tabs
{
	inline ui::menu_tab config(xorstr(L"Config"), &ui::texture::config, sizeof(ui::texture::config));
}