#pragma once

#include <vector>

#include <dll/globals.hpp>
#include <dll/utils/chat_print.hpp>

#include <sdk/singleton.hpp>
#include <sdk/utils/str_copy.hpp>

#include "cm_module.hpp"
#include "commands/cm_ctag.hpp"

namespace cm
{
	constexpr char chat_command_prefix = '!';
	
	class manager : public sdk::singleton<cm::manager>
	{
	public:
		enum class e_result
		{
			ABORT = false,
			CONTINUE = true
		};

		e_result ClientCMD(const char *cmdstring)
		{
			sdk::offset_t offset = 0;
			if (cmdstring[0] != 's' || cmdstring[1] != 'a' || cmdstring[2] != 'y'
			||  cmdstring[offset = (cmdstring[3] == '_' ? sizeof("say_team ") : sizeof("say "))] != chat_command_prefix
			) {
				return e_result::CONTINUE;
			}

			bool all_chat = offset == sizeof("say ");
			cmdstring += offset + 1;

			for (module *chat_module : cm::module::instances)
			{
				if (chat_module->command_raw == *reinterpret_cast<const sdk::uint32_t *>(cmdstring))
				{
					char args[256] = { '\0' };
					
					if (cmdstring[4] == ' ' && cmdstring[6] != '\0') // only copy arg if after the command there's a space and an argument after the space
					{
						sdk::size_t len = sdk::str::copy(cmdstring + 5, args);
						args[len - 1] = '\0'; // removes the " at the end of the cmd string
					}
					else if (cmdstring[4] != '\"') // if the command doesn't take args the 5th character should be a " if it isn't the user supplied a non arg command with args
					{
						utils::hudchat_print(xorstr("\x02Chat command doesn't take parameters!"));
						break;
					}

					chat_module->callback(*args ? args : nullptr, all_chat);
					return e_result::ABORT;
				}
			}

			utils_hudchat_print_static("\x02Unknown chat command!");
			return e_result::ABORT;
		}
	};
}