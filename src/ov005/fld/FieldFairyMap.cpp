#pragma ipa file
#include "ov005/fld/FieldFairyMap.hpp"
#include "main/global/Global.hpp"

THUMB fld::FieldFairyMap::FieldFairyMap()
{
}

THUMB fld::FieldFairyMap::~FieldFairyMap()
{
}

THUMB void fld::FieldFairyMap::setup()
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
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_fw.tex");
    unk_04.loadFile(path, 0);
    unk_04.setSubScreen();
    unk_04.setPolygonID(0x3e);
    unk_04.setDepth(0);
    unk_04.setAlpha(0);
    unk_04.freeVram();
    unk_a8.freeVram();
    unk_54.setSubScreen();
    unk_54.setPolygonID(0x3e);
    unk_54.setDepth(4);
    unk_54.setAlpha(0);
    unk_54.setSize(3, 3);
    unk_f8 = g_Global.getFieldType();
    load();
}
