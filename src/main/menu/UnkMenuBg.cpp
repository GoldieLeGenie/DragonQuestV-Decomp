#include "main/menu/UnkMenuBg.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkMenuIconData.hpp"
#include "main/menu/MenuIconDisplay.hpp"
#include "main/menu/UnkMenuSystem.hpp"
#include "main/menu/UiMsg.hpp"
#include "nitro/gx.h"
#include "main/dss/UnkVramRequest.hpp"

THUMB void unkfunc_02063414()
{
    data_02106178.back_.unkfunc_02063574();
    data_02106178.window_.unkfunc_020636e0();
    data_02106178.icon_.unkfunc_0206375c(unkfunc_0204d03c());
}

THUMB void unkfunc_0206343c()
{
}

THUMB void unkfunc_02063440()
{
    data_02106178.back_.unkfunc_020635d4();
}

UnkMenuBg data_02106178;

THUMB void unkfunc_02063450()
{
    UnkMenuBg* bg = &data_02106178;
    if (!unkfunc_0204cca8() || bg->transferCount_ == 0) {
        return;
    }
    int frame = getDisplayFrame() & 1;
    int line = frame * 192;
    int index = unkfunc_0204ced8(line);
    if (index != -1) {
        int y = frame * 24;
        void* chr = unkfunc_0204e564(bg->window_.unkfunc_02063708(), 0, y);
        unkfunc_0204dca8(unkfunc_0204de14(index), 0x1000, chr, 0x6000);
        UnkScreenBuffer* window = bg->window_.unkfunc_0206370c();
        UnkScreenBuffer* screen = getDebugScreenBuffer();
        unsigned short* src = unkfunc_0204e858(window, 0, y);
        unsigned short* dst = unkfunc_0204e858(screen, 0, y);
        for (int i = 0; i < 0x300; i++) {
            if (*dst < 0xf020 || *dst == 0xf07f || *dst >= 0xf080) {
                *dst = *src;
            }
            dst++;
            src++;
        }
    }
    index = unkfunc_0204cf7c(line);
    if (index != -1) {
        unsigned short* back = unkfunc_0204e858(bg->back_.getScreenBuffer(), 0, frame * 24);
        unkfunc_0204dca8(unkfunc_0204de5c(index), 0, back, 0x600);
    }
    bg->icon_.unkfunc_02063ba4(frame);
    bg->transferCount_--;
}

THUMB void unkfunc_02063568()
{
    data_02106178.transferCount_ = 2;
}

THUMB void MenuBackBg::unkfunc_02063574()
{
    unkfunc_0204e83c(&screen_, screenData_, 32, 48);
    startFade(0, 0, 0, 0);
    enable_ = 0;
    unk_c34 = 0;
}

THUMB UnkScreenBuffer* MenuBackBg::getScreenBuffer()
{
    return &screen_;
}

THUMB void MenuBackBg::startFade(int r, int g, int b, int frame)
{
    enable_ = 1;
    targetR_ = r;
    targetG_ = g;
    targetB_ = b;
    frame_ = frame;
}

THUMB void MenuBackBg::unkfunc_020635d4()
{
    if (!enable_) {
        return;
    }
    if (frame_ == 0) {
        r_ = targetR_;
        g_ = targetG_;
        b_ = targetB_;
    } else {
        r_ += (targetR_ - r_) / frame_;
        g_ += (targetG_ - g_) / frame_;
        b_ += (targetB_ - b_) / frame_;
        frame_--;
    }
    getBgPaletteBuffer(1)->unkfunc_0204dbe8(13, 15, GX_RGB(r_, g_, b_));
    unkfunc_0204e90c(&screen_, 0, 24, 16, 20, 13, 7);
    unkfunc_0204e90c(&screen_, unk_c34 * 8, 44, 32 - unk_c34 * 8, 4, 13, 7);
}

THUMB void UnkMenuWindowBg::unkfunc_020636e0()
{
    unkfunc_0204e558(&char_, charData_, 32, 48);
    unkfunc_0204e83c(&screen_, screenData_, 32, 48);
}

THUMB UnkCharBuffer* UnkMenuWindowBg::unkfunc_02063708()
{
    return &char_;
}

THUMB UnkScreenBuffer* UnkMenuWindowBg::unkfunc_0206370c()
{
    return &screen_;
}

THUMB void UnkMenuIconSlot::unkfunc_02063710(int offset)
{
    offset_ = offset;
    key_ = -1;
    state_ = 0;
    unk_0c = 0;
}

THUMB void UnkMenuIconSlot::unkfunc_02063720(unsigned int key)
{
    key_ = key;
}

THUMB unsigned int UnkMenuIconSlot::unkfunc_02063724()
{
    return key_;
}

THUMB void UnkMenuIconSlot::unkfunc_02063728(int state)
{
    state_ = state;
}

THUMB int UnkMenuIconSlot::unkfunc_0206372c()
{
    return state_;
}

THUMB int UnkMenuIconSlot::unkfunc_02063730()
{
    return offset_;
}

THUMB int MenuIconRequest::set(int x, int y, int w, int h, int type, int index)
{
    enable_ = 1;
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    type_ = type;
    index_ = index;
    return 1;
}

THUMB UnkMenuIconBg::UnkMenuIconBg()
{
    enable_ = 0;
}

THUMB void UnkMenuIconBg::unkfunc_0206375c(int enable)
{
    enable_ = enable;
    if (enable) {
        unkfunc_0204e83c(&screen_, screenData_, 32, 48);
        unkfunc_0204e868(&screen_, 0);
        for (int i = 0; i < 28; i++) {
            slots_[i].unkfunc_02063710(i * 32 + 2);
        }
        unkfunc_020637ac();
        requestCount_ = 0;
    }
}

