#pragma once

#include <sdk/valve_sdk/usercmd.hpp>

namespace sdk::valve
{
	class IClientMode
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
	public:

		virtual bool ShouldDrawFog(void) = 0;
	private:

		virtual void zz_pad_18(void) = 0;
		virtual void zz_pad_19(void) = 0;
		virtual void zz_pad_20(void) = 0;
		virtual void zz_pad_21(void) = 0;
		virtual void zz_pad_22(void) = 0;
		virtual void zz_pad_23(void) = 0;
	public:

		virtual bool CreateMove(float flInputSampleTime, void *usercmd) = 0;
	private:

		virtual void zz_pad_25(void) = 0;
		virtual void zz_pad_26(void) = 0;
		virtual void zz_pad_27(void) = 0;
	public:

		virtual bool ShouldDrawCrosshair(void) = 0;
	private:

		virtual void zz_pad_29(void) = 0;
		virtual void zz_pad_30(void) = 0;
		virtual void zz_pad_31(void) = 0;
		virtual void zz_pad_32(void) = 0;
		virtual void zz_pad_33(void) = 0;
		virtual void zz_pad_34(void) = 0;
	public:

		virtual float GetViewModelFOV(void) = 0;
	private:

		virtual void zz_pad_36(void) = 0;
	public:

		virtual wchar_t *GetServerName(void) = 0;
	private:

		virtual void zz_pad_38(void) = 0;
	public:

		virtual wchar_t *GetMapName(void) = 0;
	private:

		virtual void zz_pad_40(void) = 0;
		virtual void zz_pad_41(void) = 0;
		virtual void zz_pad_42(void) = 0;
		virtual void zz_pad_43(void) = 0;
		virtual void zz_pad_44(void) = 0;
		virtual void zz_pad_45(void) = 0;
		virtual void zz_pad_46(void) = 0;
		virtual void zz_pad_47(void) = 0;
		virtual void zz_pad_48(void) = 0;
		virtual void zz_pad_49(void) = 0;
		virtual void zz_pad_50(void) = 0;
		virtual void zz_pad_51(void) = 0;
		virtual void zz_pad_52(void) = 0;
		virtual void zz_pad_53(void) = 0;
		virtual void zz_pad_54(void) = 0;
		virtual void zz_pad_55(void) = 0;
		virtual void zz_pad_56(void) = 0;
		virtual void zz_pad_57(void) = 0;
		virtual void zz_pad_58(void) = 0;
		virtual void zz_pad_59(void) = 0;
		virtual void zz_pad_60(void) = 0;
		virtual void zz_pad_61(void) = 0;
		virtual void zz_pad_62(void) = 0;
		virtual void zz_pad_63(void) = 0;
		virtual void zz_pad_64(void) = 0;
		virtual void zz_pad_65(void) = 0;
		virtual void zz_pad_66(void) = 0;
		virtual void zz_pad_67(void) = 0;
		virtual void zz_pad_68(void) = 0;
		virtual void zz_pad_69(void) = 0;
		virtual void zz_pad_70(void) = 0;
		virtual void zz_pad_71(void) = 0;
		virtual void zz_pad_72(void) = 0;
		virtual void zz_pad_73(void) = 0;
		virtual void zz_pad_74(void) = 0;
		virtual void zz_pad_75(void) = 0;
		virtual void zz_pad_76(void) = 0;
		virtual void zz_pad_77(void) = 0;
		virtual void zz_pad_78(void) = 0;
		virtual void zz_pad_79(void) = 0;
	};
}