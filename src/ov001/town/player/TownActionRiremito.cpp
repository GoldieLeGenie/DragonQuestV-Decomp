#include "ov001/town/player/TownActionRiremito.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/window/ScreenEffectManager.hpp"

#pragma thumb on

inline int status::StageInfo::getSymbolID()
{
    return symbolID_;
}

inline int status::StageInfo::getRiremitMapId()
{
    return riremitMap_;
}

inline void cmn::CommonPartyInfo::setShipNo(int shipNo)
{
    shipNo_ = shipNo;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

int twn::TownActionRiremito::setup()
{
    return -1;
}

void twn::TownActionRiremito::execute()
{
    update();
}

int twn::TownActionRiremito::update()
{
    if (isEffectEnd() == true) {
        TownPlayerManager::getSingleton().setRemote(false);
        int id = status::g_StageInfo.getSymbolID();
        int map = status::g_StageInfo.getRiremitMapId();
        if (map == 999) {
            dss::Fix32Vector3 pos(0, 0, 0);
            bool ship = false;
            switch (id) {
            case 0x1a:
                ship = true;
                pos.vy.value = 0xa000;
                break;
            case 0x2e:
            case 0x2f:
                ship = true;
                break;
            }
            if (ship == true) {
                if (status::g_Story.isVehicleEnable(0) == true) {
                    cmn::g_cmnPartyInfo.setShipNo(0);
                } else {
                    cmn::g_cmnPartyInfo.setShipNo(1);
                }
                cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
            }
            cmn::g_extraMapLink.setExtraExitField(id, pos);
        } else {
            if (map == 0x65) {
                id = 0x10064;
            } else if (map == 0x70) {
                id = 0x10068;
            }
            cmn::g_extraMapLink.setExtraExitTown(map, id);
        }
        return 0;
    }
    return -1;
}

int twn::TownActionRiremito::isEffectEnd()
{
    return window::gScreenEffect.isEnd();
}

void twn::TownActionRiremito::start()
{
    TownPlayerManager::getSingleton().setRemote(true);
    counter_ = 0;
    window::gScreenEffect.effectStart(window::ScreenEffectManager::PLAY_BACK_RIREMITO);
    cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
}
