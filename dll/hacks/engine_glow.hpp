#pragma once

#include <dll/globals.hpp>
#include <sdk/utils/patch.hpp>
#include <sdk/singleton.hpp>
#include <sdk/valve_sdk/glow_outline_effect.hpp>

// TODO: do more reversing, should be implemented in an efficient way, preferably (???) on glow setup in ApplyEntityGlow

namespace hacks
{
	class engine_glow : public sdk::singleton<engine_glow>
	{
	public:
		engine_glow() = default;

		bool init()
		{
			*reinterpret_cast<void**>(sdk_to_ptr(&this->ApplyEntityGlowEffect_iterator_detour.new_bytes) + 1) = &engine_glow::glow_object_iterator_should_glow;

			if (!this->ApplyEntityGlowEffect_iterator_detour.set_write(modules::client.sigscan_traverse<sdk::byte_t>(sdk_sig_cache_as_arg_cx("66 66 0F 1F 84 00 ?? ?? ?? ?? 8B 07"), 0xA)))
				return false;

			return true;
		}

		// check start sig: 66 66 0F 1F 84 00 ?? ?? ?? ?? 8B 07 + 0xA | can also move to + 0xC this way no need to re asm to obtain the members
		// registers ecx and edx should be available, except for eax which is used for the next iteration check, should restore later by deref edi
		static bool __fastcall glow_object_iterator_should_glow(sdk::valve::CGlowObjectManager::GlowObjectDefinition *object, int slot)
		{
			sdk::valve::C_BaseEntity *entity = object->m_pEntity;
			
			if (!entity)
				return false;

			if (!engine_glow::instance().enable
			||  !entity->IsPlayer()
			||   entity->IsDormant()
			||  !entity->IsAlive()
			||   entity->m_iTeamNum() == (*globals::localplayer)->m_iTeamNum()
			||   object->m_nNextFreeSlot != sdk::valve::CGlowObjectManager::GlowObjectDefinition::ENTRY_IN_USE
			) {
				// original entity object check
				return object->m_nNextFreeSlot == sdk::valve::CGlowObjectManager::GlowObjectDefinition::ENTRY_IN_USE
					&& (object->m_nSplitScreenSlot == -2 || object->m_nSplitScreenSlot == slot)
					&& (object->m_bRenderWhenOccluded    || object->m_bRenderWhenUnoccluded   )
					&& entity->ShouldDraw()
					&& object->m_nRenderStyle == sdk::valve::GlowRenderStyle::GLOWRENDERSTYLE_DEFAULT;
			}

			// TODO: get player max health instead of hard coding 100
			int ent_health                = reinterpret_cast<sdk::valve::C_BasePlayer *>(entity)->m_iHealth();
			object->m_vGlowColor          = sdk::valve::GlowColor(1.f - ent_health / 100.f, ent_health / 100.f, 0);
			object->m_nRenderStyle        = sdk::valve::GlowRenderStyle::GLOWRENDERSTYLE_DEFAULT;
			object->m_bRenderWhenOccluded = true;

			return true;
		}

	public:
		bool enable = true;

	private:
		sdk::patch<26> ApplyEntityGlowEffect_iterator_detour = sdk::patch<26>
		(
			0xB8, 0x00, 0x00, 0x00, 0x00,	    // MOV  EAX, engine_glow::glow_object_iterator_should_glow()
			0x8B, 0x0F,						    // MOV  ECX, DWORD PTR DS:[EDI]
			0x03, 0xCE,						    // ADD  ECX, ESI
			0x8B, 0x55, 0x0C,				    // MOV  EDX, DWORD PTR SS:[EBP+0xC]
			0xFF, 0xD0,						    // CALL EAX
			0x84, 0xC0,						    // TEST AL, AL
			0x0F, 0x84, 0x67, 0x0A, 0x00, 0x00, // JE   iterator_next
			0x8B, 0x07,						    // MOV  EAX, DWORD PTR DS:[EDI]
			0xEB, 0x42 						    // JMP  next_unpatched_instruction
		);

	};
}