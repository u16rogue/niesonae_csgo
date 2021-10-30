#pragma once

#include <sdk/console.hpp>
#include "module.hpp"

namespace sdk
{
	class module_csgo : public sdk::module
	{
		using engine_create_interface_fn_t   = void*(__cdecl)(const char*, int*);
		using engine_create_interface_fn_ptr = engine_create_interface_fn_t*;

		class InterfaceReg
		{
		public:
			sdk::ptr_t(*m_CreateFn)(void);
			const char *m_pName;
			InterfaceReg *m_pNext;
		};

	public:

		module_csgo(sdk::hash::fnv64_t name_) : module(name_) {}

	public:

		sdk::env::structs::PLDR_DATA_TABLE_ENTRY init()
		{
			if (!sdk::module::init())
				return nullptr;

			// based off engine.dll export, should be the same across all dll's
			// push    ebp                     (1 byte)
			// mov     ebp, esp                (2 bytes)
			// pop     ebp                     (1 byte)
			// jmp     CreateInterfaceInternal (relative jmp 1 byte)
			sdk::ptr_t create_interface_fnptr = this->import_function<sdk::byte_t>(sdk_fnv64_cx("CreateInterface"));
			this->ptr_create_interface_internal = reinterpret_cast<engine_create_interface_fn_ptr>( (create_interface_fnptr + 0x9) + reinterpret_cast<char*>(create_interface_fnptr)[0x5]); // get the address of the next instruction then add the offset from the first byte of the 4 byte operand of the jmp instruction to "simulate" the jump
			
			// push    ebp                   (1 byte)
			// mov     ebp, esp              (2 bytes)
			// push    esi                   (1 byte)
			// mov     esi, s_pInterfaceRegs (mov esi 2 bytes)
			this->s_pInterfaceRegs = *reinterpret_cast<InterfaceReg***>(reinterpret_cast<sdk::ptr_t>(this->ptr_create_interface_internal) + 0x6);
			
			return this->get_entry();
		}

		template <typename t_interface>
		t_interface* create_interface(const char *iface_name)
		{
			return reinterpret_cast<t_interface*>(this->ptr_create_interface_internal(iface_name, nullptr));
		}
		
		template <typename t_interface>
		t_interface* create_interface(sdk::hash::fnv_contracted_t iface_contracted)
		{
			sdk::hash::fnv32_t iface_name = sdk_fnv_contracted_hi(iface_contracted);
			sdk::size32_t      iface_len  = sdk_fnv_contracted_lo(iface_contracted);
			InterfaceReg      *current    = *this->s_pInterfaceRegs;

			while (current)
			{
				if (sdk::hash::fnv32(current->m_pName, iface_len) == iface_name)
					return reinterpret_cast<t_interface*>(current->m_CreateFn());

				current = current->m_pNext;
			}

			return nullptr;
		}

		#ifdef _DEBUG
		void dump_interface()
		{
			InterfaceReg* current = *this->s_pInterfaceRegs;
			while (current)
			{
				sdk_con_cout_debug("\n" << current->m_pName << ": 0x" << (void*)current->m_CreateFn());
				current = current->m_pNext;
			}
		}
		#endif

	private:
		engine_create_interface_fn_ptr ptr_create_interface_internal { nullptr };
		InterfaceReg **s_pInterfaceRegs { nullptr };
	};
}