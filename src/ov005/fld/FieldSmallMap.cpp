#pragma ipa file
#include "ov005/fld/FieldSmallMap.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB fld::FieldSmallMap::FieldSmallMap()
{
}

THUMB fld::FieldSmallMap::~FieldSmallMap()
{
}

THUMB void fld::FieldSmallMap::cleanup()
{
    unk_f8.unkfunc_02051ac4();
    GlobalMap::cleanup();
}

THUMB void fld::FieldSmallMap::setup()
{
    char path[0x80];

    dss::sprintf_s(path, sizeof(path), "data/field/2d/point_s.tex");
    unk_f8.unkfunc_02051a50(path, 0);
    unk_f8.unkfunc_02051b80();
    unk_f8.unkfunc_02051ba0(0x34);
    unk_f8.unkfunc_02051bb0(0xa);
    unk_f8.unkfunc_02051b90(0);
    unk_f8.unkfunc_02051b74(1);
    unk_f8.unkfunc_02051b2c(0, 0, 0x10, 0x10);
    unk_f8.unkfunc_02051b20(0x10, 0x10);
    unk_f8.unkfunc_02051a20();
    GlobalMap::setup();
    load();
}

THUMB void fld::FieldSmallMap::playerMapPosition()
{
    dss::Fix32Vector3 playerPos = FieldPlayerManager::getSingleton().getPosition();
    dss::Vector2<int> pos = convertMapPos(playerPos.vx.value, playerPos.vy.value);
    unk_f8.unkfunc_02051b14(pos.vx, pos.vy - 0xe);
}

THUMB void fld::FieldSmallMap::setAlpha(unsigned char alpha)
{
    unk_f8.unkfunc_02051b90(alpha);
    GlobalMap::setAlpha(alpha);
}

THUMB void fld::FieldSmallMap::draw()
{
    GlobalMap::draw();
    unk_f8.unkfunc_02051b68();
}

THUMB void fld::FieldSmallMap::load()
{
    unk_f8.unkfunc_02051a38();
    unk_f8.unkfunc_02051a2c();
    GlobalMap::load();
}

THUMB void fld::FieldSmallMap::clear()
{
    GlobalMap::clear();
    unk_f8.unkfunc_02051a20();
}
