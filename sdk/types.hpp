#pragma once

namespace sdk
{
	using ptr_t     = unsigned char*;
	using iptr_t    = unsigned long;
	using offset_t  = unsigned long;

	using byte_t    = unsigned char;
	using uint16_t  = unsigned short;
	using uint32_t  = unsigned long;
	using uint64_t  = unsigned long long;

	using int8_t    = char;
	using int16_t   = short;
	using int32_t   = long;
	using int64_t   = long long;

	using size_t    = unsigned long long;
	using size32_t  = unsigned long;
}

#define sdk_to_ptr(var) reinterpret_cast<sdk::ptr_t>(var)