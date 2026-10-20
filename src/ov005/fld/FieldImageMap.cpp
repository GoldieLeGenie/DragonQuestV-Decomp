#include "ov005/fld/FieldImageMap.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/global/Global.hpp"

THUMB fld::FieldImageMap::FieldImageMap()
{
    frame_ = 0;
    map2d_ = 0;
}

THUMB fld::FieldImageMap::~FieldImageMap()
{
}

THUMB void fld::FieldImageMap::setup(Render* render)
{
    render_ = render;
    switch (g_Global.getFieldType()) {
    case 0:
        worldMap_ = &smallMap_;
        break;
    case 1:
    case 2:
        worldMap_ = &fairyMap_;
        break;
    case 3:
        worldMap_ = &darkMap_;
        break;
    }
    worldMap_->setup();
    map2d_ = 2;
}

THUMB void fld::FieldImageMap::cleanup()
{
    worldMap_->cleanup();
    render_ = NULL;
}

THUMB void fld::FieldImageMap::execute()
{
    switch (map2d_) {
    case 2:
        frame_ = 0x1f;
        worldMap_->playerMapPosition();
        worldMap_->setAlpha(frame_);
        break;
    case 3:
        if (--frame_ < 0) {
            worldMap_->cleanup();
            map2d_ = 4;
            frame_ = 0;
        }
        worldMap_->playerMapPosition();
        worldMap_->setAlpha(frame_);
        break;
    case 4:
        if (getDisplayFrame() & 1) {
            return;
        }
        map2d_ = 5;
        largeMap_.unkfunc_02133d0c(render_);
        break;
    case 5:
        if (++frame_ >= 0x1f) {
            map2d_ = 7;
            frame_ = 0x1f;
        }
        largeMap_.unkfunc_021340c8(frame_);
        break;
    case 6:
        break;
    case 7:
        frame_ = 0x1f;
        largeMap_.unkfunc_021340c8(frame_);
        largeMap_.unkfunc_021340e0();
        break;
    case 8:
        if (--frame_ < 0) {
            largeMap_.unkfunc_02133d18();
            map2d_ = 0;
            frame_ = 0;
        }
        largeMap_.unkfunc_021340c8(frame_);
        break;
    case 0:
        if (getDisplayFrame() & 1) {
            return;
        }
        worldMap_->setup();
        map2d_ = 1;
        break;
    case 1:
        if (++frame_ >= 0x1f) {
            map2d_ = 2;
            frame_ = 0x1f;
        }
        worldMap_->playerMapPosition();
        worldMap_->setAlpha(frame_);
        break;
    case 9:
        break;
    }
}

THUMB void fld::FieldImageMap::draw()
{
    setupOrtho2DBackground();
    worldMap_->draw();
}

THUMB void fld::FieldImageMap::reload()
{
    worldMap_->load();
}

THUMB void fld::FieldImageMap::closeLargeMap()
{
    map2d_ = 8;
}

THUMB void fld::FieldImageMap::closeSmallMap()
{
    map2d_ = 3;
}

THUMB void fld::FieldImageMap::open()
{
    closeSmallMap();
}

THUMB void fld::FieldImageMap::close()
{
    closeLargeMap();
}

THUMB bool fld::FieldImageMap::isOpen()
{
    return map2d_ == 7;
}

THUMB bool fld::FieldImageMap::isClose()
{
    return map2d_ == 2;
}
