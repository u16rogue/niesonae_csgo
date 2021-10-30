#pragma once

#include <sdk/color.hpp>

namespace sdk::valve
{
    enum class FontFeature
    {
        ANTIALIASED_FONTS = 1,
        DROPSHADOW_FONTS  = 2,
        OUTLINE_FONTS     = 6,
    };

    enum class FontDrawType
    {
        DEFAULT = 0,
        NONADDITIVE,
        ADDITIVE,
        TYPE_COUNT = 2,
    };

    enum class FontFlags : int
    {
        NONE,
        ITALIC       = 0x001,
        UNDERLINE    = 0x002,
        STRIKEOUT    = 0x004,
        SYMBOL       = 0x008,
        ANTIALIAS    = 0x010,
        GAUSSIANBLUR = 0x020,
        ROTARY       = 0x040,
        DROPSHADOW   = 0x080,
        ADDITIVE     = 0x100,
        OUTLINE      = 0x200,
        CUSTOM       = 0x400,
        BITMAP       = 0x800,
    };
	
	class ISurface
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
	public:

		virtual void DrawSetColor(int r, int g, int b, int a) = 0;
		virtual void DrawSetColor(sdk::color col) = 0;
		virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	private:

		virtual void zz_pad_17(void) = 0;
		virtual void zz_pad_18(void) = 0;
		virtual void zz_pad_19(void) = 0;
		virtual void zz_pad_20(void) = 0;
		virtual void zz_pad_21(void) = 0;
		virtual void zz_pad_22(void) = 0;
	public:

		virtual void SetTextFont(unsigned long font) = 0;
	private:

		virtual void zz_pad_24(void) = 0;
	public:

		virtual void SetTextColor(int r, int g, int b, int a) = 0;
		virtual void SetTextPosition(int x, int y) = 0;
	private:

		virtual void zz_pad_27(void) = 0;
	public:

		virtual void DrawTextW(const wchar_t *text, int length, sdk::valve::FontDrawType drawtype) = 0;
	private:

		virtual void zz_pad_29(void) = 0;
		virtual void zz_pad_30(void) = 0;
		virtual void zz_pad_31(void) = 0;
		virtual void zz_pad_32(void) = 0;
		virtual void zz_pad_33(void) = 0;
		virtual void zz_pad_34(void) = 0;
		virtual void zz_pad_35(void) = 0;
		virtual void zz_pad_36(void) = 0;
		virtual void zz_pad_37(void) = 0;
		virtual void zz_pad_38(void) = 0;
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
	public:

		virtual unsigned long CreateFont_(void) = 0;
		virtual bool SetFontGlyphSet(unsigned long font, const char *font_name, int tall, int weight, int blur, int scanlines, sdk::valve::FontFlags flags, int range_min, int range_max) = 0;
	private:

		virtual void zz_pad_73(void) = 0;
		virtual void zz_pad_74(void) = 0;
		virtual void zz_pad_75(void) = 0;
		virtual void zz_pad_76(void) = 0;
		virtual void zz_pad_77(void) = 0;
		virtual void zz_pad_78(void) = 0;
		virtual void zz_pad_79(void) = 0;
		virtual void zz_pad_80(void) = 0;
		virtual void zz_pad_81(void) = 0;
		virtual void zz_pad_82(void) = 0;
		virtual void zz_pad_83(void) = 0;
		virtual void zz_pad_84(void) = 0;
		virtual void zz_pad_85(void) = 0;
		virtual void zz_pad_86(void) = 0;
		virtual void zz_pad_87(void) = 0;
		virtual void zz_pad_88(void) = 0;
		virtual void zz_pad_89(void) = 0;
		virtual void zz_pad_90(void) = 0;
		virtual void zz_pad_91(void) = 0;
		virtual void zz_pad_92(void) = 0;
		virtual void zz_pad_93(void) = 0;
		virtual void zz_pad_94(void) = 0;
		virtual void zz_pad_95(void) = 0;
		virtual void zz_pad_96(void) = 0;
		virtual void zz_pad_97(void) = 0;
	};
}