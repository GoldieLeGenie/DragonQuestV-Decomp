#include "ov001/town/player/TownActionRanaruta.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/ScreenEffectManager.hpp"

#pragma thumb on

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

int twn::TownActionRanaruta::setup()
{
    counter_ = 0;
    change_ = false;
    return -1;
}

void twn::TownActionRanaruta::execute()
{
    update();
}

int twn::TownActionRanaruta::update()
{
    if (isEffectEnd() == true) {
        TownPlayerManager::getSingleton().setRemote(false);
        if (change_ == true) {
            cmn::g_extraMapLink.setRanaLink();
            cmn::g_cmnPartyInfo.setMenuAction(cmn::RANA_START);
            if (cmn::g_cmnPartyInfo.getMenuAction() == cmn::RANA_START) {
                TownPlayerManager::getSingleton().setRemote(true);
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
                if (status::g_StageInfo.getTimeZone() == TIME_ZONE_NIGHT) {
                    status::g_StageInfo.setTimeZone(TIME_ZONE_DAYTIME);
                } else {
                    status::g_StageInfo.setTimeZone(TIME_ZONE_NIGHT);
                }
            }
        }
        cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
        return 0;
    }
    return -1;
}

void twn::TownActionRanaruta::start()
{
    TownPlayerManager::getSingleton().setRemote(true);
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_RANARUTA);
    if (status::g_StageInfo.getTimeZone() == TIME_ZONE_NIGHT) {
        window::gScreenEffect.ranarutaEffect_.morningFlag_ = true;
    } else {
        window::gScreenEffect.ranarutaEffect_.morningFlag_ = false;
    }
    counter_ = 0;
    change_ = true;
}

int twn::TownActionRanaruta::isEffectEnd()
{
    return window::gScreenEffect.isEnd();
}
