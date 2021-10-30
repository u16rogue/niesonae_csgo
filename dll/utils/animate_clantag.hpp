#pragma once

#include <array>

namespace utils
{
	// TODO: reverse animation on half
	// TODO: remake this to receive multi-byte instead
	template <typename... args>
	constexpr std::array<char[16], sizeof...(args)> create_animated_clantag(args... ct_parts)
	{
		constexpr int char_count = sizeof...(ct_parts);

		//static_assert(char_count > 15, "Clantag buffer overflow!");

		std::array<char, char_count>     parts  = { { ct_parts... } };
		std::array<char[16], char_count> result = {  { '\0' }   };

		for (int buffer_idx = 0; buffer_idx < char_count; buffer_idx++)
			for (int char_idx = 0; char_idx < char_count; char_idx++)
				result[buffer_idx][char_idx] = parts[(char_idx + buffer_idx) % char_count];

		return result;
	}

	template <char upper, typename... args>
	constexpr std::array<char[16], sizeof...(args)> create_animated_clantag_u8(args... ct_parts)
	{
		constexpr int char_count = sizeof...(ct_parts);

		std::array<char, char_count>     parts = { { ct_parts... } };
		std::array<char[16], char_count> result = { { '\0' } };

		for (int buffer_idx = 0; buffer_idx < char_count; buffer_idx++)
			for (int char_idx = 0; char_idx < char_count; char_idx++)
			{
				result[buffer_idx][char_idx * 2]     = upper;
				result[buffer_idx][char_idx * 2 + 1] = parts[(char_idx + buffer_idx) % char_count];
			}

		return result;
	}
}