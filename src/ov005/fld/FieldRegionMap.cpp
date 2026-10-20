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
    mapSprite_.unload();
}

THUMB void fld::FieldRegionMap::draw()
{
    mapSprite_.draw();
    symbolDraw(unk_f8);
    unk_a8.draw();
}

THUMB void fld::FieldRegionMap::load()
{
    unk_a8.allocVram();
    unk_a8.transferToVram();
    mapSprite_.allocVram();
    mapSprite_.transferToVram();
}

THUMB void fld::FieldRegionMap::clear()
{
    mapSprite_.freeVram();
    unk_a8.freeVram();
}

THUMB void fld::FieldRegionMap::setAlpha(unsigned char alpha)
{
    mapSprite_.setAlpha(alpha);
    unk_a8.setAlpha(alpha);
    symbolSprite_.setAlpha(alpha);
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
