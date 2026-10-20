#include "main/dss/Pad.hpp"
#include "main/menu/MenuManager.hpp"
#include "nitro/os.hpp"
#include "nitro/pad.h"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssUtils.hpp"

inline dss::Pad::Pad()
{
    unkfunc_0204b640();
}

dss::Pad dss::g_Pad;
unsigned short data_020f9918[7201];

ARM void dss::Pad::unkfunc_0204b640()
{
    maskL_ = 0;
    mode_ = 0;
    playIndex_ = 0;
    recordCount_ = 0;
    unkfunc_0204bc24(0);
}

ARM void dss::Pad::unkfunc_0204b660()
{
    unsigned short keys = PAD_Read();
    if ((keys & (PAD_KEY_UP | PAD_KEY_DOWN)) == (PAD_KEY_UP | PAD_KEY_DOWN)) {
        keys ^= PAD_KEY_DOWN;
    }
    if ((keys & (PAD_KEY_RIGHT | PAD_KEY_LEFT)) == (PAD_KEY_RIGHT | PAD_KEY_LEFT)) {
        keys ^= PAD_KEY_LEFT;
    }
    if (unkfunc_0204b61c()) {
        keys = 0;
    }
    switch (mode_) {
    case 0:
        break;
    case 1:
        if (wait_ != 0) {
            data_020f6f9c.unkfunc_0204b04c(0x18, 0x17, "REC WAIT");
            keys = 0;
            wait_--;
        } else {
            data_020f6f9c.unkfunc_0204b04c(0x18, 0x17, "REC %4d", 7200 - recordCount_);
            if (PAD_DetectFold()) {
                unkfunc_0204bc48();
            }
            if (keys & PAD_BUTTON_START) {
                unkfunc_0204bc48();
            }
            if (mode_ == 1) {
                unkfunc_0204be10(keys);
                if (recordCount_ == 7200) {
                    if (unk_0c != 0) {
                        unkfunc_0204bc44();
                        return;
                    }
                    unkfunc_0204bc48();
                }
            }
        }
        break;
    case 2:
        if (wait_ != 0) {
            data_020f6f9c.unkfunc_0204b04c(0x17, 0x17, "PLAY WAIT");
            keys = 0;
            wait_--;
        } else {
            data_020f6f9c.unkfunc_0204b04c(0x17, 0x17, "PLAY %4d", playCount_ + 1);
            data_020f6f9c.unkfunc_0204b04c(0x17, 0x16, "%4d/%4d", playIndex_, recordCount_);
            if (PAD_DetectFold()) {
                unkfunc_0204be48();
            }
            if (keys & PAD_BUTTON_START) {
                unkfunc_0204be48();
            }
            if (mode_ == 2) {
                unsigned short playMask = playMask_;
                unsigned short played = unkfunc_0204bdb8() & (unsigned short)(playMask ^ 0xffff);
                keys = (unsigned short)(keys & playMask) | played;
            }
        }
        break;
    }
    trig_ = keys & (keys ^ cont_);
    release_ = cont_ & (keys ^ cont_);
    cont_ = keys;
    for (unsigned int i = 0; i < 12; i++) {
        if (pad() & (1 << i)) {
            repeat_ &= ~(1 << i);
            if (repeatTimer_[i] == 0) {
                repeatTimer_[i] = 0x200000;
                repeat_ |= 1 << i;
            } else {
                if (repeatTimer_[i] & 0x80000000) {
                    repeat_ |= 1 << i;
                }
                repeatTimer_[i] <<= 1;
                if (repeatTimer_[i] == 0) {
                    repeatTimer_[i] = 0x2000000;
                }
            }
        } else {
            repeat_ &= ~(1 << i);
            repeatTimer_[i] = 0;
        }
    }
    if ((pad() & PAD_KEY_UP) && (pad() & PAD_KEY_RIGHT)) {
        dir_ = 1;
        return;
    }
    if ((pad() & PAD_KEY_RIGHT) && (pad() & PAD_KEY_DOWN)) {
        dir_ = 3;
        return;
    }
    if ((pad() & PAD_KEY_DOWN) && (pad() & PAD_KEY_LEFT)) {
        dir_ = 5;
        return;
    }
    if ((pad() & PAD_KEY_LEFT) && (pad() & PAD_KEY_UP)) {
        dir_ = 7;
        return;
    }
    if ((pad() & PAD_KEY_UP) && (pad() & PAD_KEY_UP)) {
        dir_ = 0;
        return;
    }
    if ((pad() & PAD_KEY_RIGHT) && (pad() & PAD_KEY_RIGHT)) {
        dir_ = 2;
        return;
    }
    if ((pad() & PAD_KEY_DOWN) && (pad() & PAD_KEY_DOWN)) {
        dir_ = 4;
        return;
    }
    if ((pad() & PAD_KEY_LEFT) && (pad() & PAD_KEY_LEFT)) {
        dir_ = 6;
    }
}

