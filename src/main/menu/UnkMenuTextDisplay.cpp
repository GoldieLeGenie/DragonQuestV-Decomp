#include "main/menu/UnkMenuTextDisplay.hpp"
#include "main/menu/UnkMenuIconDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/text/TextAPI.hpp"
#include "nitro/g2.hpp"

THUMB UnkMenuTextDisplay::UnkMenuTextDisplay()
{
}

THUMB void UnkMenuTextDisplay::setup(int id)
{
    id_ = id;
    unkfunc_0204e558(&char_, charData_, 32, 2);
    enable_ = 0;
    xlu_ = 1;
    timer_ = 0;
    unk_330[0] = 0;
    unk_394 = 0;
    unkfunc_0206477c(2);
}

THUMB void UnkMenuTextDisplay::update(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void UnkMenuTextDisplay::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void UnkMenuTextDisplay::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    int baseY;
    int i;
    int left;
    int top;
    int y;
    int chr;
    int x;
    int width;
    int right;
    int pos;
    int back;
    if (timer_ > 0) {
        timer_--;
        return;
    }
    if (!unkfunc_02064730(main, sub)) {
        return;
    }
    y = y_ % 192;
    chr = id_;
    x = 0;
    for (i = 0; i < 8; i++, x += 32, chr += 4) {
        if (x < visibleWidth_) {
            if (visibleWidth_ < width_ && x + 32 > visibleWidth_) {
                unkfunc_02066ef4(sub, x_ + visibleWidth_, y, x + 32 - visibleWidth_, 14);
            }
            G2_SetOBJAttr(sub->unkfunc_0204dbc4(), x_ + x, y, priority_, GX_OAM_MODE_NORMAL, 0, GX_OAM_EFFECT_NONE,
                          GX_OAM_SHAPE_32x16, GX_OAM_COLORMODE_16, chr, palette_, 0);
        }
    }
    if (frame_) {
        left = x_ - 2;
        baseY = y_;
        top = baseY - 2;
        width = frameWidth_ + 4;
        if (width < 40) {
            unkfunc_020672ac(sub, left, top, 0x109);
            unkfunc_020672ac(sub, left, baseY + 2, 0x189);
            right = left + width - 16;
            unkfunc_020672ac(sub, right, top, 0x10d);
            unkfunc_020672ac(sub, right, baseY + 2, 0x18d);
            unkfunc_020672e8(sub, left + 16, top, 0x10b);
            unkfunc_020672e8(sub, left + 16, baseY + 2, 0x18b);
        } else {
            unkfunc_02067270(sub, left, top, 0x109);
            unkfunc_02067270(sub, left, baseY + 2, 0x189);
            right = left + width - 32;
            unkfunc_02067270(sub, right, top, 0x10b);
            unkfunc_02067270(sub, right, baseY + 2, 0x18b);
        }
        width -= 64;
        left += 32;
        for (pos = 0; pos < width; pos += 32) {
        if (pos + 32 > width) {
            back = pos + 32 - width;
            if (back > 16) {
                back = 16;
            }
        } else {
            back = 0;
        }
        unkfunc_02067270(sub, left + pos - back, top, 0x10a);
        unkfunc_02067270(sub, left + pos - back, baseY + 2, 0x18a);
        }
        for (pos = 0; pos < frameWidth_; pos += 16) {
            back = 0;
            if (pos + 16 >= frameWidth_) {
                back = pos + 16 - frameWidth_;
            }
            GXOamAttr* oam = sub->unkfunc_0204dbc4();
            G2_SetOBJAttr(oam, x_ + pos - back, y_, priority_, GX_OAM_MODE_XLU, 0, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8,
                          GX_OAM_COLORMODE_16, 0x101, 15, 0);
            oam = sub->unkfunc_0204dbc4();
            G2_SetOBJAttr(oam, x_ + pos - back, y_ + 6, priority_, GX_OAM_MODE_XLU, 0, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8,
                          GX_OAM_COLORMODE_16, 0x101, 15, 0);
        }
        frame_ = 0;
    }
}

THUMB void UnkMenuTextDisplay::unkfunc_02066ef4(UnkOamBuffer* oam, int x, int y, int width, int height)
{
    int y2 = y + height - 8;
    int size;
    int chr;
    int shape;
    if (width > 16) {
        size = 16;
        chr = size + 0xf1;
        shape = size << 10;
    } else if (width > 8) {
        size = 8;
        chr = size + 0xf9;
        shape = 0;
    } else if (width > 4) {
        size = 4;
        chr = 0x10f;
        shape = 0;
    } else if (width > 2) {
        size = 2;
        chr = 0x12f;
        shape = 0;
    } else if (width >= 1) {
        chr = 0x14f;
        size = 1;
        shape = 0;
    } else {
        return;
    }
    int mode = xlu_ ? 1 : 0;
    GXOamAttr* obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x, y, 0, mode, 0, GX_OAM_EFFECT_NONE, shape, GX_OAM_COLORMODE_16, chr, 15, 0);
    obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x, y2, 0, mode, 0, GX_OAM_EFFECT_NONE, shape, GX_OAM_COLORMODE_16, chr, 15, 0);
    obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x + size - (size * 2 - width), y, 0, mode, 0, GX_OAM_EFFECT_NONE, shape, GX_OAM_COLORMODE_16, chr, 15, 0);
    obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x + size - (size * 2 - width), y2, 0, mode, 0, GX_OAM_EFFECT_NONE, shape, GX_OAM_COLORMODE_16, chr, 15, 0);
}

