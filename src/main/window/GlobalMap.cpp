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
    veilSprite_.unload();
    mapSprite_.unload();
}

THUMB void window::GlobalMap::setup()
{
    char path[0x80];

    blinkCount_ = 0;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1.tex");
    mapSprite_.loadFile(path, 0);
    mapSprite_.setSubScreen();
    mapSprite_.setPolygonID(0x3e);
    mapSprite_.setDepth(0);
    mapSprite_.sprite_.color0Opaque_ = 1;
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_wmap1m.tex");
    veilSprite_.loadFile(path, 0);
    veilSprite_.setSubScreen();
    veilSprite_.setPolygonID(0x3e);
    veilSprite_.setDepth(8);
    mapSprite_.setAlpha(0);
    veilSprite_.setAlpha(0);
    mapSprite_.freeVram();
    veilSprite_.freeVram();
    symbolSprite_.setSubScreen();
    symbolSprite_.setPolygonID(0x3e);
    symbolSprite_.setDepth(4);
    symbolSprite_.setAlpha(0);
    symbolSprite_.setSize(3, 3);
}

THUMB void window::GlobalMap::draw()
{
    drawVeilMap();
    symbolDraw(0);
}

THUMB void window::GlobalMap::drawVeilMap()
{
    mapSprite_.setSubScreen();
    mapSprite_.setDepth(0);
    mapSprite_.setTexCoords(0, 0, 0x30, 0xc0);
    mapSprite_.setPosition(0, 0);
    mapSprite_.setSize(0x30, 0xc0);
    mapSprite_.draw();

    mapSprite_.setSubScreen();
    mapSprite_.setDepth(0);
    mapSprite_.setTexCoords(0xd0, 0, 0x100, 0xc0);
    mapSprite_.setPosition(0xd0, 0);
    mapSprite_.setSize(0x30, 0xc0);
    mapSprite_.draw();

    mapSprite_.setSubScreen();
    mapSprite_.setDepth(0);
    mapSprite_.setTexCoords(0x30, 0, 0xd0, 0x10);
    mapSprite_.setPosition(0x30, 0);
    mapSprite_.setSize(0xa0, 0x10);
    mapSprite_.draw();

    mapSprite_.setSubScreen();
    mapSprite_.setDepth(0);
    mapSprite_.setTexCoords(0x30, 0xb0, 0xd0, 0xc0);
    mapSprite_.setPosition(0x30, 0xb0);
    mapSprite_.setSize(0xa0, 0x10);
    mapSprite_.draw();

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            veilDraw(x, y, status::g_StageInfo.getMapVeil(x, y));
        }
    }
}

THUMB void window::GlobalMap::veilDraw(int x, int y, bool veil)
{
    if (veil) {
        veilSprite_.setSubScreen();
        veilSprite_.setDepth(8);
        veilSprite_.setTexCoords(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
        veilSprite_.setPosition(x * 10 + 0x30, y * 10 + 0x10);
        veilSprite_.setSize(10, 10);
        veilSprite_.draw();
    }
    mapSprite_.setSubScreen();
    mapSprite_.setDepth(0);
    mapSprite_.setTexCoords(x * 10 + 0x30, y * 10 + 0x10, (x + 1) * 10 + 0x30, (y + 1) * 10 + 0x10);
    mapSprite_.setPosition(x * 10 + 0x30, y * 10 + 0x10);
    mapSprite_.setSize(10, 10);
    mapSprite_.draw();
}

THUMB void window::GlobalMap::load()
{
    OS_Wait();
    mapSprite_.allocVram();
    mapSprite_.transferToVram();
    veilSprite_.allocVram();
    veilSprite_.transferToVram();
}

THUMB void window::GlobalMap::clear()
{
    mapSprite_.freeVram();
    veilSprite_.freeVram();
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
    mapSprite_.setAlpha(alpha);
    veilSprite_.setAlpha(alpha);
    symbolSprite_.setAlpha(alpha);
}

ARM void window::GlobalMap::playerMapPosition()
{
}
