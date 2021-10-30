#pragma once

#include <sdk/singleton.hpp>
#include <dll/globals.hpp>

namespace hacks
{
	class clantag : public sdk::singleton<clantag>
	{
		using SendClanTag_t = void(__fastcall)(const char *tag, const char *name);
		
	public:
		clantag() = default;

		bool init()
		{
			this->set = modules::engine.sigscan<SendClanTag_t>(sdk_sig_cache_as_arg_cx("53 56 57 8B DA 8B F9 FF"));
			return this->set != nullptr;
		}

	public:
		SendClanTag_t *set;
	};
}