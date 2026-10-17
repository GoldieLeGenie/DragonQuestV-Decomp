#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/ScreenEffectManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB int fld::FieldActionRana::setup()
{
    counter_ = 0;
    change_ = 0;
    return -1;
}

THUMB void fld::FieldActionRana::execute()
{
    update();
}

THUMB int fld::FieldActionRana::update()
{
    if (isEffectEnd() == true) {
        FieldPlayerManager::getSingleton().setRemote(false);
        cmn::g_extraMapLink.setRanaLink();
        if (status::g_StageInfo.getTimeZone() == 4) {
            status::g_StageInfo.setTimeZone(TIME_ZONE(2));
        } else {
            status::g_StageInfo.setTimeZone(TIME_ZONE(4));
        }
        return prevType_;
    }
    return -1;
}

THUMB void fld::FieldActionRana::start(int type)
{
    FieldPlayerManager::getSingleton().setRemote(true);
    FieldPlayerManager::getSingleton().player_.setMoveType(3);
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_RANARUTA);
    if (status::g_StageInfo.getTimeZone() == 4) {
        window::gScreenEffect.ranarutaEffect_.morningFlag_ = true;
    } else {
        window::gScreenEffect.ranarutaEffect_.morningFlag_ = false;
    }
    prevType_ = type;
    counter_ = 0;
    change_ = 1;
}

THUMB int fld::FieldActionRana::isEffectEnd()
{
    return window::gScreenEffect.isEnd();
}

ARM bool fld::FieldActionRana::search()
{
    return false;
}
