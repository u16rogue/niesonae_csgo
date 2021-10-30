#pragma once

#include <vector>
#include <sdk/types.hpp>
#include <sdk/console.hpp>

namespace cm
{
	using callbackfn_t = void(*)(const char *args, bool all_chat);

	class module
	{
	public:
		cm::module(sdk::uint32_t command_, callbackfn_t callback_) : command_raw(command_), callback(callback_)
		{
			cm::module::instances.push_back(this);
		}

		union
		{
			char          command[5] { '\0' };
			sdk::uint32_t command_raw;
		};

		callbackfn_t callback;

	public:
		inline static std::vector<module *> instances;
	};
}

#define cm_create_command(str) [] () -> sdk::uint32_t \
{ \
	static_assert(sizeof(str) == 5, "Command must be exactly 4 characters long!"); \
	constexpr sdk::uint32_t result = static_cast<sdk::uint32_t>(str[3]) << 24 | static_cast<sdk::uint32_t>(str[2]) << 16 | static_cast<sdk::uint32_t>(str[1]) << 8 | static_cast<sdk::uint32_t>(str[0]); \
	return result; \
} ()