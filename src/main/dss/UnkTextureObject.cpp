#include "main/dss/UnkTextureObject.hpp"
#include "main/dss/UnkVramTransfer.hpp"
#include "nitro/g3.hpp"

ARM UnkTextureObject::UnkTextureObject()
{
}

ARM UnkTextureObject::~UnkTextureObject()
{
}

ARM void UnkTextureObject::unkfunc_02049e9c(int flag)
{
    if (unk_14 & 1) {
        return;
    }
    unk_14 |= 1;
    unkfunc_02049ef0();
    unkfunc_0204a004();
    if (flag != 0) {
        unkfunc_0204a090(1);
    } else {
        unkfunc_0204a090(0);
    }
}

ARM void UnkTextureObject::unkfunc_02049ef0()
{
    unk_34 = (int)((unsigned char*)this + unk_34);
    unk_3c = (int)((unsigned char*)this + unk_3c);
    unk_30 = unkfunc_02049f7c(unk_30, 0x400);
    unk_38 = unkfunc_02049f7c(unk_38, 0x20);
    if (unk_18 == 1 || unk_18 == 2) {
        unk_54 = (int)((unsigned char*)this + unk_54);
        unk_5c = (int)((unsigned char*)this + unk_5c);
        unk_50 = unkfunc_02049f7c(unk_50, 0x400);
        unk_58 = unkfunc_02049f7c(unk_58, 0x20);
    }
}

ARM unsigned int unkfunc_02049f7c(unsigned int value, unsigned int align)
{
    return (value + (align - 1)) & ~(align - 1);
}

ARM void UnkTextureObject::unkfunc_02049f90()
{
    if (!(unk_14 & 1)) {
        return;
    }
    unk_14 &= ~1;
    if (unk_40 != 0) {
        data_020f4f74.unkfunc_0204a618(unk_40);
    }
    if (unk_44 != 0) {
        data_020f4f74.unkfunc_0204a690(unk_44);
    }
    if (unk_18 == 1 || unk_18 == 2) {
        if (unk_64 != 0) {
            data_020f4f74.unkfunc_0204a690(unk_64);
        }
    }
}

ARM void UnkTextureObject::unkfunc_0204a004()
{
    unk_14 |= 1;
    unk_40 = data_020f4f74.unkfunc_0204a5f4(unk_30);
    unk_44 = data_020f4f74.unkfunc_0204a658(unk_38);
    unk_48 = data_020f4f74.unkfunc_0204a634(unk_40);
    unk_4c = data_020f4f74.unkfunc_0204a6cc(unk_44);
    if (unk_18 == 1 || unk_18 == 2) {
        unk_64 = data_020f4f74.unkfunc_0204a658(unk_58);
        unk_6c = data_020f4f74.unkfunc_0204a6cc(unk_64);
    }
}

ARM void UnkTextureObject::unkfunc_0204a090(int flag)
{
    data_020f4f74.unkfunc_0204a6f0(0, (void*)unk_34, unk_48, unk_30, flag);
    data_020f4f74.unkfunc_0204a6f0(1, (void*)unk_3c, unk_4c, unk_38, flag);
    if (unk_18 == 1 || unk_18 == 2) {
        data_020f4f74.unkfunc_0204a6f0(1, (void*)unk_5c, unk_6c, unk_58, flag);
    }
}

ARM void UnkTextureObject::unkfunc_0204a114(UnkTextureObject* src, int flag)
{
    if (src->unk_14 & 1) {
        data_020f4f74.unkfunc_0204a6f0(0, (void*)unk_34, unk_48, unk_30, flag);
        data_020f4f74.unkfunc_0204a6f0(1, (void*)unk_3c, unk_4c, unk_38, flag);
    } else {
        data_020f4f74.unkfunc_0204a6f0(0, (unsigned char*)src + src->unk_34, unk_48, unk_30, flag);
        data_020f4f74.unkfunc_0204a6f0(1, (unsigned char*)src + src->unk_3c, unk_4c, unk_38, flag);
    }
}

ARM int UnkTextureObject::unkfunc_0204a1bc()
{
    return unk_48;
}

ARM int UnkTextureObject::unkfunc_0204a1c4()
{
    return unk_34;
}

ARM int UnkTextureObject::unkfunc_0204a1cc()
{
    return unk_4c;
}

ARM int UnkTextureObject::unkfunc_0204a1d4()
{
    return unk_3c;
}

ARM int UnkTextureObject::unkfunc_0204a1dc()
{
    return unk_38;
}

ARM void UnkTextureObject::unkfunc_0204a1e4()
{
    G3_TexImageParam(unk_20, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, unk_48);
}

ARM void UnkTextureObject::unkfunc_0204a21c()
{
    G3_TexImageParam(unk_20, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, unk_48);
}

ARM void unkfunc_0204a250()
{
    *(volatile unsigned int*)0x040004a8 = 0x60000000;
}

ARM void UnkTextureObject::unkfunc_0204a264()
{
    *(volatile unsigned int*)0x040004ac = (unsigned int)unk_4c >> (4 - (unk_20 == 2));
}

ARM void UnkTextureObject::unkfunc_0204a290()
{
    if (unk_18 == 1) {
        G3_TexImageParam(GX_TEXFMT_A3I5, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, unk_48);
    }
    if (unk_18 == 2) {
        G3_TexImageParam(GX_TEXFMT_A5I3, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, unk_48);
    }
}

ARM void UnkTextureObject::unkfunc_0204a300()
{
    if (unk_18 == 1) {
        *(volatile unsigned int*)0x040004ac = (unsigned int)unk_6c >> 4;
    }
    if (unk_18 == 2) {
        *(volatile unsigned int*)0x040004ac = (unsigned int)unk_6c >> 4;
    }
}

ARM int UnkTextureObject::unkfunc_0204a340()
{
    int width = 0;
    if (unk_24 == 0) {
        width = 8;
    }
    if (unk_24 == 1) {
        width = 0x10;
    }
    if (unk_24 == 2) {
        width = 0x20;
    }
    if (unk_24 == 3) {
        width = 0x40;
    }
    if (unk_24 == 4) {
        width = 0x80;
    }
    if (unk_24 == 5) {
        width = 0x100;
    }
    if (unk_24 == 6) {
        width = 0x200;
    }
    if (unk_24 == 7) {
        width = 0x400;
    }
    return width;
}

ARM int UnkTextureObject::unkfunc_0204a38c()
{
    int height = 0;
    if (unk_28 == 0) {
        height = 8;
    }
    if (unk_28 == 1) {
        height = 0x10;
    }
    if (unk_28 == 2) {
        height = 0x20;
    }
    if (unk_28 == 3) {
        height = 0x40;
    }
    if (unk_28 == 4) {
        height = 0x80;
    }
    if (unk_28 == 5) {
        height = 0x100;
    }
    if (unk_28 == 6) {
        height = 0x200;
    }
    if (unk_28 == 7) {
        height = 0x400;
    }
    return height;
}