THUMB void UnkMenuTextDisplay::unkfunc_02066fe4(int font, const char* text, int x, int y, int clear, int center)
{
    unkfunc_02067324(text);
    unkfunc_0204e478(font);
    int offset = 0;
    if (center) {
        unkfunc_0204dfa8(NULL, 0, 0, 0, text);
        offset = (240 - unkfunc_0204e540()) / 2;
    }
    unkfunc_0204e574(&char_, 0);
    unkfunc_0204dfa8(&char_, x + offset, y, 1, text);
    count_ = unkfunc_0204e4dc(charWidths_, 0x100);
    unkfunc_0204e50c(unk_130, 0x200);
    width_ = unkfunc_0204e540();
    visibleCount_ = 0;
    visibleWidth_ = 0;
    unkfunc_02067180(0);
    unk_398 = offset;
    width_ += offset;
    unkfunc_0204dca8(0x13, id_ << 5, charData_, 0x800);
    palette_ = 15;
    frame_ = 0;
    frameWidth_ = 0;
    unk_bc8 = 0;
    priority_ = 0;
    timer_ = 1;
    if (clear) {
        for (int i = 0; i < width_ + 1; i++) {
            unkfunc_0204e5ec(&char_, i, 15, 1);
        }
    }
}

THUMB int UnkMenuTextDisplay::unkfunc_020670f4(int font, const char* text, int priority, int flag)
{
    unkfunc_02067324(text);
    unkfunc_0204e478(10);
    unkfunc_0204dfa8(NULL, 0, 0, 0, text);
    int width = unkfunc_0204e540();
    unkfunc_02066fe4(font, text, 4, 2, 0, 0);
    palette_ = flag ? 15 : 14;
    frame_ = 1;
    frameWidth_ = width + 9;
    unk_bc8 = 14;
    priority_ = priority;
    unkfunc_020671c8(width + 9);
    timer_ = 1;
    return width + 13;
}

THUMB void UnkMenuTextDisplay::unkfunc_02067180(int count)
{
    if (count == -1) {
        count = count_;
    }
    if (count > count_) {
        count = count_;
    }
    visibleCount_ = count;
    int width = 0;
    for (int i = 0; i < count; i++) {
        width += charWidths_[i];
    }
    visibleWidth_ = width + unk_398;
}

THUMB void UnkMenuTextDisplay::unkfunc_020671c8(int width)
{
    visibleWidth_ = width;
}

THUMB int UnkMenuTextDisplay::unkfunc_020671d0()
{
    return visibleCount_;
}

THUMB int UnkMenuTextDisplay::unkfunc_020671d8()
{
    return count_;
}

THUMB int UnkMenuTextDisplay::unkfunc_020671e0()
{
    return width_;
}

THUMB void UnkMenuTextDisplay::unkfunc_020671e8(int scroll)
{
    int i;
    char* dst;
    int row = 0;
    if (scroll > 0) {
        int size = scroll * 4;
        do {
            dst = (char*)unkfunc_0204e564(&char_, 0, row);
            if (scroll > 8) {
                MI_CpuFill(0, dst, 0x400);
            } else {
                for (i = 0; i < 32; i++) {
                    MI_CpuFill(0, dst, size);
                    dst += 0x20;
                }
            }
            size -= 0x20;
            scroll -= 8;
            row++;
        } while (scroll > 0);
    }
    unkfunc_0204dca8(0x13, id_ << 5, charData_, 0x800);
}

THUMB void UnkMenuTextDisplay::unkfunc_02067268(int flag)
{
    xlu_ = flag;
}

THUMB void UnkMenuTextDisplay::unkfunc_02067270(UnkOamBuffer* oam, int x, int y, int chr)
{
    GXOamAttr* obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x, y, priority_, GX_OAM_MODE_NORMAL, 0, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x16, GX_OAM_COLORMODE_16,
                  chr, palette_, 0);
}

THUMB void UnkMenuTextDisplay::unkfunc_020672ac(UnkOamBuffer* oam, int x, int y, int chr)
{
    GXOamAttr* obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x, y, priority_, GX_OAM_MODE_NORMAL, 0, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLORMODE_16,
                  chr, palette_, 0);
}

THUMB void UnkMenuTextDisplay::unkfunc_020672e8(UnkOamBuffer* oam, int x, int y, int chr)
{
    GXOamAttr* obj = oam->unkfunc_0204dbc4();
    G2_SetOBJAttr(obj, x, y, priority_, GX_OAM_MODE_NORMAL, 0, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x16, GX_OAM_COLORMODE_16,
                  chr, palette_, 0);
}

THUMB void UnkMenuTextDisplay::unkfunc_02067324(const char* text)
{
    dss::strcpy_s(unk_330, 0x62, text);
}
