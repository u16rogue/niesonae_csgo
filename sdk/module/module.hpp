#pragma once

#include <sdk/hash/fnv.hpp>
#include <sdk/winternal/environment.hpp>
#include <sdk/utils/sigscan.hpp>
#include <sdk/utils/pointers.hpp>

namespace sdk
{
	class module
	{
	public:

		module(sdk::hash::fnv64_t name_) : name(name_) { }

	public:

		sdk::env::structs::PLDR_DATA_TABLE_ENTRY init()
		{
			this->entry_ptr = sdk::env::ldr_find(this->name);
			return this->entry_ptr;
		}

		const sdk::env::structs::PLDR_DATA_TABLE_ENTRY &get_entry(void)
		{
			return this->entry_ptr;
		}

		template <typename fn_t>
		fn_t *import_function(sdk::hash::fnv64_t fn_name)
		{
			return sdk::env::import_function<fn_t>(this->entry_ptr->DllBase, fn_name);
		}

		template <typename T>
		T *sigscan(sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count)
		{
			return sdk::sig::scan<T>(this->entry_ptr->DllBase, this->entry_ptr->SizeOfImage, cached_sig, pattern_count);
		}

		template <typename T>
		T *sigscan_traverse(sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count, sdk::offset_t offset)
		{
			sdk::ptr_t result = sdk::sig::scan<sdk::byte_t>(this->entry_ptr->DllBase, this->entry_ptr->SizeOfImage, cached_sig, pattern_count);
			return sdk::ptr::traverse<T>(result, offset);
		}

		template <typename T, typename... ptrmap_t>
		T *sigscan_traverse(sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count,sdk::offset_t offset, ptrmap_t... ptrmap)
		{
			sdk::ptr_t result = sdk::sig::scan<sdk::byte_t>(this->entry_ptr->DllBase, this->entry_ptr->SizeOfImage, cached_sig, pattern_count);
			return sdk::ptr::traverse<T>(result, offset, ptrmap...);
		}

	private:
		sdk::hash::fnv_contracted_t name { 0 };
		sdk::env::structs::PLDR_DATA_TABLE_ENTRY entry_ptr { nullptr };
	};
}