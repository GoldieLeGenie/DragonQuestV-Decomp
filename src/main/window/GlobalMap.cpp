#pragma ipa file
#include "main/window/GlobalMap.hpp"
#include "main/status/StageInfo.hpp"
#include <nitro/os.hpp>

THUMB window::GlobalMap::GlobalMap()
{
}

THUMB window::GlobalMap::~GlobalMap()
{
}

THUMB void window::GlobalMap::cleanup()
{
    unk_a8.unkfunc_02051ac4();
    unk_04.unkfunc_02051ac4();
}

THUMB void window::GlobalMap::setup()
{
    char path[0x80];

    unk_a4 = 0;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1.tex");
    unk_04.unkfunc_02051a50(path, 0);
    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051ba0(0x3e);
    unk_04.unkfunc_02051bb0(0);
    unk_04.sprite_.unk_32 = 1;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1m.tex");
    unk_a8.unkfunc_02051a50(path, 0);
    unk_a8.unkfunc_02051b80();
    unk_a8.unkfunc_02051ba0(0x3e);
    unk_a8.unkfunc_02051bb0(8);
    unk_04.unkfunc_02051b90(0);
    unk_a8.unkfunc_02051b90(0);
    unk_04.unkfunc_02051a20();
    unk_a8.unkfunc_02051a20();
    unk_54.unkfunc_02051b80();
    unk_54.unkfunc_02051ba0(0x3e);
    unk_54.unkfunc_02051bb0(4);
    unk_54.unkfunc_02051b90(0);
    unk_54.unkfunc_02051b20(3, 3);
}

THUMB void window::GlobalMap::draw()
{
    unkfunc_020195f0();
    symbolDraw(0);
}

THUMB void window::GlobalMap::unkfunc_020195f0()
{
    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b2c(0, 0, 0x30, 0xc0);
    unk_04.unkfunc_02051b14(0, 0);
    unk_04.unkfunc_02051b20(0x30, 0xc0);
    unk_04.unkfunc_02051b68();

    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b2c(0xd0, 0, 0x100, 0xc0);
    unk_04.unkfunc_02051b14(0xd0, 0);
    unk_04.unkfunc_02051b20(0x30, 0xc0);
    unk_04.unkfunc_02051b68();

    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b2c(0x30, 0, 0xd0, 0x10);
    unk_04.unkfunc_02051b14(0x30, 0);
    unk_04.unkfunc_02051b20(0xa0, 0x10);
    unk_04.unkfunc_02051b68();

    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b2c(0x30, 0xb0, 0xd0, 0xc0);
    unk_04.unkfunc_02051b14(0x30, 0xb0);
    unk_04.unkfunc_02051b20(0xa0, 0x10);
    unk_04.unkfunc_02051b68();

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            unkfunc_02019704(x, y, status::g_StageInfo.getMapVeil(x, y));
        }
    }
}

THUMB void window::GlobalMap::unkfunc_02019704(int x, int y, bool veil)
{
    if (veil) {
        unk_a8.unkfunc_02051b80();
        unk_a8.unkfunc_02051bb0(8);
        unk_a8.unkfunc_02051b2c(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
        unk_a8.unkfunc_02051b14(x * 10 + 0x30, y * 10 + 0x10);
        unk_a8.unkfunc_02051b20(10, 10);
        unk_a8.unkfunc_02051b68();
    }
    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b2c(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
    unk_04.unkfunc_02051b14(x * 10 + 0x30, y * 10 + 0x10);
    unk_04.unkfunc_02051b20(10, 10);
    unk_04.unkfunc_02051b68();
}

THUMB void window::GlobalMap::load()
{
    OS_Wait();
    unk_04.unkfunc_02051a38();
    unk_04.unkfunc_02051a2c();
    unk_a8.unkfunc_02051a38();
    unk_a8.unkfunc_02051a2c();
}

THUMB void window::GlobalMap::clear()
{
    unk_04.unkfunc_02051a20();
    unk_a8.unkfunc_02051a20();
}

THUMB dss::Vector2<int> window::GlobalMap::convertMapPos(int x, int y)
{
    dss::Vector2<int> pos;
    pos.vx = x / 0x19999 + 0x30;
    pos.vy = y / 0x19999 + 0x10;
    return pos;
}

THUMB void window::GlobalMap::setAlpha(unsigned char alpha)
{
    unk_04.unkfunc_02051b90(alpha);
    unk_a8.unkfunc_02051b90(alpha);
    unk_54.unkfunc_02051b90(alpha);
}

ARM void window::GlobalMap::playerMapPosition()
{
}
