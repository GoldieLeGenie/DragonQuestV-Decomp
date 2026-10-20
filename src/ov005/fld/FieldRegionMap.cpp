#pragma ipa file
#include "ov005/fld/FieldRegionMap.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB fld::FieldRegionMap::FieldRegionMap()
{
}

THUMB fld::FieldRegionMap::~FieldRegionMap()
{
}

THUMB void fld::FieldRegionMap::cleanup()
{
    unk_a8.unload();
    unk_04.unload();
}

THUMB void fld::FieldRegionMap::draw()
{
    unk_04.draw();
    symbolDraw(unk_f8);
    unk_a8.draw();
}

THUMB void fld::FieldRegionMap::load()
{
    unk_a8.allocVram();
    unk_a8.transferToVram();
    unk_04.allocVram();
    unk_04.transferToVram();
}

THUMB void fld::FieldRegionMap::clear()
{
    unk_04.freeVram();
    unk_a8.freeVram();
}

THUMB void fld::FieldRegionMap::setAlpha(unsigned char alpha)
{
    unk_04.setAlpha(alpha);
    unk_a8.setAlpha(alpha);
    unk_54.setAlpha(alpha);
}

THUMB void fld::FieldRegionMap::playerMapPosition()
{
    dss::Fix32Vector3 playerPos = FieldPlayerManager::getSingleton().getPosition();
    dss::Vector2<int> pos = convertMapPos(playerPos.vx.value, playerPos.vy.value);
    unk_a8.setSize(0x10, 0x10);
    unk_a8.setPosition(pos.vx, pos.vy - 0x10);
}

THUMB dss::Vector2<int> fld::FieldRegionMap::convertMapPos(int x, int y)
{
    dss::Vector2<int> pos;
    pos.vx = (x - 0x400000) / 0x6666 + 0x30;
    pos.vy = (y - 0x400000) / 0x6666 + 0x10;
    return pos;
}
