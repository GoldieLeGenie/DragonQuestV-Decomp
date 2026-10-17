; ARM9 secure area (0x02000000-0x02000800), left unfilled: the undefined-instruction filler 0xe7ffdeff,
; followed by the BIOS system call stubs (hand-written Thumb, 0x02000800-0x02000850).

	.text
	.thumb

	.global SoftReset
	.global WaitByLoop
	.global IntrWait
	.global VBlankIntrWait
	.global Halt
	.global Div
	.global Mod
	.global CpuSet
	.global CpuFastSet
	.global Sqrt
	.global GetCRC16
	.global IsDebugger
	.global BitUnPack
	.global LZ77UnCompReadNormalWrite8bit
	.global LZ77UnCompReadByCallbackWrite16bit
	.global HuffUnCompReadByCallback
	.global RLUnCompReadNormalWrite8bit
	.global RLUnCompReadByCallbackWrite16bit

	.rept 0x200
	.long 0xe7ffdeff
	.endr

	.type SoftReset, @function
SoftReset:
	swi 0x0
	bx lr
	.size SoftReset, 4

	.type WaitByLoop, @function
WaitByLoop:
	swi 0x3
	bx lr
	.size WaitByLoop, 4

	.type IntrWait, @function
IntrWait:
	mov r2, #0
	swi 0x4
	bx lr
	.size IntrWait, 6

	.type VBlankIntrWait, @function
VBlankIntrWait:
	mov r2, #0
	swi 0x5
	bx lr
	.size VBlankIntrWait, 6

	.type Halt, @function
Halt:
	swi 0x6
	bx lr
	.size Halt, 4

	.type Div, @function
Div:
	swi 0x9
	bx lr
	.size Div, 4

	.type Mod, @function
Mod:
	swi 0x9
	mov r0, r1
	bx lr
	.size Mod, 6

	.type CpuSet, @function
CpuSet:
	swi 0xb
	bx lr
	.size CpuSet, 4

	.type CpuFastSet, @function
CpuFastSet:
	swi 0xc
	bx lr
	.size CpuFastSet, 4

	.type Sqrt, @function
Sqrt:
	swi 0xd
	bx lr
	.size Sqrt, 4

	.type GetCRC16, @function
GetCRC16:
	swi 0xe
	bx lr
	.size GetCRC16, 4

	.type IsDebugger, @function
IsDebugger:
	swi 0xf
	bx lr
	.size IsDebugger, 4

	.type BitUnPack, @function
BitUnPack:
	swi 0x10
	bx lr
	.size BitUnPack, 4

	.type LZ77UnCompReadNormalWrite8bit, @function
LZ77UnCompReadNormalWrite8bit:
	swi 0x11
	bx lr
	.size LZ77UnCompReadNormalWrite8bit, 4

	.type LZ77UnCompReadByCallbackWrite16bit, @function
LZ77UnCompReadByCallbackWrite16bit:
	swi 0x12
	bx lr
	.size LZ77UnCompReadByCallbackWrite16bit, 4

	.type HuffUnCompReadByCallback, @function
HuffUnCompReadByCallback:
	swi 0x13
	bx lr
	.size HuffUnCompReadByCallback, 4

	.type RLUnCompReadNormalWrite8bit, @function
RLUnCompReadNormalWrite8bit:
	swi 0x14
	bx lr
	.size RLUnCompReadNormalWrite8bit, 4

	.type RLUnCompReadByCallbackWrite16bit, @function
RLUnCompReadByCallbackWrite16bit:
	swi 0x15
	bx lr
	.size RLUnCompReadByCallbackWrite16bit, 4

	.short 0
