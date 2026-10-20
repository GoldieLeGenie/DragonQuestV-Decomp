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
        subTexData_ = (int)((unsigned char*)this + subTexData_);
        subPlttData_ = (int)((unsigned char*)this + subPlttData_);
        subTexSize_ = unkfunc_02049f7c(subTexSize_, 0x400);
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
    G3_TexImageParam(texFormat_, GX_TEXGEN_TEXCOORD, sizeS_, sizeT_, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
}

ARM void TextureObject::applyTexImageParamOpaque()
{
    G3_TexImageParam(texFormat_, GX_TEXGEN_TEXCOORD, sizeS_, sizeT_, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, texAddr_);
}

ARM void disableTexture()
{
    *(volatile unsigned int*)0x040004a8 = 0x60000000;
}

ARM void TextureObject::applyPlttBase()
{
    *(volatile unsigned int*)0x040004ac = (unsigned int)plttAddr_ >> (4 - (texFormat_ == 2));
}

ARM void TextureObject::applySubTexImageParam()
{
    if (type_ == 1) {
        G3_TexImageParam(GX_TEXFMT_A3I5, GX_TEXGEN_TEXCOORD, sizeS_, sizeT_, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
    }
    if (type_ == 2) {
        G3_TexImageParam(GX_TEXFMT_A5I3, GX_TEXGEN_TEXCOORD, sizeS_, sizeT_, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, texAddr_);
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
    if (sizeS_ == 0) {
        width = 8;
    }
    if (sizeS_ == 1) {
        width = 0x10;
    }
    if (sizeS_ == 2) {
        width = 0x20;
    }
    if (sizeS_ == 3) {
        width = 0x40;
    }
    if (sizeS_ == 4) {
        width = 0x80;
    }
    if (sizeS_ == 5) {
        width = 0x100;
    }
    if (sizeS_ == 6) {
        width = 0x200;
    }
    if (sizeS_ == 7) {
        width = 0x400;
    }
    return width;
}

ARM int TextureObject::getHeight()
{
    int height = 0;
    if (sizeT_ == 0) {
        height = 8;
    }
    if (sizeT_ == 1) {
        height = 0x10;
    }
    if (sizeT_ == 2) {
        height = 0x20;
    }
    if (sizeT_ == 3) {
        height = 0x40;
    }
    if (sizeT_ == 4) {
        height = 0x80;
    }
    if (sizeT_ == 5) {
        height = 0x100;
    }
    if (sizeT_ == 6) {
        height = 0x200;
    }
    if (sizeT_ == 7) {
        height = 0x400;
    }
    return height;
}
