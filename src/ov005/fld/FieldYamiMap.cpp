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
    unk_a8.loadFile(path, 0);
    unk_a8.setSubScreen();
    unk_a8.setPolygonID(0x34);
    unk_a8.setTexCoords(0, 0, 0x10, 0x10);
    unk_a8.setDepth(0xa);
    unk_a8.setAlpha(0);
    unk_a8.setEnabled(1);
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_yw.tex");
    mapSprite_.loadFile(path, 0);
    mapSprite_.setSubScreen();
    mapSprite_.setPolygonID(0x3e);
    mapSprite_.setDepth(0);
    mapSprite_.sprite_.color0Opaque_ = 1;
    mapSprite_.setAlpha(0);
    mapSprite_.freeVram();
    unk_a8.freeVram();
    symbolSprite_.setSubScreen();
    symbolSprite_.setPolygonID(0x3e);
    symbolSprite_.setDepth(4);
    symbolSprite_.setAlpha(0);
    symbolSprite_.setSize(3, 3);
    unk_f8 = 3;
    load();
}
