#pragma ipa file
#include "ov001/town/TownImageShoplist.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/status/StageAttribute.hpp"

twn::TownImageShoplist twn::gTownImageShoplist;

THUMB twn::TownImageShoplist::TownImageShoplist()
{
    isEnable_ = false;
    frame_ = 0;
    map2d_ = 0;
}

THUMB twn::TownImageShoplist::~TownImageShoplist()
{
}

THUMB void twn::TownImageShoplist::setup()
{
    checkData();
    if (isEnable_) {
        shop_.unkfunc_02051a50("data/2d/map/shop.tex", 0);
        shop_.unkfunc_02051b80();
        shop_.unkfunc_02051b90(0);
        shop_.unkfunc_02051ba0(0x3f);
        shop_.sprite_.unk_32 = 1;
        black_.unkfunc_02051b20(0x100, 0xc0);
        black_.unkfunc_02051b90(0);
        black_.unkfunc_02051b80();
        black_.unkfunc_02051bbc(0, 0, 0);
        black_.unkfunc_02051ba0(0x3f);
    }
    map2d_ = 1;
}

THUMB void twn::TownImageShoplist::cleanup()
{
    if (isEnable_) {
        shop_.unkfunc_02051ac4();
    }
    isEnable_ = false;
}

THUMB void twn::TownImageShoplist::execute()
{
    if (isEnable_) {
        switch (map2d_) {
        case 0:
            frame_ = 0;
            break;
        case 1:
            shop_.unkfunc_02051b74(true);
            shop_.unkfunc_02051b90(frame_);
            frame_++;
            if (frame_ == 0x1f) {
                black_.unkfunc_02051b90(0);
                map2d_ = 2;
            }
            break;
        case 4:
            shop_.unkfunc_02051b74(true);
            shop_.unkfunc_02051b90(0x1f);
            black_.unkfunc_02051b90(0x1f - frame_);
            frame_++;
            if (frame_ == 0x1f) {
                black_.unkfunc_02051b90(0);
                map2d_ = 2;
            }
            break;
        case 2:
            frame_ = 0x1f;
            shop_.unkfunc_02051b90(0x1f);
            shop_.unkfunc_02051b74(true);
            break;
        case 3:
            frame_ = dss::clamp<int>(frame_, 0, 0x1f);
            shop_.unkfunc_02051b90(frame_);
            frame_--;
            if (frame_ <= 0) {
                shop_.unkfunc_02051b74(false);
                map2d_ = 0;
                cleanup();
            }
            break;
        }
    }
}

THUMB void twn::TownImageShoplist::checkData()
{
    if (status::g_StageAttribute.isShopIcon()) {
        isEnable_ = true;
    } else {
        isEnable_ = false;
    }
}

THUMB void twn::TownImageShoplist::draw()
{
    if (isEnable_) {
        setupOrtho2D();
        shop_.unkfunc_02051b68();
        setupOrtho2DFine();
        black_.unkfunc_02051b68();
    }
}

THUMB void twn::TownImageShoplist::open()
{
    setup();
    map2d_ = 1;
}

THUMB void twn::TownImageShoplist::openBlack()
{
    setup();
    map2d_ = 4;
}

THUMB void twn::TownImageShoplist::close()
{
    map2d_ = 3;
}

THUMB bool twn::TownImageShoplist::isOpen()
{
    return map2d_ == 2;
}

THUMB bool twn::TownImageShoplist::isClose()
{
    return map2d_ == 0;
}

THUMB int twn::TownImageShoplist::isEnable()
{
    return isEnable_;
}
