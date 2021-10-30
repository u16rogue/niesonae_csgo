#pragma once

#include <dll/initialization/init_base.hpp>

namespace init
{
	init::result modules()
	{
		__init_assert(modules::client.init(),         L"\nFailed to initialize client.dll");
		__init_assert(modules::engine.init(),         L"\nFailed to initialize engine.dll");
		__init_assert(modules::vgui2.init(),          L"\nFailed to initialize vgui2.dll");
		__init_assert(modules::vguimatsurface.init(), L"\nFailed to initialize vguimatsurface.dll");
		__init_assert(modules::shaderapidx9.init(),   L"\nFailed to initialize shaderapidx9.dll");

		return init::result::SUCCESS;
	}
}