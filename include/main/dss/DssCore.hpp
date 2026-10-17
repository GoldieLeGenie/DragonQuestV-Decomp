#pragma once
#include <globaldefs.h>

// debug text 
struct UnkDebugConsole {
    UnkDebugConsole();
    void unkfunc_0204aff0();                    // init
    void unkfunc_0204aff4();                    // clear
    void unkfunc_0204affc();                    // clear
    void unkfunc_0204b00c(int x, int y, int w, int h);  // clear a rect
    void unkfunc_0204b034(int x, int y, const char* str);
    void unkfunc_0204b04c(int x, int y, const char* format, ...);
};

extern UnkDebugConsole data_020f6f9c;
extern int data_020f6fa0;                       // main extended arena enabled
extern unsigned char data_020f6fe0[0x2800] __attribute__((aligned(32)));  // read buffer of the LZ-compressed files

void unkfunc_0204afd8();
void unkfunc_0204afdc();
int unkfunc_0204afe0();                         // tick count
void unkfunc_0204afe8(const char* format, ...); // debug print
void unkfunc_0204b080();                        // V-blank interrupt
void unkfunc_0204b09c(int exArena);             // OS/system init
void unkfunc_0204b15c();                        // clear the VRAM, OAM and palettes
unsigned int unkfunc_0204b360(unsigned int value, unsigned int align);  // round down
void unkfunc_0204b50c();                        // reset the BG/OBJ VRAM
void unkfunc_0204b53c(int brightness);          // main screen master brightness
void unkfunc_0204b554(int brightness);          // sub screen master brightness

extern "C" {
    unsigned long long func_020885e0(void);     // OS_GetTick
    void func_020786d4(void);
    void func_0208a8b0(void);
    void func_020743b4(int);
    void func_02088548(void);
    void func_02086f88(int type, void (*function)());   // OS_SetIrqFunction
    void func_020870c4(int mask);               // OS_EnableIrqMask
    void func_02073850(int dma);                // FS_Init
    void func_0207b328(void);
    void func_02075550(void);                   // GX_DisableBankForLcdc
    void func_02075b38(void);
    void func_02075cd8(void);
    void func_02075c44(void);
    void func_02075d70(void);
    void func_020827ac(void);
    void func_0207438c(void* reg, int brightness);  // master brightness
}

// LZ77 streaming decompression
struct MIUncompContextLZ {
    char unk_00[0x14];
};

extern "C" {
    void func_020708d4(MIUncompContextLZ* context, void* dest, const void* header);  // MI_InitUncompContextLZ
    int func_020708fc(MIUncompContextLZ* context, const void* data, unsigned int len);  // MI_ReadUncompLZ8
}
