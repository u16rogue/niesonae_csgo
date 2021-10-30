#pragma once

#include <sdk/utils/patch.hpp>

namespace patches
{
	// sig: FF D0 84 C0 74 0C 8B 0D - call to IClientMode::CreateMove from CInput::CreateMove
	// for obtaining the bSendPacket in the current stack before calling the hooked createmove and passing it in the available register
	inline sdk::patch<12> cmove_sendpacket_cinput_cm
	(
		0x8D, 0x55, 0xE4,              // lea  edx, [ebp - 0x1c]
		0xFF, 0xD0,                    // call eax
		0x33, 0xD2,                    // xor  edx, edx
		0xE9, 0x06, 0x00, 0x00, 0x00   // jmp  0x06
	);

	// sig: 8B 06 8B CE 6A 00 FF 50 08 - call setup from CInput::ExtraMouseSample()
	// sig: FF D0 84 C0 74 22 8B 0D ?? ?? ?? ?? 68 - actual call
	// skip the entire call setup, call, and return check
	inline sdk::patch<5> cmove_cinput_ems
	(
		0xE9, 0x8B, 0x00, 0x00, 0x00   // jmp 0x8b
	);
}