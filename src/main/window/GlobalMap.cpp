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
    unk_a8.unload();
    unk_04.unload();
}

THUMB void window::GlobalMap::setup()
{
    char path[0x80];

    unk_a4 = 0;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1.tex");
    unk_04.loadFile(path, 0);
    unk_04.setSubScreen();
    unk_04.setPolygonID(0x3e);
    unk_04.setDepth(0);
    unk_04.sprite_.color0Opaque_ = 1;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1m.tex");
    unk_a8.loadFile(path, 0);
    unk_a8.setSubScreen();
    unk_a8.setPolygonID(0x3e);
    unk_a8.setDepth(8);
    unk_04.setAlpha(0);
    unk_a8.setAlpha(0);
    unk_04.freeVram();
    unk_a8.freeVram();
    unk_54.setSubScreen();
    unk_54.setPolygonID(0x3e);
    unk_54.setDepth(4);
    unk_54.setAlpha(0);
    unk_54.setSize(3, 3);
}

THUMB void window::GlobalMap::draw()
{
    drawVeilMap();
    symbolDraw(0);
}

THUMB void window::GlobalMap::drawVeilMap()
{
    unk_04.setSubScreen();
    unk_04.setDepth(0);
    unk_04.setTexCoords(0, 0, 0x30, 0xc0);
    unk_04.setPosition(0, 0);
    unk_04.setSize(0x30, 0xc0);
    unk_04.draw();

    unk_04.setSubScreen();
    unk_04.setDepth(0);
    unk_04.setTexCoords(0xd0, 0, 0x100, 0xc0);
    unk_04.setPosition(0xd0, 0);
    unk_04.setSize(0x30, 0xc0);
    unk_04.draw();

    unk_04.setSubScreen();
    unk_04.setDepth(0);
    unk_04.setTexCoords(0x30, 0, 0xd0, 0x10);
    unk_04.setPosition(0x30, 0);
    unk_04.setSize(0xa0, 0x10);
    unk_04.draw();

    unk_04.setSubScreen();
    unk_04.setDepth(0);
    unk_04.setTexCoords(0x30, 0xb0, 0xd0, 0xc0);
    unk_04.setPosition(0x30, 0xb0);
    unk_04.setSize(0xa0, 0x10);
    unk_04.draw();

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            veilDraw(x, y, status::g_StageInfo.getMapVeil(x, y));
        }
    }
}

THUMB void window::GlobalMap::veilDraw(int x, int y, bool veil)
{
    if (veil) {
        unk_a8.setSubScreen();
        unk_a8.setDepth(8);
        unk_a8.setTexCoords(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
        unk_a8.setPosition(x * 10 + 0x30, y * 10 + 0x10);
        unk_a8.setSize(10, 10);
        unk_a8.draw();
    }
    unk_04.setSubScreen();
    unk_04.setDepth(0);
    unk_04.setTexCoords(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
    unk_04.setPosition(x * 10 + 0x30, y * 10 + 0x10);
    unk_04.setSize(10, 10);
    unk_04.draw();
}

THUMB void window::GlobalMap::load()
{
    OS_Wait();
    unk_04.allocVram();
    unk_04.transferToVram();
    unk_a8.allocVram();
    unk_a8.transferToVram();
}

THUMB void window::GlobalMap::clear()
{
    unk_04.freeVram();
    unk_a8.freeVram();
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
    unk_04.setAlpha(alpha);
    unk_a8.setAlpha(alpha);
    unk_54.setAlpha(alpha);
}

ARM void window::GlobalMap::playerMapPosition()
{
}