ARM void dss::Pad::unkfunc_0204baec()
{
    unkfunc_0204b660();
    if (maskL_ == 0) {
        return;
    }
    mask_ = 0xfdff;
    if (!(PAD_Read() & PAD_BUTTON_L)) {
        return;
    }
    do {
        mask_ = 0xfcff;
        unsigned short keys = PAD_Read();
        OS_Wait();
        if (keys & PAD_BUTTON_R) {
            break;
        }
        if (!(keys & PAD_BUTTON_L)) {
            break;
        }
    } while (!unkfunc_0204bc10());
    unsigned short keys;
    do {
        keys = PAD_Read();
        OS_Wait();
    } while (keys & PAD_BUTTON_R);
}

ARM int dss::Pad::pad()
{
    return cont_ & mask_;
}

ARM int dss::Pad::padDir()
{
    return dir_;
}

ARM int dss::Pad::edge()
{
    return trig_ & mask_;
}

ARM int dss::Pad::repeat()
{
    return repeat_ & mask_;
}

ARM int dss::Pad::unkfunc_0204bc10()
{
    return cont_ == (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_SELECT | PAD_BUTTON_START);
}

ARM void dss::Pad::unkfunc_0204bc24(int flag)
{
    maskL_ = flag;
    if (flag) {
        mask_ = 0xfcff;
    } else {
        mask_ = 0xffff;
    }
}

ARM void dss::Pad::unkfunc_0204bc44()
{
}

ARM void dss::Pad::unkfunc_0204bc48()
{
    data_020f6f9c.unkfunc_0204b04c(0x18, 0x17, "        ");
    mode_ = 0;
}

ARM int dss::Pad::unkfunc_0204bc78()
{
    int size = 0;
    if (unk_10 == 0) {
        unkfunc_0204be48();
        return size;
    }
    dss::memset(data_020f9918, 0xff, sizeof(data_020f9918));
    int offset = unk_14 * 0x3840;
    if (unk_98 == 0) {
        size = dss::g_File.unkfunc_0204b250(fileName_, data_020f9918, offset, 0x3840, 0);
    }
    unk_14++;
    if (data_020f9918[0] == 0xffff) {
        unkfunc_0204be48();
        return 0;
    }
    recordCount_ = size / 2;
    unkfunc_0204bd74();
    return size;
}

ARM void dss::Pad::unkfunc_0204bd50(unsigned short playMask)
{
    playMask_ = playMask;
    mode_ = 2;
    playIndex_ = 0;
    playCount_ = 0;
    wait_ = 60;
}

ARM void dss::Pad::unkfunc_0204bd74()
{
    playMask_ = 0;
    mode_ = 2;
    playIndex_ = 0;
    playCount_ = 0;
    wait_ = 60;
}

ARM void dss::Pad::unkfunc_0204bd98()
{
    mode_ = 2;
    playIndex_ = 0;
    playCount_++;
}

ARM unsigned short dss::Pad::unkfunc_0204bdb8()
{
    unsigned short keys = data_020f9918[playIndex_++];
    if (keys == 0xffff) {
        if (unk_10 != 0) {
            unkfunc_0204bc78();
            return 0;
        }
        unkfunc_0204bd98();
        keys = 0;
    }
    return keys;
}

ARM void dss::Pad::unkfunc_0204be10(unsigned short keys)
{
    data_020f9918[recordCount_++] = keys;
    data_020f9918[recordCount_] = 0xffff;
}

ARM void dss::Pad::unkfunc_0204be48()
{
    data_020f6f9c.unkfunc_0204b04c(0x17, 0x17, "         ");
    data_020f6f9c.unkfunc_0204b04c(0x17, 0x16, "         ");
    mode_ = 0;
}

ARM void dss::Pad::unkfunc_0204be8c()
{
    recordCount_ = 0;
}

ARM void dss::Pad::addRecordKeys(unsigned short keys, int count)
{
    for (int i = 0; i < count; i++) {
        data_020f9918[recordCount_++] = keys;
    }
    data_020f9918[recordCount_] = 0xffff;
}

ARM void dss::Pad::addRecordPresses(unsigned short keys, int count)
{
    for (int i = 0; i < count; i++) {
        addRecordKeys(keys, 10);
        addRecordKeys(0, 10);
    }
}
