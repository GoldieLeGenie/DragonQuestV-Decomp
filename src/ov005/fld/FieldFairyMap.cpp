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
    unk_a8.unkfunc_02051a50(path, 0);
    unk_a8.unkfunc_02051b80();
    unk_a8.unkfunc_02051ba0(0x34);
    unk_a8.unkfunc_02051b2c(0, 0, 0x10, 0x10);
    unk_a8.unkfunc_02051bb0(0xa);
    unk_a8.unkfunc_02051b90(0);
    unk_a8.unkfunc_02051b74(1);
    dss::sprintf_s(path, sizeof(path), "data/field/2d/dq5ds_fw.tex");
    unk_04.unkfunc_02051a50(path, 0);
    unk_04.unkfunc_02051b80();
    unk_04.unkfunc_02051ba0(0x3e);
    unk_04.unkfunc_02051bb0(0);
    unk_04.unkfunc_02051b90(0);
    unk_04.unkfunc_02051a20();
    unk_a8.unkfunc_02051a20();
    unk_54.unkfunc_02051b80();
    unk_54.unkfunc_02051ba0(0x3e);
    unk_54.unkfunc_02051bb0(4);
    unk_54.unkfunc_02051b90(0);
    unk_54.unkfunc_02051b20(3, 3);
    unk_f8 = g_Global.getFieldType();
    load();
}
