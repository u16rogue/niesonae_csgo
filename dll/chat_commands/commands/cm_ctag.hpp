#pragma once

#include <dll/utils/chat_print.hpp>
#include <dll/chat_commands/cm_module.hpp>
#include <dll/hacks/clantag.hpp>

#include <dll/utils/animate_clantag.hpp>

namespace cm::commands
{
	inline cm::module ctag (cm_create_command("ctag"), [](const char *args, bool all_chat) -> void
	{
	  //constexpr std::array<char[16], 5> cheat_tag_animated = utils::create_animated_clantag('\x30CB', '\x30A8', '\x30BD', '\x30CA', '\x30A8');
	  //constexpr std::array<char[16], 5> cheat_tag_animated = utils::create_animated_clantag_u8<'\x30'>('\xCB', '\xA8', '\xBD', '\xCA', '\xA8');
		// no-strike.jp
		static const char *cheat_tag = xorstr(u8"\x30CB\x30A8\x30BD\x30CA\x30A8");
		const char *tag = args ? args : cheat_tag;

		hacks::clantag::instance().set(tag, tag);

		utils_hudchat_print_static("Clantag set!");
	});
}