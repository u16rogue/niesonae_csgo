#pragma once

#include <sdk/types.hpp>
#include <sdk/valve_sdk/utlvector.hpp>

namespace sdk::valve
{
	class CHudElement_interface
	{

	private:

		virtual void zz_pad_0(void) = 0;
		virtual void zz_pad_1(void) = 0;
		virtual void zz_pad_2(void) = 0;
		virtual void zz_pad_3(void) = 0;
		virtual void zz_pad_4(void) = 0;
		virtual void zz_pad_5(void) = 0;
		virtual void zz_pad_6(void) = 0;
		virtual void zz_pad_7(void) = 0;
		virtual void zz_pad_8(void) = 0;
		virtual void zz_pad_9(void) = 0;
		virtual void zz_pad_10(void) = 0;
		virtual void zz_pad_11(void) = 0;
	public:

		virtual const char *GetName(void) = 0;
	private:

		virtual void zz_pad_13(void) = 0;
		virtual void zz_pad_14(void) = 0;
		virtual void zz_pad_15(void) = 0;
		virtual void zz_pad_16(void) = 0;
		virtual void zz_pad_17(void) = 0;
		virtual void zz_pad_18(void) = 0;
		virtual void zz_pad_19(void) = 0;
		virtual void zz_pad_20(void) = 0;
		virtual void zz_pad_21(void) = 0;
		virtual void zz_pad_22(void) = 0;
		virtual void zz_pad_23(void) = 0;
		virtual void zz_pad_24(void) = 0;
		virtual void zz_pad_25(void) = 0;
		virtual void zz_pad_26(void) = 0;
		virtual void zz_pad_27(void) = 0;
		virtual void zz_pad_28(void) = 0;
		virtual void zz_pad_29(void) = 0;
	};

	class CHudElement : public CHudElement_interface
	{
		/*
		* 
		* TODO: actually properly reverse the correct structure of this
		* 
		class CHud;

	private: // padded. too lazy. implementation: ~\cstrike15_src\game\shared\GameEventListener.h
		sdk::byte_t       pad[0x15];

	public:
		bool			  m_bActive;
		bool              m_bWantLateUpdate;
		int				  m_iHiddenBits;
		int				  m_nSplitScreenPlayerSlot;
		bool			  m_ignoreGlobalHudDisable;
		const char       *m_pElementName;
		bool			  m_bNeedsRemove;
		bool			  m_bIsParentedToClientDLLRootPanel;
		CUtlVector<int>   m_HudRenderGroups;
		CHud             *m_pHud;
		*/
	};
}