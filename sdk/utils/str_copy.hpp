#pragma once

#include <sdk/types.hpp>

namespace sdk::str
{
	// WARNING: null terminator is not copied
	template <typename T>
	static sdk::size_t copy(const T *src, T *dest)
	{
		sdk::size_t len = 0;

		while (*src)
		{
			dest[len] = *src;
			++src;
			++len;
		}

		return len;
	}
}