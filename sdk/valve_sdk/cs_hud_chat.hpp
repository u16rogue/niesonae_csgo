#pragma once

namespace sdk::valve
{
	class CBaseHudChat
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
		virtual void zz_pad_12(void) = 0;
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
	public:

		virtual void ChatPrintf(int iPlayerIndex, int iFilter, const char *fmt, ...) = 0;
		virtual void ChatPrintfW(int iPlayerIndex, int iFilter, const wchar_t *wszNotice) = 0;
	private:

		virtual void zz_pad_29(void) = 0;
	};

	class CHudChat : public CBaseHudChat
	{

	};
}