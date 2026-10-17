#pragma ipa file
#include "main/menu/UnkMenuIconDisplay.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "nitro/g2.hpp"

static const int s_hopping[39] = {
    0, 0, -2, -2, -3, -3, -3, -3, -2, -2, -1, -1, 0, 0, -1, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -99,
};

THUMB void UnkHoppingDigit::unkfunc_020658c8()
{
    frame_ = -99;
}

THUMB void UnkHoppingDigit::unkfunc_020658d0(int x, int y, int number, int delay)
{
    frame_ = 0;
    number_ = number;
    x_ = x;
    y_ = y;
    drawY_ = 0;
    frame_ = (signed char)-delay;
}

THUMB void UnkHoppingDigit::unkfunc_020658ec(UnkOamBuffer* oam)
{
    if (frame_ == -99) {
        return;
    }
    frame_++;
    if (frame_ < 0) {
        return;
    }
    drawY_ = y_ + s_hopping[frame_];
    if (s_hopping[frame_] == -99) {
        frame_ = -99;
    }
}

THUMB void UnkHoppingDigit::unkfunc_02065920(UnkOamBuffer* oam)
{
    int name;
    if (frame_ < 0) {
        return;
    }
    switch (number_) {
        case 0:
            name = 0x110;
            break;
        case 1:
            name = 0x111;
            break;
        case 2:
            name = 0x112;
            break;
        case 3:
            name = 0x113;
            break;
        case 4:
            name = 0x130;
            break;
        case 5:
            name = 0x131;
            break;
        case 6:
            name = 0x132;
            break;
        case 7:
            name = 0x133;
            break;
        case 8:
            name = 0x150;
            break;
        case 9:
            name = 0x151;
            break;
        default:
            return;
    }
    G2_SetOBJAttr(oam->unkfunc_0204dbc4(), x_, drawY_, 0, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLORMODE_16, name, 15, 0);
}

THUMB int UnkHoppingDigit::unkfunc_020659bc()
{
    if (frame_ == -99) {
        return 1;
    }
    return 0;
}

THUMB UnkHoppingNumber::UnkHoppingNumber()
{
}

THUMB void UnkHoppingNumber::setup(int id)
{
    id_ = id;
    unkfunc_0206477c(2);
    for (int i = 0; i < 40; i++) {
        digit_[i].unkfunc_020658c8();
    }
}

THUMB void UnkHoppingNumber::update(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    for (int i = 0; i < 40; i++) {
        digit_[i].unkfunc_020658ec(sub);
    }
}

THUMB void UnkHoppingNumber::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void UnkHoppingNumber::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    unkfunc_02064780(1);
    if (unkfunc_02064730(main, sub)) {
        for (int i = 0; i < 40; i++) {
            digit_[i].unkfunc_02065920(sub);
        }
    }
}

THUMB UnkHoppingDigit* UnkHoppingNumber::unkfunc_02065a58()
{
    for (int i = 0; i < 40; i++) {
        if (digit_[i].unkfunc_020659bc()) {
            return &digit_[i];
        }
    }
    return 0;
}

THUMB void UnkHoppingNumber::unkfunc_02065a84(int x, int y, int value, int delay)
{
    char buf[8];
    delay++;
    dss::sprintf_s(buf, 8, "%d", value);
    if (value < 10) {
        x -= 4;
    } else if (value < 100) {
        x -= 8;
    } else {
        x -= 12;
    }
    for (char* p = buf; *p != 0; p++) {
        UnkHoppingDigit* digit = unkfunc_02065a58();
        if (digit != 0) {
            digit->unkfunc_020658d0(x, y - 8, *p - '0', delay);
            x += 8;
            delay += 4;
        }
    }
}
