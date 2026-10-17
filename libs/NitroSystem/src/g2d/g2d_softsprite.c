// The SDK reserves both sprite state records.
#pragma define_section sdk_state ".data" ".bss.keep" ".rodata" RW
#include <nitro/types.h>
#include <nitro/reg.h>

#pragma thumb on

/* Software sprites drawn as textured quads through the 3D geometry engine. */


typedef struct UnkG2dImageAttr {
    int unk_00;                 // 0x00 texture width (size code)
    int unk_04;                 // 0x04 texture height (size code)
    int unk_08;                 // 0x08 texture format
    int unk_0c;                 // 0x0C
    int unk_10;                 // 0x10 palette color 0 transparent
    int unk_14;                 // 0x14
} UnkG2dImageAttr;

/* Same layout as the game's UnkG2dSprite (simple 0x0C / basic 0x1C / extended 0x3C parts). */
typedef struct UnkG2dSprite {
    s16 unk_00;                 // 0x00 x
    s16 unk_02;                 // 0x02 y
    s16 unk_04;                 // 0x04 width
    s16 unk_06;                 // 0x06 height
    u16 unk_08;                 // 0x08 rotation Z
    u8 unk_0a;                  // 0x0A priority (z)
    u8 unk_0b;                  // 0x0B alpha
    UnkG2dImageAttr* unk_0c;    // 0x0C image attributes
    u32 unk_10;                 // 0x10 texture address
    u32 unk_14;                 // 0x14 palette address
    u16 unk_18;                 // 0x18 palette number
    u16 unk_1a;                 // 0x1A color
    s32 unk_1c;                 // 0x1C upper-left u
    s32 unk_20;                 // 0x20 upper-left v
    s32 unk_24;                 // 0x24 lower-right u
    s32 unk_28;                 // 0x28 lower-right v
    BOOL unk_2c;                // 0x2C flip u
    BOOL unk_30;                // 0x30 flip v
    s16 unk_34;                 // 0x34 rotation origin x
    s16 unk_36;                 // 0x36 rotation origin y
    u16 unk_38;                 // 0x38 rotation X
    u16 unk_3a;                 // 0x3A rotation Y
} UnkG2dSprite;

typedef struct UnkG2dSpriteState {
    u16 unk_00;                 // 0x00 polygon id
    u32 unk_04;                 // 0x04 enabled attribute flags
} UnkG2dSpriteState;

__declspec(sdk_state) UnkG2dSpriteState data_02124b70;
__declspec(sdk_state) UnkG2dSprite      data_02124b78; // not referenced by the code in the ROM

#define TEXCOORD(s, t) ((u32)(u16)(s16)((s) >> 8) | ((u32)(u16)(s16)((t) >> 8) << 16))

/* Draws a unit quad with the given texture coordinates. */
void func_0207ec28(s32 u0, s32 u1, s32 v0, s32 v1) {
    REG_GFX_FIFO_POLYGONS_BEGIN = 1;
    REG_GFX_FIFO_VERTEX_TEXCOORD = TEXCOORD(u0, v1);
    REG_GFX_FIFO_VERTEX_16 = 0x10000000;
    REG_GFX_FIFO_VERTEX_16 = 0;
    REG_GFX_FIFO_VERTEX_TEXCOORD = TEXCOORD(u1, v1);
    REG_GFX_FIFO_VERTEX_16 = 0x10001000;
    REG_GFX_FIFO_VERTEX_16 = 0;
    REG_GFX_FIFO_VERTEX_TEXCOORD = TEXCOORD(u1, v0);
    REG_GFX_FIFO_VERTEX_16 = 0x1000;
    REG_GFX_FIFO_VERTEX_16 = 0;
    REG_GFX_FIFO_VERTEX_TEXCOORD = TEXCOORD(u0, v0);
    REG_GFX_FIFO_VERTEX_16 = 0;
    REG_GFX_FIFO_VERTEX_16 = 0;
    REG_GFX_FIFO_POLYGONS_END = 0;
}

/* Sets the enabled sprite attribute flags. */
void func_0207ec9c(u32 flags) {
    data_02124b70.unk_04 = flags;
}

/* Draws a textured rectangle at (x, y, z) of size (w, h) with texture coordinates (u0, v0)-(u1, v1). */
void func_0207eca8(int x, int y, int z, int w, int h, int u0, int v0, int u1, int v1) {
    REG_GFX_FIFO_MATRIX_TRANSLATE = x << 12;
    REG_GFX_FIFO_MATRIX_TRANSLATE = y << 12;
    REG_GFX_FIFO_MATRIX_TRANSLATE = z << 12;
    REG_GFX_FIFO_MATRIX_SCALE = w << 12;
    REG_GFX_FIFO_MATRIX_SCALE = h << 12;
    REG_GFX_FIFO_MATRIX_SCALE = 0x1000;
    func_0207ec28(u0 << 12, u1 << 12, v0 << 12, v1 << 12);
}
