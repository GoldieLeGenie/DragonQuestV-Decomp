#pragma ipa file
#include "ov001/town/TownGlobalMap.hpp"
#include "main/dss/RenderObject.hpp"

THUMB twn::TownGlobalMap::TownGlobalMap()
{
    isEnable_ = false;
    frame_ = 0;
    map2d_ = 0;
}

THUMB twn::TownGlobalMap::~TownGlobalMap()
{
}

THUMB twn::TownGlobalMap& twn::TownGlobalMap::getSingleton()
{
    static TownGlobalMap m_singleton;
    return m_singleton;
}

THUMB void twn::TownGlobalMap::setup()
{
    map_.loadFile("data/field/2d/dq5ds_wmap1.tex", 0);
    map_.setSubScreen();
    map_.setAlpha(0);
    map_.setPolygonID(0x3f);
    map_.sprite_.color0Opaque_ = 1;
}

THUMB void twn::TownGlobalMap::cleanup()
{
    if (isEnable_) {
        cleanupPoint();
        map_.unload();
        point_[0].setEnabled(false);
        point_[1].setEnabled(false);
    }
}

THUMB void twn::TownGlobalMap::execute()
{
    if (isEnable_) {
        switch (map2d_) {
        case 0:
            frame_ = 0;
            break;
        case 1:
            frame_++;
            if (frame_ == 0x1f) {
                map2d_ = 2;
            }
            break;
        case 2:
            frame_ = 0x1f;
            break;
        case 3:
            frame_--;
            if (frame_ <= 0) {
                map2d_ = 0;
                cleanup();
                isEnable_ = false;
            }
            break;
        }
        map_.setAlpha((unsigned char)frame_);
        point_[0].setAlpha(frame_);
        point_[1].setAlpha(frame_);
    }
}

THUMB void twn::TownGlobalMap::draw()
{
    if (isEnable_) {
        setupOrtho2D();
        map_.draw();
        point_[0].draw();
        point_[1].draw();
    }
}

THUMB void twn::TownGlobalMap::setupPoint(int x, int y, int kind)
{
    if (point_[kind].isLoaded()) {
        point_[kind].unload();
    }
    point_[kind].setEnabled(true);
    if (kind == 0) {
        point_[kind].loadFile("data/field/2d/point_s.tex", 0);
    } else {
        point_[kind].loadFile("data/field/2d/point_s2.tex", 0);
    }
    point_[kind].setSubScreen();
    point_[kind].setPolygonID(0x3d);
    point_[kind].setDepth(0x18);
    point_[kind].setTexCoords(0, 0, 0x10, 0x10);
    point_[kind].setSize(0x10, 0x10);
    point_[kind].setPosition(x, y);
    unk_0f8 = 0;
    unk_0fc = 0;
}

THUMB void twn::TownGlobalMap::cleanupPoint()
{
    if (point_[0].isLoaded()) {
        point_[0].unload();
    }
    if (point_[1].isLoaded()) {
        point_[1].unload();
    }
}

THUMB void twn::TownGlobalMap::open()
{
    isEnable_ = true;
    map2d_ = 1;
}

THUMB void twn::TownGlobalMap::close()
{
    map2d_ = 3;
}

THUMB bool twn::TownGlobalMap::isOpen()
{
    return map2d_ == 2;
}

THUMB bool twn::TownGlobalMap::isClose()
{
    return map2d_ == 0;
}

ARM int twn::TownGlobalMap::isEnable()
{
    return isEnable_;
}
