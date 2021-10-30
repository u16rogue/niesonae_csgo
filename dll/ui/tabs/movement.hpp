#pragma once

#include <dll/ui/tab.hpp>
#include <dll/ui/textures/movement.hpp>

namespace ui::tabs
{
	inline ui::menu_tab movement(xorstr(L"Movement"), &ui::texture::movement, sizeof(ui::texture::movement));
}