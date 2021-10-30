#pragma once

#include <string>

#include <dll/globals.hpp>
#include <sdk/encryption/xorstr.hpp>


#define __m_utils_chatprefix u8" \x04[\x03\x30CB\x30A8\x30BD\x30CA\x30A8.\x30E2\x30A4\x04] \x01" // [ニエソナエ.モイ]

namespace utils
{
	inline void hudchat_print(const char *msg)
	{
		interfaces::hudchat->ChatPrintf(0, 0, xorstr(__m_utils_chatprefix "%s"), msg);
	}
}

#define utils_hudchat_print_static(msg) interfaces::hudchat->ChatPrintf(0, 0, xorstr(__m_utils_chatprefix msg));