#pragma once

// GX functions without a name in the libs headers (the named ones are in nitro/gx.h)
extern "C" {
    int func_0207534c(void);                    // reset the BG VRAM bank (GXState.bg)
    int func_02075360(void);                    // reset the OBJ VRAM bank (GXState.obj)
    void func_02076e98(void);                   // GX_BeginLoadTex
    void func_02076ef4(const void* src, unsigned int dest, unsigned int size);  // GX_LoadTex
    void func_02077034(void);                   // GX_EndLoadTex
    void func_02077080(void);                   // GX_BeginLoadTexPltt
    void func_020770b4(const void* src, unsigned int dest, unsigned int size);  // GX_LoadTexPltt
    void func_02077120(void);                   // GX_EndLoadTexPltt
}

inline void GX_SetOBJVRamModeBmp(int mode)
{
    *(volatile unsigned int*)0x04000000 = (*(volatile unsigned int*)0x04000000 & ~0x400060) | mode;
}

inline void GX_SetVisibleWnd(int window)
{
    *(volatile unsigned int*)0x04000000 = (*(volatile unsigned int*)0x04000000 & ~0xe000) | (window << 13);
}
