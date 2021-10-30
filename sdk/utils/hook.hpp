#pragma once

#include <sdk/types.hpp>
#include "minhook/MinHook.hpp"

namespace sdk
{
	template <typename t_fn>
	class hook
	{
	public:
		hook(t_fn *fn_hook_) : fn_hook(fn_hook_) {}

	public:
		t_fn *attach(t_fn *fn_original_)
		{
			this->fn_original = fn_original_;

			bool result = MH_CreateHook(reinterpret_cast<void*>(this->fn_original), reinterpret_cast<void*>(this->fn_hook), reinterpret_cast<void**>(&this->fn_new_entry)) == MH_OK;

			if (!result)
				return nullptr;
			
			return this->fn_new_entry;
		}

		bool dettach()
		{
			return MH_RemoveHook(this->fn_original) == MH_OK;
		}

		bool commit()
		{
			return MH_EnableHook(this->fn_original) == MH_OK;
		}

		bool uncommit()
		{
			return MH_DisableHook(this->fn_original) == MH_OK;
		}

	public:
		t_fn *get_new_entry()
		{
			return this->fn_new_entry;
		}

		t_fn *get_hook()
		{
			return this->fn_hook;
		}

	private:
		t_fn *fn_original  { nullptr };
		t_fn *fn_hook      { nullptr };
		t_fn *fn_new_entry { nullptr };
	};

	static bool hook_init()
	{
		return MH_Initialize() == MH_OK;
	}

	static bool hook_uninit()
	{
		return MH_Uninitialize() == MH_OK;
	}

	static bool hook_commit_all()
	{
		return MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
	}

	static bool hook_uncommit_all()
	{
		return MH_DisableHook(MH_ALL_HOOKS) == MH_OK;
	}
}