#pragma once

#include <sdk/matrix.hpp>
#include <sdk/angle.hpp>

namespace sdk::valve
{
	class IVEngineClient
	{

	private:

		virtual void zz_pad_0(void) = 0;
		virtual void zz_pad_1(void) = 0;
		virtual void zz_pad_2(void) = 0;
		virtual void zz_pad_3(void) = 0;
		virtual void zz_pad_4(void) = 0;
	public:

		virtual void GetScreenSize(int &width, int &height) = 0;
		virtual void ServerCmd(const char *szCmdString, bool bReliable = true) = 0;
		virtual void ClientCmd(const char *szCmdString) = 0;
	private:

		virtual void zz_pad_8(void) = 0;
		virtual void zz_pad_9(void) = 0;
		virtual void zz_pad_10(void) = 0;
		virtual void zz_pad_11(void) = 0;
	public:

		virtual int GetLocalPlayer(void) = 0;
	private:

		virtual void zz_pad_13(void) = 0;
		virtual void zz_pad_14(void) = 0;
		virtual void zz_pad_15(void) = 0;
		virtual void zz_pad_16(void) = 0;
		virtual void zz_pad_17(void) = 0;
		virtual void zz_pad_18(void) = 0;
	public:

		virtual void SetViewAngles(sdk::angle &va) = 0;
		virtual int GetMaxClients(void) = 0;
	private:

		virtual void zz_pad_21(void) = 0;
		virtual void zz_pad_22(void) = 0;
		virtual void zz_pad_23(void) = 0;
		virtual void zz_pad_24(void) = 0;
		virtual void zz_pad_25(void) = 0;
	public:

		virtual bool IsInGame(void) = 0;
		virtual bool IsConnected(void) = 0;
	private:

		virtual void zz_pad_28(void) = 0;
		virtual void zz_pad_29(void) = 0;
		virtual void zz_pad_30(void) = 0;
		virtual void zz_pad_31(void) = 0;
		virtual void zz_pad_32(void) = 0;
		virtual void zz_pad_33(void) = 0;
		virtual void zz_pad_34(void) = 0;
		virtual void zz_pad_35(void) = 0;
		virtual void zz_pad_36(void) = 0;
	public:

		virtual const sdk::matrix4x4 &WorldToScreenMatrix(void) = 0;
		virtual const sdk::matrix4x4 &WorldToViewMatrix(void) = 0;
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
		virtual void zz_pad_98(void) = 0;
		virtual void zz_pad_99(void) = 0;
		virtual void zz_pad_100(void) = 0;
		virtual void zz_pad_101(void) = 0;
		virtual void zz_pad_102(void) = 0;
		virtual void zz_pad_103(void) = 0;
		virtual void zz_pad_104(void) = 0;
		virtual void zz_pad_105(void) = 0;
		virtual void zz_pad_106(void) = 0;
		virtual void zz_pad_107(void) = 0;
	public:

		virtual void ExecuteClientCmd(const char *szCmdString) = 0;
	private:

		virtual void zz_pad_109(void) = 0;
		virtual void zz_pad_110(void) = 0;
		virtual void zz_pad_111(void) = 0;
		virtual void zz_pad_112(void) = 0;
		virtual void zz_pad_113(void) = 0;
	public:

		virtual void ClientCmd_Unrestricted(const char *szCmdString) = 0;
	private:

