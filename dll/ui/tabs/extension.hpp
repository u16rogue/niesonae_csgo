#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/extension.hpp>

namespace ui::tabs
{
	inline ui::menu_tab extension(xorstr(L"Extension"), &ui::texture::extension, sizeof(ui::texture::extension));
}