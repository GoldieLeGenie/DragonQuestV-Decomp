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
    unk_f8.unload();
    GlobalMap::cleanup();
}

THUMB void fld::FieldSmallMap::setup()
{
    char path[0x80];

    dss::sprintf_s(path, sizeof(path), "data/field/2d/point_s.tex");
    unk_f8.loadFile(path, 0);
    unk_f8.setSubScreen();
    unk_f8.setPolygonID(0x34);
    unk_f8.setDepth(0xa);
    unk_f8.setAlpha(0);
    unk_f8.setEnabled(1);
    unk_f8.setTexCoords(0, 0, 0x10, 0x10);
    unk_f8.setSize(0x10, 0x10);
    unk_f8.freeVram();
    GlobalMap::setup();
    load();
}

THUMB void fld::FieldSmallMap::playerMapPosition()
{
    dss::Fix32Vector3 playerPos = FieldPlayerManager::getSingleton().getPosition();
    dss::Vector2<int> pos = convertMapPos(playerPos.vx.value, playerPos.vy.value);
    unk_f8.setPosition(pos.vx, pos.vy - 0xe);
}

THUMB void fld::FieldSmallMap::setAlpha(unsigned char alpha)
{
    unk_f8.setAlpha(alpha);
    GlobalMap::setAlpha(alpha);
}

THUMB void fld::FieldSmallMap::draw()
{
    GlobalMap::draw();
    unk_f8.draw();
}

THUMB void fld::FieldSmallMap::load()
{
    unk_f8.allocVram();
    unk_f8.transferToVram();
    GlobalMap::load();
}

THUMB void fld::FieldSmallMap::clear()
{
    GlobalMap::clear();
    unk_f8.freeVram();
}
