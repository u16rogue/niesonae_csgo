#pragma once

#include <dll/initialization/init_base.hpp>
#include <dll/ui/menu.hpp>

namespace init
{
	init::result menu()
	{
		int width, height;
		interfaces::engine->GetScreenSize(width, height);
		__init_assert(ui::main_menu::instance().init(static_cast<float>(width), static_cast<float>(height)), "\nFailed to initalize menu!");

		return init::result::SUCCESS;
	}
}