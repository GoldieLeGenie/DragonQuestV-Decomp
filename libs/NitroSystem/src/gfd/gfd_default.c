#include "../nns_internal.h"

#pragma thumb on

/* default texture VRAM allocator: always fails */
u32 func_020864e0(u32 szByte, BOOL is4x4comp, u32 opt)
{
    return 0;
}

/* default texture VRAM free: always fails */
int func_020864e4(u32 key)
{
    return -1;
}

/* default palette VRAM allocator: always fails */
u32 func_020864ec(u32 szByte, BOOL is4pltt, u32 opt)
{
    return 0;
}

/* default palette VRAM free: always fails */
int func_020864f0(u32 key)
{
    return -1;
}

/* Current VRAM allocator functions (replaced by the linked VRAM managers, gfd_lnktex.c / gfd_lnkpltt.c).
   The definition order gives the ROM data layout (texture alloc, texture free, palette alloc, palette free). */
u32 (*data_0209c790)(u32 szByte, BOOL is4pltt, u32 opt) = func_020864ec;
int (*data_0209c78c)(u32 key) = func_020864e4;
u32 (*data_0209c788)(u32 szByte, BOOL is4x4comp, u32 opt) = func_020864e0;
int (*data_0209c794)(u32 key) = func_020864f0;
