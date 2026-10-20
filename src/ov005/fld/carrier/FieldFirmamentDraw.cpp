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
    kumo_.loadFile("data/chr/kumo.tex", 0);
    kumo_.setDepth(2);
    kumo_.setMainScreen();
    kumo_.setSize(0x40, 0x28);
    kumo_.setTexCoords(0, 0, 0x40, 0x28);
    kumo_.setPolygonID(0x1f);
    shadow_.loadFile("data/chr/tenkukage.tex", 0);
    shadow_.setDepth(2);
    shadow_.setAlpha(0x10);
    shadow_.setMainScreen();
    shadow_.setPolygonID(0x1f);
    firmament_.loadFile("data/chr/tenkujo.tex", 0);
    firmament_.setDepth(2);
    firmament_.setMainScreen();
    firmament_.setPolygonID(0x1f);
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
        kumo_.setSize(size * 2 + 0x40, size * 2 + 0x28);
        kumo_.setPosition(pos.vx + s_kumoOffset[0] - 0x20 - size, s_kumoOffset[1] + (pos.vy - high_) - 0x30 - size);
        firmament_.setPosition(pos.vx - 0x20, pos.vy - high_ - 0x30);
        shadow_.setPosition(pos.vx - 0x10, pos.vy - 0x14);
        frame_++;
        if (frame_ >= 0x78) {
            frame_ = 0;
        }
        firmament_.draw();
        kumo_.draw();
        shadow_.draw();
    } else {
        firmament_.setPosition(pos.vx - 0x20, pos.vy - 0x30);
        kumo_.setPosition(pos.vx + s_kumoOffset[0] - 0x20, pos.vy + s_kumoOffset[1] - 0x30);
        shadow_.setPosition(pos.vx - 0x10, pos.vy - 0x14);
        firmament_.setDepth(2);
        kumo_.setDepth(2);
        shadow_.setDepth(2);
        firmament_.draw();
        kumo_.draw();
    }
}

THUMB void fld::FieldFirmamentDraw::cleanup()
{
    firmament_.unload();
    shadow_.unload();
    kumo_.unload();
}

THUMB void fld::FieldFirmamentDraw::setDrawPosition(int x, int y)
{
    firmament_.setPosition(x, y);
    kumo_.setPosition(x, y);
    shadow_.setPosition(x, y);
}

THUMB void fld::FieldFirmamentDraw::setDepth(int depth)
{
    firmament_.setDepth(depth + 2);
    kumo_.setDepth(depth + 1);
    shadow_.setDepth(depth);
}

THUMB void fld::FieldFirmamentDraw::setShadowWH(int w, int h)
{
    shadow_.setSize(w, h);
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
    shadow_.setEnabled(flag);
    kumo_.setEnabled(flag);
}

THUMB void fld::FieldFirmamentDraw::setShadowDepth(int depth)
{
    shadow_.setDepth(depth);
}

THUMB void fld::FieldFirmamentDraw::setShadowAlpha(unsigned char alpha)
{
    kumo_.setAlpha(alpha);
}
