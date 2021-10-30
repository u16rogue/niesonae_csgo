#pragma once

#include <dll/initialization/init_base.hpp>

#include <dll/hacks/engine_glow.hpp>
#include <dll/hacks/clantag.hpp>

namespace init
{
	init::result hacks()
	{
		__init_assert(hacks::engine_glow::instance().init(), L"\nFailed to initialize engine glow");
		__init_assert(hacks::clantag::instance().init(),     L"\nFailed to initialize clantag");

		return init::result::SUCCESS;
	}
}