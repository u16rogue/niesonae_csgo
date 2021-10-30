#pragma once

#include <array>
#include <sdk/types.hpp>

namespace sdk::ptr
{
	// NOTE: Last offset is NOT dereferenced but rather returned as a pointer
	template <typename ret_t, typename arg_t>
	ret_t *traverse(sdk::ptr_t adr, arg_t offset)
	{
		return reinterpret_cast<ret_t *>(adr + static_cast<sdk::offset_t>(offset));
	}

	// NOTE: Last offset is NOT dereferenced but rather returned as a pointer
	template <typename ret_t, typename arg_t, typename... ptrmap_t>
	ret_t *traverse(sdk::ptr_t adr, arg_t offset, ptrmap_t... ptrmap)
	{
		return traverse<ret_t>(*reinterpret_cast<sdk::ptr_t *>(adr + static_cast<sdk::offset_t>(offset)), ptrmap...);
	}
}

// #define sdk_as_ptr_offset(index) (index * sizeof(void*))