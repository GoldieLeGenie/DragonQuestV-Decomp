#pragma once
#include <globaldefs.h>

// debug text 
struct UnkDebugConsole {
    UnkDebugConsole();
    void init();                    // init
    void reset();                    // clear
    void clear();                    // clear
    void clearRect(int x, int y, int w, int h);  // clear a rect
    void print(int x, int y, const char* str);
    void printf(int x, int y, const char* format, ...);
};

extern UnkDebugConsole data_020f6f9c;
extern int data_020f6fa0;                       // main extended arena enabled
extern unsigned char data_020f6fe0[0x2800] __attribute__((aligned(32)));  // read buffer of the LZ-compressed files

void unkfunc_0204afd8();
void unkfunc_0204afdc();
int getTick();                         // tick count
void debugPrintfStub(const char* format, ...); // debug print
void dssVBlankIntr();                        // V-blank interrupt
void initSystem(int exArena);             // OS/system init
void clearVram();                        // clear the VRAM, OAM and palettes
unsigned int roundDown(unsigned int value, unsigned int align);  // round down
void resetBgObjVram();                        // reset the BG/OBJ VRAM
void setMainBrightness(int brightness);          // main screen master brightness
void setSubBrightness(int brightness);          // sub screen master brightness

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
