#pragma ipa file
#include "ov005/fld/FieldCarrierDraw.hpp"

static int s_kumoOffset[2] = { 1, 0x12 };

THUMB fld::FieldFirmamentDraw::FieldFirmamentDraw()
{
    unk_100 = 0;
    unk_104 = 0;
}

THUMB fld::FieldFirmamentDraw::~FieldFirmamentDraw()
{
}

THUMB void fld::FieldFirmamentDraw::setHeight(int height)
{
    high_ = height;
}

THUMB void fld::FieldFirmamentDraw::setup()
{
    kumo_.unkfunc_02051a50("data/chr/kumo.tex", 0);
    kumo_.unkfunc_02051bb0(2);
    kumo_.unkfunc_02051b78();
    kumo_.unkfunc_02051b20(0x40, 0x28);
    kumo_.unkfunc_02051b2c(0, 0, 0x40, 0x28);
    kumo_.unkfunc_02051ba0(0x1f);
    shadow_.unkfunc_02051a50("data/chr/tenkukage.tex", 0);
    shadow_.unkfunc_02051bb0(2);
    shadow_.unkfunc_02051b90(0x10);
    shadow_.unkfunc_02051b78();
    shadow_.unkfunc_02051ba0(0x1f);
    firmament_.unkfunc_02051a50("data/chr/tenkujo.tex", 0);
    firmament_.unkfunc_02051bb0(2);
    firmament_.unkfunc_02051b78();
    firmament_.unkfunc_02051ba0(0x1f);
    high_ = 0;
    frame_ = 0;
    setShadowFlag(0);
}

THUMB void fld::FieldFirmamentDraw::setRotate(unsigned int rot)
{
}

THUMB void fld::FieldFirmamentDraw::draw(dss::Vector2<int>& pos)
{
    if (high_ != 0) {
        int size = (frame_ < 0x3c) ? 1 : 0;
        kumo_.unkfunc_02051b20(size * 2 + 0x40, size * 2 + 0x28);
        kumo_.unkfunc_02051b14(pos.vx + s_kumoOffset[0] - 0x20 - size, s_kumoOffset[1] + (pos.vy - high_) - 0x30 - size);
        firmament_.unkfunc_02051b14(pos.vx - 0x20, pos.vy - high_ - 0x30);
        shadow_.unkfunc_02051b14(pos.vx - 0x10, pos.vy - 0x14);
        frame_++;
        if (frame_ >= 0x78) {
            frame_ = 0;
        }
        firmament_.unkfunc_02051b68();
        kumo_.unkfunc_02051b68();
        shadow_.unkfunc_02051b68();
    } else {
        firmament_.unkfunc_02051b14(pos.vx - 0x20, pos.vy - 0x30);
        kumo_.unkfunc_02051b14(pos.vx + s_kumoOffset[0] - 0x20, pos.vy + s_kumoOffset[1] - 0x30);
        shadow_.unkfunc_02051b14(pos.vx - 0x10, pos.vy - 0x14);
        firmament_.unkfunc_02051bb0(2);
        kumo_.unkfunc_02051bb0(2);
        shadow_.unkfunc_02051bb0(2);
        firmament_.unkfunc_02051b68();
        kumo_.unkfunc_02051b68();
    }
}

THUMB void fld::FieldFirmamentDraw::cleanup()
{
    firmament_.unkfunc_02051ac4();
    shadow_.unkfunc_02051ac4();
    kumo_.unkfunc_02051ac4();
}

THUMB void fld::FieldFirmamentDraw::setDrawPosition(int x, int y)
{
    firmament_.unkfunc_02051b14(x, y);
    kumo_.unkfunc_02051b14(x, y);
    shadow_.unkfunc_02051b14(x, y);
}

THUMB void fld::FieldFirmamentDraw::setDepth(int depth)
{
    firmament_.unkfunc_02051bb0(depth + 2);
    kumo_.unkfunc_02051bb0(depth + 1);
    shadow_.unkfunc_02051bb0(depth);
}

THUMB void fld::FieldFirmamentDraw::setShadowWH(int w, int h)
{
    shadow_.unkfunc_02051b20(w, h);
}

THUMB void fld::FieldFirmamentDraw::setDisplayEnable(int flag)
{
    unk_100 = flag;
}

THUMB int fld::FieldFirmamentDraw::isDisplayEnable()
{
    return unk_100;
}

THUMB void fld::FieldFirmamentDraw::setShadowStay(int flag)
{
}

THUMB void fld::FieldFirmamentDraw::setAnimFlag(int flag)
{
    unk_104 = flag;
}

THUMB void fld::FieldFirmamentDraw::setShadowFlag(int flag)
{
    shadow_.unkfunc_02051b74(flag);
    kumo_.unkfunc_02051b74(flag);
}

THUMB void fld::FieldFirmamentDraw::setShadowDepth(int depth)
{
    shadow_.unkfunc_02051bb0(depth);
}

THUMB void fld::FieldFirmamentDraw::setShadowAlpha(unsigned char alpha)
{
    kumo_.unkfunc_02051b90(alpha);
}
