#pragma ipa file
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHECK_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHANGE_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov001/town/shop/TownCurseSpotLight.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/menu/MaterielMenu_NameEdit.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_JISAN_CHECK_NAME::menuExecute()
{
}

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_JISAN_ROOT::setActiveMenu(char select)
{
    active_ = select;
}

inline char* status::PlayerData::getNameString()
{
    return name_;
}

inline void status::PlayerData::setCursedName(int val)
{
    cursedName_ = val;
}

inline void status::HaveItemSack::setCursedName(int flag)
{
    cursedName_ = flag;
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 1;
    mode_ = MODE_EDIT;
    short active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
    target_ = 0;
    if (active != -1) {
        target_ = MenuStatusInfo::getPlayerIndex(active);
    }
    if (status::g_Menu.returnMenuType_ != 0) {
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.returnMenuType_ = 0;
        if (status::g_Menu.actorIndex_ == -1) {
            target_ = 0;
        }
        else {
            target_ = MenuStatusInfo::getPlayerIndex(status::g_Menu.actorIndex_);
        }
        setTargetMacro();
        TextAPI::setMACRO0(0x7f, 0xd0000000, 0);
        openMessage(0x43, 0x44, 0x46, true);
        mode_ = MODE_CANCEL;
        if (status::g_Menu.actorIndex_ == -1) {
            MenuStatusInfo::setFukuroName(gMaterielMenu_NameEdit.getNameUTF8());
            MenuStatusInfo::getHaveItemSack().setCursedName(1);
        }
        else {
            MenuStatusInfo::getPlayerData(status::g_Menu.actorIndex_).setNameString(gMaterielMenu_NameEdit.getNameUTF8());
            MenuStatusInfo::getPlayerData(status::g_Menu.actorIndex_).setCursedName(1);
        }
        status::g_Menu.actorIndex_ = 0;
        return;
    }
    gMaterielMenu_NameEdit.open();
    gMaterielMenu_NameEdit.clearName();
    if (active == -1) {
        gMaterielMenu_NameEdit.setDefaultName(MenuStatusInfo::getFukuroName());
        return;
    }
    gMaterielMenu_NameEdit.setDefaultName(MenuStatusInfo::getPlayerData(active).getNameString());
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        unkfunc_0217a464(menu::MaterielMenuPlayerControl::getSingleton()->activeChara_, 0);
    }
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
            return;
        }
        return;
    }
    switch (MaterielMenu_NameEdit::status_) {
        case MaterielMenu_NameEdit::ERROR_S:
            TextAPI::setUserString(0, gMaterielMenu_NameEdit.getNameUTF8());
            TextAPI::setMACRO0(0x7f, 0xd0000000, 0);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x39), getMessageNo(0x45));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_RETRY;
            break;
        case MaterielMenu_NameEdit::COMPLETE: {
            TextAPI::setUserString(0, gMaterielMenu_NameEdit.getNameUTF8());
            setTargetMacro();
            TextAPI::setMACRO0(0x7f, 0xd0000000, 0);
            int active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            char tempName[25];
            for (int i = 0; i < 25; i++) {
                tempName[i] = 0;
            }
            if (active == -1) {
                dss::strcpy_s(tempName, 25, MenuStatusInfo::getFukuroName());
            }
            else {
                dss::strcpy_s(tempName, 25, MenuStatusInfo::getPlayerData(active).getNameString());
            }
            if (dss::strcmp(tempName, gMaterielMenu_NameEdit.getNameUTF8()) == 0) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x38), getMessageNo(0x46));
                gTownMenu_MESSAGE.setYesNo();
                mode_ = MODE_CANCEL;
                return;
            }
            if (MenuAPI::judgeReserveWord(gMaterielMenu_NameEdit.getNameUTF8()) == true) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x39), getMessageNo(0x45));
                gTownMenu_MESSAGE.setYesNo();
                mode_ = MODE_RETRY;
                return;
            }
            if (MenuAPI::judgeOverlapWord((unsigned char*)gMaterielMenu_NameEdit.getNameUTF8()) == true) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x3a), getMessageNo(0x45));
                gTownMenu_MESSAGE.setYesNo();
                mode_ = MODE_RETRY;
                return;
            }
            if (MenuAPI::judgeRepeatWord((unsigned char*)gMaterielMenu_NameEdit.getNameUTF8()) == true) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x3c));
                gTownMenu_MESSAGE.setYesNo();
                mode_ = MODE_ERROR_RENSHA;
                return;
            }
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x3f));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_SET_NAME;
            break;
        }
        case MaterielMenu_NameEdit::CANCEL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x38), getMessageNo(0x46));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CANCEL;
            break;
        case MaterielMenu_NameEdit::EDIT_INIT:
        case MaterielMenu_NameEdit::EXEC:
            break;
    }
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::selectYes()
{
    switch (mode_) {
        case MODE_EDIT:
            break;
        case MODE_RETRY: {
            short active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            gMaterielMenu_NameEdit.open();
            gMaterielMenu_NameEdit.clearName();
            if (active == -1) {
                gMaterielMenu_NameEdit.setDefaultName(MenuStatusInfo::getFukuroName());
                return;
            }
            gMaterielMenu_NameEdit.setDefaultName(MenuStatusInfo::getPlayerData(active).getNameString());
            break;
        }
        case MODE_CANCEL:
            close();
            gMaterielMenu_JISAN_CHANGE_NAME.open();
            break;
        case MODE_ERROR_HUSE:
        case MODE_ERROR_RENSHA:
        case MODE_ERROR_RENSHA2:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x41));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CURSE_NAME;
            break;
        case MODE_SET_NAME: {
            setTargetMacro();
            TextAPI::setMACRO0(0x7f, 0xd0000000, 0);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x40), getMessageNo(0x46));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CANCEL;
            int active = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            if (active == -1) {
                MenuStatusInfo::setFukuroName(gMaterielMenu_NameEdit.getNameUTF8());
                return;
            }
            MenuStatusInfo::getPlayerData(active).setNameString(gMaterielMenu_NameEdit.getNameUTF8());
            break;
        }
        case MODE_CURSE_NAME:
            setTargetMacro();
            TextAPI::setMACRO0(0x7f, 0xd0000000, 0);
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x42));
            mode_ = MODE_SOUND;
            break;
        case MODE_SOUND:
            close();
            status::g_Menu.bookingFlag_ = menu::BOOKING_JISAN;
            status::g_Menu.returnMenuType_ = 3;
            status::g_Menu.curseEffectStart_ = 1;
            status::g_Menu.actorIndex_ = menu::MaterielMenuPlayerControl::getSingleton()->activeChara_;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            twn::TownCurseSpotLight::getSingleton().setup();
            break;
        case MODE_END:
            break;
    }
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::selectNo()
{
    switch (mode_) {
        case MODE_EDIT:
            break;
        case MODE_RETRY:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x46));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CANCEL;
            break;
        case MODE_CANCEL:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
            gTownMenu_MESSAGE.addMessageWAITKEY();
            close();
            gMaterielMenu_JISAN_ROOT.setActiveMenu(4);
            gMaterielMenu_JISAN_ROOT.open();
            break;
        case MODE_ERROR_HUSE:
        case MODE_SET_NAME:
        case MODE_CURSE_NAME:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x45));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_RETRY;
            break;
        case MODE_ERROR_RENSHA:
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x3d));
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_ERROR_RENSHA2;
            break;
        case MODE_ERROR_RENSHA2:
            setTargetMacro();
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x3e));
            mode_ = MODE_RETRY;
            break;
        case MODE_SOUND:
        case MODE_END:
            break;
    }
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::setTargetMacro()
{
    if (target_ == 0) {
        TextAPI::setMACRO0(0x12, 0x50000000, 0x24e);
        return;
    }
    TextAPI::setMACRO0(0x12, 0x50000000, target_);
}

THUMB int MaterielMenu_JISAN_CHECK_NAME::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_JISAN_CHECK_NAME::openMessage(int mes1, int mes2, int mes3, int yesno)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(getMessageNo(mes1));
    if (mes2 != 0) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(mes2));
    }
    if (mes3 != 0) {
        gTownMenu_MESSAGE.addMessage(getMessageNo(mes3));
    }
    if (yesno == 1) {
        gTownMenu_MESSAGE.setYesNo();
    }
}
