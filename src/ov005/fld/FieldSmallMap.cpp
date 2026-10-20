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
    playerMarker_.unload();
    GlobalMap::cleanup();
}

THUMB void fld::FieldSmallMap::setup()
{
    char path[0x80];

    dss::sprintf_s(path, sizeof(path), "data/field/2d/point_s.tex");
    playerMarker_.loadFile(path, 0);
    playerMarker_.setSubScreen();
    playerMarker_.setPolygonID(0x34);
    playerMarker_.setDepth(0xa);
    playerMarker_.setAlpha(0);
    playerMarker_.setEnabled(1);
    playerMarker_.setTexCoords(0, 0, 0x10, 0x10);
    playerMarker_.setSize(0x10, 0x10);
    playerMarker_.freeVram();
    GlobalMap::setup();
    load();
}

THUMB void fld::FieldSmallMap::playerMapPosition()
{
    dss::Fix32Vector3 playerPos = FieldPlayerManager::getSingleton().getPosition();
    dss::Vector2<int> pos = convertMapPos(playerPos.vx.value, playerPos.vy.value);
    playerMarker_.setPosition(pos.vx, pos.vy - 0xe);
}

THUMB void fld::FieldSmallMap::setAlpha(unsigned char alpha)
{
    playerMarker_.setAlpha(alpha);
    GlobalMap::setAlpha(alpha);
}

THUMB void fld::FieldSmallMap::draw()
{
    GlobalMap::draw();
    playerMarker_.draw();
}

THUMB void fld::FieldSmallMap::load()
{
    playerMarker_.allocVram();
    playerMarker_.transferToVram();
    GlobalMap::load();
}

THUMB void fld::FieldSmallMap::clear()
{
    GlobalMap::clear();
    playerMarker_.freeVram();
}
