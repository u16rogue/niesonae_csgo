#pragma once

#include <iostream>

#include <intrin.h>
#include <sdk/hash/fnv.hpp>
#include "structs.hpp"

namespace sdk::env
{
	bool ldr_next(sdk::env::structs::PLDR_DATA_TABLE_ENTRY *ldr_ptr)
	{
		using entry_t = sdk::env::structs::PLDR_DATA_TABLE_ENTRY;

		if (!ldr_ptr)
			return false;

		static entry_t first_entry = reinterpret_cast<entry_t>(reinterpret_cast<sdk::env::structs::PPEB>(__readfsdword(0x30))->Ldr->InLoadOrderModuleList.Flink);
		
		if (*ldr_ptr == nullptr)
		{
			*ldr_ptr = first_entry;
			return true;
		}
		
		if (*ldr_ptr != nullptr && ((*ldr_ptr)->InLoadOrderLinks.Flink == nullptr || reinterpret_cast<entry_t>((*ldr_ptr)->InLoadOrderLinks.Flink) == first_entry) )
			return false;

		*ldr_ptr = reinterpret_cast<entry_t>((*ldr_ptr)->InLoadOrderLinks.Flink);
		return true;
	}
	
	sdk::env::structs::PLDR_DATA_TABLE_ENTRY ldr_find(sdk::hash::fnv_contracted_t module_name)
	{
		sdk::hash::fnv32_t name = sdk_fnv_contracted_hi(module_name);
		sdk::hash::fnv32_t len  = sdk_fnv_contracted_lo(module_name);
		sdk::env::structs::PLDR_DATA_TABLE_ENTRY ldr_entry = nullptr;

		while (sdk::env::ldr_next(&ldr_entry))
		{
			if (!ldr_entry)
				break;

			if (ldr_entry->DllBase == nullptr)
				continue;

			if (sdk::hash::fnv32(ldr_entry->BaseDllName.Buffer, len) == name)
				return ldr_entry;
		}

		return nullptr;
	}

	template <typename fn_t>
	fn_t* import_function(sdk::ptr_t mod_address, sdk::hash::fnv64_t fn_name)
	{
		sdk::env::structs::PIMAGE_EXPORT_DIRECTORY export_dir     = reinterpret_cast<sdk::env::structs::PIMAGE_EXPORT_DIRECTORY>(mod_address + (reinterpret_cast<sdk::env::structs::PIMAGE_NT_HEADERS>(mod_address + reinterpret_cast<sdk::env::structs::PIMAGE_DOS_HEADER>(mod_address)->e_lfanew)->OptionalHeader.DataDirectory[0].VirtualAddress)); // NT Header address
		sdk::env::structs::ExportFnNames           export_names   = reinterpret_cast<sdk::env::structs::ExportFnNames>(mod_address + export_dir->AddressOfNames);
		sdk::env::structs::ExportFnAddress         export_address = reinterpret_cast<sdk::env::structs::ExportFnAddress>(mod_address + export_dir->AddressOfFunctions);
		sdk::env::structs::ExportFnOrdinal         export_ordinal = reinterpret_cast<sdk::env::structs::ExportFnOrdinal>(mod_address + export_dir->AddressOfNameOrdinals);

		if (!export_dir->NumberOfFunctions)
			return nullptr;

		for (unsigned int idx = 0; idx < export_dir->NumberOfNames; idx++)
		{
			if (sdk::hash::fnv64(reinterpret_cast<const char *>(mod_address + export_names[idx])) != fn_name)
				continue;

			#ifdef _DEBUG
			std::cout << "\n[IMPORT] Module: 0x" << reinterpret_cast<void*>(mod_address) << "\n\t" << reinterpret_cast<const char *>(mod_address + export_names[idx]) << ": 0x" << reinterpret_cast<void*>(mod_address + export_address[export_ordinal[idx]]);
			#endif
			return reinterpret_cast<fn_t*>(mod_address + export_address[export_ordinal[idx]]);
		}

		return nullptr;
	}

	template <typename fn_t>
	fn_t *import_function(sdk::hash::fnv64_t fn_name)
	{
		sdk::env::structs::PLDR_DATA_TABLE_ENTRY ldr_entry = nullptr;

		while (sdk::env::ldr_next(&ldr_entry))
		{
			if (!ldr_entry)
				break;

			if (ldr_entry->DllBase == nullptr)
				continue;
			
			if (fn_t *result = sdk::env::import_function<fn_t>(ldr_entry->DllBase, fn_name))
				return result;
		}

		return nullptr;
	}
}