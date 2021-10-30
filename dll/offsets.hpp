#pragma once

#include <sdk/types.hpp>

#define sdk_create_offset(name, value) \
	constexpr sdk::iptr_t name = static_cast<sdk::iptr_t>(value)

namespace offsets
{
	sdk_create_offset(matsystoppanel_id, 0xF4A14);
}

#undef sdk_create_offset