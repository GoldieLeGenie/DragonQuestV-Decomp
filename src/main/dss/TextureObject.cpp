#include "main/dss/TextureObject.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "nitro/g3.hpp"

ARM TextureObject::TextureObject()
{
}

ARM TextureObject::~TextureObject()
{
}

ARM void TextureObject::loadToVram(int flag)
{
    if (flags_ & 1) {
        return;
    }
    flags_ |= 1;
    relocate();
    allocVram();
    if (flag != 0) {
        transferToVram(1);
    } else {
        transferToVram(0);
    }
}

ARM void TextureObject::relocate()
{
    texData_ = (int)((unsigned char*)this + texData_);
    plttData_ = (int)((unsigned char*)this + plttData_);
    texSize_ = unkfunc_02049f7c(texSize_, 0x400);
    plttSize_ = unkfunc_02049f7c(plttSize_, 0x20);
    if (type_ == 1 || type_ == 2) {
        unk_54 = (int)((unsigned char*)this + unk_54);
        subPlttData_ = (int)((unsigned char*)this + subPlttData_);
        unk_50 = unkfunc_02049f7c(unk_50, 0x400);
        subPlttSize_ = unkfunc_02049f7c(subPlttSize_, 0x20);
    }
}

ARM unsigned int unkfunc_02049f7c(unsigned int value, unsigned int align)
{
    return (value + (align - 1)) & ~(align - 1);
}

ARM void TextureObject::freeVram()
{
    if (!(flags_ & 1)) {
        return;
    }
    flags_ &= ~1;
    if (texVramKey_ != 0) {
        data_020f4f74.freeTexVram(texVramKey_);
    }
    if (plttVramKey_ != 0) {
        data_020f4f74.freePlttVram(plttVramKey_);
    }
    if (type_ == 1 || type_ == 2) {
        if (subPlttVramKey_ != 0) {
            data_020f4f74.freePlttVram(subPlttVramKey_);
        }
    }
}

ARM void TextureObject::allocVram()
{
    flags_ |= 1;
    texVramKey_ = data_020f4f74.allocTexVram(texSize_);
    plttVramKey_ = data_020f4f74.allocPlttVram(plttSize_);
    texAddr_ = data_020f4f74.getTexVramAddr(texVramKey_);
    plttAddr_ = data_020f4f74.getPlttVramAddr(plttVramKey_);
    if (type_ == 1 || type_ == 2) {
        subPlttVramKey_ = data_020f4f74.allocPlttVram(subPlttSize_);
        subPlttAddr_ = data_020f4f74.getPlttVramAddr(subPlttVramKey_);
    }
}

ARM void TextureObject::transferToVram(int flag)
{
    data_020f4f74.transferToVram(0, (void*)texData_, texAddr_, texSize_, flag);
    data_020f4f74.transferToVram(1, (void*)plttData_, plttAddr_, plttSize_, flag);
    if (type_ == 1 || type_ == 2) {
        data_020f4f74.transferToVram(1, (void*)subPlttData_, subPlttAddr_, subPlttSize_, flag);
    }
}

ARM void TextureObject::transferFrom(TextureObject* src, int flag)
{
    if (src->flags_ & 1) {
        data_020f4f74.transferToVram(0, (void*)texData_, texAddr_, texSize_, flag);
        data_020f4f74.transferToVram(1, (void*)plttData_, plttAddr_, plttSize_, flag);
    } else {
        data_020f4f74.transferToVram(0, (unsigned char*)src + src->texData_, texAddr_, texSize_, flag);
        data_020f4f74.transferToVram(1, (unsigned char*)src + src->plttData_, plttAddr_, plttSize_, flag);
    }
}

ARM int TextureObject::getTexAddr()
{
    return texAddr_;
}

ARM int TextureObject::getTexData()
{
    return texData_;
}

ARM int TextureObject::getPlttAddr()
{
    return plttAddr_;
}

ARM int TextureObject::getPlttData()
{
    return plttData_;
}

ARM int TextureObject::getPlttSize()
{
    return plttSize_;
}

ARM void TextureObject::applyTexImageParam()
{
    G3_TexImageParam(unk_20, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
}

ARM void TextureObject::applyTexImageParamOpaque()
{
    G3_TexImageParam(unk_20, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, texAddr_);
}

ARM void disableTexture()
{
    *(volatile unsigned int*)0x040004a8 = 0x60000000;
}

ARM void TextureObject::applyPlttBase()
{
    *(volatile unsigned int*)0x040004ac = (unsigned int)plttAddr_ >> (4 - (unk_20 == 2));
}

ARM void TextureObject::applySubTexImageParam()
{
    if (type_ == 1) {
        G3_TexImageParam(GX_TEXFMT_A3I5, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
    }
    if (type_ == 2) {
        G3_TexImageParam(GX_TEXFMT_A5I3, GX_TEXGEN_TEXCOORD, unk_24, unk_28, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
    }
}

ARM void TextureObject::applySubPlttBase()
{
    if (type_ == 1) {
        *(volatile unsigned int*)0x040004ac = (unsigned int)subPlttAddr_ >> 4;
    }
    if (type_ == 2) {
        *(volatile unsigned int*)0x040004ac = (unsigned int)subPlttAddr_ >> 4;
    }
}

ARM int TextureObject::getWidth()
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

ARM int TextureObject::getHeight()
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
