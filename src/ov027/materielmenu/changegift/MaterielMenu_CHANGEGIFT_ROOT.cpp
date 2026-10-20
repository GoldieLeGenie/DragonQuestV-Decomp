#pragma ipa file
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_ROOT.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTGIFT.hpp"
#include "ov027/leveldata/GiftMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_CHANGEGIFT_ROOT::menuExecute()
{
}

inline dq5::level::GiftMessage* dq5::level::GiftMessage::getRecord(int index)
{
    return (GiftMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::GiftMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_CHANGEGIFT_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    mode_ = CHANGEGIFT_FIRST;
}

THUMB void MaterielMenu_CHANGEGIFT_ROOT::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217bfe8();
}

THUMB void MaterielMenu_CHANGEGIFT_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == CHANGEGIFT_CHANGE || mode_ == CHANGEGIFT_BACK) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x14));
                mode_ = CHANGEGIFT_END;
            }
        }
        return;
    }
    if (mode_ == CHANGEGIFT_FIRST) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessage(getMessageNo(1));
        checkCoin();
        resetCaptureOffset();
    }
}

THUMB int MaterielMenu_CHANGEGIFT_ROOT::getMessageNo(int index)
{
    return dq5::level::GiftMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_CHANGEGIFT_ROOT::selectYes()
{
    gTownMenu_MESSAGE.close();
    switch (mode_) {
        case CHANGEGIFT_FIRST:
            break;
        case CHANGEGIFT_CHECK:
            gTownMenu_MESSAGE.openMessageForTALK();
            checkCoin();
            break;
        case CHANGEGIFT_CHANGE:
        case CHANGEGIFT_BACK:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(3));
            mode_ = CHANGEGIFT_SELECT;
            break;
        case CHANGEGIFT_SELECT:
            close();
            gMaterielMenu_CHANGEGIFT_SELECTGIFT.open();
            break;
        case CHANGEGIFT_END:
            resetCaptureOffset();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_CHANGEGIFT_ROOT::checkCoin()
{
    if (MenuStatusInfo::getCoin() == 0) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(0x15), getMessageNo(0x16));
        mode_ = CHANGEGIFT_END;
        return;
    }
    TextAPI::setMACRO0(0x2a, 0xf0000000, MenuStatusInfo::getCoin());
    gTownMenu_MESSAGE.addMessage(getMessageNo(2));
    gTownMenu_MESSAGE.setYesNo();
    mode_ = CHANGEGIFT_CHANGE;
}
