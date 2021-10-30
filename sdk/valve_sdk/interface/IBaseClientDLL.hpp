#pragma once

#include <sdk/types.hpp>
#include <sdk/valve_sdk/client_class.hpp>

namespace sdk::valve
{
	class IBaseClientDLL
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
	public:

		virtual sdk::valve::ClientClass *GetAllClasses(void) = 0;
	private:

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
		virtual void zz_pad_27(void) = 0;
		virtual void zz_pad_28(void) = 0;
		virtual void zz_pad_29(void) = 0;
		virtual void zz_pad_30(void) = 0;
		virtual void zz_pad_31(void) = 0;
		virtual void zz_pad_32(void) = 0;
		virtual void zz_pad_33(void) = 0;
		virtual void zz_pad_34(void) = 0;
		virtual void zz_pad_35(void) = 0;
		virtual void zz_pad_36(void) = 0;
		virtual void zz_pad_37(void) = 0;
	public:

		virtual bool DispatchUserMessage(int msg_type, sdk::int32_t nFlags, int size, const void *msg) = 0;
	private:

		virtual void zz_pad_39(void) = 0;
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
	};
}