THUMB void UnkMenuIconBg::unkfunc_020637ac()
{
    UnkPaletteBuffer* palette = getBgPaletteBuffer(0);
    void* item = getMenuIconData(0xf0000000, 9999);
    void* chara = getMenuIconData(0xf1000000, 9999);
    palette->unkfunc_0204dbf4(0, 0, item, 0xa0);
    palette->unkfunc_0204dbf4(10, 0, chara, 0x40);
}

THUMB void UnkMenuIconBg::unkfunc_020637f8()
{
    unkfunc_0204e868(&screen_, 0);
}

THUMB int UnkMenuIconBg::unkfunc_02063804(unsigned int key, void* src, int size)
{
    int found = unkfunc_020638ac(key);
    if (found != -1) {
        return found;
    }
    int cached = unkfunc_02063988(key);
    if (cached != -1) {
        slots_[cached].unkfunc_02063728(1);
        return cached;
    }
    int slot = unkfunc_020638e8(key);
    if (slot == -1) {
        slot = unkfunc_02063960();
        if (slot == -1) {
            slot = unkfunc_020639bc();
            if (slot == -1) {
                return -1;
            }
        }
    }
    slots_[slot].unkfunc_02063720(key);
    slots_[slot].unkfunc_02063728(1);
    unkfunc_0204dc6c(7, slots_[slot].unkfunc_02063730() << 5, src, size << 6);
    return slot;
}

THUMB int UnkMenuIconBg::unkfunc_020638ac(unsigned int key)
{
    for (int i = 0; i < 28; i++) {
        if (key == slots_[i].unkfunc_02063724()) {
            slots_[i].unkfunc_02063728(1);
            return i;
        }
    }
    return -1;
}

THUMB int UnkMenuIconBg::unkfunc_020638e8(unsigned int key)
{
    unsigned int base = (key & 0xff000000) | ((key & 0xffffff) % 1000);
    for (int i = 0; i < 28; i++) {
        unsigned int type = slots_[i].unkfunc_02063724() & 0xff000000;
        unsigned int index = (slots_[i].unkfunc_02063724() & 0xffffff) % 1000;
        if (base == (type | index)) {
            slots_[i].unkfunc_02063728(1);
            return i;
        }
    }
    return -1;
}

THUMB int UnkMenuIconBg::unkfunc_02063960()
{
    for (int i = 0; i < 28; i++) {
        if (slots_[i].unkfunc_0206372c() == 0) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkMenuIconBg::unkfunc_02063988(unsigned int key)
{
    for (int i = 0; i < 28; i++) {
        if (slots_[i].unkfunc_0206372c() == 2 && key == slots_[i].unkfunc_02063724()) {
            return i;
        }
    }
    return -1;
}

THUMB int UnkMenuIconBg::unkfunc_020639bc()
{
    int max = 0;
    int result = -1;
    for (int i = 0; i < 28; i++) {
        if (slots_[i].unkfunc_0206372c() == 2 && max <= slots_[i].unk_0c) {
            result = i;
            max = slots_[i].unk_0c;
        }
    }
    return result;
}

THUMB void UnkMenuIconBg::unkfunc_020639f8(int x, int y, int w, int h, int type, int index)
{
    if (index == -1 || !enable_ || y - 24 < 0) {
        return;
    }
    w /= 8;
    h /= 8;
    void* src = getMenuIconData(type, index);
    if (src == NULL) {
        return;
    }
    int slot = unkfunc_02063804(type | index, src, w * h);
    if (slot == -1) {
        return;
    }
    int chr = slots_[slot].unkfunc_02063730() / 2;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            unkfunc_0204e958(&screen_, x + i, y - 24 + j, chr++);
        }
    }
}

THUMB void UnkMenuIconBg::unkfunc_02063aac(int x, int y, int w, int h, int type, int index)
{
    requests_[requestCount_].set(x, y, w, h, type, index);
    requestCount_++;
}

THUMB void UnkMenuIconBg::unkfunc_02063ae4()
{
    unkfunc_02063b50(0xf4000000);
    unkfunc_02063b50(0xf3000000);
    unkfunc_02063b50(0xf2000000);
    MenuIconRequest* request = requests_;
    for (int i = 0; i < requestCount_; i++, request++) {
        if (request->enable_) {
            unkfunc_020639f8(request->x_, request->y_, request->w_, request->h_, request->type_, request->index_);
            request->enable_ = 0;
        }
    }
}

THUMB void UnkMenuIconBg::unkfunc_02063b50(int type)
{
    MenuIconRequest* request = requests_;
    for (int i = 0; i < requestCount_; i++, request++) {
        if (type == request->type_ && request->enable_) {
            unkfunc_020639f8(request->x_, request->y_, request->w_, request->h_, request->type_, request->index_);
            request->enable_ = 0;
        }
    }
}

THUMB void UnkMenuIconBg::unkfunc_02063ba4(int frame)
{
    if (enable_) {
        unkfunc_02063ae4();
        if (frame == 1) {
            unkfunc_0204dca8(unkfunc_0204de5c(3), 0, screenData_, 0x600);
        }
        for (int i = 0; i < 28; i++) {
            if (slots_[i].unkfunc_0206372c() == 1) {
                slots_[i].unkfunc_02063728(2);
            }
        }
        requestCount_ = 0;
    }
}
                                                           