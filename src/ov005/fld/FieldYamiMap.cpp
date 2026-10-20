#pragma ipa file
#include "ov005/fld/FieldYamiMap.hpp"

THUMB fld::FieldYamiMap::FieldYamiMap()
{
}

THUMB fld::FieldYamiMap::~FieldYamiMap()
{
}

THUMB void fld::FieldYamiMap::setup()
{
    char path[0x80];

    dss::sprintf_s(path, sizeof(path), "data/field/2d/point_s.tex");
    playerMarker_.loadFile(path, 0);
    playerMarker_.setSubScreen();
    playerMarker_.setPolygonID(0x34);
    playerMarker_.setTexCoords(0, 0, 0x10, 0x10);
    playerMarker_.setDepth(0xa);
    playerMarker_.setAlpha(0);
    playerMarker_.setEnabled(1);
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_yw.tex");
    mapSprite_.loadFile(path, 0);
    mapSprite_.setSubScreen();
    mapSprite_.setPolygonID(0x3e);
    mapSprite_.setDepth(0);
    mapSprite_.sprite_.color0Opaque_ = 1;
    mapSprite_.setAlpha(0);
    mapSprite_.freeVram();
    playerMarker_.freeVram();
    symbolSprite_.setSubScreen();
    symbolSprite_.setPolygonID(0x3e);
    symbolSprite_.setDepth(4);
    symbolSprite_.setAlpha(0);
    symbolSprite_.setSize(3, 3);
    world_ = 3;
    load();
}
