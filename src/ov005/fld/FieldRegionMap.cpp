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
    unk_a8.unkfunc_02051ac4();
    unk_04.unkfunc_02051ac4();
}

THUMB void fld::FieldRegionMap::draw()
{
    unk_04.unkfunc_02051b68();
    symbolDraw(unk_f8);
    unk_a8.unkfunc_02051b68();
}

THUMB void fld::FieldRegionMap::load()
{
    unk_a8.unkfunc_02051a38();
    unk_a8.unkfunc_02051a2c();
    unk_04.unkfunc_02051a38();
    unk_04.unkfunc_02051a2c();
}

THUMB void fld::FieldRegionMap::clear()
{
    unk_04.unkfunc_02051a20();
    unk_a8.unkfunc_02051a20();
}

THUMB void fld::FieldRegionMap::setAlpha(unsigned char alpha)
{
    unk_04.unkfunc_02051b90(alpha);
    unk_a8.unkfunc_02051b90(alpha);
    unk_54.unkfunc_02051b90(alpha);
}

THUMB void fld::FieldRegionMap::playerMapPosition()
{
    dss::Fix32Vector3 playerPos = FieldPlayerManager::getSingleton().getPosition();
    dss::Vector2<int> pos = convertMapPos(playerPos.vx.value, playerPos.vy.value);
    unk_a8.unkfunc_02051b20(0x10, 0x10);
    unk_a8.unkfunc_02051b14(pos.vx, pos.vy - 0x10);
}

THUMB dss::Vector2<int> fld::FieldRegionMap::convertMapPos(int x, int y)
{
    dss::Vector2<int> pos;
    pos.vx = (x - 0x400000) / 0x6666 + 0x30;
    pos.vy = (y - 0x400000) / 0x6666 + 0x10;
    return pos;
}
