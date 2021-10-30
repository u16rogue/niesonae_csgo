#pragma once

#include <cstring>
#include <sdk/types.hpp>
#include <sdk/imports.hpp>

namespace sdk
{
	template <sdk::size_t size>
	class patch
	{
		struct bytes_struct_t
		{
			sdk::byte_t data[size];
		};

	public:
		constexpr patch() : is_nop_patch(true) {}
		
		template <typename... byte_arg_template>
		constexpr patch(byte_arg_template... new_bytes_) : is_nop_patch(false), new_bytes({ { static_cast<sdk::byte_t>(new_bytes_)... } }) { static_assert(size == sizeof...(new_bytes_), "Patched bytes must match number of arguments!"); }

		void set_adr(sdk::ptr_t adr)
		{
			this->address = adr;
		}

		bool write()
		{
			DWORD old_protect = 0;
			if (!imports::VirtualProtect(this->address, size, PAGE_EXECUTE_READWRITE, &old_protect))
				return false;

			memcpy(&this->original_bytes, this->address, size);

			if (this->is_nop_patch)
				memset(this->address, 0x90, size);
			else
				memcpy(this->address, &this->new_bytes, size);

			if (!imports::VirtualProtect(this->address, size, old_protect, nullptr))
				return false;

			return true;
		}

		bool restore()
		{
			DWORD old_protect = 0;
			if (!imports::VirtualProtect(this->address, size, PAGE_EXECUTE_READWRITE, &old_protect))
				return false;

			memcpy(this->address, this->original_bytes, size);

			if (!imports::VirtualProtect(this->address, size, old_protect, nullptr))
				return false;

			return true;
		}

		bool set_write(sdk::ptr_t adr)
		{
			if (adr == nullptr)
				return false;

			this->address = adr;
			return this->write();
		}

		bool is_patched()
		{
			return !memcmp(this->new_bytes, this->address, size);
		}

	public:
		const bool     is_nop_patch   { false };
		sdk::ptr_t     address         { 0x0 };
		bytes_struct_t original_bytes  { 0x0 };
		bytes_struct_t new_bytes       { 0x0 };
	};
}