		virtual void zz_pad_115(void) = 0;
		virtual void zz_pad_116(void) = 0;
		virtual void zz_pad_117(void) = 0;
		virtual void zz_pad_118(void) = 0;
		virtual void zz_pad_119(void) = 0;
		virtual void zz_pad_120(void) = 0;
		virtual void zz_pad_121(void) = 0;
		virtual void zz_pad_122(void) = 0;
		virtual void zz_pad_123(void) = 0;
		virtual void zz_pad_124(void) = 0;
		virtual void zz_pad_125(void) = 0;
		virtual void zz_pad_126(void) = 0;
		virtual void zz_pad_127(void) = 0;
		virtual void zz_pad_128(void) = 0;
		virtual void zz_pad_129(void) = 0;
		virtual void zz_pad_130(void) = 0;
		virtual void zz_pad_131(void) = 0;
		virtual void zz_pad_132(void) = 0;
		virtual void zz_pad_133(void) = 0;
		virtual void zz_pad_134(void) = 0;
		virtual void zz_pad_135(void) = 0;
		virtual void zz_pad_136(void) = 0;
		virtual void zz_pad_137(void) = 0;
		virtual void zz_pad_138(void) = 0;
		virtual void zz_pad_139(void) = 0;
		virtual void zz_pad_140(void) = 0;
		virtual void zz_pad_141(void) = 0;
		virtual void zz_pad_142(void) = 0;
		virtual void zz_pad_143(void) = 0;
		virtual void zz_pad_144(void) = 0;
		virtual void zz_pad_145(void) = 0;
		virtual void zz_pad_146(void) = 0;
		virtual void zz_pad_147(void) = 0;
		virtual void zz_pad_148(void) = 0;
		virtual void zz_pad_149(void) = 0;
		virtual void zz_pad_150(void) = 0;
		virtual void zz_pad_151(void) = 0;
		virtual void zz_pad_152(void) = 0;
		virtual void zz_pad_153(void) = 0;
		virtual void zz_pad_154(void) = 0;
		virtual void zz_pad_155(void) = 0;
		virtual void zz_pad_156(void) = 0;
		virtual void zz_pad_157(void) = 0;
		virtual void zz_pad_158(void) = 0;
		virtual void zz_pad_159(void) = 0;
		virtual void zz_pad_160(void) = 0;
		virtual void zz_pad_161(void) = 0;
		virtual void zz_pad_162(void) = 0;
		virtual void zz_pad_163(void) = 0;
		virtual void zz_pad_164(void) = 0;
		virtual void zz_pad_165(void) = 0;
		virtual void zz_pad_166(void) = 0;
		virtual void zz_pad_167(void) = 0;
		virtual void zz_pad_168(void) = 0;
		virtual void zz_pad_169(void) = 0;
		virtual void zz_pad_170(void) = 0;
		virtual void zz_pad_171(void) = 0;
		virtual void zz_pad_172(void) = 0;
		virtual void zz_pad_173(void) = 0;
		virtual void zz_pad_174(void) = 0;
		virtual void zz_pad_175(void) = 0;
		virtual void zz_pad_176(void) = 0;
		virtual void zz_pad_177(void) = 0;
		virtual void zz_pad_178(void) = 0;
		virtual void zz_pad_179(void) = 0;
		virtual void zz_pad_180(void) = 0;
		virtual void zz_pad_181(void) = 0;
		virtual void zz_pad_182(void) = 0;
		virtual void zz_pad_183(void) = 0;
		virtual void zz_pad_184(void) = 0;
		virtual void zz_pad_185(void) = 0;
		virtual void zz_pad_186(void) = 0;
		virtual void zz_pad_187(void) = 0;
		virtual void zz_pad_188(void) = 0;
		virtual void zz_pad_189(void) = 0;
		virtual void zz_pad_190(void) = 0;
		virtual void zz_pad_191(void) = 0;
		virtual void zz_pad_192(void) = 0;
		virtual void zz_pad_193(void) = 0;
		virtual void zz_pad_194(void) = 0;
		virtual void zz_pad_195(void) = 0;
		virtual void zz_pad_196(void) = 0;
		virtual void zz_pad_197(void) = 0;
		virtual void zz_pad_198(void) = 0;
		virtual void zz_pad_199(void) = 0;
		virtual void zz_pad_200(void) = 0;
		virtual void zz_pad_201(void) = 0;
		virtual void zz_pad_202(void) = 0;
		virtual void zz_pad_203(void) = 0;
		virtual void zz_pad_204(void) = 0;
		virtual void zz_pad_205(void) = 0;
		virtual void zz_pad_206(void) = 0;
		virtual void zz_pad_207(void) = 0;
		virtual void zz_pad_208(void) = 0;
		virtual void zz_pad_209(void) = 0;
		virtual void zz_pad_210(void) = 0;
		virtual void zz_pad_211(void) = 0;
		virtual void zz_pad_212(void) = 0;
		virtual void zz_pad_213(void) = 0;
		virtual void zz_pad_214(void) = 0;
		virtual void zz_pad_215(void) = 0;
		virtual void zz_pad_216(void) = 0;
		virtual void zz_pad_217(void) = 0;
		virtual void zz_pad_218(void) = 0;
		virtual void zz_pad_219(void) = 0;
		virtual void zz_pad_220(void) = 0;
		virtual void zz_pad_221(void) = 0;
		virtual void zz_pad_222(void) = 0;
		virtual void zz_pad_223(void) = 0;
		virtual void zz_pad_224(void) = 0;
		virtual void zz_pad_225(void) = 0;
		virtual void zz_pad_226(void) = 0;
	public:

		virtual bool IsReplay(void) = 0;
	};
}