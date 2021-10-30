#pragma once

#include "init_base.hpp"

#include "inits/entry.hpp"
#include "inits/modules.hpp"
#include "inits/interfaces.hpp"
#include "inits/values.hpp"
#include "inits/patches.hpp"
#include "inits/menu.hpp"
#include "inits/hacks.hpp"
#include "inits/hooks.hpp"

namespace init
{
	init::result initialize()
	{
		__init_eval(entry);
		__init_eval(modules);
		__init_eval(interfaces);
		__init_eval(values);
		__init_eval(patches);
		__init_eval(menu);
		__init_eval(hacks);
		__init_eval(hooks);
		
		__init_dump(); // only dump when the PAUSE key is held down (in implementation)

		return init::result::SUCCESS;
	}
}